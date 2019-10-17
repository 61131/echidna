#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <runtime.h>

#include <standard/select.h>


MunitResult 
test_select_limit(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pIn, *pMaximum, *pMinimum;
    VALUE sResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    //  TYPE_LREAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_LREAL, -10.0);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_LREAL, 0.0);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_LREAL, 10.0);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, pIn->Value.Value.Double);
    value_assign(&pIn->Value, TYPE_LREAL, pMinimum->Value.Value.Double - 1.0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, pMinimum->Value.Value.Double);
    value_assign(&pIn->Value, TYPE_LREAL, pMaximum->Value.Value.Double + 1.0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LREAL);
    munit_assert_double(sResult.Value.Double, ==, pMaximum->Value.Value.Double);
    ll_destroy(&sParameters);

    //  TYPE_REAL
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_REAL, -10.0);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_REAL, 0.0);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_REAL, 10.0);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, pIn->Value.Value.Single);
    value_assign(&pIn->Value, TYPE_REAL, pMinimum->Value.Value.Single - 1.0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, pMinimum->Value.Value.Single);
    value_assign(&pIn->Value, TYPE_REAL, pMaximum->Value.Value.Single + 1.0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_REAL);
    munit_assert_float(sResult.Value.Single, ==, pMaximum->Value.Value.Single);
    ll_destroy(&sParameters);

    //  TYPE_LINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_LINT, -10);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_LINT, 0);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_LINT, 10);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, pIn->Value.Value.S64);
    value_assign(&pIn->Value, TYPE_LINT, pMinimum->Value.Value.S64 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, pMinimum->Value.Value.S64);
    value_assign(&pIn->Value, TYPE_LINT, pMaximum->Value.Value.S64 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LINT);
    munit_assert_int64(sResult.Value.S64, ==, pMaximum->Value.Value.S64);
    ll_destroy(&sParameters);

    //  TYPE_DINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_DINT, -10);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_DINT, 0);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_DINT, 10);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, pIn->Value.Value.S32);
    value_assign(&pIn->Value, TYPE_DINT, pMinimum->Value.Value.S32 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, pMinimum->Value.Value.S32);
    value_assign(&pIn->Value, TYPE_DINT, pMaximum->Value.Value.S32 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DINT);
    munit_assert_int32(sResult.Value.S32, ==, pMaximum->Value.Value.S32);
    ll_destroy(&sParameters);

    //  TYPE_INT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_INT, -10);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_INT, 0);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_INT, 10);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, pIn->Value.Value.S16);
    value_assign(&pIn->Value, TYPE_INT, pMinimum->Value.Value.S16 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, pMinimum->Value.Value.S16);
    value_assign(&pIn->Value, TYPE_INT, pMaximum->Value.Value.S16 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_INT);
    munit_assert_int16(sResult.Value.S16, ==, pMaximum->Value.Value.S16);
    ll_destroy(&sParameters);

    //  TYPE_SINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_SINT, -10);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_SINT, 0);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_SINT, 10);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_int8(sResult.Value.S8, ==, pIn->Value.Value.S8);
    value_assign(&pIn->Value, TYPE_SINT, pMinimum->Value.Value.S8 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_int8(sResult.Value.S8, ==, pMinimum->Value.Value.S8);
    value_assign(&pIn->Value, TYPE_SINT, pMaximum->Value.Value.S8 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_SINT);
    munit_assert_int8(sResult.Value.S8, ==, pMaximum->Value.Value.S8);
    ll_destroy(&sParameters);

    //  TYPE_ULINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_ULINT, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_ULINT, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_ULINT, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sResult.Value.U64, ==, pIn->Value.Value.U64);
    value_assign(&pIn->Value, TYPE_ULINT, pMinimum->Value.Value.U64 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sResult.Value.U64, ==, pMinimum->Value.Value.U64);
    value_assign(&pIn->Value, TYPE_ULINT, pMaximum->Value.Value.U64 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sResult.Value.U64, ==, pMaximum->Value.Value.U64);
    ll_destroy(&sParameters);

    //  TYPE_UDINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_UDINT, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_UDINT, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_UDINT, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sResult.Value.U32, ==, pIn->Value.Value.U32);
    value_assign(&pIn->Value, TYPE_UDINT, pMinimum->Value.Value.U32 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sResult.Value.U32, ==, pMinimum->Value.Value.U32);
    value_assign(&pIn->Value, TYPE_UDINT, pMaximum->Value.Value.U32 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sResult.Value.U32, ==, pMaximum->Value.Value.U32);
    ll_destroy(&sParameters);

    //  TYPE_UINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_UINT, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_UINT, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_UINT, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_uint16(sResult.Value.U16, ==, pIn->Value.Value.U16);
    value_assign(&pIn->Value, TYPE_UINT, pMinimum->Value.Value.U16 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_uint16(sResult.Value.U16, ==, pMinimum->Value.Value.U16);
    value_assign(&pIn->Value, TYPE_UINT, pMaximum->Value.Value.U16 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_UINT);
    munit_assert_uint16(sResult.Value.U16, ==, pMaximum->Value.Value.U16);
    ll_destroy(&sParameters);

    //  TYPE_USINT
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_USINT, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_USINT, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_USINT, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_uint8(sResult.Value.U8, ==, pIn->Value.Value.U8);
    value_assign(&pIn->Value, TYPE_USINT, pMinimum->Value.Value.U8 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_uint8(sResult.Value.U8, ==, pMinimum->Value.Value.U8);
    value_assign(&pIn->Value, TYPE_USINT, pMaximum->Value.Value.U8 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_USINT);
    munit_assert_uint8(sResult.Value.U8, ==, pMaximum->Value.Value.U8);
    ll_destroy(&sParameters);

    //  TYPE_LWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_LWORD, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_LWORD, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_LWORD, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sResult.Value.B64, ==, pIn->Value.Value.B64);
    value_assign(&pIn->Value, TYPE_LWORD, pMinimum->Value.Value.B64 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sResult.Value.B64, ==, pMinimum->Value.Value.B64);
    value_assign(&pIn->Value, TYPE_LWORD, pMaximum->Value.Value.B64 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sResult.Value.B64, ==, pMaximum->Value.Value.B64);
    ll_destroy(&sParameters);

    //  TYPE_DWORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_DWORD, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_DWORD, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_DWORD, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sResult.Value.B32, ==, pIn->Value.Value.B32);
    value_assign(&pIn->Value, TYPE_DWORD, pMinimum->Value.Value.B32 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sResult.Value.B32, ==, pMinimum->Value.Value.B32);
    value_assign(&pIn->Value, TYPE_DWORD, pMaximum->Value.Value.B32 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sResult.Value.B32, ==, pMaximum->Value.Value.B32);
    ll_destroy(&sParameters);

    //  TYPE_WORD
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_WORD, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_WORD, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_WORD, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_WORD);
    munit_assert_uint16(sResult.Value.B16, ==, pIn->Value.Value.B16);
    value_assign(&pIn->Value, TYPE_WORD, pMinimum->Value.Value.B16 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_WORD);
    munit_assert_uint16(sResult.Value.B16, ==, pMinimum->Value.Value.B16);
    value_assign(&pIn->Value, TYPE_WORD, pMaximum->Value.Value.B16 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_WORD);
    munit_assert_uint16(sResult.Value.B16, ==, pMaximum->Value.Value.B16);
    ll_destroy(&sParameters);

    //  TYPE_BYTE
    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_not_null(pMinimum = parameter_new(NULL));
    value_assign(&pMinimum->Value, TYPE_BYTE, 5);
    munit_assert_int(ll_insert(&sParameters, pMinimum), ==, 0);
    munit_assert_not_null(pIn = parameter_new(NULL));
    value_assign(&pIn->Value, TYPE_BYTE, 10);
    munit_assert_int(ll_insert(&sParameters, pIn), ==, 0);
    munit_assert_not_null(pMaximum = parameter_new(NULL));
    value_assign(&pMaximum->Value, TYPE_BYTE, 15);
    munit_assert_int(ll_insert(&sParameters, pMaximum), ==, 0);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sResult.Value.B8, ==, pIn->Value.Value.B8);
    value_assign(&pIn->Value, TYPE_BYTE, pMinimum->Value.Value.B8 - 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sResult.Value.B8, ==, pMinimum->Value.Value.B8);
    value_assign(&pIn->Value, TYPE_BYTE, pMaximum->Value.Value.B8 + 1);
    munit_assert_int(standard_limit(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sResult.Value.B8, ==, pMaximum->Value.Value.B8);
    ll_destroy(&sParameters);

    return MUNIT_OK;
}


