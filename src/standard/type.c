#include <string.h>
#include <math.h>
#include <errno.h>

#include <cast.h>
#include <echidna.h>
#include <function.h>
#include <ll.h>
#include <log.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


int
standard_bcd(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sValue;
    uint64_t uInput, uResult;
    char *pPtr, sName[32];
    int nCount, nIndex;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return ERROR_PARAMETER_COUNT;

    strcpy(sName, Name);
    if((pPtr = strchr(sName, '_')) == NULL)
        return -1;
    *pPtr++ = '\0';
    if(value_strtotype(&sValue, sName) != 0)
        return -1;
    if(sValue.Type != pParameter->Value.Type)
        return ERROR_PARAMETER_TYPE;

    /*
        The following determines the number of nibbles to be processed as part of the 
        binary-coded decimal conversion process.
    */

    uResult = 0;
    nCount = (value_typetosize(pParameter->Value.Type) << 1);

    switch(pParameter->Value.Type) {
        case TYPE_LWORD:        uInput = pParameter->Value.Value.B64; if(0) {
        case TYPE_DWORD:        uInput = pParameter->Value.Value.B32; } if(0) {
        case TYPE_WORD:         uInput = pParameter->Value.Value.B16; } if(0) {
        case TYPE_BYTE:         uInput = pParameter->Value.Value.B8; }
            for(nIndex = 0; nIndex < nCount; ++nIndex) {
                uResult += ((uInput & 0x0f) * (long unsigned int) pow(10, nIndex));
                uInput >>= 4;
            }
            break;

        case TYPE_ULINT:        uInput = pParameter->Value.Value.U64; if(0) {
        case TYPE_UDINT:        uInput = pParameter->Value.Value.U32; } if(0) {
        case TYPE_UINT:         uInput = pParameter->Value.Value.U16; } if(0) {
        case TYPE_USINT:        uInput = pParameter->Value.Value.U8; }
            for(nIndex = (nCount - 1); nIndex >= 0; --nIndex) {
                uResult <<= 4;
                uResult |= ((uInput / (long unsigned int) pow(10, nIndex)) % 10);
            }
            break;

        default:
            return ERROR_PARAMETER_TYPE;
    }

    switch(pParameter->Value.Type) {
        case TYPE_LWORD:        value_assign(Result, TYPE_ULINT, uResult); break;
        case TYPE_DWORD:        value_assign(Result, TYPE_UDINT, uResult); break;
        case TYPE_WORD:         value_assign(Result, TYPE_UINT, uResult); break;
        case TYPE_BYTE:         value_assign(Result, TYPE_USINT, uResult); break;
        case TYPE_ULINT:        value_assign(Result, TYPE_LWORD, uResult); break;
        case TYPE_UDINT:        value_assign(Result, TYPE_DWORD, uResult); break;
        case TYPE_UINT:         value_assign(Result, TYPE_WORD, uResult); break;
        case TYPE_USINT:        value_assign(Result, TYPE_BYTE, uResult); break;
        default:
            return ERROR_PARAMETER_TYPE;
    }

    return 0;
}


int
standard_trunc(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return ERROR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return ERROR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            modf(pParameter->Value.Value.Double, &Result->Value.Double);
            break;

        case TYPE_REAL:
            modff(pParameter->Value.Value.Single, &Result->Value.Single);
            break;

        default:
            return ERROR_PARAMETER_TYPE;
    }
    if(errno != 0)
        return ERROR_MATH_OVERFLOW;

    return 0;
}


int 
standard_type(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sValue;
    char *pPtr;

    /*
        Note that the source variable type is not validated against the function name 
        such that ANY_TO_* functions can be supported.
    */

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return -1;
    value_copy(Result, &pParameter->Value);

    if((pPtr = strrchr(Name, '_')) == NULL) 
        return -1;
    ++pPtr;
    if(value_strtotype(&sValue, pPtr) != 0)
        return -1;
    switch(sValue.Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:        return cast_lreal(Result);
        case TYPE_REAL:         return cast_real(Result);
        case TYPE_LINT:         return cast_lint(Result);
        case TYPE_DINT:         return cast_dint(Result);
        case TYPE_INT:          return cast_int(Result);
        case TYPE_SINT:         return cast_sint(Result);
        case TYPE_ULINT:        return cast_ulint(Result);
        case TYPE_UDINT:        return cast_udint(Result);
        case TYPE_UINT:         return cast_uint(Result);
        case TYPE_USINT:        return cast_usint(Result);
        case TYPE_LWORD:        return cast_lword(Result);
        case TYPE_DWORD:        return cast_dword(Result);
        case TYPE_WORD:         return cast_word(Result);
        case TYPE_BYTE:         return cast_byte(Result);
        case TYPE_BOOL:         return cast_bool(Result);
        case TYPE_TIME:         return cast_time(Result);
        default:
            return -1;
    }
}


