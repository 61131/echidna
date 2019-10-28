#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <frame.h>
#include <operator.h>
#include <value.h>


MunitResult
test_operand_invert(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_SKIP;
}


MunitResult
test_operand_subrange(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;
    int nIndex;

    VALUE_TYPE sType[] = {
        TYPE_LREAL,
        TYPE_REAL,
        TYPE_LWORD,
        TYPE_DWORD,
        TYPE_WORD,
        TYPE_BYTE,
        TYPE_BOOL,
        TYPE_NONE
    };

    for(nIndex = 0; sType[nIndex] != TYPE_NONE; ++nIndex) {
        value_initialise(&sValue);
        value_assign(&sValue, sType[nIndex]);
        munit_assert_int(operand_subrange(&sValue, &sValue), ==, 0);
    }
    return MUNIT_OK;
}
