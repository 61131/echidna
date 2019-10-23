#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#include <munit/munit.h>

#include <grammar.h>
#include <parse.h>
#include <token.h>

#include <suite.h>


struct _TEST_LITERAL {

    char * Source;
    union {

        int64_t Integer;

        double Double;
    }
    Value;
};


MunitResult 
test_grammar_literals_base(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex;

    struct _TEST_LITERAL sValues[] = {

        { "2#1111_1111", { .Integer = 255 } },
        { "2#1110_0000", { .Integer = 224 } },
        { "8#377", { .Integer = 255 } },
        { "8#340", { .Integer = 224 } },
        { "16#FF", { .Integer = 255 } },
        { "16#E0", { .Integer = 224 } },
        { "16#ff", { .Integer = 255 } },
        { "16#e0", { .Integer = 224 } },

        { NULL, { .Integer = 0 } }
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nIndex = 0;; ++nIndex) {
        pValue = &sValues[nIndex];
        if(!pValue->Source)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: LINT := %s; END_TYPE", pValue->Source);
        if(test_parse(pContext, sLine) != 0)
            return MUNIT_FAIL;

        munit_assert_not_null(pParse = &pContext->Parse);
        munit_assert_not_null(pList = &pParse->Tokens);
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_int(pToken->Type, ==, TYPE_LIST);
        pList = (TOKEN_LIST *) pToken;
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_not_null(pToken->Name);
        munit_assert_string_equal(pToken->Name, "TEST");
        munit_assert_uint32(pToken->Value.Type, ==, TYPE_LINT);
        munit_assert_uint32(pToken->Value.Cast, ==, TYPE_LINT);
        munit_assert_int64(pToken->Value.Value.S64, ==, pValue->Value.Integer);
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


MunitResult 
test_grammar_literals_boolean(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    struct _TEST_LITERAL sValues[] = {

        { "0", { .Integer = 0 } },
        { "1", { .Integer = 1 } },
        { "FALSE", { .Integer = 0 } },
        { "TRUE", { .Integer = 1 } },

        { NULL, { .Integer = 0 } }
    };

    for(nIndex = 0;; ++nIndex) {
        pValue = &sValues[nIndex];
        if(!pValue->Source)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: BOOL := %s; END_TYPE", pValue->Source);
        if(test_parse(pContext, sLine) != 0)
            return MUNIT_FAIL;

        munit_assert_not_null(pParse = &pContext->Parse);
        munit_assert_not_null(pList = &pParse->Tokens);
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_int(pToken->Type, ==, TYPE_LIST);
        pList = (TOKEN_LIST *) pToken;
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_not_null(pToken->Name);
        munit_assert_string_equal(pToken->Name, "TEST");
        munit_assert_uint32(pToken->Value.Type, ==, TYPE_BOOL);
        munit_assert_uint32(pToken->Value.Cast, ==, TYPE_BOOL);
        munit_assert_uint8(pToken->Value.Value.B1, ==, pValue->Value.Integer);
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


MunitResult 
test_grammar_literals_integer(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex;

    struct _TEST_LITERAL sValues[] = {

        { "-12", { .Integer = -12 } },
        { "0", { .Integer = 0 } },
        { "123_456", { .Integer = 123456 } },
        { "+986", { .Integer = 986 } },

        { NULL, { .Integer = 0 } }
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nIndex = 0;; ++nIndex) {
        pValue = &sValues[nIndex];
        if(!pValue->Source)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: LINT := %s; END_TYPE", pValue->Source);
        if(test_parse(pContext, sLine) != 0)
            return MUNIT_FAIL;

        munit_assert_not_null(pParse = &pContext->Parse);
        munit_assert_not_null(pList = &pParse->Tokens);
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_int(pToken->Type, ==, TYPE_LIST);
        pList = (TOKEN_LIST *) pToken;
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_not_null(pToken->Name);
        munit_assert_string_equal(pToken->Name, "TEST");
        munit_assert_uint32(pToken->Value.Type, ==, TYPE_LINT);
        munit_assert_uint32(pToken->Value.Cast, ==, TYPE_LINT);
        munit_assert_int64(pToken->Value.Value.S64, ==, pValue->Value.Integer);
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


MunitResult 
test_grammar_literals_real(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex;

    struct _TEST_LITERAL sValues[] = {

        { "-12.0", { .Double = -12.0 } },
        { "0.0", { .Double = 0.0 } },
        { "0.4560", { .Double = 0.4560 } },
        { "3.14159_26", { .Double = 3.1415926 } },
        { "-1.34E-12", { .Double = -1.34E-12 } },
        { "-1.34e-12", { .Double = -1.34E-12 } },
        { "1.0E+6", { .Double = 1.0E+6 } },
        { "1.0e+6", { .Double = 1.0e+6 } },
        { "1.234E6", { .Double = 1.234E6 } },
        { "1.234e6", { .Double = 1.234E6 } },

        { NULL, { .Integer = 0 } }
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nIndex = 0;; ++nIndex) {
        pValue = &sValues[nIndex];
        if(!pValue->Source)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: LREAL := %s; END_TYPE", pValue->Source);
        if(test_parse(pContext, sLine) != 0)
            return MUNIT_FAIL;

        munit_assert_not_null(pParse = &pContext->Parse);
        munit_assert_not_null(pList = &pParse->Tokens);
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_int(pToken->Type, ==, TYPE_LIST);
        pList = (TOKEN_LIST *) pToken;
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_not_null(pToken->Name);
        munit_assert_string_equal(pToken->Name, "TEST");
        munit_assert_uint32(pToken->Value.Type, ==, TYPE_LREAL);
        munit_assert_uint32(pToken->Value.Cast, ==, TYPE_LREAL);
        munit_assert_double(pToken->Value.Value.Double, ==, pValue->Value.Double);
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


MunitResult 
test_grammar_literals_time(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex;

    struct _TEST_LITERAL sValues[] = {

        { "5.5d", { .Double = 4.752E+08 } },
        { "5d_14h_12.5m", { .Double = 4.8315E+08 } },
        { "5d14h12.5m", { .Double = 4.8315E+08 } },
        { "5d_14h_12m_18.5s", { .Double = 4.831385E+08 } },
        { "5d14h12m18.5s", { .Double = 4.831385E+08 } },
        { "5d_14h_12m_18s_3.5ms", { .Double = 483138003.5 } },
        { "5d14h12m18s3.5ms", { .Double = 483138003.5 } },
        { "5d_14h_12m_18s_4ms", { .Double = 483138004.0 } },
        { "5d14h12m18s4ms", { .Double = 483138004.0 } },
        { "5d_14h_12m_18s", { .Double = 4.83138E+08 } },
        { "5d14h12m18s", { .Double = 4.83138E+08 } },
        { "5d_14h_12m_3.5ms", { .Double = 483120003.5 } },
        { "5d14h12m3.5ms", { .Double = 483120003.5 } },
        { "5d_14h_12m_4ms", { .Double = 483120004.0 } },
        { "5d14h12m4ms", { .Double = 483120004.0 } },
        { "5d_14h_12m", { .Double = 4.8312E+08 } },
        { "5d14h12m", { .Double = 4.8312E+08 } },
        { "5d_14h_18.5s", { .Double = 482418500.0 } },
        { "5d14h18.5s", { .Double = 482418500.0 } },
        { "5d_14h_18s_3.5ms", { .Double = 482418003.5 } },
        { "5d14h18s3.5ms", { .Double = 482418003.5 } },
        { "5d_14h_18s_4ms", { .Double = 482418004.0 } },
        { "5d14h18s4ms", { .Double = 482418004.0 } },
        { "5d_14h_18s", { .Double = 482418000.0 } },
        { "5d14h18s", { .Double = 482418000.0 } },
        { "5d_14h_3.5ms", { .Double = 482400003.5 } },
        { "5d14h3.5ms", { .Double = 482400003.5 } },
        { "5d_14h_4ms", { .Double = 482400004.0 } },
        { "5d14h4ms", { .Double = 482400004.0 } },
        { "5d_14h", { .Double = 4.824E+08 } },
        { "5d14h", { .Double = 4.824E+08 } },
        { "5d", { .Double = 4.32E+08 } },
        { "14h_12.5m", { .Double = 5.115E+07 } },
        { "14h12.5m", { .Double = 5.115E+07 } },
        { "14h_12m_18.5s", { .Double = 51138500.0 } },
        { "14h12m18.5s", { .Double = 51138500.0 } },
        { "14h_12m_18s_3.5ms", { .Double = 51138003.5 } },
        { "14h12m18s3.5ms", { .Double = 51138003.5 } },
        { "14h_12m_18s_4ms", { .Double = 51138004.0 } },
        { "14h12m18s4ms", { .Double = 51138004.0 } },
        { "14h_12m_18s", { .Double = 5.1138E+07 } },
        { "14h12m18s", { .Double = 5.1138E+07 } },
        { "14h_12m_3.5ms", { .Double = 51120003.5 } },
        { "14h12m3.5ms", { .Double = 51120003.5 } },
        { "14h_12m_4ms", { .Double = 51120004.0 } },
        { "14h12m4ms", { .Double = 51120004.0 } },
        { "14h_12m", { .Double = 5.112E+07 } }, 
        { "14h12m", { .Double = 5.112E+07 } },
        { "14h18.5s", { .Double = 50418500.0 } }, 
        { "14h18.5s", { .Double = 50418500.0 } },
        { "14h_18s_3.5ms", { .Double = 50418003.5 } },
        { "14h18s3.5ms", { .Double = 50418003.5 } },
        { "14h_18s_4ms", { .Double = 50418004.0 } },
        { "14h18s4ms", { .Double = 50418004.0 } },
        { "14h_18s", { .Double = 5.0418E+07 } },
        { "14h18s", { .Double = 5.0418E+07 } },
        { "14h_3.5ms", { .Double = 50400003.5 } }, 
        { "14h3.5ms", { .Double = 50400003.5 } }, 
        { "14h_4ms", { .Double = 50400004.0 } }, 
        { "14h4ms", { .Double = 50400004.0 } },
        { "14h", { .Double = 5.04E+07 } },
        { "12.5m", { .Double = 7.5E+05 } },
        { "12m_18.5s", { .Double = 7.385E+05 } },
        { "12m18.5s", { .Double = 7.385E+05 } },
        { "12m_18s_3.5ms", { .Double = 738003.5 } },
        { "12m18s3.5ms", { .Double = 738003.5 } },
        { "12m_18s_4ms", { .Double = 738004.0 } },
        { "12m18s4ms", { .Double = 738004.0 } },
        { "12m_18s", { .Double = 7.38E+05 } }, 
        { "12m18s", { .Double = 7.38E+05 } },
        { "12m_3.5ms", { .Double = 720003.5 } }, 
        { "12m3.5ms", { .Double = 720003.5 } },
        { "12m_4ms", { .Double = 720004.0 } }, 
        { "12m4ms", { .Double = 720004.0 } },
        { "12m", { .Double = 7.2E+05 } },
        { "18.5s", { .Double = 1.85E+04 } },
        { "18s_3.5ms", { .Double = 18003.5 } },
        { "18s3.5ms", { .Double = 18003.5 } },
        { "18s_4ms", { .Double = 18004.0 } },
        { "18s4ms", { .Double = 18004.0 } },
        { "18s", { .Double = 1.8E+04 } },
        { "3.5ms", { .Double = 3.5 } },
        { "4ms", { .Double = 4.0 } },

        { NULL, { .Integer = 0 } }
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nIndex = 0;; ++nIndex) {
        pValue = &sValues[nIndex];
        if(!pValue->Source)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: TIME := T#%s; END_TYPE", pValue->Source);
        if(test_parse(pContext, sLine) != 0)
            return MUNIT_FAIL;

        munit_assert_not_null(pParse = &pContext->Parse);
        munit_assert_not_null(pList = &pParse->Tokens);
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_int(pToken->Type, ==, TYPE_LIST);
        pList = (TOKEN_LIST *) pToken;
        munit_assert_size(pList->List.Size, ==, 1);
        munit_assert_not_null(pElement = pList->List.Head);

        munit_assert_not_null(pToken = (TOKEN *) pElement->Data);
        munit_assert_int(pToken->Id, ==, TYPE);
        munit_assert_not_null(pToken->Name);
        munit_assert_string_equal(pToken->Name, "TEST");
        munit_assert_uint32(pToken->Value.Type, ==, TYPE_TIME);
        munit_assert_uint32(pToken->Value.Cast, ==, TYPE_TIME);
        munit_assert_float(pToken->Value.Value.Time, ==, (float) pValue->Value.Double);
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


MunitResult 
test_grammar_literals_type(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    return MUNIT_OK;
}


