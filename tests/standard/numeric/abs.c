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


static VALUE_TYPE _Type[] = {
    TYPE_ULINT,
    TYPE_UDINT,
    TYPE_UINT,
    TYPE_USINT,
    0
};


MunitResult 
test_numeric_abs(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    int nIndex;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_NUM);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, pParameter->Value.Value.Double);
    pParameter->Value.Value.Double *= -1.0;
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, fabs(pParameter->Value.Value.Double));
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0f);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, pParameter->Value.Value.Single);
    pParameter->Value.Value.Single *= -1.0f;
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, fabsf(pParameter->Value.Value.Single));
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, pParameter->Value.Value.S64);
    pParameter->Value.Value.S64 *= -1;
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, abs(pParameter->Value.Value.S64));
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, pParameter->Value.Value.S32);
    pParameter->Value.Value.S32 *= -1;
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, abs(pParameter->Value.Value.S32));
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, pParameter->Value.Value.S16);
    pParameter->Value.Value.S16 *= -1;
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, abs(pParameter->Value.Value.S16));
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_int8(sResult.Value.S8, ==, pParameter->Value.Value.S8);
    pParameter->Value.Value.S8 *= -1;
    munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_int8(sResult.Value.S8, ==, abs(pParameter->Value.Value.S8));
    ll_destroy(&sParameters);

    nIndex = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, _Type[nIndex], 1);
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_abs(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        ll_destroy(&sParameters);
    }
    while(_Type[++nIndex] != 0);

    return MUNIT_OK;
}
