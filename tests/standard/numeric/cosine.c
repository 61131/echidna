#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>

#include <standard/numeric.h>


struct _TRIG {

    int Angle;

    double Result;
};

static struct _TRIG _Values[] = {
    { 0, 1 },
    { 30, 0.866 },
    { 60, 0.5 },
    { 90, 0 },
    { 120, -0.5 },
    { 150, -0.866 },
    { 180, -1 },
    { 210, -0.866 },
    { 240, -0.5 },
    { 270, 0 },
    { 300, 0.5 },
    { 330, 0.866 },
    { 360, 1 },

    { -1, 0 },
};


MunitResult 
test_numeric_acos(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    double dValue;
    int nIndex;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_cos(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_acos(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_REAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_acos(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    //  TYPE_LREAL

    nIndex = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_LREAL, _Values[nIndex].Result);
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_acos(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
        dValue = round(sResult.Value.Double * (180.0 / 3.1415927));
        munit_assert_double(dValue, ==, (double) _Values[nIndex].Angle);
        ll_destroy(&sParameters);
    }
    while(_Values[++nIndex].Angle <= 180);

    //  TYPE_REAL

    nIndex = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_REAL, _Values[nIndex].Result);
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_acos(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
        dValue = round(((double) sResult.Value.Single) * (180.0 / 3.1415927));
        munit_assert_double(dValue, ==, (double) _Values[nIndex].Angle);
        ll_destroy(&sParameters);
    }
    while(_Values[++nIndex].Angle <= 180);

    return MUNIT_OK;
}


MunitResult 
test_numeric_cos(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    double dValue;
    int nIndex;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_cos(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_cos(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_REAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_cos(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    //  TYPE_LREAL

    nIndex = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        dValue = (double) _Values[nIndex].Angle;
        dValue *= (3.1415927 / 180.0);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_LREAL, dValue);
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_cos(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
        dValue = round(sResult.Value.Double * 1e4) / 1e4;
        munit_assert_double(dValue, ==, _Values[nIndex].Result);
        ll_destroy(&sParameters);
    }
    while(_Values[++nIndex].Angle >= 0);

    //  TYPE_REAL

    nIndex = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        dValue = (double) _Values[nIndex].Angle;
        dValue *= (3.1415927 / 180.0);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_REAL, dValue);
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_cos(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
        dValue = round(((double) sResult.Value.Single) * 1e4) / 1e4;
        munit_assert_double(dValue, ==, _Values[nIndex].Result);
        ll_destroy(&sParameters);
    }
    while(_Values[++nIndex].Angle >= 0);

    return MUNIT_OK;
}


