#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <standard/arithmetic.h>
#include <value.h>


void
_test_arithmetic_modulus(LL *Parameters, VALUE_TYPE Type) {
    PARAMETER *pParameter;
    int nValue;

    while(Parameters->Head != NULL)
        ll_delete(Parameters->Head);
    for(nValue = 5; nValue > 1; nValue -= 2) {
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, Type, nValue);
        munit_assert_int(ll_insert(Parameters, pParameter), ==, 0);
    }
}


void
_test_arithmetic_populate(LL *Parameters, VALUE_TYPE Type) {
    PARAMETER *pParameter;
    double dValue;
    int nValue;

    while(Parameters->Head != NULL)
        ll_delete(Parameters->Head);
    for(nValue = 8; nValue > 1; nValue /= 2) {
        munit_assert_not_null(pParameter = parameter_new(NULL));
        dValue = (double) nValue;
        switch(Type) {
            case TYPE_LREAL:
            case TYPE_REAL:
                value_assign(&pParameter->Value, Type, dValue);
                break;

            default:
                value_assign(&pParameter->Value, Type, nValue);
                break;
        }
        munit_assert_int(ll_insert(Parameters, pParameter), ==, 0);
    }
}


MunitResult 
test_arithmetic_add(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    _test_arithmetic_populate(&sParameters, TYPE_NONE);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, ANY_NUM);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, TYPE_LREAL);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 14.0);
    _test_arithmetic_populate(&sParameters, TYPE_REAL);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_double(sResult.Value.Single, ==, 14.0f);
    _test_arithmetic_populate(&sParameters, TYPE_LINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_double(sResult.Value.S64, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_DINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_double(sResult.Value.S32, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_INT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_double(sResult.Value.S16, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_SINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_double(sResult.Value.U64, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_double(sResult.Value.U32, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_UINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_double(sResult.Value.U16, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_USINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_double(sResult.Value.U8, ==, 14);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_arithmetic_div(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    _test_arithmetic_populate(&sParameters, TYPE_NONE);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, ANY_NUM);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);

    //  TYPE_LREAL
    _test_arithmetic_populate(&sParameters, TYPE_LREAL);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 1.0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_REAL
    _test_arithmetic_populate(&sParameters, TYPE_REAL);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_double(sResult.Value.Single, ==, 1.0f);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_LINT
    _test_arithmetic_populate(&sParameters, TYPE_LINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_double(sResult.Value.S64, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_DINT
    _test_arithmetic_populate(&sParameters, TYPE_DINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_double(sResult.Value.S32, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_INT
    _test_arithmetic_populate(&sParameters, TYPE_INT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_double(sResult.Value.S16, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_SINT
    _test_arithmetic_populate(&sParameters, TYPE_SINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_ULINT
    _test_arithmetic_populate(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_double(sResult.Value.U64, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_UDINT
    _test_arithmetic_populate(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_double(sResult.Value.U32, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_UINT
    _test_arithmetic_populate(&sParameters, TYPE_UINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_double(sResult.Value.U16, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    //  TYPE_USINT
    _test_arithmetic_populate(&sParameters, TYPE_USINT);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_double(sResult.Value.U8, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_div(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);

    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_arithmetic_expt(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);
    value_initialise(&sResult);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  TYPE_LREAL ** TYPE_LREAL -> 0
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 4.0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  TYPE_LREAL ** TYPE_LREAL ?? TYPE_LREAL -> ERROR_PARAMETER_COUNT
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN1"));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN2"));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  IN1:TYPE_LREAL ** IN2:TYPE_LREAL -> 0
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 4.0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN3"));
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  IN1:TYPE_LREAL ** IN2:TYPE_LREAL  ?? IN3:TYPE_LREAL -> ERROR_PARAMETER_UNKNOWN
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_UNKNOWN);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  TYPE_LREAL ** TYPE_BOOL -> ERROR_PARAMETER_TYPE
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  TYPE_BOOL ** TYPE_LREAL -> ERROR_PARAMETER_TYPE
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN1"));
    value_assign(&pParameter->Value, TYPE_LREAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN2"));
    value_assign(&pParameter->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  IN1:TYPE_LREAL ** IN2:TYPE_BOOL -> ERROR_PARAMETER_TYPE
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN1"));
    value_assign(&pParameter->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN2"));
    value_assign(&pParameter->Value, TYPE_LREAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    //  IN1:TYPE_BOOL ** IN2:TYPE_LREAL -> ERROR_PARAMETER_TYPE
    munit_assert_int(standard_expt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_arithmetic_mod(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    _test_arithmetic_modulus(&sParameters, TYPE_NONE);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, ANY_INT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);

    //  TYPE_LINT
    _test_arithmetic_modulus(&sParameters, TYPE_LINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_double(sResult.Value.S64, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_DINT
    _test_arithmetic_modulus(&sParameters, TYPE_DINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_double(sResult.Value.S32, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_INT
    _test_arithmetic_modulus(&sParameters, TYPE_INT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_double(sResult.Value.S16, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_SINT
    _test_arithmetic_modulus(&sParameters, TYPE_SINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_ULINT
    _test_arithmetic_modulus(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_double(sResult.Value.U64, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_UDINT
    _test_arithmetic_modulus(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_double(sResult.Value.U32, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_UINT
    _test_arithmetic_modulus(&sParameters, TYPE_UINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_double(sResult.Value.U16, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_USINT
    _test_arithmetic_modulus(&sParameters, TYPE_USINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_double(sResult.Value.U8, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_arithmetic_mul(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    _test_arithmetic_populate(&sParameters, TYPE_NONE);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, ANY_NUM);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, TYPE_LREAL);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 64.0);
    _test_arithmetic_populate(&sParameters, TYPE_REAL);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_double(sResult.Value.Single, ==, 64.0f);
    _test_arithmetic_populate(&sParameters, TYPE_LINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_double(sResult.Value.S64, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_DINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_double(sResult.Value.S32, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_INT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_double(sResult.Value.S16, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_SINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_double(sResult.Value.U64, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_double(sResult.Value.U32, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_UINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_double(sResult.Value.U16, ==, 64);
    _test_arithmetic_populate(&sParameters, TYPE_USINT);
    munit_assert_int(standard_mul(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_double(sResult.Value.U8, ==, 64);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_arithmetic_sub(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    _test_arithmetic_populate(&sParameters, TYPE_NONE);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, ANY_NUM);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, TYPE_LREAL);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 2.0);
    _test_arithmetic_populate(&sParameters, TYPE_REAL);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_double(sResult.Value.Single, ==, 2.0f);
    _test_arithmetic_populate(&sParameters, TYPE_LINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_double(sResult.Value.S64, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_DINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_double(sResult.Value.S32, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_INT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_double(sResult.Value.S16, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_SINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_double(sResult.Value.U64, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_double(sResult.Value.U32, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_UINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_double(sResult.Value.U16, ==, 2);
    _test_arithmetic_populate(&sParameters, TYPE_USINT);
    munit_assert_int(standard_sub(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_double(sResult.Value.U8, ==, 2);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}



