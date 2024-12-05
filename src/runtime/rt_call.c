#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <bytecode.h>
#include <echidna.h>
#include <frame.h>
#include <log.h>
#include <runtime.h>
#include <runtime/error.h>
#include <runtime/function.h>
#include <symbol.h>
#include <unit.h>


static RT_FUNCTION * _runtime_cache(RUNTIME_CONTEXT *Context);

static int _runtime_compare(const void *A, const void *B);

static int _runtime_value(RUNTIME_CONTEXT *Context, VALUE *Value);


static RT_FUNCTION *
_runtime_cache(RUNTIME_CONTEXT *Context) {
    FRAME *pFrame;
    RT_FUNCTION *pIndex, **pFunction, sFunction;

    pFrame = frame_current(Context);
    assert(pFrame->POU != NULL);
    sFunction.POU = pFrame->POU;
    sFunction.PC = pFrame->PC;
    pIndex = &sFunction;
    pFunction = bsearch(&pIndex, Context->Functions.Function, Context->Functions.Count, sizeof(RT_FUNCTION *), _runtime_compare);
    return (pFunction != NULL) ? *pFunction : NULL;
}


static int
_runtime_compare(const void *A, const void *B) {
    RT_FUNCTION *pFuncA, *pFuncB;

    assert(A != NULL);
    pFuncA = *(RT_FUNCTION **) A;
    assert(pFuncA != NULL);
    assert(B != NULL);
    pFuncB = *(RT_FUNCTION **) B;
    assert(pFuncB != NULL);

    if(pFuncA->POU != pFuncB->POU)
        return (pFuncA->POU < pFuncB->POU) ? -1 : 1;
    if(pFuncA->PC != pFuncB->PC)
        return (pFuncA->PC < pFuncB->PC) ? -1 : 1;
    return 0;
}


static int 
_runtime_value(RUNTIME_CONTEXT *Context, VALUE *Value) {
    switch(Value->Type & ~TYPE_IN_OUT) {
        case TYPE_LREAL:
            assert(Value->Length == sizeof(Value->Value.Double));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.Double);
        case TYPE_REAL:
            assert(Value->Length == sizeof(Value->Value.Single));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.Single);
        case TYPE_LINT:
            assert(Value->Length == sizeof(Value->Value.S64));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.S64);
        case TYPE_DINT:
            assert(Value->Length == sizeof(Value->Value.S32)); 
            return runtime_read(Context, Value->Length, (char *) &Value->Value.S32);
        case TYPE_INT:
            assert(Value->Length == sizeof(Value->Value.S16));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.S16);
        case TYPE_SINT:
            assert(Value->Length == sizeof(Value->Value.S8));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.S8);
        case TYPE_ULINT:
            assert(Value->Length == sizeof(Value->Value.U64));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.U64);
        case TYPE_UDINT:
            assert(Value->Length == sizeof(Value->Value.U32));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.U32);
        case TYPE_UINT:
            assert(Value->Length == sizeof(Value->Value.U16));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.U16);
        case TYPE_USINT:
            assert(Value->Length == sizeof(Value->Value.U8));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.U8);
        case TYPE_LWORD:
            assert(Value->Length == sizeof(Value->Value.B64));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.B64);
        case TYPE_DWORD:
            assert(Value->Length == sizeof(Value->Value.B32));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.B32);
        case TYPE_WORD:
            assert(Value->Length == sizeof(Value->Value.B16));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.B16);
        case TYPE_BYTE:
            assert(Value->Length == sizeof(Value->Value.B8));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.B8);
        case TYPE_BOOL:
            assert(Value->Length == sizeof(Value->Value.B1)); 
            return runtime_read(Context, Value->Length, (char *) &Value->Value.B1);
        case TYPE_TIME:
            assert(Value->Length == sizeof(Value->Value.Time));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.Time);
        case TYPE_DATE:
        case TYPE_DT:
        case TYPE_TOD:
            assert(Value->Length == sizeof(Value->Value.DateTime));
            return runtime_read(Context, Value->Length, (char *) &Value->Value.DateTime);
        default:
            log_debug("%s: %08x", __func__, Value->Type);
            assert(0);
    }

    return 0;
}


/*
    This function is intended to be called to parse bytecode, cache contextual 
    data and subsequently return this information associated with function calls. 
    While originally implemented for execution in association with each instance 
    of a CAL operator within a program organisation unit, this implementation has
    required extension in order to support the method of calling standard function
    blocks described in Feature 3 of Table 53 - Function block invocation and 
    function invocation features for IL language.
*/

RT_FUNCTION *
runtime_call_instance(RUNTIME_CONTEXT *Context) {
    ECHIDNA *pContext;
    FRAME *pFrame;
    RUNTIME *pRun;
    RT_FUNCTION *pFunction;
    RT_FUNCTION **pFunctions;
    RUNTIME_PARAMETER *pParameter = NULL;
    char sName[SYMBOL_NAME_MAX + 1];
    uint32_t uId, uLength, uType;
    size_t uCount, uIndex;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;

    /*
        The following code searches for a previously allocated instance of the data 
        structure associated with the current call operator. The current call operator
        is indexed by the program organisation unit and program counter of the current
        frame.
    */

    if((pFunction = _runtime_cache(Context)) != NULL)
        return pFunction;

    pFrame = frame_current(Context);
    uType = (pFrame->Type & ~TYPE_VARIABLE);
    assert((uType == TYPE_FUNCTION) ||
            (uType == TYPE_FUNCTION_BLOCK));
    if((pFunction = runtime_function_new(uType, pFrame->POU, pFrame->PC)) == NULL) 
        return NULL;

    switch(pFrame->BC & BYTECODE_MASK) {
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
            goto finish;

        case BYTECODE_CAL:
        case BYTECODE_CALC:
        case BYTECODE_CALCN:
            break;

        default:
            assert(0);
    }

    pParameter = NULL;
    if(runtime_read(Context, sizeof(uId), (char *) &uId) != 0) 
        goto error;
    switch(pFunction->Type) {
        case TYPE_FUNCTION:
            if(uId >= pContext->Functions.Count) {
                pFrame->ER = RT_ERR_INVALID_FUNCTION;
                goto error;
            }
            break;

        case TYPE_FUNCTION_BLOCK:
            if(uId >= pContext->Symbols.Count) {
                pFrame->ER = RT_ERR_INVALID_SYMBOL;
                goto error;
            }
            break;

        default:
            assert(0);
    }
    pFunction->Id = uId;

    //  Read and parse parameters

    uCount = (pFrame->BC & VALUE_MASK);
    for(uIndex = 0; uIndex < uCount; ++uIndex) {
        if((pParameter = runtime_parameter_new()) == NULL) 
            goto error;
        if(runtime_read(Context, sizeof(uType), (char *) &uType) != 0) 
            goto error;
        value_cast(&pParameter->Value, uType & ~TYPE_IN_OUT);
        pParameter->Type = uType;

        switch(uType) {
            case TYPE_PARAMETER:
                uLength = 0;
                if(runtime_read(Context, sizeof(uLength), (char *) &uLength) != 0)
                    goto error;
                if((uLength < 1) ||
                        (uLength > SYMBOL_NAME_MAX)) {
                    pFrame->ER = RT_ERR_INVALID_LENGTH;
                    goto error;
                }
                if(runtime_read(Context, uLength, (char *) sName) != 0)
                    goto error;
                sName[uLength] = '\0';
                pParameter->Parameter.Name = strdup(sName);

                if(runtime_read(Context, sizeof(uType), (char *) &uType) != 0)
                    goto error;
                value_cast(&pParameter->Value, uType & ~TYPE_IN_OUT);
                pParameter->Type = uType;
                /* break; */
            default:
                if((pParameter->Type & TYPE_VARIABLE) != 0) {
                    if(runtime_read(Context, sizeof(uId), (char *) &uId) != 0) 
                        goto error;
                    pParameter->Id = uId;
                }
                else {
                    if(_runtime_value(Context, &pParameter->Value) != 0)
                        goto error;
                }
                break;
        }

        if(ll_insert(&pFunction->Parameters, pParameter) != 0) 
            goto error;
        if(ll_insert(&pFunction->List, &pParameter->Parameter) != 0)
            goto error;
    }
    
finish:

    /*
        The following represents the first bytecode _after_ the call operator and its 
        associated parameters. This is used to skip over the parsing of parameters on
        subsequent execution of the bytecode.
    */

    pFunction->End = pFrame->PC;
    uLength = ((Context->Functions.Count + 1) * sizeof(RT_FUNCTION *));
    pFunctions = realloc(Context->Functions.Function, uLength);
    if(pFunctions == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        goto error;
    }
    Context->Functions.Function = pFunctions;
    Context->Functions.Function[Context->Functions.Count++] = pFunction;
    qsort(Context->Functions.Function, Context->Functions.Count, sizeof(RT_FUNCTION *), _runtime_compare);

    return pFunction;

error:
    runtime_parameter_destroy(pParameter);
    runtime_function_destroy(pFunction);
    return NULL;
}

