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

#include <standard/bitstring.h>


static VALUE_TYPE _Type[] = {
    TYPE_LWORD,
    TYPE_DWORD,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_BOOL,
    0
};

uint64_t _Bit[64];


MunitResult 
test_bitstring_rol(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    uint64_t uValue;
    int nCount, nIndex, nType;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);

    //  TYPE_INT -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    //  TYPE_LWORD, TYPE_BYTE -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    //  TYPE_LWORD, TYPE_INT, TYPE_INT -> ERROR_PARAMETER_COUNT
    ll_delete(sParameters.Tail);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    //  IN:TYPE_INT -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN"));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    //  IN:TYPE_LWORD, N:TYPE_BYTE -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN"));
    value_assign(&pParameter->Value, TYPE_LWORD);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("N"));
    value_assign(&pParameter->Value, TYPE_BYTE);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    //  IN:TYPE_LWORD, N:TYPE_INT, OTHER:TYPE_INT -> ERROR_PARAMETER_UNKNOWN
    ll_delete(sParameters.Tail);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("N"));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("OTHER"));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_UNKNOWN);
    ll_destroy(&sParameters);

    uValue = 1;
    for(nIndex = 0; nIndex < 64; ++nIndex)
        _Bit[nIndex] = (uValue << nIndex);

    nType = 0;
    do {
        nCount = (value_typetosize(_Type[nType]) << 3);
        nCount = (_Type[nType] == TYPE_BOOL) ? 1 : nCount;
        for(nIndex = 0; nIndex <= nCount; ++nIndex) {
            ll_initialise(&sParameters, parameter_destroy);
            munit_assert_not_null(pParameter = parameter_new(NULL));
            value_assign(&pParameter->Value, _Type[nType], 1);
            munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
            munit_assert_not_null(pParameter = parameter_new(NULL));
            value_assign(&pParameter->Value, TYPE_UINT, nIndex);
            munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
            munit_assert_int(standard_rol(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
            munit_assert_uint32(sResult.Type, ==, _Type[nType]);
            munit_assert_int(cast_lword(&sResult), ==, 0);
            munit_assert_uint64(sResult.Value.B64, ==, _Bit[nIndex % nCount]);
            ll_destroy(&sParameters);
        }
    }
    while(_Type[++nType]);

    return MUNIT_OK;
}


MunitResult 
test_bitstring_ror(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    uint64_t uValue;
    int nCount, nIndex, nType;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    //  TYPE_INT -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    //  TYPE_LWORD, TYPE_BYTE -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_LWORD);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_BYTE);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    //  TYPE_LWORD, TYPE_INT, TYPE_INT -> ERROR_PARAMETER_COUNT
    ll_delete(sParameters.Tail);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    ll_destroy(&sParameters);

    //  IN:TYPE_INT -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN"));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    //  IN:TYPE_LWORD, N:TYPE_BYTE -> ERROR_PARAMETER_TYPE
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("IN"));
    value_assign(&pParameter->Value, TYPE_LWORD);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("N"));
    value_assign(&pParameter->Value, TYPE_BYTE);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    //  IN:TYPE_LWORD, N:TYPE_INT, OTHER:TYPE_INT -> ERROR_PARAMETER_UNKNOWN
    ll_delete(sParameters.Tail);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("N"));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    munit_assert_not_null(pParameter->Name = strdup("OTHER"));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_UNKNOWN);
    ll_destroy(&sParameters);

    uValue = 1;
    for(nIndex = 0; nIndex < 64; ++nIndex)
        _Bit[nIndex] = (uValue << nIndex);

    nType = 0;
    do {
        nCount = (value_typetosize(_Type[nType]) << 3);
        nCount = (_Type[nType] == TYPE_BOOL) ? 1 : nCount;
        for(nIndex = 0; nIndex <= nCount; ++nIndex) {
            ll_initialise(&sParameters, parameter_destroy);
            munit_assert_not_null(pParameter = parameter_new(NULL));
            value_assign(&pParameter->Value, _Type[nType], 1);
            munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
            munit_assert_not_null(pParameter = parameter_new(NULL));
            value_assign(&pParameter->Value, TYPE_UINT, nIndex);
            munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
            munit_assert_int(standard_ror(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
            munit_assert_uint32(sResult.Type, ==, _Type[nType]);
            munit_assert_int(cast_lword(&sResult), ==, 0);
            munit_assert_uint64(sResult.Value.B64, ==, _Bit[(nCount - nIndex) % nCount]);
            ll_destroy(&sParameters);
        }
    }
    while(_Type[++nType]);

    return MUNIT_OK;
}


