#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <echidna.h>
#include <parameter.h>
#include <runtime.h>

#include <standard/arithmetic.h>


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
    munit_assert_float(sResult.Value.Single, ==, 14.0f);
    _test_arithmetic_populate(&sParameters, TYPE_LINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_DINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_INT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_SINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_int8(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sResult.Value.U64, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sResult.Value.U32, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_UINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_uint16(sResult.Value.U16, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_USINT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_uint8(sResult.Value.U8, ==, 14);
    _test_arithmetic_populate(&sParameters, TYPE_TIME);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TIME);
    munit_assert_float(sResult.Value.Time, ==, 14.0);
    _test_arithmetic_populate(&sParameters, TYPE_DATE);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DATE);
    munit_assert_float(sResult.Value.DateTime, ==, 14.0);
    _test_arithmetic_populate(&sParameters, TYPE_DT);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DT);
    munit_assert_float(sResult.Value.DateTime, ==, 14.0);
    _test_arithmetic_populate(&sParameters, TYPE_TOD);
    munit_assert_int(standard_add(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_TOD);
    munit_assert_float(sResult.Value.DateTime, ==, 14.0);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


