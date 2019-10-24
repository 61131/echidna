#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>

#include <standard/numeric.h>


struct _TEST_VALUE {

    double Input;

    double Output;
};

static struct _TEST_VALUE _Values[] = {
    { 0.0, 1.0 },
    { 1.0, 2.71828182846 },
    { 2.0, 7.38905609893 },
    { -1.0, 0.36787944117 },
};


MunitResult 
test_numeric_exp(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    struct _TEST_VALUE *pValue;
    double dResult, dValue;
    float fResult;
    int nIndex, nType;

    VALUE_TYPE sType[] = { 
        TYPE_LREAL, 
        TYPE_REAL 
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_exp(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_exp(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_REAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_exp(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    for(nType = 0; nType < 2; ++nType) {
        for(nIndex = 0; nIndex < 4; ++nIndex) {
            pValue = &_Values[nIndex];
            ll_initialise(&sParameters, parameter_destroy);
            value_initialise(&sResult);
            munit_assert_not_null(pParameter = parameter_new(NULL));
            value_assign(&pParameter->Value, sType[nType], pValue->Input);
            munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
            munit_assert_int(standard_exp(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
            munit_assert_uint32(sResult.Type, ==, pParameter->Value.Type);
            dValue = round(pValue->Output * 1e6) / 1e6;
            switch(pParameter->Value.Type) {
                case TYPE_LREAL:
                    dResult = round(sResult.Value.Double * 1e6) / 1e6;
                    munit_assert_double(dValue, ==, dResult);
                    break;

                case TYPE_REAL:
                    fResult = roundf(sResult.Value.Single * 1e6) / 1e6;
                    munit_assert_float((float) dValue, ==, fResult);
                    break;

                default:
                    break;
            }
            ll_destroy(&sParameters);
        }
    }

    return MUNIT_OK;
}


MunitResult 
test_numeric_ln(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    LL sParameters;
    PARAMETER *pParameter;
    VALUE sResult;
    struct _TEST_VALUE *pValue;
    double dResult, dValue;
    float fResult;
    int nIndex, nType;

    VALUE_TYPE sType[] = { 
        TYPE_LREAL, 
        TYPE_REAL 
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    ll_initialise(&sParameters, parameter_destroy);
    munit_assert_int(standard_ln(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_COUNT);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, TYPE_INT);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ln(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_delete(sParameters.Head);
    munit_assert_not_null(pParameter = parameter_new(NULL));
    value_assign(&pParameter->Value, ANY_REAL);
    munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
    munit_assert_int(standard_ln(pContext, NULL, &sParameters, &sResult, NULL), ==, ERROR_PARAMETER_TYPE);
    ll_destroy(&sParameters);

    for(nType = 0; nType < 2; ++nType) {
        for(nIndex = 0; nIndex < 4; ++nIndex) {
            pValue = &_Values[nIndex];
            ll_initialise(&sParameters, parameter_destroy);
            value_initialise(&sResult);
            munit_assert_not_null(pParameter = parameter_new(NULL));
            value_assign(&pParameter->Value, sType[nType], pValue->Output);
            munit_assert_int(ll_insert(&sParameters, pParameter), ==, 0);
            munit_assert_int(standard_ln(pContext, NULL, &sParameters, &sResult, NULL), ==, 0);
            munit_assert_uint32(sResult.Type, ==, pParameter->Value.Type);
            dValue = round(pValue->Input * 1e6) / 1e6;
            switch(pParameter->Value.Type) {
                case TYPE_LREAL:
                    dResult = round(sResult.Value.Double * 1e6) / 1e6;
                    munit_assert_double(dValue, ==, dResult);
                    break;

                case TYPE_REAL:
                    fResult = roundf(sResult.Value.Single * 1e6) / 1e6;
                    munit_assert_float((float) dValue, ==, fResult);
                    break;

                default:
                    break;
            }
            ll_destroy(&sParameters);
        }
    }

    return MUNIT_OK;
}


