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


#define SUBRANGE_MAXIMUM        (16)
#define SUBRANGE_MINIMUM        (-16)


struct _TEST_SUBRANGE {

    char * Type;

    int64_t Minimum;

    int64_t Maximum;

    int64_t Value;

    int Result;
};



MunitResult
test_grammar_subrange(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LLE *pElement;
    PARSE *pParse;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    VALUE sValue;
    struct _TEST_SUBRANGE *pValue;
    char sLine[LINE_MAX];
    int nIndex, nResult;

    struct _TEST_SUBRANGE sValues[] = {

        { "LINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - SUBRANGE_MINIMUM) >> 2), 0 },
        { "LINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0 },
        { "LINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "LINT", SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0, -1 },
        { "LINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM - 1, -1 },
        { "LINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },

        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - SUBRANGE_MINIMUM) >> 2), 0 },
        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0 },
        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "DINT", SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0, -1 },
        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM - 1, -1 },
        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) INT32_MIN) - 1, -1 },
        { "DINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) INT32_MAX) + 1, -1 },

        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - SUBRANGE_MINIMUM) >> 2), 0 },
        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0 },
        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "INT", SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0, -1 },
        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM - 1, -1 },
        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) INT16_MIN) - 1, -1 },
        { "INT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) INT16_MAX) + 1, -1 },

        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - SUBRANGE_MINIMUM) >> 2), 0 },
        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0 },
        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "SINT", SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM, 0, -1 },
        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MINIMUM - 1, -1 },
        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) INT8_MIN) - 1, -1 },
        { "SINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) INT8_MAX) + 1, -1 },

        { "ULINT", 1, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - 1) >> 2), 0 },
        { "ULINT", 1, SUBRANGE_MAXIMUM, 1, 0 },
        { "ULINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "ULINT", SUBRANGE_MAXIMUM, 1, 0, -1 },
        { "ULINT", 1, SUBRANGE_MAXIMUM, 0, -1 },
        { "ULINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "ULINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, -1, -1 },

        { "UDINT", 1, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - 1) >> 2), 0 },
        { "UDINT", 1, SUBRANGE_MAXIMUM, 1, 0 },
        { "UDINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "UDINT", SUBRANGE_MAXIMUM, 1, 0, -1 },
        { "UDINT", 1, SUBRANGE_MAXIMUM, 0, -1 },
        { "UDINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "UDINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, -1, -1 },
        { "UDINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) UINT32_MAX) + 1, -1 },

        { "UINT", 1, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - 1) >> 2), 0 },
        { "UINT", 1, SUBRANGE_MAXIMUM, 1, 0 },
        { "UINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "UINT", SUBRANGE_MAXIMUM, 1, 0, -1 },
        { "UINT", 1, SUBRANGE_MAXIMUM, 0, -1 },
        { "UINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "UINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, -1, -1 },
        { "UINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) UINT16_MAX) + 1, -1 },

        { "USINT", 1, SUBRANGE_MAXIMUM, ((SUBRANGE_MAXIMUM - 1) >> 2), 0 },
        { "USINT", 1, SUBRANGE_MAXIMUM, 1, 0 },
        { "USINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM, 0 },
        { "USINT", SUBRANGE_MAXIMUM, 1, 0, -1 },
        { "USINT", 1, SUBRANGE_MAXIMUM, 0, -1 },
        { "USINT", 1, SUBRANGE_MAXIMUM, SUBRANGE_MAXIMUM + 1, -1 },
        { "USINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, -1, -1 },
        { "USINT", SUBRANGE_MINIMUM, SUBRANGE_MAXIMUM, ((int64_t) UINT8_MAX) + 1, -1 },

        { NULL },
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nIndex = 0;; ++nIndex) {
        pValue = &sValues[nIndex];
        if(!pValue->Type)
            break;
        snprintf(sLine, sizeof(sLine), "TYPE TEST: %s (%ld..%ld) := %ld; END_TYPE", 
                pValue->Type,
                (long int) pValue->Minimum,
                (long int) pValue->Maximum,
                (long int) pValue->Value);
        value_initialise(&sValue);
        munit_assert_int(value_strtotype(&sValue, pValue->Type), ==, 0);
        munit_assert_uint32(sValue.Type, !=, TYPE_NONE);
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
        munit_assert_uint32(pToken->Value.Type, ==, sValue.Type);
        munit_assert_uint32(pToken->Value.Cast, ==, sValue.Type);
        munit_assert_uint32(pToken->Value.Flags & FLAG_SUBRANGE, ==, FLAG_SUBRANGE);
        switch(pToken->Value.Type) {
            case TYPE_LINT:
                munit_assert_int64(pToken->Value.Maximum.S64, ==, pValue->Maximum);
                munit_assert_int64(pToken->Value.Minimum.S64, ==, pValue->Minimum);
                munit_assert_int64(pToken->Value.Value.S64, ==, pValue->Value);
                break;

            case TYPE_DINT:
                munit_assert_int64((int64_t) pToken->Value.Maximum.S32, ==, pValue->Maximum);
                munit_assert_int64((int64_t) pToken->Value.Minimum.S32, ==, pValue->Minimum);
                munit_assert_int64((int64_t) pToken->Value.Value.S32, ==, pValue->Value);
                break;

            case TYPE_INT:
                munit_assert_int64((int64_t) pToken->Value.Maximum.S16, ==, pValue->Maximum);
                munit_assert_int64((int64_t) pToken->Value.Minimum.S16, ==, pValue->Minimum);
                munit_assert_int64((int64_t) pToken->Value.Value.S16, ==, pValue->Value);
                break;

            case TYPE_SINT:
                munit_assert_int64((int64_t) pToken->Value.Maximum.S8, ==, pValue->Maximum);
                munit_assert_int64((int64_t) pToken->Value.Minimum.S8, ==, pValue->Minimum);
                munit_assert_int64((int64_t) pToken->Value.Value.S8, ==, pValue->Value);
                break;

            default:
                break;
        }
        munit_assert_null(pElement->Next);

        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


