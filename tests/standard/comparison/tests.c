#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <cast.h>
#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>

#include <standard/comparison.h>


MunitResult 
test_comparison_eq(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_eq(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_comparison_ge(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ge(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_comparison_gt(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_gt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_comparison_le(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 0.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 0.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_le(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_comparison_lt(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_lt(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


MunitResult 
test_comparison_ne(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LREAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 1.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_REAL, 2.0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_SINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_ULINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UDINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_UINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_USINT, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_DWORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_WORD, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE, 2);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 1);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BOOL, 1);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sResult.Value.B1, ==, 0);
    ll_destroy(&sParameters);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ne(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


