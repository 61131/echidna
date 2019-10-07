#include <float.h>
#include <math.h>
#include <assert.h>
#include <ev.h>

#include <echidna.h>
#include <log.h>
#include <queue.h>
#include <runtime.h>


void 
runtime_task_callback(struct ev_loop *Loop, ev_timer *Timer, int Events) {
    RUNTIME *pRun;
    RUNTIME_CONTEXT *pContext;
    int nResult;

    pContext = (RUNTIME_CONTEXT *) Timer;
    assert(pContext != NULL);
    pRun = (RUNTIME *) pContext->Parent;
    assert(pRun != NULL);

    switch(pContext->State) {
        case STATE_IDLE:
            break;

        case STATE_RUN:
            if(pContext->Time > 0.0)
                ++pContext->Stats.Overrun;
            /* break; */
        case STATE_ERROR:
        case STATE_STEP:
        case STATE_STOP:
        default:
            return;
    }

    if((runtime_task_interval(pRun, pContext) > 0) &&
            (runtime_task_single(pRun, pContext) > 0)) {        
        ++pContext->Stats.Cycle;
        pContext->Stats.LatencyStart = ev_time();
        if((nResult = queue_push(&pRun->Queue, pContext)) != 0)
            pContext->State = STATE_ERROR;
    }
}


int 
runtime_task_interval(RUNTIME *Run, RUNTIME_CONTEXT *Context) {
    SYMBOL *pSymbol;
    double dTime;
    float fVal;

    /*
        If there is no interval associated with the task or program being initialised, 
        a minimal period is set such that operation - or in the situation where task 
        execution is dependent upon boolean assertion, testing of the state of the 
        designated input - can be scheduled by the run-time. This interval can be
        modified to reduce the processor load of such back-to-back tasks.
    */

    if((pSymbol = Context->Interval) == NULL) 
        goto finish;

    switch(pSymbol->Value.Type) {
        case TYPE_TIME:
            assert(pSymbol->Value.Length == sizeof(float));
            memcpy(&fVal, &Run->Memory[pSymbol->Offset], sizeof(float));
            dTime = (double) fVal;
            break;

        default:
            log_error("Invalid interval variable type: %s (%s)",
                    pSymbol->Name,
                    value_typetostr(pSymbol->Value.Type));
            Context->State = STATE_ERROR;
            return /* EINVAL */ 0;
    }

    dTime /= 1000.0;    //  ms -> s
    if(fabs(dTime - Context->Time) > DBL_EPSILON) {
        Context->Timer.repeat = dTime;
        if(ev_is_active(&Context->Timer))
            ev_timer_again(Context->Loop, &Context->Timer);
    }
    Context->Time = dTime;

finish:
    if(!ev_is_active(&Context->Timer)) {
        dTime = (Context->Time > 0.0) ? Context->Time : 0.0001;     //  0.0001 -> 100 us
        ev_timer_init(&Context->Timer, runtime_task_callback, dTime, dTime );
        ev_set_priority(&Context->Timer, Context->Priority );
        ev_timer_start(Context->Loop, &Context->Timer );
    }
    return 1;
}


void
runtime_task_limit(RUNTIME *Run, RUNTIME_CONTEXT *Context) {
    SYMBOL *pSymbol;
    uint64_t uLimit;

    /*
        This function is intended to stop operation of a task if it has exceeded the 
        limits defined for execution.
    */

    if((pSymbol = Context->Limit) == NULL)
        return;
    switch(pSymbol->Value.Type) {
        case TYPE_LINT:
            uLimit = (uint64_t) ((pSymbol->Value.Value.S64 >= 0ll) ? pSymbol->Value.Value.S64 : 0ll);
            break;

        case TYPE_DINT:
            uLimit = (uint64_t) ((pSymbol->Value.Value.S32 >= 0l) ? pSymbol->Value.Value.S32 : 0l);
            break;

        case TYPE_INT:
            uLimit = (uint64_t) ((pSymbol->Value.Value.S16 >= 0) ? pSymbol->Value.Value.S16 : 0);
            break;

        case TYPE_SINT:
            uLimit = (uint64_t) ((pSymbol->Value.Value.S8 >= 0) ? pSymbol->Value.Value.S8 : 0);
            break;

        case TYPE_ULINT:
            uLimit = (uint64_t) pSymbol->Value.Value.U64;
            break;

        case TYPE_UDINT:
            uLimit = (uint64_t) pSymbol->Value.Value.U32;
            break;

        case TYPE_UINT:
            uLimit = (uint64_t) pSymbol->Value.Value.U16;
            break;

        case TYPE_USINT:
            uLimit = (uint64_t) pSymbol->Value.Value.U8;
            break;

        default:
            return;
    }

    if(Context->Stats.Cycle < uLimit)
        return;

    log_notice("%s: Cycle limit reached, stopping task", Context->Name);
    runtime_task_stop(Run, Context);
}


int
runtime_task_single(RUNTIME *Run, RUNTIME_CONTEXT *Context) {
    SYMBOL *pSymbol;

    /*
        This function is intended to determine whether a task with a dependency on the 
        rising-edge of a boolean input should be executed. 
    */

    if((pSymbol = Context->Single) == NULL)
        return 1;
    if(Context->Edge != 0)
        return 0;

    if(pSymbol->Value.Type != TYPE_BOOL) {
        log_error("Invalid single variable type: %s (%s)",
                pSymbol->Name,
                value_typetostr(pSymbol->Value.Type));
        Context->State = STATE_ERROR;
        return /* EINVAL */ 0;
    }

    Context->Edge = (Run->Memory[pSymbol->Offset] != 0);
    return Context->Edge;
}


void 
runtime_task_stop(RUNTIME *Run, RUNTIME_CONTEXT *Context) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Run->Parent;
    
    //  TODO: Correct application of verbosity test
    if(pContext->Verbose /* > 0 */ >= 0)
        log_debug( "%s: Cycle: %llu, Over: %llu, Last: %.3f ms, Max: %.3f ms",
                Context->Name,
                Context->Stats.Cycle,
                Context->Stats.Overrun,
                Context->Stats.Execution * 1000.0,
                Context->Stats.Maximum * 1000.0 );

    log_info("Stopping task: %s", Context->Name);

    if(ev_is_active(&Context->Timer)) 
        ev_timer_stop(Context->Loop, &Context->Timer);
    Context->State = STATE_STOP;
}


