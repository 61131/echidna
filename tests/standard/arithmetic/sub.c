#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <echidna.h>
#include <parameter.h>
#include <runtime.h>

#include <standard/arithmetic.h>


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



