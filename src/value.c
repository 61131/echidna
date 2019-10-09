#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <assert.h>

#include <cast.h>
#include <log.h>
#include <value.h>


void
_value_assign(size_t Arg, ...) {
    VALUE *pValue;
    VALUE_TYPE uType;
    va_list sArg;
    char *pStr;

    if(Arg < 2)
        return;
    va_start(sArg, Arg);
    for(;;) {
        if((pValue = va_arg(sArg, VALUE *)) == NULL)
            break;
        value_initialise(pValue);
        uType = va_arg(sArg, VALUE_TYPE);

        switch(uType) {
            case ANY_NUM:
            case ANY_REAL:
            case TYPE_LREAL:
                pValue->Length = sizeof(pValue->Value.Double);
                pValue->Maximum.Double = DBL_MAX;
                pValue->Minimum.Double = DBL_MIN;
                if(Arg > 2)
                    pValue->Value.Double = (double) va_arg(sArg, double);
                else
                    pValue->Value.Double = 0.0;
                break;

            case TYPE_REAL:
                //  warning: 'float' is promoted to 'double' when passed through '...'
                pValue->Length = sizeof(pValue->Value.Single);
                pValue->Maximum.Single = FLT_MAX;
                pValue->Minimum.Single = FLT_MIN;
                if(Arg > 2)
                    pValue->Value.Single = (float) va_arg(sArg, double);
                else
                    pValue->Value.Single = 0.0f;
                break;

            case ANY_INT:
            case TYPE_LINT:
                pValue->Length = sizeof(pValue->Value.S64);
                pValue->Maximum.S64 = INT64_MAX;
                pValue->Minimum.S64 = INT64_MIN;
                if(Arg > 2)
                    pValue->Value.S64 = (int64_t) va_arg(sArg, int);
                else
                    pValue->Value.S64 = 0LL;
                break;

            case TYPE_DINT:
                pValue->Length = sizeof(pValue->Value.S32);
                pValue->Maximum.S32 = INT32_MAX;
                pValue->Minimum.S32 = INT32_MIN;
                if(Arg > 2)
                    pValue->Value.S32 = (int32_t) va_arg(sArg, int);
                else 
                    pValue->Value.S32 = 0L;
                break;

            case TYPE_INT:
                pValue->Length = sizeof(pValue->Value.S16);
                pValue->Maximum.S16 = INT16_MAX;
                pValue->Minimum.S16 = INT16_MIN;
                //  warning: 'int16_t {aka short int}' is promoted to 'int' when passed through '...'
                if(Arg > 2)
                    pValue->Value.S16 = (int16_t) va_arg(sArg, int);
                else
                    pValue->Value.S16 = 0;
                break;

            case TYPE_SINT:
                pValue->Length = sizeof(pValue->Value.S8);
                pValue->Maximum.S8 = INT8_MAX;
                pValue->Minimum.S8 = INT8_MIN;
                //  warning: 'int8_t {aka signed char}' is promoted to 'int' when passed through '...'
                if(Arg > 2)
                    pValue->Value.S8 = (int8_t) va_arg(sArg, int);
                else 
                    pValue->Value.S8 = 0;
                break;

            case TYPE_ULINT:
                pValue->Length = sizeof(pValue->Value.U64);
                pValue->Maximum.U64 = UINT64_MAX;
                pValue->Minimum.U64 = 0;
                if(Arg > 2)
                    pValue->Value.U64 = (uint64_t) va_arg(sArg, int);
                else
                    pValue->Value.U64 = 0ULL;
                break;

            case TYPE_UDINT:
                pValue->Length = sizeof(pValue->Value.U32);
                pValue->Maximum.U32 = UINT32_MAX;
                pValue->Minimum.U32 = 0;
                if(Arg > 2)
                    pValue->Value.U32 = (uint32_t) va_arg(sArg, int);
                else
                    pValue->Value.U32 = 0UL;
                break;

            case TYPE_UINT:
                pValue->Length = sizeof(pValue->Value.U16);
                pValue->Maximum.U16 = UINT16_MAX;
                pValue->Minimum.U16 = 0;
                //  warning: 'uint16_t {aka short unsigned int}' is promoted to 'int' when passed through '...'
                if(Arg > 2)
                    pValue->Value.U16 = (uint16_t) va_arg(sArg, int);
                else
                    pValue->Value.U16 = 0U;
                break;

            case TYPE_USINT:
                pValue->Length = sizeof(pValue->Value.U8);
                pValue->Maximum.U8 = UINT8_MAX;
                pValue->Minimum.U8 = 0;
                //  warning: 'uint8_t {aka unsigned char}' is promoted to 'int' when passed through '...'
                if(Arg > 2)
                    pValue->Value.U8 = (uint8_t) va_arg(sArg, int);
                else
                    pValue->Value.U8 = 0U;
                break;

            case ANY_BIT:
            case TYPE_LWORD:
                pValue->Length = sizeof(pValue->Value.B64);
                pValue->Maximum.B64 = UINT64_MAX;
                pValue->Minimum.B64 = 0;
                if(Arg > 2)
                    pValue->Value.B64 = (uint64_t) va_arg(sArg, int);
                else
                    pValue->Value.B64 = 0ULL;
                break;

            case TYPE_DWORD:
                pValue->Length = sizeof(pValue->Value.B32);
                pValue->Maximum.B32 = UINT32_MAX;
                pValue->Minimum.B32 = 0;
                if(Arg > 2)
                    pValue->Value.B32 = (uint32_t) va_arg(sArg, int);
                else
                    pValue->Value.B32 = 0UL;
                break;

            case TYPE_WORD:
                pValue->Length = sizeof(pValue->Value.B16);
                pValue->Maximum.B16 = UINT16_MAX;
                pValue->Minimum.B16 = 0;
                //  warning: 'uint16_t {aka short unsigned int}' is promoted to 'int' when passed through '...'
                if(Arg > 2)
                    pValue->Value.B16 = (uint16_t) va_arg(sArg, int);
                else
                    pValue->Value.B16 = 0U;
                break;

            case TYPE_BYTE:
                pValue->Length = sizeof(pValue->Value.B8);
                pValue->Maximum.B8 = UINT8_MAX;
                pValue->Minimum.B8 = 0;
                //  warning: 'uint8_t {aka unsigned char}' is promoted to 'int' when passed through '...'
                if(Arg > 2)
                    pValue->Value.B8 = (uint8_t) va_arg(sArg, int);
                else
                    pValue->Value.B8 = 0U;
                break;
 
             case TYPE_BOOL:
                //  error: 'sizeof' applied to a bit-field
                pValue->Length = sizeof(uint8_t);
                pValue->Maximum.B1 = 1;
                pValue->Minimum.B1 = 0;
                //  error: 'typeof' applied to a bit-field
                //  warning: 'uint8_t {aka unsigned char}' is promoted to 'int' when passed through '...'
                if(Arg > 2) {
                    pValue->Value.B1 = (uint8_t) va_arg(sArg, int);
                    pValue->Value.B1 &= 1;
                }
                else
                    pValue->Value.B1 = 0U;
                break;
           
            case TYPE_TIME:
                //  warning: 'float' is promoted to 'double' when passed through '...'
                pValue->Length = sizeof(pValue->Value.Time);
                pValue->Maximum.Time = FLT_MAX;
                pValue->Minimum.Time = FLT_MIN;
                if(Arg > 2)
                    pValue->Value.Time = (float) va_arg(sArg, double);
                else
                    pValue->Value.Time = 0.0f;
                break;

            case TYPE_ENUMERATED:
            case TYPE_FUNCTION:
            case TYPE_FUNCTION_BLOCK:
            case TYPE_LABEL:
            case _TYPE_PROGRAM:
                pValue->Length = 0;
                pValue->Meta = NULL;
                if(Arg > 2) {
                    if((pStr = va_arg(sArg, char *)) != NULL)
                        pValue->Meta = strdup(pStr);
                }
                break;

            case TYPE_NONE:
                pValue->Length = 0;
                pValue->Value.B64 = 0;
                pValue->Maximum.B64 = 0;
                pValue->Minimum.B64 = 0;
                break;

            case TYPE_STRING:
            case TYPE_WSTRING:
            default:
                log_error("Unhandled type: %08x [%s:%u]", uType, __FILE__, __LINE__);
                assert(0);
                break;
        }

        pValue->Type = pValue->Cast = uType;
        break;
    }
    va_end(sArg);
}


int
_value_cast(size_t Arg, VALUE *Value, VALUE_TYPE Type, ...) {
    VALUE *pCopy;
    va_list sArg;

    if(!Value)
        return -EINVAL;
    
    /*
        This arrangement allows for values to be copied and cast within a single 
        function call from the grammar source file.
    */

    if(Arg > 2) {
        for(;;) {
            va_start(sArg, Type);
            if((pCopy = va_arg(sArg, VALUE *)) == NULL)
                break;
            value_copy(Value, pCopy);
            break;
        }
        va_end(sArg);
    }

    if((Value->Type == Type) ||
            (Value->Cast == Type))
        return 0;

    Type &= ~ANY_INTERNAL;
    switch(Type) {
        case TYPE_LREAL:        return cast_lreal(Value);
        case TYPE_REAL:         return cast_real(Value);
        case TYPE_LINT:         return cast_lint(Value);
        case TYPE_DINT:         return cast_dint(Value);
        case TYPE_INT:          return cast_int(Value);
        case TYPE_SINT:         return cast_sint(Value);
        case TYPE_ULINT:        return cast_ulint(Value);
        case TYPE_UDINT:        return cast_udint(Value);
        case TYPE_UINT:         return cast_uint(Value);
        case TYPE_USINT:        return cast_usint(Value);
        case TYPE_TIME:         return cast_time(Value);
        case TYPE_LWORD:        return cast_lword(Value);
        case TYPE_DWORD:        return cast_dword(Value);
        case TYPE_WORD:         return cast_word(Value);
        case TYPE_BYTE:         return cast_byte(Value);
        case TYPE_BOOL:         return cast_bool(Value);
        case ANY:
        case ANY_DERIVED:
        case ANY_ELEMENTARY:
        case ANY_MAGNITUDE:
        case ANY_NUM:
        case ANY_REAL:
        case ANY_INT:
        case ANY_BIT:
        case ANY_STRING:
        case ANY_DATE:
        case TYPE_NONE:         
            return 0;
        default:
            log_critical("%s: %08x", __func__, Type);
            assert(0);
    }

    return 0;
}


void
_value_destroy(size_t Arg, VALUE *Value, ...) {
    void (*pDestroy)(void *);
    va_list sArg;

    if(!Value)
        return;

    va_start(sArg, Value);
    if(Arg > 1)
        pDestroy = va_arg(sArg, void (*)(void *));
    else
        pDestroy = NULL;
    va_end(sArg);
    
    if(Value->Flags & FLAG_ARRAY) {
        if(pDestroy) 
            (pDestroy)(Value->Value.Pointer);
        Value->Value.Pointer = NULL;
    }

    if(Value->Meta) {
        free(Value->Meta);
        Value->Meta = NULL;
    }
}


int 
value_allocate(VALUE *Value, VALUE_TYPE Type, size_t Length) {
    if(!Value)
        return -EINVAL;

    errno = 0;
    if((Value->Value.Pointer = calloc(Length, sizeof(char))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return errno;
    }
    Value->Type = Type;
    Value->Length = Length;
    return 0;
}


int
value_copy(VALUE *Dest, VALUE *Src) {
    assert(Dest != NULL);
    assert(Src != NULL);
    memcpy(Dest, Src, sizeof(VALUE));
    if(Src->Meta) {
        Dest->Meta = strdup(Src->Meta);
//log_debug("%s: [%p] %s", __func__, Dest->Meta, Dest->Meta);
    }

    return 0;
}


void
value_initialise(VALUE *Value) {
    if(!Value)
        return;
    Value->Type = TYPE_NONE;
    Value->Flags = FLAG_NONE;
    Value->Length = 0;
    Value->Index.Lower = 0;
    Value->Index.Upper = 0;
    Value->Maximum.S64 = 0;
    Value->Minimum.S64 = 0;
    Value->Value.S64 = 0;
    Value->Meta = NULL;
}


int
value_istype(VALUE *Value, VALUE_TYPE Type) {
    assert(Value != NULL);
    if((Value->Type & Type) == Value->Type)
        return 1;
    if((Value->Type == TYPE_DERIVED) &&
            ((Value->Cast & Type) == Value->Cast))
        return 1;

    return 0;
}


int
value_strtotype(VALUE *Value, char *Str) {
    assert(Value != NULL);
    assert(Str != NULL);

    value_initialise(Value);
    if(strcasecmp(Str, "LREAL") == 0) {
        Value->Type = TYPE_LREAL;
        Value->Length = sizeof(Value->Value.Double);
        Value->Maximum.Double = DBL_MAX;
        Value->Minimum.Double = DBL_MIN;
        Value->Value.Double = 0.0;
    }
    else if(strcasecmp(Str, "REAL") == 0) {
        Value->Type = TYPE_REAL;
        Value->Length = sizeof(Value->Value.Single);
        Value->Maximum.Single = FLT_MAX;
        Value->Minimum.Single = FLT_MIN;
        Value->Value.Single = 0.0f;
    }
    else if(strcasecmp(Str, "LINT") == 0) {
        Value->Type = TYPE_LINT;
        Value->Length = sizeof(Value->Value.S64);
        Value->Maximum.S64 = INT64_MAX;
        Value->Minimum.S64 = INT64_MIN;
        Value->Value.S64 = 0;
    }
    else if(strcasecmp(Str, "DINT") == 0) {
        Value->Type = TYPE_DINT;
        Value->Length = sizeof(Value->Value.S32);
        Value->Maximum.S32 = INT32_MAX;
        Value->Minimum.S32 = INT32_MIN;
        Value->Value.S32 = 0;
    }
    else if(strcasecmp(Str, "INT") == 0) {
        Value->Type = TYPE_INT;
        Value->Length = sizeof(Value->Value.S16);
        Value->Maximum.S16 = INT16_MAX;
        Value->Minimum.S16 = INT16_MIN;
        Value->Value.S16 = 0;
    }
    else if(strcasecmp(Str, "SINT") == 0) {
        Value->Type = TYPE_SINT;
        Value->Length = sizeof(Value->Value.S8);
        Value->Maximum.S8 = INT8_MAX;
        Value->Minimum.S8 = INT8_MIN;
        Value->Value.S8 = 0;
    }
    else if(strcasecmp(Str, "ULINT") == 0) {
        Value->Type = TYPE_ULINT;
        Value->Length = sizeof(Value->Value.U64);
        Value->Maximum.U64 = UINT64_MAX;
        Value->Minimum.U64 = Value->Value.U64 = 0;
    }
    else if(strcasecmp(Str, "UDINT") == 0) {
        Value->Type = TYPE_UDINT;
        Value->Length = sizeof(Value->Value.U32);
        Value->Maximum.U32 = UINT32_MAX;
        Value->Minimum.U32 = Value->Value.U32 = 0;
    }
    else if(strcasecmp(Str, "UINT") == 0) {
        Value->Type = TYPE_UINT;
        Value->Length = sizeof(Value->Value.U16);
        Value->Maximum.U16 = UINT16_MAX;
        Value->Minimum.U16 = Value->Value.U16 = 0;
    }
    else if(strcasecmp(Str, "USINT") == 0) {
        Value->Type = TYPE_USINT;
        Value->Length = sizeof(Value->Value.U8);
        Value->Maximum.U8 = UINT8_MAX;
        Value->Minimum.U8 = Value->Value.U8 = 0;
    }
    else if(strcasecmp(Str, "LWORD") == 0) {
        Value->Type = TYPE_LWORD;
        Value->Length = sizeof(Value->Value.B64);
        Value->Maximum.B64 = UINT64_MAX;
        Value->Minimum.B64 = Value->Value.B64 = 0;
    }
    else if(strcasecmp(Str, "DWORD") == 0) {
        Value->Type = TYPE_DWORD;
        Value->Length = sizeof(Value->Value.B32);
        Value->Maximum.B32 = UINT32_MAX;
        Value->Minimum.B32 = Value->Value.B32 = 0;
    }
    else if(strcasecmp(Str, "WORD") == 0) {
        Value->Type = TYPE_WORD;
        Value->Length = sizeof(Value->Value.B16);
        Value->Maximum.B16 = UINT16_MAX;
        Value->Minimum.B16 = Value->Value.B16 = 0;
    }
    else if(strcasecmp(Str, "BYTE") == 0) {
        Value->Type = TYPE_BYTE;
        Value->Length = sizeof(Value->Value.B8);
        Value->Maximum.B8 = UINT8_MAX;
        Value->Minimum.B8 = Value->Value.B8 = 0;
    }
    else if(strcasecmp(Str, "BOOL") == 0) {
        Value->Type = TYPE_BOOL;
        //  error: 'sizeof' applied to a bit-field
        Value->Length = sizeof( uint8_t );
        Value->Maximum.B1 = 1;
        Value->Minimum.B1 = Value->Value.B1 = 0;
    }
    else if(strcasecmp(Str, "TRUE") == 0) {
        Value->Type = TYPE_BOOL;
        //  error: 'sizeof' applied to a bit-field
        Value->Length = sizeof(uint8_t);
        Value->Maximum.B1 = Value->Minimum.B1 = Value->Value.B1 = 1;
    }
    else if(strcasecmp(Str, "FALSE") == 0) {
        Value->Type = TYPE_BOOL;
        //  error: 'sizeof' applied to a bit-field
        Value->Length = sizeof(uint8_t);
        Value->Maximum.B1 = Value->Minimum.B1 = Value->Value.B1 = 0;
    }
    else if(strcasecmp(Str, "TIME") == 0) {
        Value->Type = TYPE_TIME;
        Value->Length = sizeof(Value->Value.Time);
        Value->Maximum.Time = FLT_MAX;
        Value->Minimum.Time = FLT_MIN;
        Value->Value.Time = 0.0f;
    }
    else
        return -1;

    return 0;
}

int
value_strtoval(VALUE *Value, VALUE_TYPE Type, char *Str /*, uint8_t Base = 10 */) {
    char sValue[LINE_MAX];
    char *pStart;
    int nBase, nLength;

    if(!Value)
        return -1;
    Value->Length = 0;
    Value->Type = Value->Cast = TYPE_NONE;

    /*
        Single underline characters (_) inserted between the digits of a numeric 
        literal shall not be significant. No other use of underline characters in 
        numeric literals is allowed.
    */

    Type &= ~ANY_INTERNAL;
    switch(Type) {
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
            if(!strchr(Str, '_'))
                break;

            sValue[0] = '\0';
            for(; *Str; ++Str) {
                if(*Str == '_')
                    continue;
                nLength = strlen(sValue);
                if((unsigned) nLength >= sizeof(sValue))
                    return -1;
                sValue[nLength + 1] = '\0';
                sValue[nLength] = *Str;
            }
            Str = sValue;
            break;

        default:
            break;
    }

    /*
        Integer literals can also be represented in base 2, 8, or 16. The base shall 
        be in decimal notation. For base 16, an extended set of digits consisting of 
        the letters A through F shall be used, with the conventional significance of 
        decimal 10 through 15, respectively. Based numbers shall not contain a 
        leading sign (+ or -).
    */            

    nBase = 10;
    switch(Type) {
        case TYPE_LINT:
        case TYPE_DINT:
        case TYPE_INT:
        case TYPE_SINT:
        case TYPE_ULINT:
        case TYPE_UDINT:
        case TYPE_UINT:
        case TYPE_USINT:
            if(!(pStart = strchr(Str, '#')))
                break;
            ++pStart;
            if(*pStart == '\0')
                break;
            nBase = strtol(Str, NULL, 10);
            switch(nBase) {
                case 2:
                case 8:
                case 10:
                case 16:
                    break;

                default:
                    return -1;
            }
            Str = pStart;
            break;

        default:
            break;
    }

    switch(Type) {
        case TYPE_LREAL:
            Value->Length = sizeof(Value->Value.Double);
            Value->Maximum.Double = DBL_MAX;
            Value->Minimum.Double = DBL_MIN;
            Value->Value.Double = (double) strtod(Str, NULL);
            break;

        case TYPE_REAL:
            Value->Length = sizeof(Value->Value.Single);
            Value->Maximum.Single = FLT_MAX;
            Value->Minimum.Single = FLT_MIN;
            Value->Value.Single = (float) strtof(Str, NULL);
            break;

        case TYPE_LINT:
            Value->Length = sizeof(Value->Value.S64);
            Value->Maximum.S64 = INT64_MAX;
            Value->Minimum.S64 = INT64_MIN;            
            Value->Value.S64 = (int64_t) strtoll(Str, NULL, nBase);
            break;

        case TYPE_DINT:
            Value->Length = sizeof(Value->Value.S32);
            Value->Maximum.S32 = INT32_MAX;
            Value->Minimum.S32 = INT32_MIN;
            Value->Value.S32 = (int32_t) strtol(Str, NULL, nBase);
            break;

        case TYPE_INT:
            Value->Length = sizeof(Value->Value.S16);
            Value->Maximum.S16 = INT16_MAX;
            Value->Minimum.S16 = INT16_MIN;
            Value->Value.S16 = (int16_t) strtol(Str, NULL, nBase);
            break;

        case TYPE_SINT:
            Value->Length = sizeof(Value->Value.S8);
            Value->Maximum.S8 = INT8_MAX;
            Value->Minimum.S8 = INT8_MIN;        
            Value->Value.S8 = (int8_t) strtol(Str, NULL, nBase);
            break;

        case TYPE_ULINT:
            Value->Length = sizeof(Value->Value.U64);
            Value->Maximum.U64 = UINT64_MAX;
            Value->Minimum.U64 = 0;
            Value->Value.U64 = (uint64_t) strtoull(Str, NULL, nBase);
            break;

        case TYPE_UDINT:
            Value->Length = sizeof(Value->Value.U32);
            Value->Maximum.U32 = UINT32_MAX;
            Value->Minimum.U32 = 0;
            Value->Value.U32 = (uint32_t) strtoul(Str, NULL, nBase);
            break;

        case TYPE_UINT:
            Value->Length = sizeof(Value->Value.U16);
            Value->Maximum.U16 = UINT16_MAX;
            Value->Minimum.U16 = 0;
            Value->Value.U16 = (uint16_t) strtoul(Str, NULL, nBase);
            break;

        case TYPE_USINT:
            Value->Length = sizeof(Value->Value.U8);
            Value->Maximum.U8 = UINT8_MAX;
            Value->Minimum.U8 = 0;
            Value->Value.U8 = (uint8_t) strtoul(Str, NULL, nBase);
            break;

        case TYPE_LWORD:
            Value->Length = sizeof(Value->Value.B64);
            Value->Maximum.B64 = UINT64_MAX;
            Value->Minimum.B64 = 0;
            Value->Value.B64 = (uint64_t) strtoul(Str, NULL, 10);
            break;

        case TYPE_DWORD:
            Value->Length = sizeof(Value->Value.B32);
            Value->Maximum.B32 = UINT32_MAX;
            Value->Minimum.B32 = 0;
            Value->Value.B32 = (uint32_t) strtoul(Str, NULL, 10);
            break;

        case TYPE_WORD:
            Value->Length = sizeof(Value->Value.B16);
            Value->Maximum.B16 = UINT16_MAX;
            Value->Minimum.B16 = 0;
            Value->Value.B16 = (uint16_t) strtoul(Str, NULL, 10);
            break;

        case TYPE_BYTE:
            Value->Length = sizeof(Value->Value.B8);
            Value->Maximum.B8 = UINT8_MAX;
            Value->Minimum.B8 = 0;
            Value->Value.B8 = (uint8_t) strtoul(Str, NULL, 10);
            break;

        case TYPE_BOOL:
            //  error: 'sizeof' applied to a bit-field
            Value->Length = sizeof(uint8_t);
            Value->Maximum.B1 = 1;
            Value->Minimum.B1 = 0;
            //  error: 'typeof' applied to a bit-field
            Value->Value.B1 = (uint8_t) (strtoul(Str, NULL, 10) > 0);
            break;

        case TYPE_TIME:
            Value->Length = sizeof(Value->Value.Time);
            Value->Maximum.Time = FLT_MAX;
            Value->Minimum.Time = FLT_MIN;
            Value->Value.Time = (float) strtof(Str, NULL);
            break;

        case TYPE_DATE:
        case TYPE_DT:
        case TYPE_TOD:
        default:
            return -1;
    }

    Value->Type = Value->Cast = Type;
    return 0;
}


int
value_typetosize(VALUE_TYPE Type) {
    VALUE sValue;

    switch(Type) {
        case TYPE_INPUT:
        case TYPE_IN_OUT:
        case TYPE_OUTPUT:       return 0;
        case TYPE_LABEL:        return sizeof(uint32_t);
        default:
            break;
    }

    switch(Type & ~ANY_INTERNAL) {
        case ANY_NUM:           //  Assume maximum size
        case ANY_REAL:          //  Assume maximum size
        case TYPE_LREAL:        return sizeof(sValue.Value.Double);
        case TYPE_REAL:         return sizeof(sValue.Value.Single);
        case ANY_INT:           //  Assume maximum size
        case TYPE_LINT:         return sizeof(sValue.Value.S64);
        case TYPE_DINT:         return sizeof(sValue.Value.S32);
        case TYPE_INT:          return sizeof(sValue.Value.S16);
        case TYPE_SINT:         return sizeof(sValue.Value.S8);
        case TYPE_ULINT:        return sizeof(sValue.Value.U64);
        case TYPE_UDINT:        return sizeof(sValue.Value.U32);
        case TYPE_UINT:         return sizeof(sValue.Value.U16);
        case TYPE_USINT:        return sizeof(sValue.Value.U8);
        case TYPE_LWORD:        return sizeof(sValue.Value.B64);
        case TYPE_DWORD:        return sizeof(sValue.Value.B32);
        case TYPE_WORD:         return sizeof(sValue.Value.B16);
        case TYPE_BYTE:         return sizeof(sValue.Value.B8);
        case TYPE_BOOL:         return sizeof(sValue.Value.B1);
        case TYPE_TIME:         return sizeof(sValue.Value.Time);
        default:
            return -1;
    }
}


const char * 
value_typetostr(VALUE_TYPE Type) {
    uint32_t uMask;

    uMask = /* TYPE_INTERNAL | */
            TYPE_ARRAY |
            TYPE_DERIVED |
            TYPE_ENUMERATED |
            TYPE_SUBRANGE |
            TYPE_STRUCTURED;

    switch(Type & ~uMask) {
        case TYPE_NONE:         return "(NONE)";
        case TYPE_LREAL:        return "LREAL";
        case TYPE_REAL:         return "REAL";
        case TYPE_LINT:         return "LINT";
        case TYPE_DINT:         return "DINT";
        case TYPE_INT:          return "INT";
        case TYPE_SINT:         return "SINT";
        case TYPE_ULINT:        return "ULINT";
        case TYPE_UDINT:        return "UDINT";
        case TYPE_UINT:         return "UINT";
        case TYPE_USINT:        return "USINT";
        case TYPE_LWORD:        return "LWORD";
        case TYPE_DWORD:        return "DWORD";
        case TYPE_WORD:         return "WORD";
        case TYPE_BYTE:         return "BYTE";
        case TYPE_BOOL:         return "BOOL";
        case TYPE_TIME:         return "TIME";
        case TYPE_DATE:         return "DATE";
        case TYPE_DT:           return "DATE_AND_TIME";
        case TYPE_TOD:          return "TIME_OF_DAY";
        case TYPE_FUNCTION_BLOCK:   return "FUNCTION_BLOCK";
        case TYPE_FUNCTION:     return "FUNCTION";
        case TYPE_LABEL:        return "LABEL";
        case _TYPE_PROGRAM:     return "PROGRAM";
        default:
            return "(ERROR)";
    }
}

