#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <runtime.h>

#include <standard/select.h>


MunitResult 
test_select_select(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pSelect, *pValue;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pSelect = parameter_new(NULL));
    value_assign(&pSelect->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pSelect), ==, 0);
    munit_assert_int(standard_sel(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_sel(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_sel(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 1);
    value_assign(&pSelect->Value, TYPE_BOOL, 1);
    munit_assert_int(standard_sel(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 2);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_sel(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    munit_assert_not_null(pValue->Name = strdup("G"));
    value_assign(&pValue->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    munit_assert_not_null(pValue->Name = strdup("IN0"));
    value_assign(&pValue->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    munit_assert_not_null(pValue->Name = strdup("IN1"));
    value_assign(&pValue->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_sel(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 1);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


