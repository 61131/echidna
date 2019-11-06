#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <echidna.h>
#include <parameter.h>
#include <runtime.h>

#include <standard/time.h>


MunitResult 
test_time_add_dttime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pFirst, *pParameter, *pSecond;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pFirst = parameter_new(NULL));
    value_assign(&pFirst->Value, TYPE_TIME);
    munit_assert_int(ll_insert(&sParameters, pFirst), ==, 0);
    munit_assert_not_null(pSecond = parameter_new(NULL));
    value_assign(&pSecond->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pSecond), ==, 0);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pFirst->Value, TYPE_DT);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pSecond->Value, TYPE_TIME);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, (int64_t) 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, (int64_t) 2);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_add_time(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pFirst, *pParameter, *pSecond;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pFirst = parameter_new(NULL));
    value_assign(&pFirst->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pFirst), ==, 0);
    munit_assert_not_null(pSecond = parameter_new(NULL));
    value_assign(&pSecond->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pSecond), ==, 0);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pFirst->Value, TYPE_TIME);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pSecond->Value, TYPE_TIME);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 2.0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 3.0);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_add_todtime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pFirst, *pParameter, *pSecond;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pFirst = parameter_new(NULL));
    value_assign(&pFirst->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pFirst), ==, 0);
    munit_assert_not_null(pSecond = parameter_new(NULL));
    value_assign(&pSecond->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pSecond), ==, 0);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pFirst->Value, TYPE_TOD);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pSecond->Value, TYPE_TIME);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TOD);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TOD);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, 3);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_divtime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    ll_destroy(&sParameters);

    return MUNIT_SKIP;
}


MunitResult 
test_time_multime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_time_sub_datedate(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_time_sub_dtdt(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_time_sub_dttime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_time_sub_time(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_time_sub_todtime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


MunitResult 
test_time_sub_todtod(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_SKIP;
}


