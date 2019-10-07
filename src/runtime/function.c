#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include <block.h>
#include <echidna.h>
#include <frame.h>
#include <ll.h>
#include <log.h>
#include <runtime.h>
#include <runtime/error.h>
#include <runtime/function.h>
#include <tree.h>
#include <unit.h>
#include <value.h>


int
runtime_function(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    BLOCK sBlock;
    RUNTIME_CONTEXT *pContext;
    UNIT *pPOU;

    assert(Context != NULL);
    block_initialise(&sBlock, Name);
    if((pPOU = tree_search(&Context->POU, &sBlock)) == NULL) 
        return ERROR_INVALID_FUNCTION;

    pContext = (RUNTIME_CONTEXT *) User;
    frame_store(pContext);
    frame_push(pContext, pPOU, 0, Parameters);

    return 0;
}


int 
runtime_function_block(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    BLOCK sBlock;
    FUNCTION_BLOCK_FIELD *pField;
    RUNTIME *pRun;
    RUNTIME_CONTEXT *pContext;
    SYMBOL *pSymbol;
    UNIT *pPOU;
    size_t uIndex;

    assert(Context != NULL);
    block_initialise(&sBlock, Function->Name);
    if((pPOU = tree_search(&Context->POU, &sBlock)) == NULL)
        return ERROR_INVALID_FUNCTION;

    pContext = (RUNTIME_CONTEXT *) User;
    frame_store(pContext);
    frame_push(pContext, pPOU);

    pRun = (RUNTIME *) pContext->Parent;
    assert(pRun != NULL);

    for(uIndex = 0; uIndex < Function->Count; ++uIndex) {
        pField = &Function->Fields[uIndex];
        if((pSymbol = symbol_search(Context, pPOU->Config,
                pPOU->Resource,
                pPOU->POU,
                (char *) pField->Name)) == NULL)
            continue;
        memcpy(&pRun->Memory[pSymbol->Offset], &Instance[pField->Offset], pSymbol->Value.Length);
    }

    return 0;
}


void
runtime_function_destroy(void *Arg) {
    RUNTIME_FUNCTION *pFunction;

    if((pFunction = (RUNTIME_FUNCTION *) Arg) == NULL)
        return;
    ll_destroy(&pFunction->List, NULL);
    ll_destroy(&pFunction->Parameters, runtime_parameter_destroy);
    free(pFunction);
}


RUNTIME_FUNCTION *
runtime_function_new(VALUE_TYPE Type, UNIT *POU, uint32_t PC) {
    RUNTIME_FUNCTION *pFunction;

    assert(POU != NULL);
    errno = 0;
    if((pFunction = calloc(1, sizeof(RUNTIME_FUNCTION))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pFunction->POU = POU;
    pFunction->PC = PC;
    pFunction->Type = Type;
    pFunction->End = 0;
    pFunction->Id = -1;
    ll_initialise(&pFunction->Parameters);
    ll_initialise(&pFunction->List);

    return pFunction;
}

