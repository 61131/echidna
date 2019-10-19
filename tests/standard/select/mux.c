#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <runtime.h>

#include <standard/select.h>


MunitResult 
test_select_mux(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pK, *pValue;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_mux(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_INTERNAL);
    munit_assert_int(standard_mux(pContext, "mux", &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pK = parameter_new(NULL));
    value_assign(&pK->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pK), ==, 0);
    munit_assert_int(standard_mux(pContext, "mux", &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_assign(&pK->Value, TYPE_INT, 2);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_mux(pContext, "mux", &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 2);

    munit_assert_int(standard_mux(pContext, "mux_int", &sParameters, &sResult, NULL), ==, ERROR_INVALID_FUNCTION);
    munit_assert_int(standard_mux(pContext, "mux_int_bool", &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    munit_assert_int(standard_mux(pContext, "mux_int_int", &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 2);

    munit_assert_not_null(pK->Name = strdup("K"));
    munit_assert_int(standard_mux(pContext, "mux_bool_int", &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_assign(&pK->Value, TYPE_BOOL);
    munit_assert_int(standard_mux(pContext, "mux_bool_int", &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    value_assign(&pK->Value, TYPE_INT, 2);
    munit_assert_int(standard_mux(pContext, "mux_int_int", &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 2);

    ll_destroy(&sParameters);

    return MUNIT_OK;
}


