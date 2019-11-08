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

    int Result;
};


MunitResult
test_grammar_literals_bitstring(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    VALUE sValue;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex, nType;

    char * sType[] = {
        "LWORD",
        "DWORD",
        "WORD",
        "BYTE",

        NULL
    };

    struct _TEST_LITERAL sValues[] = {

        { "0", { .Integer = 0 } },
        { "123_456", { .Integer = 123456 } },
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

    for(nType = 0; sType[nType] != NULL; ++nType) {
        for(nIndex = 0;; ++nIndex) {
            pValue = &sValues[nIndex];
            if(!pValue->Source)
                break;
            snprintf(sLine, sizeof(sLine), "TYPE TEST: %s := %s#%s; END_TYPE", 
                    sType[nType], 
                    sType[nType], 
                    pValue->Source);
            value_initialise(&sValue);
            munit_assert_int(value_strtotype(&sValue, sType[nType]), ==, 0);
            munit_assert_uint32(sValue.Type, !=, TYPE_NONE);
            switch(sValue.Type) {
                case TYPE_UINT:
                    if(pValue->Value.Integer > UINT16_MAX)
                        continue;
                    break;

                case TYPE_USINT:
                    if(pValue->Value.Integer > UINT8_MAX)
                        continue;
                    break;

                default:
                    break;
            }
            fprintf(stderr, "%s\n", sLine);
            munit_assert_int(test_parse(pContext, sLine), ==, 0);

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
            munit_assert_uint32(pToken->Value.Type, ==, sValue.Type);
            munit_assert_uint32(pToken->Value.Cast, ==, sValue.Type);
            munit_assert_int64(pToken->Value.Value.S64, ==, pValue->Value.Integer);
            munit_assert_null(pElement->Next);

            parse_reset(pContext, pParse);
        }
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
test_grammar_literals_datetime(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex, nPrefix, nResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    struct _TEST_LITERAL sDate[] = {

        { "2000-01-01", { .Integer = 946684800 } },
        { "2000-00-01", { .Integer = 0 }, -1 },
        { "2000-13-01", { .Integer = 0 }, -1 },
        { "2000-01-00", { .Integer = 0 }, -1 },
        { "2000-01-32", { .Integer = 0 }, -1 },
        { "1899-12-31", { .Integer = 0 }, -1 },

        { NULL }
    };
    struct _TEST_LITERAL sTime[] = {

        { "00:00:00", { .Integer = 0 } },
        { "12:00:00", { .Integer = 43200 } },
        { "23:59:59", { .Integer = 86399 } },
        { "24:00:00", { .Integer = 0 }, -1 },
        { "23:60:00", { .Integer = 0 }, -1 },
        { "23:00:60", { .Integer = 0 }, -1 },

        { NULL }
    };
    struct _TEST_LITERAL sDateTime[] = {

        { "2000-01-01-00:00:00", { .Integer = 946684800 } },
        { "2000-01-01-12:00:00", { .Integer = 946728000 } },
        { "2000-01-01-23:59:59", { .Integer = 946771199 } },
        { "2000-00-01-00:00:00", { .Integer = 0 }, -1 },
        { "2000-01-01-24:00:00", { .Integer = 0 }, -1 },

        { NULL }
    };

    //  TYPE_DATE

    for(nIndex = 0;; ++nIndex) {
        pValue = &sDate[nIndex];
        if(!pValue->Source)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: DATE := %s; END_TYPE", pValue->Source);
        fprintf(stderr, "%s\n", sLine);
        nResult = test_parse(pContext, sLine);
        munit_assert_int(nResult, ==, pValue->Result);
        if(nResult != 0)
            continue;

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
        munit_assert_uint32(pToken->Value.Type, ==, TYPE_DATE);
        munit_assert_uint32(pToken->Value.Cast, ==, TYPE_DATE);
        munit_assert_uint64((uint64_t) pToken->Value.Value.DateTime, ==, pValue->Value.Integer);
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    //  TYPE_TOD

    char * pTOD[] = {
        "TIME_OF_DAY",
        "TOD",
    };

    for(nPrefix = 0; nPrefix < 2; ++nPrefix) {
        for(nIndex = 0;; ++nIndex) {
            pValue = &sTime[nIndex];
            if(!pValue->Source)
                break;
            snprintf(sLine, sizeof(sLine), "TYPE TEST: %s := %s; END_TYPE", pTOD[nPrefix], pValue->Source);
            fprintf(stderr, "%s\n", sLine);
            nResult = test_parse(pContext, sLine);
            munit_assert_int(nResult, ==, pValue->Result);
            if(nResult != 0)
                continue;

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
            munit_assert_uint32(pToken->Value.Type, ==, TYPE_TOD);
            munit_assert_uint32(pToken->Value.Cast, ==, TYPE_TOD);
            munit_assert_uint64((uint64_t) pToken->Value.Value.DateTime, ==, pValue->Value.Integer);
            munit_assert_null(pElement->Next);

            parse_reset(pContext, pParse);
        }
    }

    //  TYPE_DT

    char * pDT[] = {
        "DATE_AND_TIME",
        "DT",
    };

    for(nPrefix = 0; nPrefix < 2; ++nPrefix) {
        for(nIndex = 0;; ++nIndex) {
            pValue = &sDateTime[nIndex];
            if(!pValue->Source)
                break;
            snprintf(sLine, sizeof(sLine), "TYPE TEST: %s := DT#%s; END_TYPE", pDT[nPrefix], pValue->Source);
            fprintf(stderr, "%s\n", sLine);
            nResult = test_parse(pContext, sLine);
            munit_assert_int(nResult, ==, pValue->Result);
            if(nResult != 0)
                continue;

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
            munit_assert_uint32(pToken->Value.Type, ==, TYPE_DT);
            munit_assert_uint32(pToken->Value.Cast, ==, TYPE_DT);
            munit_assert_uint64((uint64_t) pToken->Value.Value.DateTime, ==, pValue->Value.Integer);
            munit_assert_null(pElement->Next);

            parse_reset(pContext, pParse);
        }
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
    VALUE sValue;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex, nType;

    char * sType[] = {
        "LINT",
        "DINT",
        "INT",
        "SINT",
        "ULINT",
        "UDINT",
        "UINT",
        "USINT",

        NULL
    };

    struct _TEST_LITERAL sValues[] = {

        { "-12", { .Integer = -12 } },
        { "0", { .Integer = 0 } },
        { "123_456", { .Integer = 123456 } },
        { "+986", { .Integer = 986 } },
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

    for(nType = 0; sType[nType] != NULL; ++nType) {
        for(nIndex = 0;; ++nIndex) {
            pValue = &sValues[nIndex];
            if(!pValue->Source)
                break;
            snprintf(sLine, sizeof(sLine), "TYPE TEST: %s := %s#%s; END_TYPE", 
                    sType[nType], 
                    sType[nType], 
                    pValue->Source);
            value_initialise(&sValue);
            munit_assert_int(value_strtotype(&sValue, sType[nType]), ==, 0);
            munit_assert_uint32(sValue.Type, !=, TYPE_NONE);
            switch(sValue.Type) {
                case TYPE_DINT:
                    if((pValue->Value.Integer > ((int64_t) sValue.Maximum.S32)) ||
                            (pValue->Value.Integer < ((int64_t) sValue.Minimum.S32)))
                        continue;
                    break;
                            
                case TYPE_INT:
                    if((pValue->Value.Integer > ((int64_t) sValue.Maximum.S16)) ||
                            (pValue->Value.Integer < ((int64_t) sValue.Minimum.S16)))
                        continue;
                    break;
                            
                case TYPE_SINT:
                    if((pValue->Value.Integer > ((int64_t) sValue.Maximum.S8)) ||
                            (pValue->Value.Integer < ((int64_t) sValue.Minimum.S8)))
                        continue;
                    break;
                            
                case TYPE_ULINT:
                    if(pValue->Value.Integer < 0)
                        continue;
                    break;

                case TYPE_UDINT:
                    if((pValue->Value.Integer > UINT32_MAX) ||
                            (pValue->Value.Integer < 0))
                        continue;
                    break;

                case TYPE_UINT:
                    if((pValue->Value.Integer > UINT16_MAX) ||
                            (pValue->Value.Integer < 0))
                        continue;
                    break;

                case TYPE_USINT:
                    if((pValue->Value.Integer > UINT8_MAX) ||
                            (pValue->Value.Integer < 0))
                        continue;
                    break;

                default:
                    break;
            }
            fprintf(stderr, "%s\n", sLine);
            munit_assert_int(test_parse(pContext, sLine), ==, 0);

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
            munit_assert_uint32(pToken->Value.Type, ==, sValue.Type);
            munit_assert_uint32(pToken->Value.Cast, ==, sValue.Type);
            munit_assert_int64(pToken->Value.Value.S64, ==, pValue->Value.Integer);
            munit_assert_null(pElement->Next);

            parse_reset(pContext, pParse);
        }
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
    VALUE sValue;
    struct _TEST_LITERAL *pValue;
    char sLine[LINE_MAX];
    int nIndex, nType;

    char * sType[] = {
        "LREAL",
        "REAL",
        NULL,
    };

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

        { NULL }
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nType = 0; sType[nType] != NULL; ++nType) {
        for(nIndex = 0;; ++nIndex) {
            pValue = &sValues[nIndex];
            if(!pValue->Source)
                break;
            snprintf(sLine, sizeof(sLine), "TYPE TEST: %s := %s#%s; END_TYPE", 
                    sType[nType], 
                    sType[nType], 
                    pValue->Source);
            value_initialise(&sValue);
            munit_assert_int(value_strtotype(&sValue, sType[nType]), ==, 0);
            munit_assert_uint32(sValue.Type, !=, TYPE_NONE);
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
            munit_assert_uint32(pToken->Value.Type, ==, sValue.Type);
            munit_assert_uint32(pToken->Value.Cast, ==, sValue.Type);
            switch(pToken->Value.Type) {
                case TYPE_LREAL:
                    munit_assert_double(pToken->Value.Value.Double, ==, pValue->Value.Double);
                    break;

                case TYPE_REAL:
                    munit_assert_float(pToken->Value.Value.Single, ==, (float) pValue->Value.Double);
                    break;

                default:
                    break;
            }
            munit_assert_null(pElement->Next);

            parse_reset(pContext, pParse);
        }
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
    int nIndex, nPrefix, nResult;

    char * sPrefix[] = {
        "t#",
        "time#",
    };

    struct _TEST_LITERAL sValues[] = {

        { "-4ms", { .Double = -4.0 }, 0 },
        { "4ms", { .Double = 4.0 }, 0 },
        { "-3.5ms", { .Double = -3.5 }, 0 },
        { "3.5ms", { .Double = 3.5 }, 0 },
        { "-18s", { .Double = -18000.0 }, 0 },
        { "-18s-4ms", { .Double = 0.0 }, -1 },
        { "-18s4ms", { .Double = -18004.0 }, 0 },
        { "-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-18s3.5ms", { .Double = -18003.5 }, 0 },
        { "18s", { .Double = 18000.0 }, 0 },
        { "18s-4ms", { .Double = 0.0 }, -1 },
        { "18s4ms", { .Double = 18004.0 }, 0 },
        { "18s-3.5ms", { .Double = 0.0 }, -1 },
        { "18s3.5ms", { .Double = 18003.5 }, 0 },
        { "-18.5s", { .Double = -18500.0 }, 0 },
        { "-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-18.5s4ms", { .Double = -18504.0 }, 0 },
        { "-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-18.5s3.5ms", { .Double = -18503.5 }, 0 },
        { "18.5s", { .Double = 18500.0 }, 0 },
        { "18.5s-4ms", { .Double = 0.0 }, -1 },
        { "18.5s4ms", { .Double = 18504.0 }, 0 },
        { "18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "18.5s3.5ms", { .Double = 18503.5 }, 0 },
        { "-12m", { .Double = -720000.0 }, 0 },
        { "-12m-4ms", { .Double = 0.0 }, -1 },
        { "-12m4ms", { .Double = -720004.0 }, 0 },
        { "-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-12m3.5ms", { .Double = -720003.5 }, 0 },
        { "-12m-18s", { .Double = 0.0 }, -1 },
        { "-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-12m18s", { .Double = -738000.0 }, 0 },
        { "-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-12m18s4ms", { .Double = -738004.0 }, 0 },
        { "-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-12m18s3.5ms", { .Double = -738003.5 }, 0 },
        { "-12m-18.5s", { .Double = 0.0 }, -1 },
        { "-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-12m18.5s", { .Double = -738500.0 }, 0 },
        { "-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-12m18.5s4ms", { .Double = -738504.0 }, 0 },
        { "-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-12m18.5s3.5ms", { .Double = -738503.5 }, 0 },
        { "12m", { .Double = 720000.0 }, 0 },
        { "12m-4ms", { .Double = 0.0 }, -1 },
        { "12m4ms", { .Double = 720004.0 }, 0 },
        { "12m-3.5ms", { .Double = 0.0 }, -1 },
        { "12m3.5ms", { .Double = 720003.5 }, 0 },
        { "12m-18s", { .Double = 0.0 }, -1 },
        { "12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "12m-18s4ms", { .Double = 0.0 }, -1 },
        { "12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "12m18s", { .Double = 738000.0 }, 0 },
        { "12m18s-4ms", { .Double = 0.0 }, -1 },
        { "12m18s4ms", { .Double = 738004.0 }, 0 },
        { "12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "12m18s3.5ms", { .Double = 738003.5 }, 0 },
        { "12m-18.5s", { .Double = 0.0 }, -1 },
        { "12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "12m18.5s", { .Double = 738500.0 }, 0 },
        { "12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "12m18.5s4ms", { .Double = 738504.0 }, 0 },
        { "12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "12m18.5s3.5ms", { .Double = 738503.5 }, 0 },
        { "-12.5m", { .Double = -750000.0 }, 0 },
        { "-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-12.5m4ms", { .Double = -750004.0 }, 0 },
        { "-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-12.5m3.5ms", { .Double = -750003.5 }, 0 },
        { "-12.5m-18s", { .Double = 0.0 }, -1 },
        { "-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-12.5m18s", { .Double = -768000.0 }, 0 },
        { "-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-12.5m18s4ms", { .Double = -768004.0 }, 0 },
        { "-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-12.5m18s3.5ms", { .Double = -768003.5 }, 0 },
        { "-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-12.5m18.5s", { .Double = -768500.0 }, 0 },
        { "-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-12.5m18.5s4ms", { .Double = -768504.0 }, 0 },
        { "-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-12.5m18.5s3.5ms", { .Double = -768503.5 }, 0 },
        { "12.5m", { .Double = 750000.0 }, 0 },
        { "12.5m-4ms", { .Double = 0.0 }, -1 },
        { "12.5m4ms", { .Double = 750004.0 }, 0 },
        { "12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m3.5ms", { .Double = 750003.5 }, 0 },
        { "12.5m-18s", { .Double = 0.0 }, -1 },
        { "12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m18s", { .Double = 768000.0 }, 0 },
        { "12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "12.5m18s4ms", { .Double = 768004.0 }, 0 },
        { "12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m18s3.5ms", { .Double = 768003.5 }, 0 },
        { "12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m18.5s", { .Double = 768500.0 }, 0 },
        { "12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "12.5m18.5s4ms", { .Double = 768504.0 }, 0 },
        { "12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "12.5m18.5s3.5ms", { .Double = 768503.5 }, 0 },
        { "-14h", { .Double = -50400000.0 }, 0 },
        { "-14h-4ms", { .Double = 0.0 }, -1 },
        { "-14h4ms", { .Double = -50400004.0 }, 0 },
        { "-14h-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h3.5ms", { .Double = -50400003.5 }, 0 },
        { "-14h-18s", { .Double = 0.0 }, -1 },
        { "-14h-18s4ms", { .Double = 0.0 }, -1 },
        { "-14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h18s", { .Double = -50418000.0 }, 0 },
        { "-14h18s-4ms", { .Double = 0.0 }, -1 },
        { "-14h18s4ms", { .Double = -50418004.0 }, 0 },
        { "-14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h18s3.5ms", { .Double = -50418003.5 }, 0 },
        { "-14h-18.5s", { .Double = 0.0 }, -1 },
        { "-14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h18.5s", { .Double = -50418500.0 }, 0 },
        { "-14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-14h18.5s4ms", { .Double = -50418504.0 }, 0 },
        { "-14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h18.5s3.5ms", { .Double = -50418503.5 }, 0 },
        { "-14h-12m", { .Double = 0.0 }, -1 },
        { "-14h-12m4ms", { .Double = 0.0 }, -1 },
        { "-14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-14h-12m18s", { .Double = 0.0 }, -1 },
        { "-14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "-14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12m", { .Double = -51120000.0 }, 0 },
        { "-14h12m-4ms", { .Double = 0.0 }, -1 },
        { "-14h12m4ms", { .Double = -51120004.0 }, 0 },
        { "-14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12m3.5ms", { .Double = -51120003.5 }, 0 },
        { "-14h12m-18s", { .Double = 0.0 }, -1 },
        { "-14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12m18s", { .Double = -51138000.0 }, 0 },
        { "-14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-14h12m18s4ms", { .Double = -51138004.0 }, 0 },
        { "-14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12m18s3.5ms", { .Double = -51138003.5 }, 0 },
        { "-14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "-14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12m18.5s", { .Double = -51138500.0 }, 0 },
        { "-14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-14h12m18.5s4ms", { .Double = -51138504.0 }, 0 },
        { "-14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12m18.5s3.5ms", { .Double = -51138503.5 }, 0 },
        { "-14h-12.5m", { .Double = 0.0 }, -1 },
        { "-14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "-14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m", { .Double = -51150000.0 }, 0 },
        { "-14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m4ms", { .Double = -51150004.0 }, 0 },
        { "-14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m3.5ms", { .Double = -51150003.5 }, 0 },
        { "-14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "-14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m18s", { .Double = -51168000.0 }, 0 },
        { "-14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m18s4ms", { .Double = -51168004.0 }, 0 },
        { "-14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m18s3.5ms", { .Double = -51168003.5 }, 0 },
        { "-14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m18.5s", { .Double = -51168500.0 }, 0 },
        { "-14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m18.5s4ms", { .Double = -51168504.0 }, 0 },
        { "-14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14h12.5m18.5s3.5ms", { .Double = -51168503.5 }, 0 },
        { "14h", { .Double = 50400000.0 }, 0 },
        { "14h-4ms", { .Double = 0.0 }, -1 },
        { "14h4ms", { .Double = 50400004.0 }, 0 },
        { "14h-3.5ms", { .Double = 0.0 }, -1 },
        { "14h3.5ms", { .Double = 50400003.5 }, 0 },
        { "14h-18s", { .Double = 0.0 }, -1 },
        { "14h-18s-4ms", { .Double = 0.0 }, -1 },
        { "14h-18s4ms", { .Double = 0.0 }, -1 },
        { "14h-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h18s", { .Double = 50418000.0 }, 0 },
        { "14h18s-4ms", { .Double = 0.0 }, -1 },
        { "14h18s4ms", { .Double = 50418004.0 }, 0 },
        { "14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h18s3.5ms", { .Double = 50418003.5 }, 0 },
        { "14h-18.5s", { .Double = 0.0 }, -1 },
        { "14h-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h18.5s", { .Double = 50418500.0 }, 0 },
        { "14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h18.5s4ms", { .Double = 50418504.0 }, 0 },
        { "14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h18.5s3.5ms", { .Double = 50418503.5 }, 0 },
        { "14h-12m", { .Double = 0.0 }, -1 },
        { "14h-12m-4ms", { .Double = 0.0 }, -1 },
        { "14h-12m4ms", { .Double = 0.0 }, -1 },
        { "14h-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m-18s", { .Double = 0.0 }, -1 },
        { "14h-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "14h-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m18s", { .Double = 0.0 }, -1 },
        { "14h-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "14h-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m-18.5s", { .Double = 0.0 }, -1 },
        { "14h-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "14h-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m", { .Double = 51120000.0 }, 0 },
        { "14h12m-4ms", { .Double = 0.0 }, -1 },
        { "14h12m4ms", { .Double = 51120004.0 }, 0 },
        { "14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m3.5ms", { .Double = 51120003.5 }, 0 },
        { "14h12m-18s", { .Double = 0.0 }, -1 },
        { "14h12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "14h12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m18s", { .Double = 51138000.0 }, 0 },
        { "14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "14h12m18s4ms", { .Double = 51138004.0 }, 0 },
        { "14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m18s3.5ms", { .Double = 51138003.5 }, 0 },
        { "14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "14h12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m18.5s", { .Double = 51138500.0 }, 0 },
        { "14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h12m18.5s4ms", { .Double = 51138504.0 }, 0 },
        { "14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12m18.5s3.5ms", { .Double = 51138503.5 }, 0 },
        { "14h-12.5m", { .Double = 0.0 }, -1 },
        { "14h-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m-18s", { .Double = 0.0 }, -1 },
        { "14h-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "14h-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "14h-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "14h-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m", { .Double = 51150000.0 }, 0 },
        { "14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m4ms", { .Double = 51150004.0 }, 0 },
        { "14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m3.5ms", { .Double = 51150003.5 }, 0 },
        { "14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "14h12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m18s", { .Double = 51168000.0 }, 0 },
        { "14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m18s4ms", { .Double = 51168004.0 }, 0 },
        { "14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m18s3.5ms", { .Double = 51168003.5 }, 0 },
        { "14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "14h12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m18.5s", { .Double = 51168500.0 }, 0 },
        { "14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14h12.5m18.5s4ms", { .Double = 51168504.0 }, 0 },
        { "14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14h12.5m18.5s3.5ms", { .Double = 51168503.5 }, 0 },
        { "-14.5h", { .Double = -52200000.0 }, 0 },
        { "-14.5h-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h4ms", { .Double = -52200004.0 }, 0 },
        { "-14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h3.5ms", { .Double = -52200003.5 }, 0 },
        { "-14.5h-18s", { .Double = 0.0 }, -1 },
        { "-14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h18s", { .Double = -52218000.0 }, 0 },
        { "-14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h18s4ms", { .Double = -52218004.0 }, 0 },
        { "-14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h18s3.5ms", { .Double = -52218003.5 }, 0 },
        { "-14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "-14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h18.5s", { .Double = -52218500.0 }, 0 },
        { "-14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h18.5s4ms", { .Double = -52218504.0 }, 0 },
        { "-14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h18.5s3.5ms", { .Double = -52218503.5 }, 0 },
        { "-14.5h-12m", { .Double = 0.0 }, -1 },
        { "-14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "-14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "-14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m", { .Double = -52920000.0 }, 0 },
        { "-14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m4ms", { .Double = -52920004.0 }, 0 },
        { "-14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m3.5ms", { .Double = -52920003.5 }, 0 },
        { "-14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "-14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m18s", { .Double = -52938000.0 }, 0 },
        { "-14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m18s4ms", { .Double = -52938004.0 }, 0 },
        { "-14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m18s3.5ms", { .Double = -52938003.5 }, 0 },
        { "-14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "-14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m18.5s", { .Double = -52938500.0 }, 0 },
        { "-14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m18.5s4ms", { .Double = -52938504.0 }, 0 },
        { "-14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12m18.5s3.5ms", { .Double = -52938503.5 }, 0 },
        { "-14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m", { .Double = -52950000.0 }, 0 },
        { "-14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m4ms", { .Double = -52950004.0 }, 0 },
        { "-14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m3.5ms", { .Double = -52950003.5 }, 0 },
        { "-14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m18s", { .Double = -52968000.0 }, 0 },
        { "-14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m18s4ms", { .Double = -52968004.0 }, 0 },
        { "-14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m18s3.5ms", { .Double = -52968003.5 }, 0 },
        { "-14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m18.5s", { .Double = -52968500.0 }, 0 },
        { "-14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m18.5s4ms", { .Double = -52968504.0 }, 0 },
        { "-14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-14.5h12.5m18.5s3.5ms", { .Double = -52968503.5 }, 0 },
        { "14.5h", { .Double = 52200000.0 }, 0 },
        { "14.5h-4ms", { .Double = 0.0 }, -1 },
        { "14.5h4ms", { .Double = 52200004.0 }, 0 },
        { "14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h3.5ms", { .Double = 52200003.5 }, 0 },
        { "14.5h-18s", { .Double = 0.0 }, -1 },
        { "14.5h-18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h18s", { .Double = 52218000.0 }, 0 },
        { "14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h18s4ms", { .Double = 52218004.0 }, 0 },
        { "14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h18s3.5ms", { .Double = 52218003.5 }, 0 },
        { "14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "14.5h-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h18.5s", { .Double = 52218500.0 }, 0 },
        { "14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h18.5s4ms", { .Double = 52218504.0 }, 0 },
        { "14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h18.5s3.5ms", { .Double = 52218503.5 }, 0 },
        { "14.5h-12m", { .Double = 0.0 }, -1 },
        { "14.5h-12m-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m-18s", { .Double = 0.0 }, -1 },
        { "14.5h-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "14.5h-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m-18.5s", { .Double = 0.0 }, -1 },
        { "14.5h-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "14.5h-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m", { .Double = 52920000.0 }, 0 },
        { "14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m4ms", { .Double = 52920004.0 }, 0 },
        { "14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m3.5ms", { .Double = 52920003.5 }, 0 },
        { "14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "14.5h12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m18s", { .Double = 52938000.0 }, 0 },
        { "14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m18s4ms", { .Double = 52938004.0 }, 0 },
        { "14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m18s3.5ms", { .Double = 52938003.5 }, 0 },
        { "14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "14.5h12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m18.5s", { .Double = 52938500.0 }, 0 },
        { "14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12m18.5s4ms", { .Double = 52938504.0 }, 0 },
        { "14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12m18.5s3.5ms", { .Double = 52938503.5 }, 0 },
        { "14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-18s", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m", { .Double = 52950000.0 }, 0 },
        { "14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m4ms", { .Double = 52950004.0 }, 0 },
        { "14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m3.5ms", { .Double = 52950003.5 }, 0 },
        { "14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m18s", { .Double = 52968000.0 }, 0 },
        { "14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m18s4ms", { .Double = 52968004.0 }, 0 },
        { "14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m18s3.5ms", { .Double = 52968003.5 }, 0 },
        { "14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m18.5s", { .Double = 52968500.0 }, 0 },
        { "14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m18.5s4ms", { .Double = 52968504.0 }, 0 },
        { "14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "14.5h12.5m18.5s3.5ms", { .Double = 52968503.5 }, 0 },
        { "-5d", { .Double = -432000000.0 }, 0 },
        { "-5d-4ms", { .Double = 0.0 }, -1 },
        { "-5d4ms", { .Double = -432000004.0 }, 0 },
        { "-5d-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d3.5ms", { .Double = -432000003.5 }, 0 },
        { "-5d-18s", { .Double = 0.0 }, -1 },
        { "-5d-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d18s", { .Double = -432018000.0 }, 0 },
        { "-5d18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d18s4ms", { .Double = -432018004.0 }, 0 },
        { "-5d18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d18s3.5ms", { .Double = -432018003.5 }, 0 },
        { "-5d-18.5s", { .Double = 0.0 }, -1 },
        { "-5d-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d18.5s", { .Double = -432018500.0 }, 0 },
        { "-5d18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d18.5s4ms", { .Double = -432018504.0 }, 0 },
        { "-5d18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d18.5s3.5ms", { .Double = -432018503.5 }, 0 },
        { "-5d-12m", { .Double = 0.0 }, -1 },
        { "-5d-12m4ms", { .Double = 0.0 }, -1 },
        { "-5d-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-12m18s", { .Double = 0.0 }, -1 },
        { "-5d-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-12m18.5s", { .Double = 0.0 }, -1 },
        { "-5d-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12m", { .Double = -432720000.0 }, 0 },
        { "-5d12m-4ms", { .Double = 0.0 }, -1 },
        { "-5d12m4ms", { .Double = -432720004.0 }, 0 },
        { "-5d12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12m3.5ms", { .Double = -432720003.5 }, 0 },
        { "-5d12m-18s", { .Double = 0.0 }, -1 },
        { "-5d12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12m18s", { .Double = -432738000.0 }, 0 },
        { "-5d12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d12m18s4ms", { .Double = -432738004.0 }, 0 },
        { "-5d12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12m18s3.5ms", { .Double = -432738003.5 }, 0 },
        { "-5d12m-18.5s", { .Double = 0.0 }, -1 },
        { "-5d12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12m18.5s", { .Double = -432738500.0 }, 0 },
        { "-5d12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d12m18.5s4ms", { .Double = -432738504.0 }, 0 },
        { "-5d12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12m18.5s3.5ms", { .Double = -432738503.5 }, 0 },
        { "-5d-12.5m", { .Double = 0.0 }, -1 },
        { "-5d-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5d-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-12.5m18s", { .Double = 0.0 }, -1 },
        { "-5d-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5d-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m", { .Double = -432750000.0 }, 0 },
        { "-5d12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m4ms", { .Double = -432750004.0 }, 0 },
        { "-5d12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m3.5ms", { .Double = -432750003.5 }, 0 },
        { "-5d12.5m-18s", { .Double = 0.0 }, -1 },
        { "-5d12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m18s", { .Double = -432768000.0 }, 0 },
        { "-5d12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m18s4ms", { .Double = -432768004.0 }, 0 },
        { "-5d12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m18s3.5ms", { .Double = -432768003.5 }, 0 },
        { "-5d12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-5d12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m18.5s", { .Double = -432768500.0 }, 0 },
        { "-5d12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m18.5s4ms", { .Double = -432768504.0 }, 0 },
        { "-5d12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d12.5m18.5s3.5ms", { .Double = -432768503.5 }, 0 },
        { "-5d-14h", { .Double = 0.0 }, -1 },
        { "-5d-14h4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h18s", { .Double = 0.0 }, -1 },
        { "-5d-14h18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h18.5s", { .Double = 0.0 }, -1 },
        { "-5d-14h18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12m", { .Double = 0.0 }, -1 },
        { "-5d-14h12m4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12m18s", { .Double = 0.0 }, -1 },
        { "-5d-14h12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12m18.5s", { .Double = 0.0 }, -1 },
        { "-5d-14h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m18s", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h", { .Double = -482400000.0 }, 0 },
        { "-5d14h-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h4ms", { .Double = -482400004.0 }, 0 },
        { "-5d14h-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h3.5ms", { .Double = -482400003.5 }, 0 },
        { "-5d14h-18s", { .Double = 0.0 }, -1 },
        { "-5d14h-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h18s", { .Double = -482418000.0 }, 0 },
        { "-5d14h18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h18s4ms", { .Double = -482418004.0 }, 0 },
        { "-5d14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h18s3.5ms", { .Double = -482418003.5 }, 0 },
        { "-5d14h-18.5s", { .Double = 0.0 }, -1 },
        { "-5d14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h18.5s", { .Double = -482418500.0 }, 0 },
        { "-5d14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h18.5s4ms", { .Double = -482418504.0 }, 0 },
        { "-5d14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h18.5s3.5ms", { .Double = -482418503.5 }, 0 },
        { "-5d14h-12m", { .Double = 0.0 }, -1 },
        { "-5d14h-12m4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12m18s", { .Double = 0.0 }, -1 },
        { "-5d14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "-5d14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m", { .Double = -483120000.0 }, 0 },
        { "-5d14h12m-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m4ms", { .Double = -483120004.0 }, 0 },
        { "-5d14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m3.5ms", { .Double = -483120003.5 }, 0 },
        { "-5d14h12m-18s", { .Double = 0.0 }, -1 },
        { "-5d14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m18s", { .Double = -483138000.0 }, 0 },
        { "-5d14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m18s4ms", { .Double = -483138004.0 }, 0 },
        { "-5d14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m18s3.5ms", { .Double = -483138003.5 }, 0 },
        { "-5d14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "-5d14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m18.5s", { .Double = -483138500.0 }, 0 },
        { "-5d14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m18.5s4ms", { .Double = -483138504.0 }, 0 },
        { "-5d14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12m18.5s3.5ms", { .Double = -483138503.5 }, 0 },
        { "-5d14h-12.5m", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m", { .Double = -483150000.0 }, 0 },
        { "-5d14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m4ms", { .Double = -483150004.0 }, 0 },
        { "-5d14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m3.5ms", { .Double = -483150003.5 }, 0 },
        { "-5d14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m18s", { .Double = -483168000.0 }, 0 },
        { "-5d14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m18s4ms", { .Double = -483168004.0 }, 0 },
        { "-5d14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m18s3.5ms", { .Double = -483168003.5 }, 0 },
        { "-5d14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m18.5s", { .Double = -483168500.0 }, 0 },
        { "-5d14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m18.5s4ms", { .Double = -483168504.0 }, 0 },
        { "-5d14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14h12.5m18.5s3.5ms", { .Double = -483168503.5 }, 0 },
        { "-5d-14.5h", { .Double = 0.0 }, -1 },
        { "-5d-14.5h4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h18s", { .Double = 0.0 }, -1 },
        { "-5d-14.5h18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h18.5s", { .Double = 0.0 }, -1 },
        { "-5d-14.5h18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m18s", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m18.5s", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m18s", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d-14.5h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h", { .Double = -484200000.0 }, 0 },
        { "-5d14.5h-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h4ms", { .Double = -484200004.0 }, 0 },
        { "-5d14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h3.5ms", { .Double = -484200003.5 }, 0 },
        { "-5d14.5h-18s", { .Double = 0.0 }, -1 },
        { "-5d14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h18s", { .Double = -484218000.0 }, 0 },
        { "-5d14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h18s4ms", { .Double = -484218004.0 }, 0 },
        { "-5d14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h18s3.5ms", { .Double = -484218003.5 }, 0 },
        { "-5d14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "-5d14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h18.5s", { .Double = -484218500.0 }, 0 },
        { "-5d14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h18.5s4ms", { .Double = -484218504.0 }, 0 },
        { "-5d14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h18.5s3.5ms", { .Double = -484218503.5 }, 0 },
        { "-5d14.5h-12m", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m", { .Double = -484920000.0 }, 0 },
        { "-5d14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m4ms", { .Double = -484920004.0 }, 0 },
        { "-5d14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m3.5ms", { .Double = -484920003.5 }, 0 },
        { "-5d14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m18s", { .Double = -484938000.0 }, 0 },
        { "-5d14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m18s4ms", { .Double = -484938004.0 }, 0 },
        { "-5d14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m18s3.5ms", { .Double = -484938003.5 }, 0 },
        { "-5d14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m18.5s", { .Double = -484938500.0 }, 0 },
        { "-5d14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m18.5s4ms", { .Double = -484938504.0 }, 0 },
        { "-5d14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12m18.5s3.5ms", { .Double = -484938503.5 }, 0 },
        { "-5d14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m", { .Double = -484950000.0 }, 0 },
        { "-5d14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m4ms", { .Double = -484950004.0 }, 0 },
        { "-5d14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m3.5ms", { .Double = -484950003.5 }, 0 },
        { "-5d14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m18s", { .Double = -484968000.0 }, 0 },
        { "-5d14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m18s4ms", { .Double = -484968004.0 }, 0 },
        { "-5d14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m18s3.5ms", { .Double = -484968003.5 }, 0 },
        { "-5d14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m18.5s", { .Double = -484968500.0 }, 0 },
        { "-5d14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m18.5s4ms", { .Double = -484968504.0 }, 0 },
        { "-5d14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5d14.5h12.5m18.5s3.5ms", { .Double = -484968503.5 }, 0 },
        { "5d", { .Double = 432000000.0 }, 0 },
        { "5d-4ms", { .Double = 0.0 }, -1 },
        { "5d4ms", { .Double = 432000004.0 }, 0 },
        { "5d-3.5ms", { .Double = 0.0 }, -1 },
        { "5d3.5ms", { .Double = 432000003.5 }, 0 },
        { "5d-18s", { .Double = 0.0 }, -1 },
        { "5d-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d18s", { .Double = 432018000.0 }, 0 },
        { "5d18s-4ms", { .Double = 0.0 }, -1 },
        { "5d18s4ms", { .Double = 432018004.0 }, 0 },
        { "5d18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d18s3.5ms", { .Double = 432018003.5 }, 0 },
        { "5d-18.5s", { .Double = 0.0 }, -1 },
        { "5d-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d18.5s", { .Double = 432018500.0 }, 0 },
        { "5d18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d18.5s4ms", { .Double = 432018504.0 }, 0 },
        { "5d18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d18.5s3.5ms", { .Double = 432018503.5 }, 0 },
        { "5d-12m", { .Double = 0.0 }, -1 },
        { "5d-12m-4ms", { .Double = 0.0 }, -1 },
        { "5d-12m4ms", { .Double = 0.0 }, -1 },
        { "5d-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m-18s", { .Double = 0.0 }, -1 },
        { "5d-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m18s", { .Double = 0.0 }, -1 },
        { "5d-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m18.5s", { .Double = 0.0 }, -1 },
        { "5d-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m", { .Double = 432720000.0 }, 0 },
        { "5d12m-4ms", { .Double = 0.0 }, -1 },
        { "5d12m4ms", { .Double = 432720004.0 }, 0 },
        { "5d12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m3.5ms", { .Double = 432720003.5 }, 0 },
        { "5d12m-18s", { .Double = 0.0 }, -1 },
        { "5d12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m18s", { .Double = 432738000.0 }, 0 },
        { "5d12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d12m18s4ms", { .Double = 432738004.0 }, 0 },
        { "5d12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m18s3.5ms", { .Double = 432738003.5 }, 0 },
        { "5d12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m18.5s", { .Double = 432738500.0 }, 0 },
        { "5d12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d12m18.5s4ms", { .Double = 432738504.0 }, 0 },
        { "5d12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12m18.5s3.5ms", { .Double = 432738503.5 }, 0 },
        { "5d-12.5m", { .Double = 0.0 }, -1 },
        { "5d-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18s", { .Double = 0.0 }, -1 },
        { "5d-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m", { .Double = 432750000.0 }, 0 },
        { "5d12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m4ms", { .Double = 432750004.0 }, 0 },
        { "5d12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m3.5ms", { .Double = 432750003.5 }, 0 },
        { "5d12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m18s", { .Double = 432768000.0 }, 0 },
        { "5d12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m18s4ms", { .Double = 432768004.0 }, 0 },
        { "5d12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m18s3.5ms", { .Double = 432768003.5 }, 0 },
        { "5d12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m18.5s", { .Double = 432768500.0 }, 0 },
        { "5d12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d12.5m18.5s4ms", { .Double = 432768504.0 }, 0 },
        { "5d12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d12.5m18.5s3.5ms", { .Double = 432768503.5 }, 0 },
        { "5d-14h", { .Double = 0.0 }, -1 },
        { "5d-14h-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-18s", { .Double = 0.0 }, -1 },
        { "5d-14h-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h18s", { .Double = 0.0 }, -1 },
        { "5d-14h18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12m", { .Double = 0.0 }, -1 },
        { "5d-14h-12m4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12m18s", { .Double = 0.0 }, -1 },
        { "5d-14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m", { .Double = 0.0 }, -1 },
        { "5d-14h12m-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m-18s", { .Double = 0.0 }, -1 },
        { "5d-14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18s", { .Double = 0.0 }, -1 },
        { "5d-14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18s", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h", { .Double = 482400000.0 }, 0 },
        { "5d14h-4ms", { .Double = 0.0 }, -1 },
        { "5d14h4ms", { .Double = 482400004.0 }, 0 },
        { "5d14h-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h3.5ms", { .Double = 482400003.5 }, 0 },
        { "5d14h-18s", { .Double = 0.0 }, -1 },
        { "5d14h-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h18s", { .Double = 482418000.0 }, 0 },
        { "5d14h18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h18s4ms", { .Double = 482418004.0 }, 0 },
        { "5d14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h18s3.5ms", { .Double = 482418003.5 }, 0 },
        { "5d14h-18.5s", { .Double = 0.0 }, -1 },
        { "5d14h-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h18.5s", { .Double = 482418500.0 }, 0 },
        { "5d14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h18.5s4ms", { .Double = 482418504.0 }, 0 },
        { "5d14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h18.5s3.5ms", { .Double = 482418503.5 }, 0 },
        { "5d14h-12m", { .Double = 0.0 }, -1 },
        { "5d14h-12m-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m-18s", { .Double = 0.0 }, -1 },
        { "5d14h-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18s", { .Double = 0.0 }, -1 },
        { "5d14h-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14h-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5d14h-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m", { .Double = 483120000.0 }, 0 },
        { "5d14h12m-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m4ms", { .Double = 483120004.0 }, 0 },
        { "5d14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m3.5ms", { .Double = 483120003.5 }, 0 },
        { "5d14h12m-18s", { .Double = 0.0 }, -1 },
        { "5d14h12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m18s", { .Double = 483138000.0 }, 0 },
        { "5d14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m18s4ms", { .Double = 483138004.0 }, 0 },
        { "5d14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m18s3.5ms", { .Double = 483138003.5 }, 0 },
        { "5d14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14h12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m18.5s", { .Double = 483138500.0 }, 0 },
        { "5d14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12m18.5s4ms", { .Double = 483138504.0 }, 0 },
        { "5d14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12m18.5s3.5ms", { .Double = 483138503.5 }, 0 },
        { "5d14h-12.5m", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m", { .Double = 483150000.0 }, 0 },
        { "5d14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m4ms", { .Double = 483150004.0 }, 0 },
        { "5d14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m3.5ms", { .Double = 483150003.5 }, 0 },
        { "5d14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m18s", { .Double = 483168000.0 }, 0 },
        { "5d14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m18s4ms", { .Double = 483168004.0 }, 0 },
        { "5d14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m18s3.5ms", { .Double = 483168003.5 }, 0 },
        { "5d14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m18.5s", { .Double = 483168500.0 }, 0 },
        { "5d14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m18.5s4ms", { .Double = 483168504.0 }, 0 },
        { "5d14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14h12.5m18.5s3.5ms", { .Double = 483168503.5 }, 0 },
        { "5d-14.5h", { .Double = 0.0 }, -1 },
        { "5d-14.5h-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d-14.5h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h", { .Double = 484200000.0 }, 0 },
        { "5d14.5h-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h4ms", { .Double = 484200004.0 }, 0 },
        { "5d14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h3.5ms", { .Double = 484200003.5 }, 0 },
        { "5d14.5h-18s", { .Double = 0.0 }, -1 },
        { "5d14.5h-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h18s", { .Double = 484218000.0 }, 0 },
        { "5d14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h18s4ms", { .Double = 484218004.0 }, 0 },
        { "5d14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h18s3.5ms", { .Double = 484218003.5 }, 0 },
        { "5d14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h18.5s", { .Double = 484218500.0 }, 0 },
        { "5d14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h18.5s4ms", { .Double = 484218504.0 }, 0 },
        { "5d14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h18.5s3.5ms", { .Double = 484218503.5 }, 0 },
        { "5d14.5h-12m", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-18s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m", { .Double = 484920000.0 }, 0 },
        { "5d14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m4ms", { .Double = 484920004.0 }, 0 },
        { "5d14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m3.5ms", { .Double = 484920003.5 }, 0 },
        { "5d14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m18s", { .Double = 484938000.0 }, 0 },
        { "5d14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m18s4ms", { .Double = 484938004.0 }, 0 },
        { "5d14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m18s3.5ms", { .Double = 484938003.5 }, 0 },
        { "5d14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m18.5s", { .Double = 484938500.0 }, 0 },
        { "5d14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m18.5s4ms", { .Double = 484938504.0 }, 0 },
        { "5d14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12m18.5s3.5ms", { .Double = 484938503.5 }, 0 },
        { "5d14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m", { .Double = 484950000.0 }, 0 },
        { "5d14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m4ms", { .Double = 484950004.0 }, 0 },
        { "5d14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m3.5ms", { .Double = 484950003.5 }, 0 },
        { "5d14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m18s", { .Double = 484968000.0 }, 0 },
        { "5d14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m18s4ms", { .Double = 484968004.0 }, 0 },
        { "5d14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m18s3.5ms", { .Double = 484968003.5 }, 0 },
        { "5d14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m18.5s", { .Double = 484968500.0 }, 0 },
        { "5d14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m18.5s4ms", { .Double = 484968504.0 }, 0 },
        { "5d14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5d14.5h12.5m18.5s3.5ms", { .Double = 484968503.5 }, 0 },
        { "-5.5d", { .Double = -475200000.0 }, 0 },
        { "-5.5d-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d4ms", { .Double = -475200004.0 }, 0 },
        { "-5.5d-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d3.5ms", { .Double = -475200003.5 }, 0 },
        { "-5.5d-18s", { .Double = 0.0 }, -1 },
        { "-5.5d-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d18s", { .Double = -475218000.0 }, 0 },
        { "-5.5d18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d18s4ms", { .Double = -475218004.0 }, 0 },
        { "-5.5d18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d18s3.5ms", { .Double = -475218003.5 }, 0 },
        { "-5.5d-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d18.5s", { .Double = -475218500.0 }, 0 },
        { "-5.5d18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d18.5s4ms", { .Double = -475218504.0 }, 0 },
        { "-5.5d18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d18.5s3.5ms", { .Double = -475218503.5 }, 0 },
        { "-5.5d-12m", { .Double = 0.0 }, -1 },
        { "-5.5d-12m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12m18s", { .Double = 0.0 }, -1 },
        { "-5.5d-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m", { .Double = -475920000.0 }, 0 },
        { "-5.5d12m-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m4ms", { .Double = -475920004.0 }, 0 },
        { "-5.5d12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m3.5ms", { .Double = -475920003.5 }, 0 },
        { "-5.5d12m-18s", { .Double = 0.0 }, -1 },
        { "-5.5d12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m18s", { .Double = -475938000.0 }, 0 },
        { "-5.5d12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m18s4ms", { .Double = -475938004.0 }, 0 },
        { "-5.5d12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m18s3.5ms", { .Double = -475938003.5 }, 0 },
        { "-5.5d12m-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m18.5s", { .Double = -475938500.0 }, 0 },
        { "-5.5d12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m18.5s4ms", { .Double = -475938504.0 }, 0 },
        { "-5.5d12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12m18.5s3.5ms", { .Double = -475938503.5 }, 0 },
        { "-5.5d-12.5m", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m18s", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m", { .Double = -475950000.0 }, 0 },
        { "-5.5d12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m4ms", { .Double = -475950004.0 }, 0 },
        { "-5.5d12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m3.5ms", { .Double = -475950003.5 }, 0 },
        { "-5.5d12.5m-18s", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m18s", { .Double = -475968000.0 }, 0 },
        { "-5.5d12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m18s4ms", { .Double = -475968004.0 }, 0 },
        { "-5.5d12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m18s3.5ms", { .Double = -475968003.5 }, 0 },
        { "-5.5d12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m18.5s", { .Double = -475968500.0 }, 0 },
        { "-5.5d12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m18.5s4ms", { .Double = -475968504.0 }, 0 },
        { "-5.5d12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d12.5m18.5s3.5ms", { .Double = -475968503.5 }, 0 },
        { "-5.5d-14h", { .Double = 0.0 }, -1 },
        { "-5.5d-14h4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h18s", { .Double = 0.0 }, -1 },
        { "-5.5d-14h18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-14h18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m18s", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m18s", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h", { .Double = -525600000.0 }, 0 },
        { "-5.5d14h-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h4ms", { .Double = -525600004.0 }, 0 },
        { "-5.5d14h-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h3.5ms", { .Double = -525600003.5 }, 0 },
        { "-5.5d14h-18s", { .Double = 0.0 }, -1 },
        { "-5.5d14h-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h18s", { .Double = -525618000.0 }, 0 },
        { "-5.5d14h18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h18s4ms", { .Double = -525618004.0 }, 0 },
        { "-5.5d14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h18s3.5ms", { .Double = -525618003.5 }, 0 },
        { "-5.5d14h-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h18.5s", { .Double = -525618500.0 }, 0 },
        { "-5.5d14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h18.5s4ms", { .Double = -525618504.0 }, 0 },
        { "-5.5d14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h18.5s3.5ms", { .Double = -525618503.5 }, 0 },
        { "-5.5d14h-12m", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m18s", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m", { .Double = -526320000.0 }, 0 },
        { "-5.5d14h12m-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m4ms", { .Double = -526320004.0 }, 0 },
        { "-5.5d14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m3.5ms", { .Double = -526320003.5 }, 0 },
        { "-5.5d14h12m-18s", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m18s", { .Double = -526338000.0 }, 0 },
        { "-5.5d14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m18s4ms", { .Double = -526338004.0 }, 0 },
        { "-5.5d14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m18s3.5ms", { .Double = -526338003.5 }, 0 },
        { "-5.5d14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m18.5s", { .Double = -526338500.0 }, 0 },
        { "-5.5d14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m18.5s4ms", { .Double = -526338504.0 }, 0 },
        { "-5.5d14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12m18.5s3.5ms", { .Double = -526338503.5 }, 0 },
        { "-5.5d14h-12.5m", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m", { .Double = -526350000.0 }, 0 },
        { "-5.5d14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m4ms", { .Double = -526350004.0 }, 0 },
        { "-5.5d14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m3.5ms", { .Double = -526350003.5 }, 0 },
        { "-5.5d14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m18s", { .Double = -526368000.0 }, 0 },
        { "-5.5d14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m18s4ms", { .Double = -526368004.0 }, 0 },
        { "-5.5d14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m18s3.5ms", { .Double = -526368003.5 }, 0 },
        { "-5.5d14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m18.5s", { .Double = -526368500.0 }, 0 },
        { "-5.5d14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m18.5s4ms", { .Double = -526368504.0 }, 0 },
        { "-5.5d14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14h12.5m18.5s3.5ms", { .Double = -526368503.5 }, 0 },
        { "-5.5d-14.5h", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h18s", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m18s", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m18s", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d-14.5h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h", { .Double = -527400000.0 }, 0 },
        { "-5.5d14.5h-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h4ms", { .Double = -527400004.0 }, 0 },
        { "-5.5d14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h3.5ms", { .Double = -527400003.5 }, 0 },
        { "-5.5d14.5h-18s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h18s", { .Double = -527418000.0 }, 0 },
        { "-5.5d14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h18s4ms", { .Double = -527418004.0 }, 0 },
        { "-5.5d14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h18s3.5ms", { .Double = -527418003.5 }, 0 },
        { "-5.5d14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h18.5s", { .Double = -527418500.0 }, 0 },
        { "-5.5d14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h18.5s4ms", { .Double = -527418504.0 }, 0 },
        { "-5.5d14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h18.5s3.5ms", { .Double = -527418503.5 }, 0 },
        { "-5.5d14.5h-12m", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m", { .Double = -528120000.0 }, 0 },
        { "-5.5d14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m4ms", { .Double = -528120004.0 }, 0 },
        { "-5.5d14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m3.5ms", { .Double = -528120003.5 }, 0 },
        { "-5.5d14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m18s", { .Double = -528138000.0 }, 0 },
        { "-5.5d14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m18s4ms", { .Double = -528138004.0 }, 0 },
        { "-5.5d14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m18s3.5ms", { .Double = -528138003.5 }, 0 },
        { "-5.5d14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m18.5s", { .Double = -528138500.0 }, 0 },
        { "-5.5d14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m18.5s4ms", { .Double = -528138504.0 }, 0 },
        { "-5.5d14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12m18.5s3.5ms", { .Double = -528138503.5 }, 0 },
        { "-5.5d14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m", { .Double = -528150000.0 }, 0 },
        { "-5.5d14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m4ms", { .Double = -528150004.0 }, 0 },
        { "-5.5d14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m3.5ms", { .Double = -528150003.5 }, 0 },
        { "-5.5d14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m18s", { .Double = -528168000.0 }, 0 },
        { "-5.5d14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m18s4ms", { .Double = -528168004.0 }, 0 },
        { "-5.5d14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m18s3.5ms", { .Double = -528168003.5 }, 0 },
        { "-5.5d14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m18.5s", { .Double = -528168500.0 }, 0 },
        { "-5.5d14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m18.5s4ms", { .Double = -528168504.0 }, 0 },
        { "-5.5d14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "-5.5d14.5h12.5m18.5s3.5ms", { .Double = -528168503.5 }, 0 },
        { "5.5d", { .Double = 475200000.0 }, 0 },
        { "5.5d-4ms", { .Double = 0.0 }, -1 },
        { "5.5d4ms", { .Double = 475200004.0 }, 0 },
        { "5.5d-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d3.5ms", { .Double = 475200003.5 }, 0 },
        { "5.5d-18s", { .Double = 0.0 }, -1 },
        { "5.5d-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d18s", { .Double = 475218000.0 }, 0 },
        { "5.5d18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d18s4ms", { .Double = 475218004.0 }, 0 },
        { "5.5d18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d18s3.5ms", { .Double = 475218003.5 }, 0 },
        { "5.5d-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d18.5s", { .Double = 475218500.0 }, 0 },
        { "5.5d18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d18.5s4ms", { .Double = 475218504.0 }, 0 },
        { "5.5d18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d18.5s3.5ms", { .Double = 475218503.5 }, 0 },
        { "5.5d-12m", { .Double = 0.0 }, -1 },
        { "5.5d-12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18s", { .Double = 0.0 }, -1 },
        { "5.5d-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m", { .Double = 475920000.0 }, 0 },
        { "5.5d12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m4ms", { .Double = 475920004.0 }, 0 },
        { "5.5d12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m3.5ms", { .Double = 475920003.5 }, 0 },
        { "5.5d12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m18s", { .Double = 475938000.0 }, 0 },
        { "5.5d12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m18s4ms", { .Double = 475938004.0 }, 0 },
        { "5.5d12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m18s3.5ms", { .Double = 475938003.5 }, 0 },
        { "5.5d12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m18.5s", { .Double = 475938500.0 }, 0 },
        { "5.5d12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12m18.5s4ms", { .Double = 475938504.0 }, 0 },
        { "5.5d12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12m18.5s3.5ms", { .Double = 475938503.5 }, 0 },
        { "5.5d-12.5m", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m", { .Double = 475950000.0 }, 0 },
        { "5.5d12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m4ms", { .Double = 475950004.0 }, 0 },
        { "5.5d12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m3.5ms", { .Double = 475950003.5 }, 0 },
        { "5.5d12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m18s", { .Double = 475968000.0 }, 0 },
        { "5.5d12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m18s4ms", { .Double = 475968004.0 }, 0 },
        { "5.5d12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m18s3.5ms", { .Double = 475968003.5 }, 0 },
        { "5.5d12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m18.5s", { .Double = 475968500.0 }, 0 },
        { "5.5d12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m18.5s4ms", { .Double = 475968504.0 }, 0 },
        { "5.5d12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d12.5m18.5s3.5ms", { .Double = 475968503.5 }, 0 },
        { "5.5d-14h", { .Double = 0.0 }, -1 },
        { "5.5d-14h-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h", { .Double = 525600000.0 }, 0 },
        { "5.5d14h-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h4ms", { .Double = 525600004.0 }, 0 },
        { "5.5d14h-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h3.5ms", { .Double = 525600003.5 }, 0 },
        { "5.5d14h-18s", { .Double = 0.0 }, -1 },
        { "5.5d14h-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h18s", { .Double = 525618000.0 }, 0 },
        { "5.5d14h18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h18s4ms", { .Double = 525618004.0 }, 0 },
        { "5.5d14h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h18s3.5ms", { .Double = 525618003.5 }, 0 },
        { "5.5d14h-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h18.5s", { .Double = 525618500.0 }, 0 },
        { "5.5d14h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h18.5s4ms", { .Double = 525618504.0 }, 0 },
        { "5.5d14h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h18.5s3.5ms", { .Double = 525618503.5 }, 0 },
        { "5.5d14h-12m", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m", { .Double = 526320000.0 }, 0 },
        { "5.5d14h12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m4ms", { .Double = 526320004.0 }, 0 },
        { "5.5d14h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m3.5ms", { .Double = 526320003.5 }, 0 },
        { "5.5d14h12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m18s", { .Double = 526338000.0 }, 0 },
        { "5.5d14h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m18s4ms", { .Double = 526338004.0 }, 0 },
        { "5.5d14h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m18s3.5ms", { .Double = 526338003.5 }, 0 },
        { "5.5d14h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m18.5s", { .Double = 526338500.0 }, 0 },
        { "5.5d14h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m18.5s4ms", { .Double = 526338504.0 }, 0 },
        { "5.5d14h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12m18.5s3.5ms", { .Double = 526338503.5 }, 0 },
        { "5.5d14h-12.5m", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m", { .Double = 526350000.0 }, 0 },
        { "5.5d14h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m4ms", { .Double = 526350004.0 }, 0 },
        { "5.5d14h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m3.5ms", { .Double = 526350003.5 }, 0 },
        { "5.5d14h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m18s", { .Double = 526368000.0 }, 0 },
        { "5.5d14h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m18s4ms", { .Double = 526368004.0 }, 0 },
        { "5.5d14h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m18s3.5ms", { .Double = 526368003.5 }, 0 },
        { "5.5d14h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m18.5s", { .Double = 526368500.0 }, 0 },
        { "5.5d14h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m18.5s4ms", { .Double = 526368504.0 }, 0 },
        { "5.5d14h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14h12.5m18.5s3.5ms", { .Double = 526368503.5 }, 0 },
        { "5.5d-14.5h", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d-14.5h12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h", { .Double = 527400000.0 }, 0 },
        { "5.5d14.5h-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h4ms", { .Double = 527400004.0 }, 0 },
        { "5.5d14.5h-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h3.5ms", { .Double = 527400003.5 }, 0 },
        { "5.5d14.5h-18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h18s", { .Double = 527418000.0 }, 0 },
        { "5.5d14.5h18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h18s4ms", { .Double = 527418004.0 }, 0 },
        { "5.5d14.5h18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h18s3.5ms", { .Double = 527418003.5 }, 0 },
        { "5.5d14.5h-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h18.5s", { .Double = 527418500.0 }, 0 },
        { "5.5d14.5h18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h18.5s4ms", { .Double = 527418504.0 }, 0 },
        { "5.5d14.5h18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h18.5s3.5ms", { .Double = 527418503.5 }, 0 },
        { "5.5d14.5h-12m", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m", { .Double = 528120000.0 }, 0 },
        { "5.5d14.5h12m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m4ms", { .Double = 528120004.0 }, 0 },
        { "5.5d14.5h12m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m3.5ms", { .Double = 528120003.5 }, 0 },
        { "5.5d14.5h12m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m18s", { .Double = 528138000.0 }, 0 },
        { "5.5d14.5h12m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m18s4ms", { .Double = 528138004.0 }, 0 },
        { "5.5d14.5h12m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m18s3.5ms", { .Double = 528138003.5 }, 0 },
        { "5.5d14.5h12m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m18.5s", { .Double = 528138500.0 }, 0 },
        { "5.5d14.5h12m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m18.5s4ms", { .Double = 528138504.0 }, 0 },
        { "5.5d14.5h12m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12m18.5s3.5ms", { .Double = 528138503.5 }, 0 },
        { "5.5d14.5h-12.5m", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h-12.5m18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m", { .Double = 528150000.0 }, 0 },
        { "5.5d14.5h12.5m-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m4ms", { .Double = 528150004.0 }, 0 },
        { "5.5d14.5h12.5m-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m3.5ms", { .Double = 528150003.5 }, 0 },
        { "5.5d14.5h12.5m-18s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m18s", { .Double = 528168000.0 }, 0 },
        { "5.5d14.5h12.5m18s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m18s4ms", { .Double = 528168004.0 }, 0 },
        { "5.5d14.5h12.5m18s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m18s3.5ms", { .Double = 528168003.5 }, 0 },
        { "5.5d14.5h12.5m-18.5s", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18.5s4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m-18.5s3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m18.5s", { .Double = 528168500.0 }, 0 },
        { "5.5d14.5h12.5m18.5s-4ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m18.5s4ms", { .Double = 528168504.0 }, 0 },
        { "5.5d14.5h12.5m18.5s-3.5ms", { .Double = 0.0 }, -1 },
        { "5.5d14.5h12.5m18.5s3.5ms", { .Double = 528168503.5 }, 0 },
        { NULL, { .Integer = 0 } }
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nPrefix = 0; nPrefix < 2; ++nPrefix) {
        for(nIndex = 0;; ++nIndex) {
            pValue = &sValues[nIndex];
            if(!pValue->Source)
                break;
            snprintf(sLine, sizeof(sLine), "TYPE TEST: TIME := %s%s; END_TYPE", sPrefix[nPrefix], pValue->Source);
            fprintf(stderr, "%s\n", sLine);
            nResult = test_parse(pContext, sLine);
            munit_assert_int(nResult, ==, pValue->Result);
            if(nResult != 0)
                continue;

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
    }

    return MUNIT_OK;
}




