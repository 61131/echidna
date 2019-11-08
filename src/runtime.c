#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <assert.h>

#include <bytecode.h>
#include <callback.h>
#include <echidna.h>
#include <frame.h>
#include <json.h>
#include <ll.h>
#include <log.h>
#include <operator.h>
#include <queue.h>
#include <runtime.h>
#include <runtime/error.h>
#include <symbol.h>
#include <unit.h>
#include <value.h>


static int _runtime_queue(const void *A, const void *B);

static void _runtime_signal(struct ev_loop *Loop, ev_signal *Signal, int Events);

static int _runtime_start(RUNTIME *Run, CONFIG *Config);


static int
_runtime_queue(const void *A, const void *B) {
    RUNTIME_CONTEXT *pContextA, *pContextB;

    pContextA = *(RUNTIME_CONTEXT **) A;
    assert(pContextA != NULL);
    pContextB = *(RUNTIME_CONTEXT **) B;
    assert(pContextB != NULL);

    if(pContextA->Priority == pContextB->Priority)
        return 0;
    if(pContextA->Priority < 0)
        return 1;
    if(pContextB->Priority < 0)
        return 0;
    return (pContextA->Priority > pContextB->Priority);
}


static void 
_runtime_signal(struct ev_loop *Loop, ev_signal *Signal, int Events) {
    RUNTIME *pRun;
    char *pSig;

    pRun = container_of(Signal, RUNTIME, Signal);
    assert(pRun != NULL);
    assert(pRun->Loop == Loop);

    switch(Signal->signum) {
        case SIGINT:            
            pSig = "SIGINT";
            if(0) {
        case SIGTERM:
                pSig = "SIGTERM";
            }
            log_notice("Received %s signal, shutting down", pSig);
            break;

        default:
            return;
    }

    runtime_stop(pRun);
}


static int 
_runtime_start( RUNTIME *pRun, CONFIG *pConfig ) {
    RUNTIME_CONTEXT *pContext;
    CONFIG *pProgram;
    LL_ITER sIter;
    int nResult;

    switch( pConfig->Type ) {
        case TYPE_PROGRAM:
        case TYPE_TASK:
            break;
        default:
            return -EINVAL;
    }

    if( ( pContext = runtime_context_new( pRun ) ) == NULL )
        return -errno;
    pContext->Name = pConfig->Name;

    switch( pConfig->Type ) {
        case TYPE_TASK:
            pContext->Priority = pConfig->Priority;
            pContext->Interval = pConfig->Interval;
            pContext->Single = pConfig->Single;
            pContext->Limit = pConfig->Limit;

            for( pProgram = ( CONFIG * ) ll_iterate_first( &sIter, &pConfig->List );
                    pProgram;
                    pProgram = ( CONFIG * ) ll_iterate_next( &sIter ) ) {
                if( ( nResult = ll_copy( &pContext->POU, &pProgram->List ) ) != 0 ) {
                    runtime_context_destroy( pContext );
                    return nResult;
                }
            }
            break;

        case TYPE_PROGRAM:
            if( ( nResult = ll_copy( &pContext->POU, &pConfig->List ) ) != 0 ) {
                runtime_context_destroy( pContext );
                return nResult;
            }
            break;

        default:
            break;
    }
    
    runtime_task_interval( pRun, pContext );
    runtime_task_single( pRun, pContext );

    pContext->State = STATE_IDLE;
    if( ( nResult = ll_insert( &pRun->Context, pContext ) ) != 0 ) {
        runtime_context_destroy( pContext );
        return nResult;
    }
    queue_size( &pRun->Queue, pRun->Context.Size );

    return 0;
}



void 
_runtime_destroy(size_t Arg, ...) {
    RUNTIME *pRun;
    va_list sArg;

    va_start(sArg, Arg);
    for(; Arg > 0; --Arg) {
        if((pRun = va_arg(sArg, RUNTIME *)) == NULL)
            continue;

        ll_destroy(&pRun->Context, runtime_context_destroy);
        queue_destroy(&pRun->Queue, NULL);
//        ev_ref(pRun->Loop);
//        ev_signal_stop(pRun->Loop, &pRun->Signal);
        ev_loop_destroy(pRun->Loop);

        free(pRun->Memory);
        if(pRun->Alloc)
            free(pRun);
    }
    va_end(sArg);
}


int
runtime_execute( RUNTIME *pRun ) {
    ECHIDNA *pEch;
    RUNTIME_CONTEXT *pContext, *pNext;
    BLOCK *pPOU;
    BLOCK sSymbol;
    LL_ITER sIter;
    double dTime;

    assert( pRun != NULL );
    pEch = pRun->Parent;
    assert( pEch != NULL );

    /*
        The following abuses the BLOCK data structure to permit the dumping of the 
        symbol table associated with the virtual machine run-time during trace 
        operations. This is performed by pointing the block to the run-time symbol 
        table block and manually setting the size of the block to match that of the 
        symbol table.
    */

    block_initialise(&sSymbol);
    block_pointer(&sSymbol, pRun->Memory);
    sSymbol.End = symbol_table_size(pEch);
    if(pEch->Verbose > 0) {
        log_debug("Initial symbol table");
        block_dump(&sSymbol);
    }

    for(pContext = NULL; pRun->Exit == 0;) {
        if(!ev_run(pRun->Loop, EVRUN_NOWAIT))
            break;
        if(pContext == NULL) {
            if((pContext = queue_pop(&pRun->Queue)) == NULL) {

                /*
                    The following checks for any non-interval tasks which are dependent upon the 
                    rising-edge of a boolean input for execution. This is performed by iterating
                    through all runtime context data structures and testing for the rising-edge 
                    input for those context entries which have no interval symbol definition and
                    a single symbol definition.
                */

                for(pContext = (RUNTIME_CONTEXT *) ll_iterate_first(&sIter, &pRun->Context);
                    pContext;
                    pContext = (RUNTIME_CONTEXT *) ll_iterate_next(&sIter)) {

                    switch(pContext->State) {
                        case STATE_ERROR:
                        case STATE_STEP:
                        case STATE_STOP:
                            continue;
                        default:
                            break;
                    }

                    if((pContext->Interval != NULL) ||
                            (pContext->Single == NULL))  //  Always true for TYPE_PROGRAM
                        continue;
                    if(runtime_task_single(pRun, pContext) != 0) {
                        if(queue_push(&pRun->Queue, pContext) != 0)
                            pContext->State = STATE_ERROR;  //  TODO: Error handling?!
                    }
                }

                /*
                    The following sleep (500 us) has been included to minimise idle cycles of the 
                    event loop and enforces a minimum resolution for run-time operations. This 
                    may be omitted to lower jitter in operations, at the cost of processor load 
                    during execution.
                */

                ev_sleep(0.0005);
                continue;
            }
        }

        if( pContext->Stats.LatencyEnd == 0.0 ) {
            pContext->Stats.LatencyEnd = ev_time();
            pContext->Stats.Latency = ( pContext->Stats.LatencyEnd - pContext->Stats.LatencyStart );
        }
        switch( pContext->State ) {
            case STATE_IDLE:
                /* assert( pContext->State.Depth == 1 ); */
                if((pPOU = ll_iterate_first(&pContext->Next, &pContext->POU)) == NULL) {
                    pContext->State = STATE_ERROR;
                    continue;
                }

                callback_execute(pEch, CALLBACK_CYCLE_START, pContext);
                frame_initialise(&pContext->Stack.Frame[0], pPOU);
                pContext->State = STATE_RUN;
                pContext->Stats.ExecutionStart = ev_time();
                /* break; */
            case STATE_RUN:
                for( ;; ) {
                    if( runtime_bytecode_execute( pContext ) != 0 ) {
                        pContext->State = STATE_ERROR;
                        break;
                    }
                    if( pContext->Stack.Frame[0].POU == NULL ) {
                        //  Execution finished, return to STATE_IDLE
                        pContext->State = STATE_IDLE;

                        dTime = ev_time();
                        pContext->Stats.Execution = ( dTime - pContext->Stats.ExecutionStart );
                        pContext->Stats.LatencyEnd = 0.0;
                        if( pContext->Stats.Execution > pContext->Stats.Maximum )
                            pContext->Stats.Maximum = pContext->Stats.Execution;
                        runtime_task_interval(pRun, pContext);

                        callback_execute(pEch, CALLBACK_CYCLE_FINISH, pContext);

                        if(pEch->Verbose > 0) {
                            block_dump(&sSymbol);
                            log_debug("Cycle: %llu, Over: %llu, Lat: %.3f ms, Exec: %.3f ms, Time: %.3f",
                                    pContext->Stats.Cycle,
                                    pContext->Stats.Overrun,
                                    pContext->Stats.Latency * 1000.0,
                                    pContext->Stats.Execution * 1000.0,
                                    (dTime - pContext->Stats.Start) * 1000.0);
                        }
                        runtime_task_limit(pRun, pContext);

                        pContext = NULL;
                        break;
                    }

                    /*
                        The following is required for the round-robin execution of queued byte code 
                        with equal (or greater) task or contextual priority. This is technically wrong 
                        as no task should interrupt another of equal priority but has been included
                        to provide a more equitable execution model.
                    */

                    if((pRun->Exit != 0) ||
                            (!ev_run(pRun->Loop, EVRUN_NOWAIT))) {
                        ++pRun->Exit;
                        break;
                    }
                    if((pNext = queue_peek(&pRun->Queue)) != NULL) {
                        if((pNext->Priority >= 0) &&
                                (pNext->Priority /* < */ <= pContext->Priority)) {
                            if(queue_push(&pRun->Queue, pContext) != 0)
                                pContext->State = STATE_ERROR;
                            pContext = NULL;
                            break;
                        }
                    }
                }
                break;

            case STATE_STEP:
            case STATE_STOP:
            default:
                continue;
        }
    }
    return 0;
}


int
runtime_initialise(RUNTIME *Run) {
    ECHIDNA *pContext;
    int nSignal;

    assert(Run != NULL);
    pContext = (ECHIDNA *) Run->Parent;
    assert(pContext != NULL);

    if((Run->Loop = ev_loop_new(EVFLAG_NOENV)) == NULL)
        return -EFAULT;
    nSignal = (pContext->Option & OPTION_DAEMON) ? SIGTERM : SIGINT;
    if((pContext->Option & OPTION_NOSIGNAL) == 0) {
        ev_signal_init(&Run->Signal, _runtime_signal, nSignal);
        ev_signal_start(Run->Loop, &Run->Signal);
        ev_unref(Run->Loop);
    }
    ev_set_io_collect_interval(Run->Loop, 0.1);

    ll_initialise(&Run->Context);
    queue_initialise(&Run->Queue, _runtime_queue);
    Run->Memory = NULL;
    Run->Alloc = Run->Exit = 0;

    return 0;
}


RUNTIME * 
runtime_new(struct _ECHIDNA *Context) {
    RUNTIME *pRun;
    int nResult;

    if((pRun = (RUNTIME *) calloc(1, sizeof(RUNTIME))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }

    pRun->Parent = Context;
    if((nResult = runtime_initialise(pRun)) != 0) {
        runtime_destroy(pRun);
        errno = nResult;
        return NULL;
    }
    pRun->Alloc = 1;
    return pRun;
}


int 
runtime_read(RUNTIME_CONTEXT *Context, size_t Count, char *Buffer) {
    BLOCK *pBlock;
    ECHIDNA *pContext;
    FRAME *pFrame;
    RUNTIME *pRun;
    UNIT *pPOU;
    size_t uByte;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;

    pFrame = frame_current(Context);
    pPOU = pFrame->POU;
    assert(pPOU != NULL);
    pBlock = &pPOU->Block;

    if((pFrame->PC + Count) > pBlock->End) {
        log_critical( "Invalid read operation [%s:%u]", __FILE__, __LINE__ );

        pFrame->ER = ERROR_INTERNAL_READ;
        Context->State = STATE_ERROR;
        return EINVAL;
    }
    memcpy(Buffer, &pBlock->Data[pFrame->PC], Count);

    pFrame->PC += Count;
    if((uByte = (Count % pContext->Align)) != 0)
        pFrame->PC += (pContext->Align - uByte);

    return 0;
}


/*
    This function is intended to iterate through all configuration elements within 
    a configuration tree and starts each element in turn.
*/

int
runtime_start( RUNTIME *pRun, CONFIG *pConfig ) {
    ECHIDNA *pContext;
    LL *pStack[3];
    int nResult, nStack;

    if( pConfig->Context ) {
        /* assert( pConfig->Context != NULL ); */
        /* assert( ( pConfig->Type == TYPE_TASK ) || ( pConfig->Type == TYPE_PROGRAM ) ); */
        switch( pConfig->Context->State ) {
            case STATE_IDLE:
            case STATE_RUN:
            case STATE_STEP:
            case STATE_ERROR:
                break;
            case STATE_STOP:
            default:
                return 0;
        }
    }

    log_info("Starting %s: %s", config_typetostr(pConfig->Type), pConfig->Name);

    switch( pConfig->Type ) {
        case TYPE_TASK:
        case TYPE_PROGRAM:
            return _runtime_start( pRun, pConfig );

        case TYPE_CONFIG:
            pContext = (ECHIDNA *) pConfig->Parent;
            symbol_table_initialise(pContext, pConfig->Name);
            break;

        case TYPE_RESOURCE:
        default:
            break;
    }

    pStack[0] = &pConfig->List;
    ll_reset( pStack[0] );
    for( nStack = 0; nStack >= 0; --nStack ) {
        while( ( pConfig = ll_iterate( pStack[ nStack ] ) ) != NULL ) {
            switch( pConfig->Type ) {
                case TYPE_RESOURCE:
                    /* log_info("Starting resource: %s", pConfig->Name); */
                    pStack[ ++nStack ] = &pConfig->List;
                    ll_reset( pStack[ nStack ] );
                    continue;

                case TYPE_PROGRAM:
                    if( pConfig->Task != NULL )
                        continue;
                    if(0) {
                    /* break; */
                case TYPE_TASK:
                        if( pConfig->List.Size == 0 )
                            continue;
                    }
                    log_info( "Starting %s: %s", config_typetostr( pConfig->Type ), pConfig->Name );
                    if( ( nResult = _runtime_start( pRun, pConfig ) ) != 0 )
                        return nResult;
                    break;

                default:
                    continue;
            }
        }
    }

    return 0;
}


void 
runtime_stop( RUNTIME *pRun ) {
    LL_ITER sIter;
    RUNTIME_CONTEXT *pContext;

    assert( pRun != NULL );

    for( pContext = ll_iterate_last( &sIter, &pRun->Context );
            pContext;
            pContext = ll_iterate_previous( &sIter ) ) 
        runtime_task_stop( pRun, pContext );

    ev_break(pRun->Loop, EVBREAK_ALL);
    ++pRun->Exit;
}

