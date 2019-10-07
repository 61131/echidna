#include <stdint.h>
#include <float.h>
#include <math.h>

#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


int
standard_eq(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    uint8_t uResult;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    uResult = 1;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if((uResult = (fabs(sValue.Value.Double - sIn.Value.Double) < DBL_EPSILON)) == 0)
                    goto finish;
                break;

            case TYPE_REAL:
                if((uResult = (fabs(sValue.Value.Single - sIn.Value.Single) < FLT_EPSILON)) == 0)
                    goto finish;
                break;

            case TYPE_LINT:
                if((uResult = (sValue.Value.S64 == sIn.Value.S64)) == 0)
                    goto finish;
                break;

            case TYPE_DINT:
                if((uResult = (sValue.Value.S32 == sIn.Value.S32)) == 0)
                    goto finish;
                break;

            case TYPE_INT:
                if((uResult = (sValue.Value.S16 == sIn.Value.S16)) == 0)
                    goto finish;
                break;

            case TYPE_SINT:
                if((uResult = (sValue.Value.S8 == sIn.Value.S8)) == 0)
                    goto finish;
                break;

            case TYPE_ULINT:
                if((uResult = (sValue.Value.U64 == sIn.Value.U64)) == 0)
                    goto finish;
                break;

            case TYPE_UDINT:
                if((uResult = (sValue.Value.U32 == sIn.Value.U32)) == 0)
                    goto finish;
                break;

            case TYPE_UINT:
                if((uResult = (sValue.Value.U16 == sIn.Value.U16)) == 0)
                    goto finish;
                break;

            case TYPE_USINT:
                if((uResult = (sValue.Value.U8 == sIn.Value.U8)) == 0)
                    goto finish;
                break;

            case TYPE_LWORD:
                if((uResult = (sValue.Value.B64 == sIn.Value.B64)) == 0)
                    goto finish;
                break;

            case TYPE_DWORD:
                if((uResult = (sValue.Value.B32 == sIn.Value.B32)) == 0)
                    goto finish;
                break;

            case TYPE_WORD:
                if((uResult = (sValue.Value.B16 == sIn.Value.B16)) == 0)
                    goto finish;
                break;

            case TYPE_BYTE:
                if((uResult = (sValue.Value.B8 == sIn.Value.B8)) == 0)
                    goto finish;
                break;

            case TYPE_BOOL:
                if((uResult = (sValue.Value.B1 == sIn.Value.B1)) == 0)
                    goto finish;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

finish:
    value_assign(Result, TYPE_BOOL, uResult);
    return 0;
}


int
standard_ge(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    uint8_t uResult;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    uResult = 1;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if((uResult = (sValue.Value.Double >= sIn.Value.Double)) == 0)
                    goto finish;
                break;

            case TYPE_REAL:
                if((uResult = (sValue.Value.Single >= sIn.Value.Single)) == 0)
                    goto finish;
                break;

            case TYPE_LINT:
                if((uResult = (sValue.Value.S64 >= sIn.Value.S64)) == 0)
                    goto finish;
                break;

            case TYPE_DINT:
                if((uResult = (sValue.Value.S32 >= sIn.Value.S32)) == 0)
                    goto finish;
                break;

            case TYPE_INT:
                if((uResult = (sValue.Value.S16 >= sIn.Value.S16)) == 0)
                    goto finish;
                break;

            case TYPE_SINT:
                if((uResult = (sValue.Value.S8 >= sIn.Value.S8)) == 0)
                    goto finish;
                break;

            case TYPE_ULINT:
                if((uResult = (sValue.Value.U64 >= sIn.Value.U64)) == 0)
                    goto finish;
                break;

            case TYPE_UDINT:
                if((uResult = (sValue.Value.U32 >= sIn.Value.U32)) == 0)
                    goto finish;
                break;

            case TYPE_UINT:
                if((uResult = (sValue.Value.U16 >= sIn.Value.U16)) == 0)
                    goto finish;
                break;

            case TYPE_USINT:
                if((uResult = (sValue.Value.U8 >= sIn.Value.U8)) == 0)
                    goto finish;
                break;

            case TYPE_LWORD:
                if((uResult = (sValue.Value.B64 >= sIn.Value.B64)) == 0)
                    goto finish;
                break;

            case TYPE_DWORD:
                if((uResult = (sValue.Value.B32 >= sIn.Value.B32)) == 0)
                    goto finish;
                break;

            case TYPE_WORD:
                if((uResult = (sValue.Value.B16 >= sIn.Value.B16)) == 0)
                    goto finish;
                break;

            case TYPE_BYTE:
                if((uResult = (sValue.Value.B8 >= sIn.Value.B8)) == 0)
                    goto finish;
                break;

            case TYPE_BOOL:
                if((uResult = (sValue.Value.B1 >= sIn.Value.B1)) == 0)
                    goto finish;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

finish:
    value_assign(Result, TYPE_BOOL, uResult);
    return 0;
}


int
standard_gt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    uint8_t uResult;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    uResult = 1;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if((uResult = (sValue.Value.Double > sIn.Value.Double)) == 0)
                    goto finish;
                break;

            case TYPE_REAL:
                if((uResult = (sValue.Value.Single > sIn.Value.Single)) == 0)
                    goto finish;
                break;

            case TYPE_LINT:
                if((uResult = (sValue.Value.S64 > sIn.Value.S64)) == 0)
                    goto finish;
                break;

            case TYPE_DINT:
                if((uResult = (sValue.Value.S32 > sIn.Value.S32)) == 0)
                    goto finish;
                break;

            case TYPE_INT:
                if((uResult = (sValue.Value.S16 > sIn.Value.S16)) == 0)
                    goto finish;
                break;

            case TYPE_SINT:
                if((uResult = (sValue.Value.S8 > sIn.Value.S8)) == 0)
                    goto finish;
                break;

            case TYPE_ULINT:
                if((uResult = (sValue.Value.U64 > sIn.Value.U64)) == 0)
                    goto finish;
                break;

            case TYPE_UDINT:
                if((uResult = (sValue.Value.U32 > sIn.Value.U32)) == 0)
                    goto finish;
                break;

            case TYPE_UINT:
                if((uResult = (sValue.Value.U16 > sIn.Value.U16)) == 0)
                    goto finish;
                break;

            case TYPE_USINT:
                if((uResult = (sValue.Value.U8 > sIn.Value.U8)) == 0)
                    goto finish;
                break;

            case TYPE_LWORD:
                if((uResult = (sValue.Value.B64 > sIn.Value.B64)) == 0)
                    goto finish;
                break;

            case TYPE_DWORD:
                if((uResult = (sValue.Value.B32 > sIn.Value.B32)) == 0)
                    goto finish;
                break;

            case TYPE_WORD:
                if((uResult = (sValue.Value.B16 > sIn.Value.B16)) == 0)
                    goto finish;
                break;

            case TYPE_BYTE:
                if((uResult = (sValue.Value.B8 > sIn.Value.B8)) == 0)
                    goto finish;
                break;

            case TYPE_BOOL:
                if((uResult = (sValue.Value.B1 > sIn.Value.B1)) == 0)
                    goto finish;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

finish:
    value_assign(Result, TYPE_BOOL, uResult);
    return 0;
}


int
standard_le(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    uint8_t uResult;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    uResult = 1;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if((uResult = (sValue.Value.Double <= sIn.Value.Double)) == 0)
                    goto finish;
                break;

            case TYPE_REAL:
                if((uResult = (sValue.Value.Single <= sIn.Value.Single)) == 0)
                    goto finish;
                break;

            case TYPE_LINT:
                if((uResult = (sValue.Value.S64 <= sIn.Value.S64)) == 0)
                    goto finish;
                break;

            case TYPE_DINT:
                if((uResult = (sValue.Value.S32 <= sIn.Value.S32)) == 0)
                    goto finish;
                break;

            case TYPE_INT:
                if((uResult = (sValue.Value.S16 <= sIn.Value.S16)) == 0)
                    goto finish;
                break;

            case TYPE_SINT:
                if((uResult = (sValue.Value.S8 <= sIn.Value.S8)) == 0)
                    goto finish;
                break;

            case TYPE_ULINT:
                if((uResult = (sValue.Value.U64 <= sIn.Value.U64)) == 0)
                    goto finish;
                break;

            case TYPE_UDINT:
                if((uResult = (sValue.Value.U32 <= sIn.Value.U32)) == 0)
                    goto finish;
                break;

            case TYPE_UINT:
                if((uResult = (sValue.Value.U16 <= sIn.Value.U16)) == 0)
                    goto finish;
                break;

            case TYPE_USINT:
                if((uResult = (sValue.Value.U8 <= sIn.Value.U8)) == 0)
                    goto finish;
                break;

            case TYPE_LWORD:
                if((uResult = (sValue.Value.B64 <= sIn.Value.B64)) == 0)
                    goto finish;
                break;

            case TYPE_DWORD:
                if((uResult = (sValue.Value.B32 <= sIn.Value.B32)) == 0)
                    goto finish;
                break;

            case TYPE_WORD:
                if((uResult = (sValue.Value.B16 <= sIn.Value.B16)) == 0)
                    goto finish;
                break;

            case TYPE_BYTE:
                if((uResult = (sValue.Value.B8 <= sIn.Value.B8)) == 0)
                    goto finish;
                break;

            case TYPE_BOOL:
                if((uResult = (sValue.Value.B1 <= sIn.Value.B1)) == 0)
                    goto finish;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

finish:
    value_assign(Result, TYPE_BOOL, uResult);
    return 0;
}


int
standard_lt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    uint8_t uResult;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    uResult = 1;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if((uResult = (sValue.Value.Double < sIn.Value.Double)) == 0)
                    goto finish;
                break;

            case TYPE_REAL:
                if((uResult = (sValue.Value.Single < sIn.Value.Single)) == 0)
                    goto finish;
                break;

            case TYPE_LINT:
                if((uResult = (sValue.Value.S64 < sIn.Value.S64)) == 0)
                    goto finish;
                break;

            case TYPE_DINT:
                if((uResult = (sValue.Value.S32 < sIn.Value.S32)) == 0)
                    goto finish;
                break;

            case TYPE_INT:
                if((uResult = (sValue.Value.S16 < sIn.Value.S16)) == 0)
                    goto finish;
                break;

            case TYPE_SINT:
                if((uResult = (sValue.Value.S8 < sIn.Value.S8)) == 0)
                    goto finish;
                break;

            case TYPE_ULINT:
                if((uResult = (sValue.Value.U64 < sIn.Value.U64)) == 0)
                    goto finish;
                break;

            case TYPE_UDINT:
                if((uResult = (sValue.Value.U32 < sIn.Value.U32)) == 0)
                    goto finish;
                break;

            case TYPE_UINT:
                if((uResult = (sValue.Value.U16 < sIn.Value.U16)) == 0)
                    goto finish;
                break;

            case TYPE_USINT:
                if((uResult = (sValue.Value.U8 < sIn.Value.U8)) == 0)
                    goto finish;
                break;

            case TYPE_LWORD:
                if((uResult = (sValue.Value.B64 < sIn.Value.B64)) == 0)
                    goto finish;
                break;

            case TYPE_DWORD:
                if((uResult = (sValue.Value.B32 < sIn.Value.B32)) == 0)
                    goto finish;
                break;

            case TYPE_WORD:
                if((uResult = (sValue.Value.B16 < sIn.Value.B16)) == 0)
                    goto finish;
                break;

            case TYPE_BYTE:
                if((uResult = (sValue.Value.B8 < sIn.Value.B8)) == 0)
                    goto finish;
                break;

            case TYPE_BOOL:
                if((uResult = (sValue.Value.B1 < sIn.Value.B1)) == 0)
                    goto finish;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

finish:
    value_assign(Result, TYPE_BOOL, uResult);
    return 0;
}


int
standard_ne(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;
    uint8_t uResult;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    uResult = 1;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if((uResult = (sValue.Value.Double != sIn.Value.Double)) == 0)
                    goto finish;
                break;

            case TYPE_REAL:
                if((uResult = (sValue.Value.Single != sIn.Value.Single)) == 0)
                    goto finish;
                break;

            case TYPE_LINT:
                if((uResult = (sValue.Value.S64 != sIn.Value.S64)) == 0)
                    goto finish;
                break;

            case TYPE_DINT:
                if((uResult = (sValue.Value.S32 != sIn.Value.S32)) == 0)
                    goto finish;
                break;

            case TYPE_INT:
                if((uResult = (sValue.Value.S16 != sIn.Value.S16)) == 0)
                    goto finish;
                break;

            case TYPE_SINT:
                if((uResult = (sValue.Value.S8 != sIn.Value.S8)) == 0)
                    goto finish;
                break;

            case TYPE_ULINT:
                if((uResult = (sValue.Value.U64 != sIn.Value.U64)) == 0)
                    goto finish;
                break;

            case TYPE_UDINT:
                if((uResult = (sValue.Value.U32 != sIn.Value.U32)) == 0)
                    goto finish;
                break;

            case TYPE_UINT:
                if((uResult = (sValue.Value.U16 != sIn.Value.U16)) == 0)
                    goto finish;
                break;

            case TYPE_USINT:
                if((uResult = (sValue.Value.U8 != sIn.Value.U8)) == 0)
                    goto finish;
                break;

            case TYPE_LWORD:
                if((uResult = (sValue.Value.B64 != sIn.Value.B64)) == 0)
                    goto finish;
                break;

            case TYPE_DWORD:
                if((uResult = (sValue.Value.B32 != sIn.Value.B32)) == 0)
                    goto finish;
                break;

            case TYPE_WORD:
                if((uResult = (sValue.Value.B16 != sIn.Value.B16)) == 0)
                    goto finish;
                break;

            case TYPE_BYTE:
                if((uResult = (sValue.Value.B8 != sIn.Value.B8)) == 0)
                    goto finish;
                break;

            case TYPE_BOOL:
                if((uResult = (sValue.Value.B1 != sIn.Value.B1)) == 0)
                    goto finish;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

finish:
    value_assign(Result, TYPE_BOOL, uResult);
    return 0;
}


