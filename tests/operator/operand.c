#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <frame.h>
#include <operator.h>
#include <value.h>


MunitResult
test_operand_invert(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;

    frame_initialise(&sFrame);
    value_assign(&sValue, TYPE_LREAL);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, -1);
    value_assign(&sValue, TYPE_REAL);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, -1);
    value_assign(&sValue, TYPE_LINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_int64(sValue.Value.S64, ==, (int64_t)(~1));
    value_assign(&sValue, TYPE_DINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_int32(sValue.Value.S32, ==, (int32_t)(~1));
    value_assign(&sValue, TYPE_INT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_int16(sValue.Value.S16, ==, (int16_t)(~1));
    value_assign(&sValue, TYPE_SINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_int8(sValue.Value.S8, ==, (int8_t)(~1));
    value_assign(&sValue, TYPE_ULINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint64(sValue.Value.U64, ==, (uint64_t)(~1));
    value_assign(&sValue, TYPE_UDINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sValue.Value.U32, ==, (uint32_t)(~1));
    value_assign(&sValue, TYPE_UINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint16(sValue.Value.U16, ==, (uint16_t)(~1));
    value_assign(&sValue, TYPE_USINT, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint8(sValue.Value.U8, ==, (uint8_t)(~1));
    value_assign(&sValue, TYPE_LWORD, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint64(sValue.Value.B64, ==, (uint64_t)(~1));
    value_assign(&sValue, TYPE_DWORD, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sValue.Value.B32, ==, (uint32_t)(~1));
    value_assign(&sValue, TYPE_WORD, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint16(sValue.Value.B16, ==, (uint16_t)(~1));
    value_assign(&sValue, TYPE_BYTE, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint8(sValue.Value.B8, ==, (uint8_t)(~1));
    value_assign(&sValue, TYPE_BOOL, 1);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, 0);
    munit_assert_uint8(sValue.Value.B1, ==, (uint8_t)((~1) & 1));
    value_assign(&sValue, TYPE_TIME);
    sFrame.Type = sValue.Type;
    munit_assert_int(operand_invert(&sFrame, &sValue), ==, -1);

    return MUNIT_OK;
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
