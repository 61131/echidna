#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <echidna.h>
#include <parameter.h>
#include <runtime.h>

#include <standard/arithmetic.h>


MunitResult 
test_arithmetic_mod(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    _test_arithmetic_modulus(&sParameters, TYPE_NONE);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    _test_arithmetic_populate(&sParameters, ANY_INT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);

    //  TYPE_LINT
    _test_arithmetic_modulus(&sParameters, TYPE_LINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_double(sResult.Value.S64, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_DINT
    _test_arithmetic_modulus(&sParameters, TYPE_DINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_double(sResult.Value.S32, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_INT
    _test_arithmetic_modulus(&sParameters, TYPE_INT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_double(sResult.Value.S16, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_SINT
    _test_arithmetic_modulus(&sParameters, TYPE_SINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_double(sResult.Value.S8, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_ULINT
    _test_arithmetic_modulus(&sParameters, TYPE_ULINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_double(sResult.Value.U64, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_UDINT
    _test_arithmetic_modulus(&sParameters, TYPE_UDINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_double(sResult.Value.U32, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_UINT
    _test_arithmetic_modulus(&sParameters, TYPE_UINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_double(sResult.Value.U16, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    //  TYPE_USINT
    _test_arithmetic_modulus(&sParameters, TYPE_USINT);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_double(sResult.Value.U8, ==, 2);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_mod(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_MODULUS_ZERO);

    ll_destroy(&sParameters);

    return MUNIT_OK;
}


