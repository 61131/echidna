#include <stdint.h>
#include <stdarg.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>

#include <bytecode.h>
#include <frame.h>
#include <function.h>
#include <ll.h>
#include <log.h>
#include <operator.h>
#include <parameter.h>
#include <runtime.h>
#include <runtime/error.h>
#include <value.h>


enum {

    FRAME_STORE = 0,
    FRAME_RESTORE,
};


static int _frame_function(RUNTIME_CONTEXT *Context);

static int _frame_function_block(RUNTIME_CONTEXT *Context);

static void _frame_stash(RUNTIME_CONTEXT *Context, int Action);


static int
_frame_function(RUNTIME_CONTEXT *Context) {
    BLOCK *pBlock;
    ECHIDNA *pContext;
    FRAME *pCurrent, *pPrevious;
    LL_ITER sIter;
    RUNTIME *pRun;
    RUNTIME_FUNCTION *pFunction;
    RUNTIME_PARAMETER *pParameter;
    SYMBOL *pLocal, *pSymbol;
    UNIT *pPOU;
    VALUE *pValue;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;

    pCurrent = frame_current(Context);
    pPrevious = frame_previous(Context);

    /*
        The first loop below iterates through the parameters returned as outputs from 
        the current program organisation unit. The values of all symbols in the previous 
        program organisation unit are then restored and then these output values are 
        written to their appropriate return locations. This is specifically so as to 
        properly handle the recursive execution of functions.
    */

    pPOU = pCurrent->POU;
    assert(pPOU != NULL);
    pBlock = (BLOCK *) &pPOU->Block;
    assert(pBlock->Name != NULL);
    pFunction = pPrevious->Function;
    assert(pFunction != NULL);

    for(pParameter = ll_iterate_first(&sIter, &pFunction->Parameters);
            pParameter;
            pParameter = ll_iterate_next(&sIter)) {
        if(((pParameter->Type & TYPE_OUTPUT) == 0) ||
                (pParameter->Parameter.Name == NULL) ||
                ((pParameter->Type & TYPE_VARIABLE) == 0))
            continue;

        pSymbol = pContext->Symbols.Symbol[pParameter->Id];
        pValue = &pParameter->Parameter.Value;
        if(strcasecmp(pParameter->Parameter.Name, "ENO") == 0) {
            value_cast(pValue, TYPE_BOOL, 1);
        }
        else {
            if((pLocal = symbol_search(pContext, NULL, NULL, pBlock->Name, (char *) pParameter->Parameter.Name)) == NULL)
                continue;
            value_copy(pValue, &pLocal->Value);
            memcpy((char *) &pValue->Value.Pointer, &pRun->Memory[pLocal->Offset], pLocal->Value.Length);
            value_cast(pValue, pSymbol->Value.Type);
        }
    }

    frame_restore(Context);

    for(pParameter = ll_iterate_first(&sIter, &pFunction->Parameters);
            pParameter;
            pParameter = ll_iterate_next(&sIter)) {
        if(((pParameter->Type & TYPE_OUTPUT) == 0) ||
                (pParameter->Parameter.Name == NULL) ||
                ((pParameter->Type & TYPE_VARIABLE) == 0))
            continue;

        pSymbol = pContext->Symbols.Symbol[pParameter->Id];
        pValue = &pParameter->Parameter.Value;
        memcpy(&pRun->Memory[pSymbol->Offset], (char *) &pValue->Value.Pointer, pValue->Length);
    }

    /*
        Finally, the following copies the current register from the program organisation 
        unit that has completed execution to the previous frame. This is intended to serve 
        as the primary means by which functions can directly return a result, but still 
        needs to be validated against the return type defined for the program 
        organisation unit.
    */

    value_copy(&pPrevious->CR, &pCurrent->CR);  //  TODO: Add type checking

    return 0;
}


static int
_frame_function_block(RUNTIME_CONTEXT *Context) {
    ECHIDNA *pContext;
    FRAME *pCurrent, *pPrevious;
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    FUNCTION_REGISTER *pFunction;
    RUNTIME *pRun;
    RUNTIME_FUNCTION *pInstance;
    SYMBOL *pSymbol1, *pSymbol2;
    UNIT *pPOU;
    size_t uIndex, uOffset;

    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);

    pCurrent = frame_current(Context);
    pPrevious = frame_previous(Context);
    pInstance = pPrevious->Function;
    assert(pInstance != NULL);
    if(pInstance->Type != TYPE_FUNCTION_BLOCK)
        return ERROR_INTERNAL;
    if(pInstance->Id >= pContext->Symbols.Count)
        return ERROR_INVALID_SYMBOL;

    pSymbol1 = pContext->Symbols.Symbol[pInstance->Id];
    assert(pSymbol1 != NULL);
    pFunction = pSymbol1->Function;
    assert(pFunction != NULL);
    pBlock = pFunction->Block;
    assert(pBlock != NULL);

    pPOU = (UNIT *) pCurrent->POU;
    assert(pPOU != NULL);
    for(uIndex = 0; uIndex < pBlock->Count; ++uIndex) {
        pField = &pBlock->Fields[uIndex];
        if((pSymbol2 = symbol_search(pContext, pPOU->Config,
                pPOU->Resource,
                pPOU->POU,
                (char *) pField->Name)) == NULL)
            continue;
        uOffset = pSymbol1->Offset + pField->Offset;
        memcpy(&pRun->Memory[uOffset], &pRun->Memory[pSymbol2->Offset], pSymbol1->Value.Length);
    }

    frame_restore(Context);

    return 0;
}


static void
_frame_stash(RUNTIME_CONTEXT *Context, int Action) {
    ECHIDNA *pContext;
    FRAME *pFrame;
    LL *pSymbols;
    LL_ITER sIter;
    RUNTIME *pRun;
    SYMBOL *pSymbol;
    UNIT *pPOU;
    size_t uByte, uOffset;
    ssize_t nLength;

    /*
        This function is intended to restore the value of local variables in the 
        previous frame of execution. This is important in the event that this previous 
        program organisation unit has been called recursively or within the current 
        (or descendent) frames of execution.
    */

    assert(Context != NULL);
    pFrame = (Action == FRAME_STORE) ? 
            frame_current(Context) : 
            frame_previous(Context);
    pPOU = pFrame->POU;
    assert(pPOU != NULL);
    if(pPOU->Size == 0)
        return;

    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);
    pSymbols = &pPOU->Symbols;
    assert(pSymbols->Size > 0);

    if(Action == FRAME_STORE) {
        block_initialise(&pFrame->Data);
        block_size(&pFrame->Data, pPOU->Size);
    }

    uOffset = 0;
    for(pSymbol = ll_iterate_first(&sIter, pSymbols);
            pSymbol;
            pSymbol = ll_iterate_next(&sIter)) {

        if((nLength = pSymbol->Value.Length) <= 0)
            continue;
        if(pSymbol->Value.Type == TYPE_FUNCTION_BLOCK)
            continue;
        switch(Action) {
            case FRAME_RESTORE:
                memcpy(&pRun->Memory[pSymbol->Offset], &pFrame->Data.Data[uOffset], nLength);
                break;

            case FRAME_STORE:
                memcpy(&pFrame->Data.Data[uOffset], &pRun->Memory[pSymbol->Offset], nLength);
                break;

            default:
                assert(0);
        }

        uOffset += (size_t) nLength;
        if((uByte = (uOffset % pContext->Align)) != 0)
            uOffset += (pContext->Align - uByte);
    }
}


void 
_frame_initialise(size_t Arg, FRAME *Frame, ...) {
    va_list sArg;
    size_t uIndex;

    Frame->PC = 0;
    Frame->ER = 0;
    Frame->BC = 0;
    Frame->Function = NULL;
    Frame->Parameter = 0;
    ll_initialise(&Frame->Parameters);

    Frame->Type = TYPE_NONE;
    value_initialise(&Frame->CR);
    value_assign(&Frame->CR, Frame->Type);
    for(uIndex = 0; uIndex < 10; ++uIndex)
        value_initialise(&Frame->Inputs[uIndex]);

    if(Arg > 1) {
        va_start(sArg, Frame);
        Frame->POU = va_arg(sArg, void *);
        va_end(sArg);
    }
    else
        Frame->POU = NULL;
}


int 
_frame_push(size_t Arg, RUNTIME_CONTEXT *Context, ...) {
    FRAME *pFrame;
    PARAMETER *pCopy, *pParameter;
    LL *pParameters;
    va_list sArg;
    int nResult;

    assert(Context != NULL);
    if(Context->Stack.Depth == FRAME_MAX) {
        pFrame = frame_current(Context);
        pFrame->ER = ERROR_STACK_OVERFLOW;
        Context->State = STATE_ERROR;
        return ENOMEM;
    }

    pFrame = &Context->Stack.Frame[Context->Stack.Depth++];
    frame_initialise(pFrame);

    for(nResult = 0;;) {
        va_start(sArg, Context);
        if(Arg > 1)
            pFrame->POU = va_arg(sArg, void *); //  UNIT *
        if(Arg > 2)
            pFrame->PC = va_arg(sArg, uint32_t);
        if(Arg > 3) {

            /*
                If a list of parameters have been passed to this frame, indicative that this
                new frame of execution is a function or function block written in an IEC 61131-3
                language, these need to be copied in the event that this function or function 
                block is executed recursively.
            */

            if((pParameters = va_arg(sArg, LL *)) == NULL)
                break;
            ll_reset(pParameters);
            while((pParameter = ll_iterate(pParameters)) != NULL) {
                if(((pCopy = parameter_new(pParameter)) == NULL) ||
                        (ll_insert(&pFrame->Parameters, pCopy) != 0)) {
                    pFrame->ER = ERROR_INTERNAL_ALLOCATION;
                    Context->State = STATE_ERROR;
                    nResult = errno;
                    break;
                }
            }
        }
        break;
    }
    va_end(sArg);
    return nResult;
}


FRAME *
frame_current(RUNTIME_CONTEXT *Context) {
    assert(Context != NULL);
    assert(Context->Stack.Depth > 0);
    return &Context->Stack.Frame[Context->Stack.Depth - 1];
}


void 
frame_next(RUNTIME_CONTEXT *Context) {
    FRAME *pFrame;

    pFrame = frame_current(Context);
    switch(Context->Stack.Depth) {
        case 1:
            frame_initialise(pFrame, ll_iterate_next(&Context->Next));
            break;

        default:
            frame_pop(Context);
            break;
    }
}


int 
frame_pop(RUNTIME_CONTEXT *Context) {
    FRAME *pCurrent, *pPrevious;
    int nResult;

    pCurrent = frame_current(Context);
    pPrevious = frame_previous(Context);

    nResult = 0;
    switch(pPrevious->BC & BYTECODE_MASK) {
        case BYTECODE_ANDN_P:
            if((nResult = operand_invert(pPrevious, &pCurrent->CR)) != 0)
                break;
            /* break; */
        case BYTECODE_AND_P:
            if((nResult = operator_and(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
         case BYTECODE_ORN_P:
            if((nResult = operand_invert(pPrevious, &pCurrent->CR)) != 0)
                break;
            /* break; */
        case BYTECODE_ORN:
            if((nResult = operator_or(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;

        case BYTECODE_XORN_P:
            if((nResult = operand_invert(pPrevious, &pCurrent->CR)) != 0)
                break;
            /* break; */
        case BYTECODE_XOR_P:
            if((nResult = operator_xor(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;

        case BYTECODE_ADD_P:
            if((nResult = operator_add(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;

        case BYTECODE_SUB_P:
            if((nResult = operator_sub(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;

        case BYTECODE_MUL_P:
            if((nResult = operator_mul(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_DIV_P:
            if((nResult = operator_div(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;

        case BYTECODE_MOD_P:
            if((nResult = operator_mod(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_GT_P:
            if((nResult = operator_gt(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_GE_P:
            if((nResult = operator_ge(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_EQ_P:
            if((nResult = operator_eq(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_NE_P:
            if((nResult = operator_ne(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_LE_P:
            if((nResult = operator_le(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
        
        case BYTECODE_LT_P:
            if((nResult = operator_lt(pPrevious, &pCurrent->CR)) == 0)
                pPrevious->PC = pCurrent->PC;
            break;
            
        case BYTECODE_CAL:
        case BYTECODE_CALC:
        case BYTECODE_CALCN:
            switch(pPrevious->Type & ANY_INTERNAL) {
                case TYPE_FUNCTION:
                    _frame_function(Context);
                    break;

                case TYPE_FUNCTION_BLOCK:
                    nResult = _frame_function_block(Context);
                    break;

                default:
                    break;
            }
            if(block_size(&pCurrent->Data) > 0)
                block_destroy(&pCurrent->Data);
            break;

        default:
            assert(0);
            break;
    }

    ll_destroy(&pCurrent->Parameters, parameter_destroy);
    assert(pCurrent->Parameters.Size == 0);

    if(nResult == 0)
        --Context->Stack.Depth;
    else
        Context->State = STATE_ERROR;

    return nResult;
}


FRAME *
frame_previous(RUNTIME_CONTEXT *Context) {
    assert(Context != NULL);
    assert(Context->Stack.Depth > 1);
    return &Context->Stack.Frame[Context->Stack.Depth - 2];
}


void
frame_restore(RUNTIME_CONTEXT *Context) {
    _frame_stash(Context, FRAME_RESTORE);
}


void
frame_store(RUNTIME_CONTEXT *Context) {
    _frame_stash(Context, FRAME_STORE);
}

