#include <stdio.h>
#include <string.h>
#include <math.h>

#include <tests.h>

#include <parameter.h>


void
_test_arithmetic_modulus(LL *Parameters, VALUE_TYPE Type) {
    PARAMETER *pParameter;
    int nValue;

    while(Parameters->Head != NULL)
        ll_delete(Parameters->Head);
    for(nValue = 5; nValue > 1; nValue -= 2) {
        munit_assert_not_null(pParameter = parameter_new(NULL));
        value_assign(&pParameter->Value, Type, nValue);
        munit_assert_int(ll_insert(Parameters, pParameter), ==, 0);
    }
}


void
_test_arithmetic_populate(LL *Parameters, VALUE_TYPE Type) {
    PARAMETER *pParameter;
    double dValue;
    int nValue;

    while(Parameters->Head != NULL)
        ll_delete(Parameters->Head);
    for(nValue = 8; nValue > 1; nValue /= 2) {
        munit_assert_not_null(pParameter = parameter_new(NULL));
        dValue = (double) nValue;
        switch(Type) {
            case TYPE_LREAL:
            case TYPE_REAL:
                value_assign(&pParameter->Value, Type, dValue);
                break;

            default:
                value_assign(&pParameter->Value, Type, nValue);
                break;
        }
        munit_assert_int(ll_insert(Parameters, pParameter), ==, 0);
    }
}


