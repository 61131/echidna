#include <errno.h>
#include <math.h>

#include <echidna.h>
#include <function.h>
#include <ll.h>
#include <operator.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


int
standard_abs(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_NUM) == 0)
        return RT_ERR_PARAMETER_TYPE;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            if(Result->Value.Double < 0.0)
                Result->Value.Double *= -1.0;
            break;

        case TYPE_REAL:
            if(Result->Value.Single < 0.0f)
                Result->Value.Single *= -1.0f;
            break;

        case TYPE_LINT:
            if(Result->Value.S64 < 0)
                Result->Value.S64 *= -1ll;
            break;

        case TYPE_DINT:
            if(Result->Value.S32 < 0)
                Result->Value.S32 *= -1l;
            break;

        case TYPE_INT:
            if(Result->Value.S16 < 0)
                Result->Value.S16 *= -1;
            break;

        case TYPE_SINT:
            if(Result->Value.S8 < 0)
                Result->Value.S8 *= -1;
            break;

        case TYPE_ULINT:
        case TYPE_UDINT:
        case TYPE_UINT:
        case TYPE_USINT:
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }

    operand_subrange(Result, Result);
    return 0;
}


int
standard_acos(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = acos(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = acosf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0) 
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_asin(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = asin(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = asinf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0) 
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_atan(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = atan(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = atanf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0) 
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_cos(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = cos(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = cosf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0) 
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_exp(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = exp(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = expf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0)
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_ln(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = log(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = logf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0)
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_log(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = log10(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = log10f(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0)
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_sin(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = sin(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = sinf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0) 
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_sqrt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = sqrt(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = sqrtf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0) 
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}


int
standard_tan(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User) {
    PARAMETER *pParameter;

    Result->Type = TYPE_NONE;
    ll_reset(Parameters);
    if((pParameter = ll_iterate(Parameters)) == NULL)
        return RT_ERR_PARAMETER_COUNT;
    if((pParameter->Value.Type & ANY_REAL) == 0)
        return RT_ERR_PARAMETER_TYPE;

    errno = 0;
    value_copy(Result, &pParameter->Value);
    switch(Result->Type & ~ANY_INTERNAL) {
        case TYPE_LREAL:
            Result->Value.Double = tan(pParameter->Value.Value.Double);
            break;

        case TYPE_REAL:
            Result->Value.Single = tanf(pParameter->Value.Value.Single);
            break;

        default:
            return RT_ERR_PARAMETER_TYPE;
    }
    if(errno != 0)
        return RT_ERR_MATH_OVERFLOW;

    /* operand_subrange(Result, Result); */
    return 0;
}

