#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>
#include <assert.h>

#include <block.h>
#include <bytecode.h>
#include <echidna.h>
#include <frame.h>
#include <log.h>
#include <operator.h>
#include <runtime.h>
#include <runtime/bytecode.h>
#include <runtime/error.h>
#include <symbol.h>
#include <unit.h>
#include <value.h>


#define runtime_debug(...)      _runtime_debug( _NARG( __VA_ARGS__ ), __VA_ARGS__ )


static int _runtime_bytecode_value(RUNTIME_CONTEXT *Context, FRAME *Frame, SYMBOL **Symbol, VALUE *Value);

static void _runtime_debug( size_t Arg, RUNTIME_CONTEXT *pContext, ... );


static int 
_runtime_bytecode_value(RUNTIME_CONTEXT *Context, FRAME *Frame, SYMBOL **Symbol, VALUE *Value) {
    ECHIDNA *pContext;
    RUNTIME *pRun;
    uint32_t uId;
    int nLength, nResult;

    /*
        This function is intended to read an operand value from bytecode during virtual 
        machine run-time operations.
    */

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(Frame != NULL);
    assert(Value != NULL);

    value_initialise(Value);
    if(!runtime_bytecode_operand(Frame))
        return 0;
    if((nResult = runtime_read(Context, sizeof(Frame->Type), (char *) &Frame->Type)) != 0)
        return nResult;
    value_assign(Value, (Frame->Type & ~(TYPE_VARIABLE | TYPE_IN_OUT)));
    switch(Value->Type) {
        case TYPE_LREAL:
        case TYPE_REAL:
        case TYPE_LINT:
        case TYPE_DINT:
        case TYPE_INT:
        case TYPE_SINT:
        case TYPE_ULINT:
        case TYPE_UDINT:
        case TYPE_UINT:
        case TYPE_USINT:
        case TYPE_LWORD:
        case TYPE_DWORD:
        case TYPE_WORD:
        case TYPE_BYTE:
        case TYPE_BOOL:
        case TYPE_TIME:
        case TYPE_FUNCTION:
        case TYPE_FUNCTION_BLOCK:
        case TYPE_LABEL:
        case TYPE_NONE:
            break;

        default:
            assert(0);
    }

    if((G_MODIFIER(Frame->BC) & MODIFIER_PARENTHESIS) == 0) {
        nLength = value_typetosize(Frame->Type & ~TYPE_VARIABLE);
        if((Frame->Type & TYPE_VARIABLE) != 0) {
            if((nResult = runtime_read(Context, sizeof(uId), (char *) &uId)) != 0)
                return nResult;
            if(uId >= pContext->Symbols.Count) {
                Frame->ER = ERROR_INVALID_SYMBOL;
                Context->State = STATE_ERROR;
                return EINVAL;
            }
            *Symbol = pContext->Symbols.Symbol[uId];
            value_copy(Value, &(*Symbol)->Value);
            if(nLength > 0)
                memcpy((char *) &Value->Value.Pointer, &pRun->Memory[(*Symbol)->Offset], nLength);
        }
        else {
            if(nLength > 0) {
                if((nResult = runtime_read(Context, nLength, (char *) &Value->Value.Pointer)) != 0)
                    return nResult;
            }
        }
    }

    return 0;
}


static void 
_runtime_debug(size_t Arg, RUNTIME_CONTEXT *Context, ...) {
    BLOCK *pBlock;
    FRAME *pFrame;
    UNIT *pPOU;
    VALUE *pValue;
    va_list sArg;
    char sValue1[64], sValue2[32];
    uint32_t uPC;

    pFrame = frame_current(Context);
    pValue = NULL;
    if(Arg > 1) {
        va_start(sArg, Context);
        uPC = va_arg(sArg, uint32_t);
        if(Arg > 2)
            pValue = va_arg(sArg, VALUE *);
        va_end(sArg);
    }
    else 
        uPC = pFrame->PC;

    pPOU = pFrame->POU;
    assert(pPOU != NULL);
    pBlock = &pPOU->Block;
    assert(pBlock->Name != NULL);

    if(pValue) {
        switch(pValue->Type) {
            case TYPE_LREAL:        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:LREAL(%g)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.Double); break;
            case TYPE_REAL:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:REAL(%f)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.Single); break;
            case TYPE_LINT:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:LINT(%ld)", bytecode_typetostr(pFrame->BC), pFrame->BC, (long int) pValue->Value.S64); break;
            case TYPE_DINT:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:DINT(%d)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.S32); break;
            case TYPE_INT:          snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:INT(%d)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.S16); break;
            case TYPE_SINT:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:SINT(%d)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.S8); break;
            case TYPE_ULINT:        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:ULINT(%lu)", bytecode_typetostr(pFrame->BC), pFrame->BC, (long unsigned int) pValue->Value.U64); break;
            case TYPE_UDINT:        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:UDINT(%u)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.U32); break;
            case TYPE_UINT:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:UINT(%u)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.U16); break;
            case TYPE_USINT:        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:USINT(%u)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.U8); break;
            case TYPE_LWORD:        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:LWORD(%lx)", bytecode_typetostr(pFrame->BC), pFrame->BC, (long unsigned int) pValue->Value.B64); break;
            case TYPE_DWORD:        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:DWORD(%08x)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.B32); break;
            case TYPE_WORD:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:WORD(%04x)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.B16); break;
            case TYPE_BYTE:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:BYTE(%02x)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.B8); break;
            case TYPE_BOOL:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:BOOL(%s)", bytecode_typetostr(pFrame->BC), pFrame->BC, (pValue->Value.B1 > 0) ? "true" : "false"); break;
            case TYPE_TIME:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:TIME(%f)", bytecode_typetostr(pFrame->BC), pFrame->BC, pValue->Value.Time); break;
            case TYPE_NONE:         snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x)", bytecode_typetostr(pFrame->BC), pFrame->BC); break;
            default:
                snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x) OP:%s", bytecode_typetostr(pFrame->BC), pFrame->BC, value_typetostr(pValue->Type));
                break;
        }
    }
    else
        snprintf(sValue1, sizeof(sValue1), "BC:%5s(%08x)", bytecode_typetostr(pFrame->BC), pFrame->BC);

    switch(pFrame->CR.Type) {
        case TYPE_LREAL:        snprintf(sValue2, sizeof(sValue2), "CR:LREAL(%g)", pFrame->CR.Value.Double); break;
        case TYPE_REAL:         snprintf(sValue2, sizeof(sValue2), "CR:REAL(%f)", pFrame->CR.Value.Single); break;
        case TYPE_LINT:         snprintf(sValue2, sizeof(sValue2), "CR:LINT(%ld)", pFrame->CR.Value.S64); break;
        case TYPE_DINT:         snprintf(sValue2, sizeof(sValue2), "CR:DINT(%d)", pFrame->CR.Value.S32); break;
        case TYPE_INT:          snprintf(sValue2, sizeof(sValue2), "CR:INT(%d)", pFrame->CR.Value.S16); break;
        case TYPE_SINT:         snprintf(sValue2, sizeof(sValue2), "CR:SINT(%d)", pFrame->CR.Value.S8); break;
        case TYPE_ULINT:        snprintf(sValue2, sizeof(sValue2), "CR:ULINT(%lu)", pFrame->CR.Value.U64); break;
        case TYPE_UDINT:        snprintf(sValue2, sizeof(sValue2), "CR:UDINT(%u)", pFrame->CR.Value.U32); break;
        case TYPE_UINT:         snprintf(sValue2, sizeof(sValue2), "CR:UINT(%u)", pFrame->CR.Value.U16); break;
        case TYPE_USINT:        snprintf(sValue2, sizeof(sValue2), "CR:USINT(%u)", pFrame->CR.Value.U8); break;
        case TYPE_LWORD:        snprintf(sValue2, sizeof(sValue2), "CR:LWORD(%lx)", pFrame->CR.Value.B64); break;
        case TYPE_DWORD:        snprintf(sValue2, sizeof(sValue2), "CR:DWORD(%08x)", pFrame->CR.Value.B32); break;
        case TYPE_WORD:         snprintf(sValue2, sizeof(sValue2), "CR:WORD(%04x)", pFrame->CR.Value.B16); break;
        case TYPE_BYTE:         snprintf(sValue2, sizeof(sValue2), "CR:BYTE(%02x)", pFrame->CR.Value.B8); break;
        case TYPE_BOOL:         snprintf(sValue2, sizeof(sValue2), "CR:BOOL(%s)", (pFrame->CR.Value.B1 > 0) ? "true" : "false"); break;
        case TYPE_TIME:         snprintf(sValue2, sizeof(sValue2), "CR:TIME(%f)", pFrame->CR.Value.Time); break;
        default:
            snprintf(sValue2, sizeof(sValue2), "CR:%s", value_typetostr(pFrame->CR.Type));
            break;
    }

    //  Suppress output of current register for selected operators

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
            if(pValue->Type == TYPE_FUNCTION_BLOCK)
                break;
            /* break; */
        case BYTECODE_LD:
        case BYTECODE_LDN:
        case BYTECODE_CAL:
        case BYTECODE_JMP:
            sValue2[0] = '\0';
            break;

        default:
            break;
    }

    log_debug("%s: Stack:%u Error:%u PC:%04u %s %s", pBlock->Name, Context->Stack.Depth, pFrame->ER, uPC, sValue1, sValue2);
}


int
runtime_bytecode_execute(RUNTIME_CONTEXT *Context) {
    BLOCK *pBlock;
    ECHIDNA *pContext;
    RUNTIME *pRun;
    FRAME *pFrame;
    SYMBOL *pSymbol;
    UNIT *pPOU;
    VALUE sValue;
    uint32_t uDepth, uPC;
    int nResult;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);

    /*
        The following code will read the operator bytecode from the memory block 
        into the execution frame - Where there is an operand associated with the 
        operator, this too is read into the execution frame registers. Note that
        the test to see if the program counter is at the end of the frame is 
        immediately performed in the event that the current POU does not cleanly
        finish with a return operator.
    */

    pFrame = frame_current(Context);
    pPOU = pFrame->POU;
    assert(pPOU != NULL);
    pBlock = &pPOU->Block;
    if(pFrame->PC >= pBlock->End) {
        frame_next(Context);
        return 0;
    }

    //  Read operator and operand (if appropriate)

    uPC = pFrame->PC;
    if((nResult = runtime_read(Context, sizeof(pFrame->BC), (char *) &pFrame->BC)) != 0)
        return nResult;
    pSymbol = NULL;
    if((nResult = _runtime_bytecode_value(Context, pFrame, &pSymbol, &sValue)) != 0)
        return nResult;

    if(pContext->Verbose > 1)
        runtime_debug(Context, uPC, &sValue);

    nResult = 0;
    switch(pFrame->BC & BYTECODE_MASK) {
        case BYTECODE_LDN:
            if((nResult = operand_invert(pFrame, &sValue)) != 0)
                break;
        case BYTECODE_LD:
            value_copy(&pFrame->CR, &sValue);
            break;

        case BYTECODE_STN:
            if((nResult = operand_invert(pFrame, &pFrame->CR)) != 0)
                break;
        case BYTECODE_ST:
            assert(pSymbol != NULL);
            assert(pSymbol->Value.Length > 0);
            operand_subrange(&pFrame->CR, &sValue);
            memcpy(&pRun->Memory[pSymbol->Offset], &pFrame->CR.Value.Pointer, pSymbol->Value.Length);
            break;

        case BYTECODE_CD:
        case BYTECODE_CLK:
        case BYTECODE_CU:
        case BYTECODE_IN:
        case BYTECODE_PT:
        case BYTECODE_PV:
        case BYTECODE_S:
        case BYTECODE_S1:
        case BYTECODE_R:
        case BYTECODE_R1:
            nResult = operator_inputs(Context, pSymbol, &sValue);
            break;

        case BYTECODE_ANDN:
            if((nResult = operand_invert(pFrame, &sValue)) == 0) {
        case BYTECODE_AND:
                nResult = operator_and(pFrame, &sValue); 
            }
            break;

        case BYTECODE_ORN:
            if((nResult = operand_invert(pFrame, &sValue)) == 0) {
        case BYTECODE_OR:
                nResult = operator_or(pFrame, &sValue); 
            }
            break;

        case BYTECODE_XORN:
            if((nResult = operand_invert(pFrame, &sValue)) == 0) {
        case BYTECODE_XOR:
                nResult = operator_xor(pFrame, &sValue); 
            }
            break;

        case BYTECODE_NOT:
            nResult = operator_not(pFrame, &sValue); 
            break;

        case BYTECODE_ADD:
            nResult = operator_add(pFrame, &sValue); 
            break;

        case BYTECODE_SUB:
            nResult = operator_sub(pFrame, &sValue); 
            break;

        case BYTECODE_MUL:
            nResult = operator_mul(pFrame, &sValue); 
            break;

        case BYTECODE_DIV:
            nResult = operator_div(pFrame, &sValue); 
            break;

        case BYTECODE_MOD:
            nResult = operator_mod(pFrame, &sValue); 
            break;

        case BYTECODE_GT:
            nResult = operator_gt(pFrame, &sValue); 
            break;

        case BYTECODE_GE:
            nResult = operator_ge(pFrame, &sValue); 
            break;

        case BYTECODE_EQ:
            nResult = operator_eq(pFrame, &sValue); 
            break;

        case BYTECODE_NE:
            nResult = operator_ne(pFrame, &sValue);
            break;

        case BYTECODE_LE:
            nResult = operator_le(pFrame, &sValue); 
            break;

        case BYTECODE_LT:
            nResult = operator_lt(pFrame, &sValue); 
            break;

        case BYTECODE_ANDN_P:
        case BYTECODE_AND_P:
        case BYTECODE_ORN_P:
        case BYTECODE_OR_P:
        case BYTECODE_XORN_P:
        case BYTECODE_XOR_P:
        case BYTECODE_ADD_P:
        case BYTECODE_SUB_P:
        case BYTECODE_MUL_P:
        case BYTECODE_DIV_P:
        case BYTECODE_MOD_P:
        case BYTECODE_GT_P:
        case BYTECODE_GE_P:
        case BYTECODE_EQ_P:
        case BYTECODE_NE_P:
        case BYTECODE_LE_P:
        case BYTECODE_LT_P:
            frame_push(Context, pFrame->POU, pFrame->PC);
            break;

        case BYTECODE_JMP:
        case BYTECODE_JMPC:
        case BYTECODE_JMPCN:
            nResult = operator_jump(pFrame, &sValue); 
            break;

        case BYTECODE_CAL:
        case BYTECODE_CALC:
        case BYTECODE_CALCN:
            uDepth = Context->Stack.Depth;
            nResult = operator_call(Context);
            if((nResult == 0) &&
                    (Context->Stack.Depth > uDepth))
                return 0;
            break;

        case BYTECODE_RET:
        case BYTECODE_RETC:
        case BYTECODE_RETCN:
            operator_return(pFrame);
            break;

        case BYTECODE_PARAMETER:
            nResult = operator_parameter(Context);
            break;

        case BYTECODE_PARENTHESIS:
            assert(Context->Stack.Depth > 1);
            nResult = frame_pop(Context);
            break;

        case BYTECODE_NOP:
            break;

        default:
            log_error("Unhandled operator: %u", G_OP(pFrame->BC));
            assert(0);
    }

    if((nResult != 0) &&
            (pFrame->ER == 0))
        pFrame->ER = nResult;
    if(pFrame->ER != ERROR_NONE) {
        log_error("%s: Cycle: %llu, Error: %s", 
                Context->Name,
                Context->Stats.Cycle,
                runtime_errortostr(pFrame->ER));
        Context->State = STATE_ERROR;
    }
    if(pFrame->PC >= pBlock->End)
        frame_next(Context);

    value_destroy(&sValue);
    return nResult;
}


int
runtime_bytecode_operand(FRAME *Frame) {
    switch(Frame->BC & BYTECODE_MASK) {
        case BYTECODE_NOP:
        case BYTECODE_RET:
        case BYTECODE_RETC:
        case BYTECODE_RETCN:
        case BYTECODE_PARENTHESIS:
            return 0;

        default:
            return 1;
    }
}



