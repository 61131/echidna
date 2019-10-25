#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>

#include <callback.h>
#include <echidna.h>
#include <ll.h>
#include <log.h>


int 
_callback_register(size_t Arg, ECHIDNA *Context, CALLBACK_TYPE Type, ...) {
    CALLBACK *pCallback;
    va_list sArg;
    int nResult;

    errno = 0;
    if((pCallback = calloc(1, sizeof(CALLBACK))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return -1;
    }
    pCallback->Type = Type;

    switch(Type) {
        case CALLBACK_CYCLE_START:
        case CALLBACK_CYCLE_FINISH:
        case CALLBACK_TASK_START:
        case CALLBACK_TASK_STOP:
            if(Arg < 4)
                goto error;
            va_start(sArg, Type);
            pCallback->Name = va_arg(sArg, char *);
            pCallback->Function = va_arg(sArg, CALLBACK_CALLBACK);
            pCallback->User = (Arg > 4) ? va_arg(sArg, void *) : NULL;
            va_end(sArg);
            break;

        default:
            goto error;
    }

    if((nResult = ll_insert(&Context->Callbacks, pCallback)) != 0) {
        callback_destroy(pCallback);
        return nResult;
    }

    return 0;

error:
    callback_destroy(pCallback);
    errno = EINVAL;
    return -1;
}


void
callback_destroy(void *Arg) {
    CALLBACK *pCallback;

    if((pCallback = (CALLBACK *) Arg) == NULL)
        return;
    free(pCallback);
}


int
callback_execute(ECHIDNA *Context, CALLBACK_TYPE Type, void *Arg) {
    CALLBACK *pCallback;
    RUNTIME_CONTEXT *pContext;
    
    assert(Context != NULL);
    ll_reset(&Context->Callbacks);
    while((pCallback = ll_iterate(&Context->Callbacks)) != NULL) {
        if(pCallback->Type != Type)
            continue;
        switch(pCallback->Type) {
            case CALLBACK_CYCLE_FINISH:
                pContext = (RUNTIME_CONTEXT *) Arg;
                assert(pContext != NULL);
                if((pCallback->Name != NULL) &&
                        (strcasecmp(pCallback->Name, pContext->Name) == 0))
                    continue;
                pCallback->Function(Context, &pContext->Stats, pCallback->User);
                break;

            case CALLBACK_CYCLE_START:
            case CALLBACK_TASK_START:
            case CALLBACK_TASK_STOP:
            default:
                break;
        }
    }
    return 0;
}

