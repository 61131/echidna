#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <echidna.h>
#include <parameter.h>
#include <runtime.h>

#include <standard/type.h>


MunitResult 
test_type_bcd(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_type_conversion(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_type_trunc(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_trunc(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_trunc(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_assign(&pParameter->Value, ANY_REAL);
    munit_assert_int(standard_trunc(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_assign(&pParameter->Value, TYPE_LREAL, 3.142);
    munit_assert_int(standard_trunc(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 3);
    value_assign(&pParameter->Value, TYPE_REAL, 3.142);
    munit_assert_int(standard_trunc(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, 3);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


