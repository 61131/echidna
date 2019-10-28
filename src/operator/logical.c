#include <cast.h>
#include <frame.h>
#include <operator.h>
#include <runtime.h>
#include <value.h>


int 
operator_and(FRAME *Frame, VALUE *Value) {
    switch(Frame->CR.Type) {
        case TYPE_LINT:
            if(cast_lint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S64 &= Value->Value.S64;
            break;

        case TYPE_DINT:
            if(cast_dint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S32 &= Value->Value.S32;
            break;

        case TYPE_INT:
            if(cast_int(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S16 &= Value->Value.S16;
            break;

        case TYPE_SINT:
            if(cast_sint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S8 &= Value->Value.S8;
            break;

        case TYPE_ULINT:
            if(cast_ulint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U64 &= Value->Value.U64;
            break;

        case TYPE_UDINT:
            if(cast_udint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U32 &= Value->Value.U32;
            break;

        case TYPE_UINT:
            if(cast_uint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U16 &= Value->Value.U16;
            break;

        case TYPE_USINT:
            if(cast_usint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U8 &= Value->Value.U8;
            break;

        case TYPE_LWORD:
            if(cast_lword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B64 &= Value->Value.B64;
            break;

        case TYPE_DWORD:
            if(cast_dword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B32 &= Value->Value.B32;
            break;

        case TYPE_WORD:
            if(cast_word(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B16 &= Value->Value.B16;
            break;

        case TYPE_BYTE:
            if(cast_byte(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B8 &= Value->Value.B8;
            break;

        case TYPE_BOOL:
            if(cast_bool(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B1 &= Value->Value.B1;
            Frame->CR.Value.B1 &= 1;
            break;

        case TYPE_REAL:
        case TYPE_LREAL:
        case TYPE_TIME:
        default:
            return ERROR_OPERAND_TYPE;
    }

    operand_subrange(&Frame->CR, &Frame->CR);
    return 0;
}


int 
operator_not(FRAME *Frame, VALUE *Value) {
    switch(Frame->CR.Type) {
        case TYPE_LINT:
            if(cast_lint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S64 = ~Value->Value.S64;
            break;

        case TYPE_DINT:
            if(cast_dint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S32 = ~Value->Value.S32;
            break;

        case TYPE_INT:
            if(cast_int(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S16 = ~Value->Value.S16;
            break;

        case TYPE_SINT:
            if(cast_sint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S8 = ~Value->Value.S8;
            break;

        case TYPE_ULINT:
            if(cast_ulint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U64 = ~Value->Value.U64;
            break;

        case TYPE_UDINT:
            if(cast_udint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U32 = ~Value->Value.U32;
            break;

        case TYPE_UINT:
            if(cast_uint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U16 = ~Value->Value.U16;
            break;

        case TYPE_USINT:
            if(cast_usint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U8 = ~Value->Value.U8;
            break;

        case TYPE_LWORD:
            if(cast_lword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B64 = ~Value->Value.B64;
            break;

        case TYPE_DWORD:
            if(cast_dword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B32 = ~Value->Value.B32;
            break;

        case TYPE_WORD:
            if(cast_word(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B16 = ~Value->Value.B16;
            break;

        case TYPE_BYTE:
            if(cast_byte(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B8 = ~Value->Value.B8;
            break;

        case TYPE_BOOL:
            if(cast_bool(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B1 = ~Value->Value.B1;
            Frame->CR.Value.B1 &= 1;
            break;

        case TYPE_REAL:
        case TYPE_LREAL:
        case TYPE_TIME:
        default:
            return ERROR_OPERAND_TYPE;
    }

    operand_subrange(&Frame->CR, &Frame->CR);
    return 0;
}


int 
operator_or(FRAME *Frame, VALUE *Value) {
    switch(Frame->CR.Type) {
        case TYPE_LINT:
            if(cast_lint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S64 |= Value->Value.S64;
            break;

        case TYPE_DINT:
            if(cast_dint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S32 |= Value->Value.S32;
            break;

        case TYPE_INT:
            if(cast_int(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S16 |= Value->Value.S16;
            break;

        case TYPE_SINT:
            if(cast_sint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S8 |= Value->Value.S8;
            break;

        case TYPE_ULINT:
            if(cast_ulint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U64 |= Value->Value.U64;
            break;

        case TYPE_UDINT:
            if(cast_udint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U32 |= Value->Value.U32;
            break;

        case TYPE_UINT:
            if(cast_uint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U16 |= Value->Value.U16;
            break;

        case TYPE_USINT:
            if(cast_usint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U8 |= Value->Value.U8;
            break;

        case TYPE_LWORD:
            if(cast_lword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B64 |= Value->Value.B64;
            break;

        case TYPE_DWORD:
            if(cast_dword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B32 |= Value->Value.B32;
            break;

        case TYPE_WORD:
            if(cast_word(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B16 |= Value->Value.B16;
            break;

        case TYPE_BYTE:
            if(cast_byte(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B8 |= Value->Value.B8;
            break;

        case TYPE_BOOL:
            if(cast_bool(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B1 |= Value->Value.B1;
            Frame->CR.Value.B1 &= 1;
            break;

        case TYPE_REAL:
        case TYPE_LREAL:
        case TYPE_TIME:
        default:
            return ERROR_OPERAND_TYPE;
    }

    operand_subrange(&Frame->CR, &Frame->CR);
    return 0;
}


int 
operator_xor(FRAME *Frame, VALUE *Value) {
    switch(Frame->CR.Type) {
        case TYPE_LINT:
            if(cast_lint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S64 ^= Value->Value.S64;
            break;

        case TYPE_DINT:
            if(cast_dint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S32 ^= Value->Value.S32;
            break;

        case TYPE_INT:
            if(cast_int(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S16 ^= Value->Value.S16;
            break;

        case TYPE_SINT:
            if(cast_sint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.S8 ^= Value->Value.S8;
            break;

        case TYPE_ULINT:
            if(cast_ulint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U64 ^= Value->Value.U64;
            break;

        case TYPE_UDINT:
            if(cast_udint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U32 ^= Value->Value.U32;
            break;

        case TYPE_UINT:
            if(cast_uint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U16 ^= Value->Value.U16;
            break;

        case TYPE_USINT:
            if(cast_usint(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.U8 ^= Value->Value.U8;
            break;

        case TYPE_LWORD:
            if(cast_lword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B64 ^= Value->Value.B64;
            break;

        case TYPE_DWORD:
            if(cast_dword(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B32 ^= Value->Value.B32;
            break;

        case TYPE_WORD:
            if(cast_word(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B16 ^= Value->Value.B16;
            break;

        case TYPE_BYTE:
            if(cast_byte(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B8 ^= Value->Value.B8;
            break;

        case TYPE_BOOL:
            if(cast_bool(Value) != 0)
                return ERROR_OPERAND_TYPE;
            Frame->CR.Value.B1 ^= Value->Value.B1;
            Frame->CR.Value.B1 &= 1;
            break;

        case TYPE_REAL:
        case TYPE_LREAL:
        case TYPE_TIME:
        default:
            return ERROR_OPERAND_TYPE;
    }

    operand_subrange(&Frame->CR, &Frame->CR);
    return 0;
}

