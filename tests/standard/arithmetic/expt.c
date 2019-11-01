#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <echidna.h>
#include <parameter.h>
#include <runtime.h>

#include <standard/arithmetic.h>


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


