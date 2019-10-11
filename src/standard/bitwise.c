#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


int
standard_and(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            if((pParameter->Value.Type & ANY_BIT) == 0)
                return ERROR_PARAMETER_TYPE;
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LWORD:
                sValue.Value.B64 &= sIn.Value.B64;
                break;

            case TYPE_DWORD:
                sValue.Value.B32 &= sIn.Value.B32;
                break;

            case TYPE_WORD:
                sValue.Value.B16 &= sIn.Value.B16;
                break;

            case TYPE_BYTE:
                sValue.Value.B8 &= sIn.Value.B8;
                break;

            case TYPE_BOOL:
                sValue.Value.B1 &= sIn.Value.B1;
                break;


            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    return 0;
}


int
standard_or(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            if((pParameter->Value.Type & ANY_BIT) == 0)
                return ERROR_PARAMETER_TYPE;
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LWORD:
                sValue.Value.B64 |= sIn.Value.B64;
                break;

            case TYPE_DWORD:
                sValue.Value.B32 |= sIn.Value.B32;
                break;

            case TYPE_WORD:
                sValue.Value.B16 |= sIn.Value.B16;
                break;

            case TYPE_BYTE:
                sValue.Value.B8 |= sIn.Value.B8;
                break;

            case TYPE_BOOL:
                sValue.Value.B1 |= sIn.Value.B1;
                break;


            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    return 0;
}


int
standard_xor(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            if((pParameter->Value.Type & ANY_BIT) == 0)
                return ERROR_PARAMETER_TYPE;
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LWORD:
                sValue.Value.B64 ^= sIn.Value.B64;
                break;

            case TYPE_DWORD:
                sValue.Value.B32 ^= sIn.Value.B32;
                break;

            case TYPE_WORD:
                sValue.Value.B16 ^= sIn.Value.B16;
                break;

            case TYPE_BYTE:
                sValue.Value.B8 ^= sIn.Value.B8;
                break;

            case TYPE_BOOL:
                sValue.Value.B1 ^= sIn.Value.B1;
                break;


            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    return 0;
}

