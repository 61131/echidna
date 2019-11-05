#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>

#include <bytecode.h>
#include <echidna.h>
#include <frame.h>
#include <function.h>
#include <ll.h>
#include <log.h>
#include <operator.h>
#include <runtime.h>
#include <symbol.h>
#include <value.h>

#include <json.h>

static void _operator_call_debug(RUNTIME_CONTEXT *Context, RUNTIME_FUNCTION *Instance, int Error);

static int _operator_call_function(RUNTIME_CONTEXT *Context, RUNTIME_FUNCTION *Instance, VALUE *Result);

static int _operator_call_function_block(RUNTIME_CONTEXT *Context, RUNTIME_FUNCTION *Instance);

static SYMBOL * _operator_call_read_symbol(SYMBOLS *Symbols, char *Instance, size_t Index);


static void 
_operator_call_debug(RUNTIME_CONTEXT *Context, RUNTIME_FUNCTION *Instance, int Error) {
    ECHIDNA *pContext;
    RUNTIME *pRun;
    FUNCTION_REGISTER *pFunction;
    FUNCTIONS *pFunctions;
    SYMBOL *pSymbol;
    SYMBOLS *pSymbols;
    const char *pError;
    char *pType, sError[8];

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);
    pFunctions = &pContext->Functions;
    pSymbols = &pContext->Symbols;

    pType = NULL;

    switch(Instance->Type) {
        case TYPE_FUNCTION:
            pFunction = pFunctions->Function[Instance->Id];
            pType = "function";
            break;

        case TYPE_FUNCTION_BLOCK:
            pSymbol = pSymbols->Symbol[Instance->Id];
            assert(pSymbol != NULL);
            pFunction = pSymbol->Function;
            pType = "function block";
            break;

        default:
            return;
    }

    assert(pFunction != NULL);
    assert(pType != NULL);

    if((pError = runtime_errortostr(Error)) == NULL) {
        snprintf(sError, sizeof(sError), "%d", Error);
        pError = sError;
    }

    log_error("Error returned from %s: %s (%s)", pType, pFunction->Name, pError);
}


static int
_operator_call_function(RUNTIME_CONTEXT *Context, RUNTIME_FUNCTION *Instance, VALUE *Result) {
    ECHIDNA *pContext;
    FUNCTION_REGISTER *pFunction;
    FUNCTIONS *pFunctions;
    RUNTIME *pRun;
    void *pUser;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);
    pFunctions = &pContext->Functions;

    assert(Instance->Type == TYPE_FUNCTION);
    if(Instance->Id >= pFunctions->Count)
        return ERROR_INVALID_FUNCTION;

    pFunction = pFunctions->Function[Instance->Id];
    pUser = (pFunction->Function == runtime_function) ? Context : pFunction->Context;
    return pFunction->Function(pContext, pFunction->Name, &Instance->List, Result, pUser);
}


int 
_operator_call_function_block(RUNTIME_CONTEXT *Context, RUNTIME_FUNCTION *Instance) {
    ECHIDNA *pContext;
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    FUNCTION_REGISTER *pFunction;
    PARAMETER *pParameter;
    RUNTIME *pRun;
    SYMBOL *pSymbol;
    SYMBOLS *pSymbols;
    char *pInstance;
    size_t uIndex, uOrder;
    void *pUser;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);
    pSymbols = &pContext->Symbols;

    assert(Instance->Type == TYPE_FUNCTION_BLOCK);
    if(Instance->Id >= pSymbols->Count)
        return ERROR_INVALID_SYMBOL;

    pSymbol = pSymbols->Symbol[Instance->Id];
    assert(pSymbol != NULL);
    assert(pSymbol->Value.Type == TYPE_FUNCTION_BLOCK);
    pFunction = pSymbol->Function;
    assert(pFunction != NULL);
    pBlock = pFunction->Block;
    assert(pBlock != NULL);
    assert(pBlock->Execute != NULL);

    /*
        The following iterates through the parameters passed to this function block 
        call and update the corresponding fields for input members of the function 
        block instance.
    */

#if 0
    BLOCK sBlock;
    block_initialise(&sBlock);
    block_pointer(&sBlock, pRun->Memory);
    sBlock.End = symbol_table_size(pContext);
    block_dump(&sBlock);

#endif
    pInstance = &pRun->Memory[pSymbol->Offset];
//log_debug("%s: %s [%u]", __func__, pBlock->Name, pSymbol->Offset);

    uOrder = 0;
    ll_reset(&Instance->List);
    while((pParameter = ll_iterate(&Instance->List)) != NULL) {
        if(pParameter->Name) {
            if((strcasecmp(pParameter->Name, "EN") == 0) ||
                    (strcasecmp(pParameter->Name, "ENO") == 0))
                continue;

            for(uIndex = 0; uIndex < pBlock->Count; ++uIndex) {
                pField = &pBlock->Fields[uIndex];
                if(strcasecmp(pParameter->Name, pField->Name) == 0)
                    break;
            }
            if(uIndex >= pBlock->Count)
                return ERROR_PARAMETER_UNKNOWN;
        }
        else 
            uIndex = uOrder++;

        if(uIndex >= pBlock->Count)
            return ERROR_PARAMETER_COUNT;

        pField = &pBlock->Fields[uIndex];
        assert(pField != NULL);
        if((pField->Type & pParameter->Value.Type) != pParameter->Value.Type)
            return ERROR_PARAMETER_TYPE;
        /* if((pField->Type & TYPE_INPUT) == 0)
            continue; */

        pSymbol = _operator_call_read_symbol(pSymbols, pInstance, uIndex);
        pSymbol->Value.Type = pParameter->Value.Type;
//log_debug("%s: pParameter->Name %s, %08x, pParameter->Value.Length %u, pSymbol->Id %u", __func__, pParameter->Name, pSymbol->Value.Type, pParameter->Value.Length, pSymbol->Id);
        memcpy(&pInstance[pField->Offset], &pParameter->Value.Value.Pointer, pParameter->Value.Length);
    }

    pSymbol = pSymbols->Symbol[Instance->Id];
    pContext->Time = (Context->Stats.ExecutionStart - Context->Stats.Start);
    pUser = (pBlock->Execute == runtime_function_block) ? Context : pSymbol->Context;
    return pBlock->Execute(pContext, pBlock, pInstance, pUser);
}


static SYMBOL * 
_operator_call_read_symbol(SYMBOLS *Symbols, char *Instance, size_t Index) {
    size_t uOffset;
    int nId;

    uOffset = sizeof(int32_t) * Index;
    memcpy(&nId, &Instance[uOffset], sizeof(int32_t));
//log_debug("%s: nId %d", __func__, nId);
    assert((unsigned) nId < Symbols->Count);
    return Symbols->Symbol[nId];
}


int 
operator_call(RUNTIME_CONTEXT *Context) {
    ECHIDNA *pContext;
    FRAME *pFrame;
    LL_ITER sIter;
    RUNTIME *pRun;
    RUNTIME_FUNCTION *pInstance;
    RUNTIME_PARAMETER *pParameter;
    SYMBOL *pSymbol;
    VALUE sResult;
    uint32_t uDepth, uResult, uValue;
    int nResult;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);

    /*
        The runtime_call_instance function returns a data structure containing contextual 
        information associated with the current instance of the call operator.
    */

    if((pInstance = runtime_call_instance(Context)) == NULL)
        return EFAULT;

    uResult = 0;
    pFrame = frame_current(Context);
    switch(uValue = (pFrame->BC & BYTECODE_MASK)) {
        case BYTECODE_CALC:
        case BYTECODE_CALCN:
            uValue = (uValue == BYTECODE_CALC);
            if((pFrame->CR.Type != TYPE_BOOL) ||
                    (pFrame->CR.Value.B1 != uValue)) 
                goto finish;
            break;

        case BYTECODE_CAL:
            break;

        case BYTECODE_CD:
        case BYTECODE_CLK:
        case BYTECODE_CU:
        case BYTECODE_IN:
        case BYTECODE_PT:
        case BYTECODE_PV:
        case BYTECODE_R:
        case BYTECODE_R1:
        case BYTECODE_S:
        case BYTECODE_S1:
            break;

        default:
            assert(0);
    }

    /*
        The following action will copy the current value of each of the input parameters 
        of the program organisation unit to a separate list of parameters that are 
        passed to this POU. This operation also includes a test to determine whether 
        execution of the new program organisation unit should be skipped based on the 
        state of the EN input, if this is defined.

        TODO: Remove EN parameter from list of parameters passed to POU
    */

    for(pParameter = ll_iterate_first(&sIter, &pInstance->Parameters);
            pParameter;
            pParameter = ll_iterate_next(&sIter)) {
        switch(pParameter->Type & ~TYPE_IN_OUT) {
            case TYPE_VARIABLE:
                pSymbol = pContext->Symbols.Symbol[pParameter->Id];
                value_copy(&pParameter->Value, &pSymbol->Value);
                memcpy((char *) &pParameter->Value.Value.Pointer, &pRun->Memory[pSymbol->Offset], pSymbol->Value.Length);
                /* break; */
            default:
                value_copy(&pParameter->Parameter.Value, &pParameter->Value);
                break;
        }

        if((pParameter->Parameter.Name) &&
                (strcasecmp(pParameter->Parameter.Name, "EN") == 0)) {
            value_cast(&pParameter->Parameter.Value, TYPE_BOOL);
            if(pParameter->Parameter.Value.Value.B1 == 0)
                goto finish;
        }
    }

    nResult = 0;
    uDepth = Context->Stack.Depth;
    switch(pInstance->Type) {
        case TYPE_FUNCTION:
            value_initialise(&sResult);
            nResult = _operator_call_function(Context, pInstance, &sResult);
            if(sResult.Type != TYPE_NONE) {
                assert(Context->Stack.Depth == uDepth); //  Essential!
                value_copy(&pFrame->CR, &sResult);
            }
            break;

        case TYPE_FUNCTION_BLOCK:
            nResult = _operator_call_function_block(Context, pInstance);
            break;

        default:
            assert(0);
    }

    /*
        The stack depth will be increased if the CAL operator was to an IEC 61131-3 
        language program organisation unit which will now been queued for execution.
    */

    if(Context->Stack.Depth > uDepth) {
        pFrame = frame_previous(Context);
        pFrame->Function = pInstance;
        pFrame->PC = pInstance->End;
        return 0;
    }

    if(pFrame->ER != 0)
        return -1;
    if((pFrame->ER = nResult) != 0) {
        _operator_call_debug(Context, pInstance, pFrame->ER);
        return -1;
    }

    uResult = 1;

finish:
    for(pParameter = ll_iterate_first(&sIter, &pInstance->Parameters);
            pParameter;
            pParameter = ll_iterate_next(&sIter)) {

        if(((pParameter->Type & TYPE_VARIABLE) == 0) ||
                ((pParameter->Type & TYPE_OUTPUT) == 0))
            continue;
        if((pParameter->Parameter.Name != NULL) &&
                (strcasecmp(pParameter->Parameter.Name, "ENO") == 0)) {
            if(pParameter->Parameter.Value.Type != TYPE_BOOL) 
                continue;
            value_assign(&pParameter->Parameter.Value, TYPE_BOOL, uResult);
        }

        pSymbol = pContext->Symbols.Symbol[pParameter->Id];
        memcpy(&pRun->Memory[pSymbol->Offset], (char *) &pParameter->Parameter.Value.Value.Pointer, pParameter->Parameter.Value.Length);
    }

    pFrame->PC = pInstance->End;
    return 0;
}


