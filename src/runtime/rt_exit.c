#include <stdint.h>
#ifndef _MSC_VER
#include <strings.h>
#else
#include "deps.h"
#endif
#include <assert.h>

#include <echidna.h>
#include <frame.h>
#include <ll.h>
#include <log.h>
#include <runtime.h>
#include <value.h>

/*
    This file implements support for a set of functions (_exit, _exitc and _exitcn) 
    that can be used to terminate execution of the echidna virtual machine run-time. 
    These functions are primarily used in association with test operations.
*/

int
runtime_exit(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    FRAME *pFrame;
    RUNTIME *pRun;
    RUNTIME_CONTEXT *pContext;
    uint8_t uValue;

    pContext = (RUNTIME_CONTEXT *) User;
    assert(pContext != NULL);
    pRun = (RUNTIME *) pContext->Parent;
    assert(pRun != NULL);

    assert(Name != NULL);
    if((strcasecmp(Name, "_exitc") == 0) ||
            (strcasecmp(Name, "_exitcn") == 0)) {

        pFrame = frame_current(pContext);
        uValue = (strcasecmp(Name, "_exitc") == 0);
        uValue &= 1;
        if((pFrame->CR.Type != TYPE_BOOL) ||
                (pFrame->CR.Value.B1 != uValue))
            return 0;
    }

    log_notice("Exit function called, stopping runtime");
    runtime_stop(pRun);

    return 0;
}
