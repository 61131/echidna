#include <string.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>

#include <cast.h>
#include <echidna.h>
#include <function.h>
#include <ll.h>
#include <operator.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


int
standard_limit(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sMax, sMin;
    size_t uParameter;

    Result->Type = TYPE_NONE;
    value_initialise(&sIn);
    value_initialise(&sMax);
    value_initialise(&sMin);

    uParameter = 0;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(pParameter->Name) {
            if(strcasecmp(pParameter->Name, "IN") == 0)
                value_copy(&sIn, &pParameter->Value);
            else if((strcasecmp(pParameter->Name, "MX") == 0) ||
                    (strcasecmp(pParameter->Name, "MAX") == 0))
                value_copy(&sMax, &pParameter->Value);
            else if((strcasecmp(pParameter->Name, "MN") == 0) ||
                    (strcasecmp(pParameter->Name, "MIN") == 0))
                value_copy(&sMin, &pParameter->Value);
        }
        else {
            switch(uParameter++) {
                case 0:     value_copy(&sMin, &pParameter->Value); break;
                case 1:     value_copy(&sIn, &pParameter->Value); break;
                case 2:     value_copy(&sMax, &pParameter->Value); break;
                default:
                    return ERROR_PARAMETER_COUNT;
            }
        }
    }

    if((sIn.Type == TYPE_NONE) ||
            (sMax.Type == TYPE_NONE) ||
            (sMin.Type == TYPE_NONE))
        return ERROR_PARAMETER_COUNT;
    /* assert(sIn.Type == sMax.Type); */
    /* assert(sMax.Type == sMin.Type); */
    if((value_cast(&sMax, sIn.Type) != 0) ||
            (value_cast(&sMin, sIn.Type) != 0))
        return ERROR_PARAMETER_TYPE;

    switch(sIn.Type) {
        case TYPE_LREAL:
            if(sIn.Value.Double < sMin.Value.Double)
                sIn.Value.Double = sMin.Value.Double;
            if(sIn.Value.Double > sMax.Value.Double)
                sIn.Value.Double = sMax.Value.Double;
            break;

        case TYPE_REAL:
            if(sIn.Value.Single < sMin.Value.Single)
                sIn.Value.Single = sMin.Value.Single;
            if(sIn.Value.Single > sMax.Value.Single)
                sIn.Value.Single = sMax.Value.Single;
            break;

        case TYPE_LINT:
            if(sIn.Value.S64 < sMin.Value.S64)
                sIn.Value.S64 = sMin.Value.S64;
            if(sIn.Value.S64 > sMax.Value.S64)
                sIn.Value.S64 = sMax.Value.S64;
            break;

        case TYPE_DINT:
            if(sIn.Value.S32 < sMin.Value.S32)
                sIn.Value.S32 = sMin.Value.S32;
            if(sIn.Value.S32 > sMax.Value.S32)
                sIn.Value.S32 = sMax.Value.S32;
            break;

        case TYPE_INT:
            if(sIn.Value.S16 < sMin.Value.S16)
                sIn.Value.S16 = sMin.Value.S16;
            if(sIn.Value.S16 > sMax.Value.S16)
                sIn.Value.S16 = sMax.Value.S16;
            break;

        case TYPE_SINT:
            if(sIn.Value.S8 < sMin.Value.S8)
                sIn.Value.S8 = sMin.Value.S8;
            if(sIn.Value.S8 > sMax.Value.S8)
                sIn.Value.S8 = sMax.Value.S8;
            break;

        case TYPE_ULINT:
            if(sIn.Value.U64 < sMin.Value.U64)
                sIn.Value.U64 = sMin.Value.U64;
            if(sIn.Value.U64 > sMax.Value.U64)
                sIn.Value.U64 = sMax.Value.U64;
            break;

        case TYPE_UDINT:
            if(sIn.Value.U32 < sMin.Value.U32)
                sIn.Value.U32 = sMin.Value.U32;
            if(sIn.Value.U32 > sMax.Value.U32)
                sIn.Value.U32 = sMax.Value.U32;
            break;

        case TYPE_UINT:
            if(sIn.Value.U16 < sMin.Value.U16)
                sIn.Value.U16 = sMin.Value.U16;
            if(sIn.Value.U16 > sMax.Value.U16)
                sIn.Value.U16 = sMax.Value.U16;
            break;

        case TYPE_USINT:
            if(sIn.Value.U8 < sMin.Value.U8)
                sIn.Value.U8 = sMin.Value.U8;
            if(sIn.Value.U8 > sMax.Value.U8)
                sIn.Value.U8 = sMax.Value.U8;
            break;

        case TYPE_LWORD:
            if(sIn.Value.B64 < sMin.Value.B64)
                sIn.Value.B64 = sMin.Value.B64;
            if(sIn.Value.B64 > sMax.Value.B64)
                sIn.Value.B64 = sMax.Value.B64;
            break;

        case TYPE_DWORD:
            if(sIn.Value.B32 < sMin.Value.B32)
                sIn.Value.B32 = sMin.Value.B32;
            if(sIn.Value.B32 > sMax.Value.B32)
                sIn.Value.B32 = sMax.Value.B32;
            break;

        case TYPE_WORD:
            if(sIn.Value.B16 < sMin.Value.B16)
                sIn.Value.B16 = sMin.Value.B16;
            if(sIn.Value.B16 > sMax.Value.B16)
                sIn.Value.B16 = sMax.Value.B16;
            break;

        case TYPE_BYTE:
            if(sIn.Value.B8 < sMin.Value.B8)
                sIn.Value.B8 = sMin.Value.B8;
            if(sIn.Value.B8 > sMax.Value.B8)
                sIn.Value.B8 = sMax.Value.B8;
            break;

        case TYPE_BOOL:
        default:
            return ERROR_PARAMETER_TYPE;
    }

    operand_subrange(&sIn, &sIn);
    value_copy(Result, &sIn);

    return 0;
}


int
standard_max(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        if(sValue.Type != pParameter->Value.Type)
            return ERROR_PARAMETER_MISMATCH;
        switch(sValue.Type) {
            case TYPE_LREAL:
                if(pParameter->Value.Value.Double > sValue.Value.Double)
                    sValue.Value.Double = pParameter->Value.Value.Double;
                break;

            case TYPE_REAL:
                if(pParameter->Value.Value.Single > sValue.Value.Single)
                    sValue.Value.Single = pParameter->Value.Value.Single;
                break;

            case TYPE_LINT:
                if(pParameter->Value.Value.S64 > sValue.Value.S64)
                    sValue.Value.S64 = pParameter->Value.Value.S64;
                break;

            case TYPE_DINT:
                if(pParameter->Value.Value.S32 > sValue.Value.S32)
                    sValue.Value.S32 = pParameter->Value.Value.S32;
                break;

            case TYPE_INT:
                if(pParameter->Value.Value.S16 > sValue.Value.S16)
                    sValue.Value.S16 = pParameter->Value.Value.S16;
                break;

            case TYPE_SINT:
                if(pParameter->Value.Value.S8 > sValue.Value.S8)
                    sValue.Value.S8 = pParameter->Value.Value.S8;
                break;

            case TYPE_ULINT:
                if(pParameter->Value.Value.U64 > sValue.Value.U64)
                    sValue.Value.U64 = pParameter->Value.Value.U64;
                break;

            case TYPE_UDINT:
                if(pParameter->Value.Value.U32 > sValue.Value.U32)
                    sValue.Value.U32 = pParameter->Value.Value.U32;
                break;

            case TYPE_UINT:
                if(pParameter->Value.Value.U16 > sValue.Value.U16)
                    sValue.Value.U16 = pParameter->Value.Value.U16;
                break;

            case TYPE_USINT:
                if(pParameter->Value.Value.U8 > sValue.Value.U8)
                    sValue.Value.U8 = pParameter->Value.Value.U8;
                break;

            case TYPE_LWORD:
                if(pParameter->Value.Value.B64 > sValue.Value.B64)
                    sValue.Value.B64 = pParameter->Value.Value.B64;
                break;

            case TYPE_DWORD:
                if(pParameter->Value.Value.B32 > sValue.Value.B32)
                    sValue.Value.B32 = pParameter->Value.Value.B32;
                break;

            case TYPE_WORD:
                if(pParameter->Value.Value.B16 > sValue.Value.B16)
                    sValue.Value.B16 = pParameter->Value.Value.B16;
                break;

            case TYPE_BYTE:
                if(pParameter->Value.Value.B8 > sValue.Value.B8)
                    sValue.Value.B8 = pParameter->Value.Value.B8;
                break;

            case TYPE_BOOL:
            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    operand_subrange(&sValue, &sValue);
    value_copy(Result, &sValue);

    return 0;
}


int
standard_min(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        if(sValue.Type != pParameter->Value.Type)
            return ERROR_PARAMETER_MISMATCH;
        switch(sValue.Type) {
            case TYPE_LREAL:
                if(pParameter->Value.Value.Double < sValue.Value.Double)
                    sValue.Value.Double = pParameter->Value.Value.Double;
                break;

            case TYPE_REAL:
                if(pParameter->Value.Value.Single < sValue.Value.Single)
                    sValue.Value.Single = pParameter->Value.Value.Single;
                break;

            case TYPE_LINT:
                if(pParameter->Value.Value.S64 < sValue.Value.S64)
                    sValue.Value.S64 = pParameter->Value.Value.S64;
                break;

            case TYPE_DINT:
                if(pParameter->Value.Value.S32 < sValue.Value.S32)
                    sValue.Value.S32 = pParameter->Value.Value.S32;
                break;

            case TYPE_INT:
                if(pParameter->Value.Value.S16 < sValue.Value.S16)
                    sValue.Value.S16 = pParameter->Value.Value.S16;
                break;

            case TYPE_SINT:
                if(pParameter->Value.Value.S8 < sValue.Value.S8)
                    sValue.Value.S8 = pParameter->Value.Value.S8;
                break;

            case TYPE_ULINT:
                if(pParameter->Value.Value.U64 < sValue.Value.U64)
                    sValue.Value.U64 = pParameter->Value.Value.U64;
                break;

            case TYPE_UDINT:
                if(pParameter->Value.Value.U32 < sValue.Value.U32)
                    sValue.Value.U32 = pParameter->Value.Value.U32;
                break;

            case TYPE_UINT:
                if(pParameter->Value.Value.U16 < sValue.Value.U16)
                    sValue.Value.U16 = pParameter->Value.Value.U16;
                break;

            case TYPE_USINT:
                if(pParameter->Value.Value.U8 < sValue.Value.U8)
                    sValue.Value.U8 = pParameter->Value.Value.U8;
                break;

            case TYPE_LWORD:
                if(pParameter->Value.Value.B64 < sValue.Value.B64)
                    sValue.Value.B64 = pParameter->Value.Value.B64;
                break;

            case TYPE_DWORD:
                if(pParameter->Value.Value.B32 < sValue.Value.B32)
                    sValue.Value.B32 = pParameter->Value.Value.B32;
                break;

            case TYPE_WORD:
                if(pParameter->Value.Value.B16 < sValue.Value.B16)
                    sValue.Value.B16 = pParameter->Value.Value.B16;
                break;

            case TYPE_BYTE:
                if(pParameter->Value.Value.B8 < sValue.Value.B8)
                    sValue.Value.B8 = pParameter->Value.Value.B8;
                break;

            case TYPE_BOOL:
            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    operand_subrange(&sValue, &sValue);
    value_copy(Result, &sValue);

    return 0;
}


int
standard_mux(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sK, sSelect, sValue;
    size_t uParameter;
    char sName[32];
    char *pSelect, *pValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sK);
    value_initialise(&sSelect);
    value_initialise(&sValue);

    if(!Name)
        return ERROR_INTERNAL;

    strcpy(sName, Name);
    if((pSelect = strchr(sName, '_')) != NULL) {

        /*
            If this block is reached, a typed form of the MUX selection function has been 
            called and the inputs should be validated accordingly.
        */

        if((pValue = strchr(++pSelect, '_')) == NULL)
            return ERROR_INVALID_FUNCTION;
        *pValue++ = '\0';
        value_strtotype(&sSelect, pSelect);
        value_strtotype(&sValue, pValue);
        assert(sSelect.Type != TYPE_NONE);
        assert((sSelect.Type & ANY_INT) != 0);
        assert(sValue.Type != TYPE_NONE);
    }

    uParameter = 0;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if((pParameter->Name) &&
                (strcasecmp(pParameter->Name, "K") == 0)) {
            if((sSelect.Type != TYPE_NONE) &&
                    (pParameter->Value.Type != sSelect.Type))
                return ERROR_PARAMETER_TYPE;
            if((pParameter->Value.Type & ANY_INT) == 0)
                return ERROR_PARAMETER_TYPE;
            value_copy(&sK, &pParameter->Value);
            value_cast(&sK, TYPE_ULINT);
            ++uParameter;
            continue;
        }
        else if(sK.Type == TYPE_NONE) {
            if((pParameter->Value.Type & TYPE_INT) == 0)
                return ERROR_PARAMETER_TYPE;
            value_copy(&sK, &pParameter->Value);
            value_cast(&sK, TYPE_ULINT);
            ++uParameter;
            continue;
        }

        if((sValue.Type != TYPE_NONE) &&
                (pParameter->Value.Type != sValue.Type))
            return ERROR_PARAMETER_TYPE;
        if(uParameter++ < sK.Value.U64)
            continue;

        value_copy(Result, &pParameter->Value);
        break;
    }

    if(Result->Type == TYPE_NONE)
        return ERROR_PARAMETER_COUNT;

    return 0;
}


int
standard_sel(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn0, sIn1, sSelect;
    size_t uParameter;

    /*
        Note that the following does not validate parameter types and is permissive 
        of mis-matching parameter types.
    */

    Result->Type = TYPE_NONE;
    value_assign(&sSelect, TYPE_BOOL);
    value_initialise(&sIn0);
    value_initialise(&sIn1);

    uParameter = 0;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(pParameter->Name) {
            if(strcasecmp(pParameter->Name, "G") == 0) 
                value_copy(&sSelect, &pParameter->Value);
            else if(strcasecmp(pParameter->Name, "IN0") == 0)
                value_copy(&sIn0, &pParameter->Value);
            else if(strcasecmp(pParameter->Name, "IN1") == 0)
                value_copy(&sIn1, &pParameter->Value);
        }
        else {
            switch(uParameter++) {
                case 0:     value_copy(&sSelect, &pParameter->Value); break;
                case 1:     value_copy(&sIn0, &pParameter->Value); break;
                case 2:     value_copy(&sIn1, &pParameter->Value); break;
                default:
                    return ERROR_PARAMETER_COUNT;
            }
        }
    }

    if((sIn0.Type == TYPE_NONE) ||
            (sIn1.Type == TYPE_NONE))
        return ERROR_PARAMETER_COUNT;
    /* assert(sIn0.Type == sIn1.Type); */
    cast_ulint(&sSelect);
    if(sSelect.Value.U64 == 0)
        value_copy(Result, &sIn0);
    else
        value_copy(Result, &sIn1);

    return 0;
}


