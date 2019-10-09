#include <stdarg.h>
#include <math.h>
#include <errno.h>
#include <assert.h>

#include <bytecode.h>
#include <bytecode/stack.h>
#include <grammar.h>
#include <token.h>
#include <value.h>


static int _bytecode_stack_compare(VALUE *A, VALUE *B);


static int 
_bytecode_stack_compare(VALUE *A, VALUE *B) {
    if(A->Type != B->Type)
        return 1;
    switch(A->Type) {
        case TYPE_LREAL:        return (abs(A->Value.Double - B->Value.Double) > DBL_EPSILON);
        case TYPE_REAL:         return (fabs(A->Value.Single - B->Value.Single) > FLT_EPSILON);
        case TYPE_LINT:         return (A->Value.S64 != B->Value.S64);
        case TYPE_DINT:         return (A->Value.S32 != B->Value.S32);
        case TYPE_INT:          return (A->Value.S16 != B->Value.S16);
        case TYPE_SINT:         return (A->Value.S8 != B->Value.S8);
        case TYPE_ULINT:        return (A->Value.U64 != B->Value.U64);
        case TYPE_UDINT:        return (A->Value.U32 != B->Value.U32);
        case TYPE_UINT:         return (A->Value.U16 != B->Value.U16);
        case TYPE_USINT:        return (A->Value.U8 != B->Value.U8);
        case TYPE_LWORD:        return (A->Value.B64 != B->Value.B64);
        case TYPE_DWORD:        return (A->Value.B32 != B->Value.B32);
        case TYPE_WORD:         return (A->Value.B16 != B->Value.B16);
        case TYPE_BYTE:         return (A->Value.B8 != B->Value.B8);
        case TYPE_BOOL:         return (A->Value.B1 != B->Value.B1);
        default:
            assert(0);
    }
    return 0;
}


void
_bytecode_stack_initialise(size_t Arg, BYTECODE_STACK *Stack, TOKEN_LIST *List, ...) {
    VALUE_TYPE uType;
    va_list sArg;

    Stack->List = List;
    Stack->BC = BYTECODE_NOP;
    Stack->Position = -1;
    Stack->Type = TYPE_NONE;
    value_initialise(&Stack->CR);
    token_list_reset(Stack->List);

    if(Arg > 2) {
        va_start(sArg, List);
        uType = va_arg(sArg, VALUE_TYPE);
        value_assign(&Stack->CR, uType);

        if(Arg > 3) 
            Stack->BC = (uint32_t) va_arg(sArg, int);
        if(Arg > 4) 
            Stack->Position = va_arg(sArg, int);
        va_end(sArg);
    }
}


int
bytecode_stack_cast(BYTECODE_STACK *Stack, TOKEN *Token) {
    VALUE sInterim, sValue;
    VALUE_TYPE uType;
    
    /*
        If there is either no operand or the operand type already matches that of 
        the current register, no further action is required. If these conditions 
        are not met, an attempt is made to cast the operand to the type of current 
        register *and* back again in order to determine if the original cast 
        operation will result in value clipping. This operation is still permitted, 
        but a warning is produced during the compilation process.
    */

    if(Stack->CR.Type == TYPE_NONE)
        return 0;
    uType = (Stack->Type & ~TYPE_VARIABLE);
    if(uType == Stack->CR.Type)
        return 0;
    if(uType == TYPE_NONE)
        return 0;

    value_initialise(&sInterim);
    value_initialise(&sValue);

    switch(Token->Id) {
        case LD:
        case LDN:
            break;

        case ST:
        case STN:
            if(Stack->CR.Type == TYPE_FUNCTION)
                break;
            if((value_cast(&sInterim, uType, &Token->Value) != 0) ||
                    (value_cast(&sValue, Stack->CR.Type, &sInterim) != 0 )) {
                log_error("Invalid cast in %s operand from %s to %s [%u:%u]",
                        yytokenname(Token->Id),
                        value_typetostr(Stack->CR.Type),
                        value_typetostr(uType),
                        Token->Line,
                        Token->Column);
                return EINVAL;
            }
            else {
                if(_bytecode_stack_compare(&Token->Value, &sValue) != 0) {
                    log_warn("Expect run-time cast of %s operand from %s to %s [%u:%u]",
                            yytokenname(Token->Id),
                            value_typetostr(Stack->CR.Type),
                            value_typetostr(uType),
                            Token->Line,
                            Token->Column);
                }
            }
            break;

        default:
            if((value_cast(&sInterim, Stack->CR.Type, &Token->Value) != 0) ||
                    (value_cast(&sValue, uType, &sInterim) != 0)) {
                log_error("Invalid cast in %s operand from %s to %s [%u:%u]",
                        yytokenname(Token->Id),
                        value_typetostr(uType),
                        value_typetostr(Stack->CR.Type),
                        Token->Line,
                        Token->Column);
                return EINVAL;
            }
            else {
                if((uType == TYPE_FUNCTION) ||
                        (uType == TYPE_FUNCTION_BLOCK) ||
                        (Stack->CR.Type == TYPE_FUNCTION))
                    break;
                if(_bytecode_stack_compare(&Token->Value, &sValue) != 0) {
                    log_warn("Expect run-time cast of %s operand from %s to %s [%u:%u]",
                            yytokenname(Token->Id),
                            value_typetostr(uType),
                            value_typetostr(Stack->CR.Type),
                            Token->Line,
                            Token->Column);
                }
            }
            break;
    }  
    return 0;
}


void 
bytecode_stack_set(BYTECODE_STACK *Stack, TOKEN *Token) {
    Stack->Id = Token->Id;
    Stack->Line = Token->Line;
    Stack->Column = Token->Column;
}


void 
bytecode_stack_type(BYTECODE_STACK *Stack, TOKEN *Token) {
    switch(Token->Id) {
        case LD:
        case LDN:
        case CD:
        case CLK:
        case CU:
        case IN:
        case PT:
        case PV:
        case R:
        case R1:
        case S:
        case S1:
        case CAL:
        case CALC:
        case CALCN:
            value_assign(&Stack->CR, (Stack->Type & ~TYPE_VARIABLE));
            break;
        
        case GT:
        case GE:
        case EQ:
        case LT:
        case LE:
        case NE:
            value_assign(&Stack->CR, TYPE_BOOL);
            break;

        default:
            break;
    }
}

