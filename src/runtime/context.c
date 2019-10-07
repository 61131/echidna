#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <echidna.h>
#include <frame.h>
#include <ll.h>
#include <log.h>
#include <runtime.h>
#include <runtime/context.h>
#include <runtime/function.h>
#include <stats.h>


void 
runtime_context_destroy(void *Arg) {
    RUNTIME_CONTEXT *pContext;
    size_t uIndex;

    if((pContext = (RUNTIME_CONTEXT *) Arg) == NULL)
        return;

    if(pContext->Functions.Function != NULL) {
        assert(pContext->Functions.Count > 0);
        for(uIndex = 0; uIndex < pContext->Functions.Count; ++uIndex)
            runtime_function_destroy(pContext->Functions.Function[uIndex]);
        free(pContext->Functions.Function);
        pContext->Functions.Count = 0;
    }
    pContext->Stack.Depth = 0;

    ll_destroy(&pContext->POU, NULL);
    if(pContext->Alloc)
        free(pContext);
}


void 
runtime_context_initialise(RUNTIME_CONTEXT *Context, RUNTIME *Run) {
    Context->Parent = Run;
    Context->Loop = Run->Loop;
    Context->Name = NULL;
    Context->State = STATE_STOP;
    Context->Priority = -1;
    Context->Interval = Context->Limit = Context->Single = NULL;
    Context->Time = 0.0;
    Context->Edge = 0;
    ll_initialise(&Context->POU);
    stats_initialise(&Context->Stats);
    
    Context->Functions.Function = NULL;
    Context->Functions.Count = 0;
    Context->Stack.Depth = 0;
    frame_push(Context);

    Context->Alloc = 0;
}


RUNTIME_CONTEXT *
runtime_context_new(RUNTIME *Run) {
    RUNTIME_CONTEXT *pContext;

    assert(Run != NULL);
    if((pContext = calloc(1, sizeof(RUNTIME_CONTEXT))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    runtime_context_initialise(pContext, Run);
    pContext->Alloc = 1;
    return pContext;
}
