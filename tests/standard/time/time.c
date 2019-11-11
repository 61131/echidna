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
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_TIME);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_DT);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TIME);
    munit_assert_int(standard_add_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, (int64_t) 1);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
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
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TIME);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TIME);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 2.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 3.0);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult
test_time_concat_datetod(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_concat_datetod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_concat_datetod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_DATE);
    munit_assert_int(standard_concat_datetod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TOD);
    munit_assert_int(standard_concat_datetod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, 1);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_concat_datetod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_add_todtime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TOD);
    munit_assert_int(standard_add_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TIME);
    munit_assert_int(standard_add_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TOD);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, 2);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
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
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_divtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_INT, 20);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_TIME, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_divtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TIME);
    munit_assert_int(standard_divtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_INT);
    munit_assert_int(standard_divtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 10.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_divtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_DIVIDE_ZERO);
    value_assign(&pParam3->Value, TYPE_INT, 5);
    munit_assert_int(standard_divtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 2.0);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_multime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_multime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_TIME, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_multime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TIME);
    munit_assert_int(standard_multime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_INT);
    munit_assert_int(standard_multime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 2.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_INT, 5);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_multime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 10.0);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_sub_datedate(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_sub_datedate(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_TIME, 4.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_sub_datedate(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_DATE);
    munit_assert_int(standard_sub_datedate(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_DATE);
    munit_assert_int(standard_sub_datedate(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 3.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_sub_datedate(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_sub_dtdt(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_sub_dtdt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_TIME, 4.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_sub_dtdt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_DT);
    munit_assert_int(standard_sub_dtdt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_DT);
    munit_assert_int(standard_sub_dtdt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 3.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_sub_dtdt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_sub_dttime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_sub_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_TIME, 4.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_sub_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_DT);
    munit_assert_int(standard_sub_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TIME);
    munit_assert_int(standard_sub_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, (int64_t) 3);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_sub_dttime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, (int64_t) 2);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_sub_time(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_sub_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_REAL, 4.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_sub_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TIME);
    munit_assert_int(standard_sub_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TIME);
    munit_assert_int(standard_sub_time(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 3.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_sub_time(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 2.0);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_sub_todtime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_sub_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_INT, 4);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_sub_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TOD);
    munit_assert_int(standard_sub_time(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TIME);
    munit_assert_int(standard_sub_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TOD);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, 3);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_sub_todtime(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TOD);
    munit_assert_int64((int64_t) sResult.Value.DateTime, ==, 2);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_time_sub_todtod(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParam1, *pParam2, *pParam3;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    value_initialise(&sResult);
    munit_assert_int(standard_sub_todtod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParam1 = parameter_new(NULL));
    value_assign(&pParam1->Value, TYPE_TIME, 4.0);
    munit_assert_int(ll_insert(&sParameters, pParam1), ==, 0);
    munit_assert_not_null(pParam2 = parameter_new(NULL));
    value_assign(&pParam2->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam2), ==, 0);
    munit_assert_int(standard_sub_todtod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam1->Value, TYPE_TOD);
    munit_assert_int(standard_sub_todtod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_cast(&pParam2->Value, TYPE_TOD);
    munit_assert_int(standard_sub_todtod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 3.0);
    munit_assert_not_null(pParam3 = parameter_new(NULL));
    value_assign(&pParam3->Value, TYPE_TIME, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParam3), ==, 0);
    munit_assert_int(standard_sub_todtod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


