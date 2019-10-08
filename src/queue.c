#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include <log.h>
#include <queue.h>


static int _queue_compare(const void *A, const void *B);


static int
_queue_compare(const void *A, const void *B) {
    return 0;
}


void
_queue_destroy(size_t Arg, QUEUE *Queue, ...) {
    _QUEUE_DESTROY pDestroy;
    va_list sArg;
    void *pData;

    if(Arg > 1) {
        va_start(sArg, Queue);
        pDestroy = va_arg(sArg, _QUEUE_DESTROY);
        va_end(sArg);
    }
    else
        pDestroy = Queue->Destroy;

    while(Queue->Count > 0) {
        if((pData = queue_pop(Queue)) != NULL) {
            if(pDestroy)
                pDestroy(pData);
        }
    }

    free(Queue->Queue);

    if(Queue->Alloc)
        free(Queue);
}


void
_queue_initialise(size_t Arg, QUEUE *Queue, ...) {
    _QUEUE_COMPARE pCompare;
    _QUEUE_DESTROY pDestroy;
    va_list sArg;

    Queue->Queue = NULL;
    Queue->Count = Queue->Size = 0;
    Queue->Compare = _queue_compare;
    Queue->Destroy = NULL;
    Queue->Alloc = 0;

    if(Arg > 1) {
        va_start(sArg, Queue);
        if((pCompare = va_arg(sArg, _QUEUE_COMPARE)) != NULL)
            Queue->Compare = pCompare;
        if(Arg > 2) {
            if((pDestroy = va_arg(sArg, _QUEUE_DESTROY)) != NULL)
                Queue->Destroy = pDestroy;
        }
        va_end(sArg);
    }
}


int
_queue_push(size_t Arg, QUEUE *Queue, ...) {
    va_list sArg;
    void *pArg;
    size_t uCount;
    int nResult;

    errno = 0;
    if(Queue->Count == Queue->Size) {
        errno = ENOMEM;
        return -1;
    }

    uCount = Queue->Count;
    va_start(sArg, Queue);
    for(nResult = 0; Arg > 1; --Arg) {
        if((pArg = va_arg(sArg, void *)) == NULL)
            continue;
        Queue->Queue[Queue->Count] = pArg;
        if(++Queue->Count == Queue->Size)
            break;
    }
    va_end(sArg);

    if(Queue->Count != uCount) {
        if(Queue->Compare)
            qsort(Queue->Queue, Queue->Count, sizeof(void *), Queue->Compare);
    }
    return nResult;
}


size_t
_queue_size(size_t Arg, QUEUE *Queue, ... ) {
    va_list sArg;
    size_t uSize;

    if(Arg == 1)
        return Queue->Size;

    for(;;) {
        va_start( sArg, Queue );
        if((uSize = va_arg(sArg, size_t)) > Queue->Size) {
            errno = 0;
            if((Queue->Queue = realloc(Queue->Queue, uSize * sizeof(void *))) == NULL) {
                log_critical("Failed to allocate memory: %s", strerror(errno));
                break;
            }
        }
        Queue->Size = uSize;
        break;
    }
    va_end(sArg);

    return Queue->Size;
}


QUEUE *
queue_new(void) {
    QUEUE *pQueue;

    errno = 0;
    if((pQueue = calloc(1, sizeof(QUEUE))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    queue_initialise(pQueue);
    pQueue->Alloc = 1;
    return pQueue;
}


void *
queue_peek(QUEUE *Queue) {
    return (Queue->Count > 0) ? Queue->Queue[0] : NULL;
}


void *
queue_pop(QUEUE *Queue) {
    void *pData;

    if( Queue->Count == 0 )
        return NULL;
    pData = Queue->Queue[0];
    memmove(Queue->Queue, &Queue->Queue[1], (--Queue->Count) * sizeof(void *));
    return pData;
}


