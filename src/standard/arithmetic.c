#include <strings.h>
#include <float.h>
#include <math.h>

#include <cast.h>
#include <function.h>
#include <ll.h>
#include <log.h>
#include <operator.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


int
standard_add(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if((pParameter->Value.Type & ANY_MAGNITUDE) == 0) 
            return ERROR_PARAMETER_TYPE;
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:    
                sValue.Value.Double += sIn.Value.Double;
                break;

            case TYPE_REAL:
                sValue.Value.Single += sIn.Value.Single;
                break;

            case TYPE_LINT:
                sValue.Value.S64 += sIn.Value.S64;
                break;

            case TYPE_DINT:
                sValue.Value.S32 += sIn.Value.S32;
                break;

            case TYPE_INT:
                sValue.Value.S16 += sIn.Value.S16;
                break;

            case TYPE_SINT:
                sValue.Value.S8 += sIn.Value.S8;
                break;

            case TYPE_ULINT:
                sValue.Value.U64 += sIn.Value.U64;
                break;

            case TYPE_UDINT:
                sValue.Value.U32 += sIn.Value.U32;
                break;

            case TYPE_UINT:
                sValue.Value.U16 += sIn.Value.U16;
                break;

            case TYPE_USINT:
                sValue.Value.U8 += sIn.Value.U8;
                break;

            case TYPE_TIME:
                sValue.Value.Time += sIn.Value.Time;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    operand_subrange(Result, Result);
    return 0;
}


int
standard_div(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if((pParameter->Value.Type & ANY_MAGNITUDE) == 0)
            return ERROR_PARAMETER_TYPE;
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:
                if(fabs(sIn.Value.Double) < DBL_EPSILON)
                    goto error;
                sValue.Value.Double /= sIn.Value.Double;
                break;

            case TYPE_REAL:
                if(fabs(sIn.Value.Single) < FLT_EPSILON)
                    goto error;
                sValue.Value.Single /= sIn.Value.Single;
                break;

            case TYPE_LINT:
                if(sIn.Value.S64 == 0ll)
                    goto error;
                sValue.Value.S64 /= sIn.Value.S64;
                break;

            case TYPE_DINT:
                if(sIn.Value.S32 == 0)
                    goto error;
                sValue.Value.S32 /= sIn.Value.S32;
                break;

            case TYPE_INT:
                if(sIn.Value.S16 == 0)
                    goto error;
                sValue.Value.S16 /= sIn.Value.S16;
                break;

            case TYPE_SINT:
                if(sIn.Value.S8 == 0)
                    goto error;
                sValue.Value.S8 /= sIn.Value.S8;
                break;

            case TYPE_ULINT:
                if(sIn.Value.U64 == 0ull)
                    goto error;
                sValue.Value.U64 /= sIn.Value.U64;
                break;

            case TYPE_UDINT:
                if(sIn.Value.U32 == 0u)
                    goto error;
                sValue.Value.U32 /= sIn.Value.U32;
                break;

            case TYPE_UINT:
                if(sIn.Value.U16 == 0u)
                    goto error;
                sValue.Value.U16 /= sIn.Value.U16;
                break;

            case TYPE_USINT:
                if(sIn.Value.U8 == 0u)
                    goto error;
                sValue.Value.U8 /= sIn.Value.U8;
                break;

            case TYPE_TIME:
                if(sIn.Value.Time == 0.0f)
                    goto error;
                sValue.Value.Time /= sIn.Value.Time;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    operand_subrange(Result, Result);
    return 0;

error:
    log_error("Invalid divide by zero operation");
    return ERROR_DIVIDE_ZERO;
}


int
standard_expt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sBase, sExponent;
    VALUE_TYPE uType;
    double dValue;
    size_t uParameter;

    Result->Type = TYPE_NONE;
    value_initialise(&sBase);
    value_initialise(&sExponent);

    uParameter = 0;
    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if(pParameter->Name) {
            if(strcasecmp(pParameter->Name, "IN1") == 0) {
                if((pParameter->Value.Type & ANY_REAL) == 0)
                    return ERROR_PARAMETER_TYPE;
                value_copy(&sBase, &pParameter->Value);
            }
            else if(strcasecmp(pParameter->Name, "IN2") == 0) {
                if((pParameter->Value.Type & ANY_NUM) == 0)
                    return ERROR_PARAMETER_TYPE;
                value_copy(&sExponent, &pParameter->Value);
            }
        }
        else {
            switch(uParameter++) {
                case 0:
                    if((pParameter->Value.Type & ANY_REAL) == 0)
                        return ERROR_PARAMETER_TYPE;
                    value_copy(&sBase, &pParameter->Value);
                    break;

                case 1:
                    if((pParameter->Value.Type & ANY_NUM) == 0)
                        return ERROR_PARAMETER_TYPE;
                    value_copy(&sExponent, &pParameter->Value);
                    break;

                default:
                    return ERROR_PARAMETER_COUNT;
            }
        }
    }

    uType = sBase.Type;
    if((cast_lreal(&sBase) != 0) ||
            (cast_lreal(&sExponent) != 0))
        return ERROR_PARAMETER_TYPE;
    dValue = pow(sBase.Value.Double, sExponent.Value.Double);
    value_assign(Result, uType, dValue);

    return 0;
}


int
standard_mod(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if((pParameter->Value.Type & ANY_INT) == 0)
            return ERROR_PARAMETER_TYPE;
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LINT:
                if(sIn.Value.S64 == 0ll)
                    goto error;
                sValue.Value.S64 %= sIn.Value.S64;
                break;

            case TYPE_DINT:
                if(sIn.Value.S32 == 0)
                    goto error;
                sValue.Value.S32 %= sIn.Value.S32;
                break;

            case TYPE_INT:
                if(sIn.Value.S16 == 0)
                    goto error;
                sValue.Value.S16 %= sIn.Value.S16;
                break;

            case TYPE_SINT:
                if(sIn.Value.S8 == 0)
                    goto error;
                sValue.Value.S8 %= sIn.Value.S8;
                break;

            case TYPE_ULINT:
                if(sIn.Value.U64 == 0ull)
                    goto error;
                sValue.Value.U64 %= sIn.Value.U64;
                break;

            case TYPE_UDINT:
                if(sIn.Value.U32 == 0u)
                    goto error;
                sValue.Value.U32 %= sIn.Value.U32;
                break;

            case TYPE_UINT:
                if(sIn.Value.U16 == 0u)
                    goto error;
                sValue.Value.U16 %= sIn.Value.U16;
                break;

            case TYPE_USINT:
                if(sIn.Value.U8 == 0u)
                    goto error;
                sValue.Value.U8 %= sIn.Value.U8;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    operand_subrange(Result, Result);
    return 0;

error:
    log_error("Invalid modulus by zero operation");
    return ERROR_MODULUS_ZERO;
}


int
standard_mul(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if((pParameter->Value.Type & ANY_MAGNITUDE) == 0)
            return ERROR_PARAMETER_TYPE;
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:    
                sValue.Value.Double *= sIn.Value.Double;
                break;

            case TYPE_REAL:
                sValue.Value.Single *= sIn.Value.Single;
                break;

            case TYPE_LINT:
                sValue.Value.S64 *= sIn.Value.S64;
                break;

            case TYPE_DINT:
                sValue.Value.S32 *= sIn.Value.S32;
                break;

            case TYPE_INT:
                sValue.Value.S16 *= sIn.Value.S16;
                break;

            case TYPE_SINT:
                sValue.Value.S8 *= sIn.Value.S8;
                break;

            case TYPE_ULINT:
                sValue.Value.U64 *= sIn.Value.U64;
                break;

            case TYPE_UDINT:
                sValue.Value.U32 *= sIn.Value.U32;
                break;

            case TYPE_UINT:
                sValue.Value.U16 *= sIn.Value.U16;
                break;

            case TYPE_USINT:
                sValue.Value.U8 *= sIn.Value.U8;
                break;

            case TYPE_TIME:
                sValue.Value.Time *= sIn.Value.Time;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    operand_subrange(Result, Result);
    return 0;
}


int
standard_sub(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;
    VALUE sIn, sValue;

    Result->Type = TYPE_NONE;
    value_initialise(&sValue);

    ll_reset(Parameters);
    while((pParameter = ll_iterate(Parameters)) != NULL) {
        if((pParameter->Value.Type & ANY_MAGNITUDE) == 0)
            return ERROR_PARAMETER_TYPE;
        if(sValue.Type == TYPE_NONE) {
            value_copy(&sValue, &pParameter->Value);
            continue;
        }
        value_copy(&sIn, &pParameter->Value);
        value_cast(&sIn, sValue.Type);
        switch(sValue.Type) {
            case TYPE_LREAL:    
                sValue.Value.Double -= sIn.Value.Double;
                break;

            case TYPE_REAL:
                sValue.Value.Single -= sIn.Value.Single;
                break;

            case TYPE_LINT:
                sValue.Value.S64 -= sIn.Value.S64;
                break;

            case TYPE_DINT:
                sValue.Value.S32 -= sIn.Value.S32;
                break;

            case TYPE_INT:
                sValue.Value.S16 -= sIn.Value.S16;
                break;

            case TYPE_SINT:
                sValue.Value.S8 -= sIn.Value.S8;
                break;

            case TYPE_ULINT:
                sValue.Value.U64 -= sIn.Value.U64;
                break;

            case TYPE_UDINT:
                sValue.Value.U32 -= sIn.Value.U32;
                break;

            case TYPE_UINT:
                sValue.Value.U16 -= sIn.Value.U16;
                break;

            case TYPE_USINT:
                sValue.Value.U8 -= sIn.Value.U8;
                break;

            case TYPE_TIME:
                sValue.Value.Time -= sIn.Value.Time;
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    value_copy(Result, &sValue);
    operand_subrange(Result, Result);
    return 0;
}
