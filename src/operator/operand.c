#include <stdint.h>

#include <frame.h>
#include <log.h>
#include <operator.h>
#include <value.h>


int
operand_invert(FRAME *Frame, VALUE *Value) {
    switch(Frame->Type & ~TYPE_VARIABLE) {
        case TYPE_LINT:
            Value->Value.S64 = ~Value->Value.S64;
            break;

        case TYPE_DINT:
            Value->Value.S32 = ~Value->Value.S32;
            break;

        case TYPE_INT:
            Value->Value.S16 = ~Value->Value.S16;
            break;

        case TYPE_SINT:
            Value->Value.S8 = ~Value->Value.S8;
            break;

        case TYPE_ULINT:
            Value->Value.U64 = ~Value->Value.U64;
            break;

        case TYPE_UDINT:
            Value->Value.U32 = ~Value->Value.U32;
            break;

        case TYPE_UINT:
            Value->Value.U16 = ~Value->Value.U16;
            break;

        case TYPE_USINT:
            Value->Value.U8 = ~Value->Value.U8;
            break;

        case TYPE_LWORD:
            Value->Value.B64 = ~Value->Value.B64;
            break;

        case TYPE_DWORD:
            Value->Value.B32 = ~Value->Value.B32;
            break;

        case TYPE_WORD:
            Value->Value.B16 = ~Value->Value.B16;
            break;

        case TYPE_BYTE:
            Value->Value.B8 = ~Value->Value.B8;
            break;

        case TYPE_BOOL:
            Value->Value.B1 = ~Value->Value.B1;
            Value->Value.B1 = ( Value->Value.B1 & 1 );
            break;

        case TYPE_REAL:
        case TYPE_LREAL:
        default:
            return -1;
    }
    return 0;
}


int
operand_subrange(VALUE *Value, VALUE *Range) {
    /*
        The generic type of a subrange derived type (feature 3 of table 12) shall be
        ANY_INT. According to Annex E (Error conditions), the following error messages
        should read "Numerical result exceeds range for data type" (Table E.1 - Error
        conditions).
    */

    /* assert(Value->Type == Range->Type); */
    if((Range->Flags & FLAG_SUBRANGE) == 0)
        return 0;
    switch(Value->Type) {
        case TYPE_LINT:
            if(Value->Value.S64 > Range->Maximum.S64) {
                log_warn("Numeric result (%lld) greater than subrange (%lld..%lld) in type declaration",
                        Value->Value.S64,
                        Range->Minimum.S64,
                        Range->Maximum.S64);
                Value->Value.S64 = Range->Maximum.S64;
            }
            if(Value->Value.S64 < Range->Minimum.S64) {
                log_warn("Numeric result (%lld) less than subrange (%lld..%lld) in type declaration",
                        Value->Value.S64,
                        Range->Minimum.S64,
                        Range->Maximum.S64);
                Value->Value.S64 = Range->Minimum.S64;
            }
            break;

        case TYPE_DINT:
            if(Value->Value.S32 > Range->Maximum.S32) {
                log_warn("Numeric result (%lld) greater than subrange (%ld..%ld) in type declaration",
                        (int64_t) Value->Value.S32,
                        Range->Minimum.S32,
                        Range->Maximum.S32);
                Value->Value.S32 = Range->Maximum.S32;
            }
            if(Value->Value.S32 < Range->Minimum.S32) {
                log_warn("Numeric result (%lld) less than subrange (%ld..%ld) in type declaration",
                        (int64_t) Value->Value.S32,
                        Range->Minimum.S32,
                        Range->Maximum.S32);
                Value->Value.S32 = Range->Minimum.S32;
            }
            break;

        case TYPE_INT:
            if(Value->Value.S16 > Range->Maximum.S16) {
                log_warn("Numeric result (%lld) greater than subrange (%d..%d) in type declaration",
                        (int64_t) Value->Value.S16,
                        Range->Minimum.S16,
                        Range->Maximum.S16);
                Value->Value.S16 = Range->Maximum.S16;
            }
            if(Value->Value.S16 < Range->Minimum.S16) {
                log_warn("Numeric result (%lld) less than subrange (%d..%d) in type declaration",
                        (int64_t) Value->Value.S16,
                        Range->Minimum.S16,
                        Range->Maximum.S16);
                Value->Value.S16 = Range->Minimum.S16;
            }
            break;

        case TYPE_SINT:
            if(Value->Value.S8 > Range->Maximum.S8) {
                log_warn("Numeric result (%lld) greater than subrange (%d..%d) in type declaration",
                        (int64_t) Value->Value.S8,
                        Range->Minimum.S8,
                        Range->Maximum.S8);
                Value->Value.S8 = Range->Maximum.S8;
            }
            if(Value->Value.S8 < Range->Minimum.S8) {
                log_warn("Numeric result (%lld) less than subrange (%d..%d) in type declaration",
                        (int64_t) Value->Value.S8,
                        Range->Minimum.S8,
                        Range->Maximum.S8);
                Value->Value.S8 = Range->Minimum.S8;
            }
            break;

        case TYPE_ULINT:
            if(Value->Value.U64 > Range->Maximum.U64) {
                log_warn("Numeric result (%llu) greater than subrange (%llu..%llu) in type declaration",
                        Value->Value.U64,
                        Range->Minimum.U64,
                        Range->Maximum.U64);
                Value->Value.U64 = Range->Maximum.U64;
            }
            if(Value->Value.U64 < Range->Minimum.U64) {
                log_warn("Numeric result (%llu) less than subrange (%llu..%llu) in type declaration",
                        Value->Value.U64,
                        Range->Minimum.U64,
                        Range->Maximum.U64);
                Value->Value.U64 = Range->Minimum.U64;
            }
            break;

        case TYPE_UDINT:
            if(Value->Value.U32 > Range->Maximum.U32) {
                log_warn("Numeric result (%llu) greater than subrange (%lu..%lu) in type declaration",
                        (uint64_t) Value->Value.U32,
                        Range->Minimum.U32,
                        Range->Maximum.U32);
                Value->Value.U32 = Range->Maximum.U32;
            }
            if(Value->Value.U32 < Range->Minimum.U32) {
                log_warn("Numeric result (%llu) less than subrange (%lu..%lu) in type declaration",
                        (uint64_t) Value->Value.U32,
                        Range->Minimum.U32,
                        Range->Maximum.U32);
                Value->Value.U32 = Range->Minimum.U32;
            }
            break;

        case TYPE_UINT:
            if(Value->Value.U16 > Range->Maximum.U16) {
                log_warn("Numeric result (%llu) greater than subrange (%u..%u) in type declaration",
                        (uint64_t) Value->Value.U16,
                        Range->Minimum.U16,
                        Range->Maximum.U16);
                Value->Value.U16 = Range->Maximum.U16;
            }
            if(Value->Value.U16 < Range->Minimum.U16) {
                log_warn("Numeric result (%llu) less than subrange (%u..%u) in type declaration",
                        (uint64_t) Value->Value.U16,
                        Range->Minimum.U16,
                        Range->Maximum.U16);
                Value->Value.U16 = Range->Minimum.U16;
            }
            break;

        case TYPE_USINT:
            if(Value->Value.U8 > Range->Maximum.U8) {
                log_warn("Numeric result (%llu) greater than subrange (%u..%u) in type declaration",
                        (uint64_t) Value->Value.U8,
                        Range->Minimum.U8,
                        Range->Maximum.U8);
                Value->Value.U8 = Range->Maximum.U8;
            }
            if(Value->Value.U8 < Range->Minimum.U8) {
                log_warn("Numeric result (%llu) less than subrange (%u..%u) in type declaration",
                        (uint64_t) Value->Value.U8,
                        Range->Minimum.U8,
                        Range->Maximum.U8);
                Value->Value.U8 = Range->Minimum.U8;
            }
            break;

        case TYPE_LREAL:
        case TYPE_REAL:
        case TYPE_LWORD:
        case TYPE_DWORD:
        case TYPE_WORD:
        case TYPE_BYTE:
        case TYPE_BOOL:
        default:
            break;
    }
    return 0;
}


