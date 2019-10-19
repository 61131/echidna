#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <runtime.h>

#include <standard/select.h>


MunitResult 
test_select_max(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pValue;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LREAL, 0.0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LREAL, -10.0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LREAL, 10.0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, 10.0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_REAL, 0.0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_REAL, -10.0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_REAL, 10.0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, 10.0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LINT, 0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LINT, -10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, 10);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_DINT, 0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_DINT, -10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_DINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, 10);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, -10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_INT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, 10);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_SINT, 0);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_SINT, -10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_SINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_int8(sResult.Value.S8, ==, 10);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_ULINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_ULINT, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_ULINT, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sResult.Value.U64, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_UDINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_UDINT, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_UDINT, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sResult.Value.U32, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_UINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_UINT, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_UINT, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_uint16(sResult.Value.U16, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_USINT, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_USINT, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_USINT, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_uint8(sResult.Value.U8, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LWORD, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LWORD, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_LWORD, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sResult.Value.B64, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_DWORD, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_DWORD, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_DWORD, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sResult.Value.B32, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_WORD, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_WORD, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_WORD, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_WORD);
    munit_assert_uint16(sResult.Value.B16, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BYTE, 10);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BYTE, 5);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BYTE, 15);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sResult.Value.B8, ==, 15);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_MISMATCH);
    ll_destroy(&sParameters);

    //  TYPE_BOOL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_not_null(pValue = parameter_new(NULL));
    value_assign(&pValue->Value, TYPE_BOOL);
    munit_assert_int(ll_insert(&sParameters, pValue), ==, 0);
    munit_assert_int(standard_max(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


