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

#include <standard/bitwise.h>


static VALUE_TYPE _Type[] = {
    TYPE_LWORD,
    TYPE_DWORD,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_BOOL,
    0
};



MunitResult 
test_bitwise_and(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    int nType;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_and(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_NONE);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_and(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_BIT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_BIT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_and(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    nType = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, _Type[nType]);
        switch(pParameter->Value.Type) {
            case TYPE_LWORD:    pParameter->Value.Value.B64 = 0xA5A5A5A5A5A5A5A5; break;
            case TYPE_DWORD:    pParameter->Value.Value.B32 = 0xA5A5A5A5; break;
            case TYPE_WORD:     pParameter->Value.Value.B16 = 0xA5A5; break;
            case TYPE_BYTE:     pParameter->Value.Value.B8 = 0xA5; break;
            case TYPE_BOOL:     pParameter->Value.Value.B1 = 1; break;
            default:
                continue;
        }
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_LWORD);
        pParameter->Value.Value.B64 = 0xF00FF00FF00FF00F;
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_and(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, _Type[nType]);
        switch(sResult.Type) {
            case TYPE_LWORD:    munit_assert_uint64(sResult.Value.B64, ==, 0xA005A005A005A005); break;
            case TYPE_DWORD:    munit_assert_uint32(sResult.Value.B32, ==, 0xA005A005); break;
            case TYPE_WORD:     munit_assert_uint16(sResult.Value.B16, ==, 0xA005); break;
            case TYPE_BYTE:     munit_assert_uint8(sResult.Value.B8, ==, 0x05); break;
            case TYPE_BOOL:     munit_assert_uint8(sResult.Value.B1, ==, 1); break;
            default:
                continue;
        }
        ll_destroy(&sParameters);
    }
    while(_Type[++nType]);

    return MUNIT_OK;
}


MunitResult 
test_bitwise_or(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    int nType;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_or(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_NONE);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_or(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_BIT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_BIT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_or(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    nType = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, _Type[nType]);
        switch(pParameter->Value.Type) {
            case TYPE_LWORD:    pParameter->Value.Value.B64 = 0xA5A5A5A5A5A5A5A5; break;
            case TYPE_DWORD:    pParameter->Value.Value.B32 = 0xA5A5A5A5; break;
            case TYPE_WORD:     pParameter->Value.Value.B16 = 0xA5A5; break;
            case TYPE_BYTE:     pParameter->Value.Value.B8 = 0xA5; break;
            case TYPE_BOOL:     pParameter->Value.Value.B1 = 0; break;
            default:
                continue;
        }
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_LWORD);
        pParameter->Value.Value.B64 = 0x5A0F5A0F5A0F5A0F;
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_or(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, _Type[nType]);
        switch(sResult.Type) {
            case TYPE_LWORD:    munit_assert_uint64(sResult.Value.B64, ==, 0xFFAFFFAFFFAFFFAF); break;
            case TYPE_DWORD:    munit_assert_uint32(sResult.Value.B32, ==, 0xFFAFFFAF); break;
            case TYPE_WORD:     munit_assert_uint16(sResult.Value.B16, ==, 0xFFAF); break;
            case TYPE_BYTE:     munit_assert_uint8(sResult.Value.B8, ==, 0xAF); break;
            case TYPE_BOOL:     munit_assert_uint8(sResult.Value.B1, ==, 1); break;
            default:
                continue;
        }
        ll_destroy(&sParameters);
    }
    while(_Type[++nType]);

    return MUNIT_OK;
}


MunitResult 
test_bitwise_xor(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    int nType;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_xor(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
    munit_assert_uint32(sResult.Type, ==, TYPE_NONE);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_xor(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_BIT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_BIT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_xor(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    nType = 0;
    do {
        ll_initialise(&sParameters, parameter_destroy);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, _Type[nType]);
        switch(pParameter->Value.Type) {
            case TYPE_LWORD:    pParameter->Value.Value.B64 = 0xA5A5A5A5A5A5A5A5; break;
            case TYPE_DWORD:    pParameter->Value.Value.B32 = 0xA5A5A5A5; break;
            case TYPE_WORD:     pParameter->Value.Value.B16 = 0xA5A5; break;
            case TYPE_BYTE:     pParameter->Value.Value.B8 = 0xA5; break;
            case TYPE_BOOL:     pParameter->Value.Value.B1 = 0; break;
            default:
                continue;
        }
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, TYPE_LWORD);
        pParameter->Value.Value.B64 = 0x5A0F5A0F5A0F5A0F;
        munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
        munit_assert_int(standard_xor(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
        munit_assert_uint32(sResult.Type, ==, _Type[nType]);
        switch(sResult.Type) {
            case TYPE_LWORD:    munit_assert_uint64(sResult.Value.B64, ==, 0xFFAAFFAAFFAAFFAA); break;
            case TYPE_DWORD:    munit_assert_uint32(sResult.Value.B32, ==, 0xFFAAFFAA); break;
            case TYPE_WORD:     munit_assert_uint16(sResult.Value.B16, ==, 0xFFAA); break;
            case TYPE_BYTE:     munit_assert_uint8(sResult.Value.B8, ==, 0xAA); break;
            case TYPE_BOOL:     munit_assert_uint8(sResult.Value.B1, ==, 1); break;
            default:
                continue;
        }
        ll_destroy(&sParameters);
    }
    while(_Type[++nType]);

    return MUNIT_OK;
}


