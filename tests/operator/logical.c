#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <frame.h>
#include <operator.h>
#include <value.h>


static VALUE_TYPE _Types[] = {
    TYPE_LREAL,
    TYPE_REAL,
    TYPE_TIME,
    TYPE_NONE,
};


MunitResult
test_operator_and(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;
    int nIndex;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    for(nIndex = 0; _Types[nIndex] != TYPE_NONE; ++nIndex) {
        value_assign(&sFrame.CR, _Types[nIndex]);
        value_assign(&sValue, _Types[nIndex]);
        munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    }

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LINT);
    munit_assert_int64(sFrame.CR.Value.S64, ==, 15);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DINT);
    munit_assert_int32(sFrame.CR.Value.S32, ==, 15);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_INT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_INT);
    munit_assert_int16(sFrame.CR.Value.S16, ==, 15);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_SINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_SINT);
    munit_assert_int8(sFrame.CR.Value.S8, ==, 15);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_ULINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sFrame.CR.Value.U64, ==, 15);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UDINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 15);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UINT);
    munit_assert_uint16(sFrame.CR.Value.U16, ==, 15);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_USINT, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_USINT);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 15);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LWORD, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sFrame.CR.Value.B64, ==, 15);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DWORD, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sFrame.CR.Value.B32, ==, 15);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_WORD, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_WORD);
    munit_assert_uint16(sFrame.CR.Value.B16, ==, 15);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BYTE, 15);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 15);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL, 1);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_and(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    return MUNIT_OK;
}


MunitResult
test_operator_not(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;
    int nIndex;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    for(nIndex = 0; _Types[nIndex] != TYPE_NONE; ++nIndex) {
        value_assign(&sFrame.CR, _Types[nIndex]);
        value_assign(&sValue, _Types[nIndex]);
        munit_assert_int(operator_and(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    }

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LINT);
    munit_assert_int64(sFrame.CR.Value.S64, ==, -16);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DINT);
    munit_assert_int32(sFrame.CR.Value.S32, ==, -16);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_INT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_INT);
    munit_assert_int16(sFrame.CR.Value.S16, ==, -16);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_SINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_SINT);
    munit_assert_int8(sFrame.CR.Value.S8, ==, -16);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_ULINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sFrame.CR.Value.U64, ==, 0xfffffffffffffff0);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UDINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 0xfffffff0);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 0xfff0);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_USINT, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_USINT);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 240);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LWORD, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sFrame.CR.Value.B64, ==, 0xfffffffffffffff0);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DWORD, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sFrame.CR.Value.B32, ==, 0xfffffff0);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_WORD, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_WORD);
    munit_assert_uint32(sFrame.CR.Value.B16, ==, 0xfff0);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE, 255);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BYTE, 15);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 240);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL, 1);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_not(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_not(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    return MUNIT_OK;
}


MunitResult
test_operator_or(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;
    int nIndex;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    for(nIndex = 0; _Types[nIndex] != TYPE_NONE; ++nIndex) {
        value_assign(&sFrame.CR, _Types[nIndex]);
        value_assign(&sValue, _Types[nIndex]);
        munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    }

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LINT);
    munit_assert_int64(sFrame.CR.Value.S64, ==, 15);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DINT);
    munit_assert_int32(sFrame.CR.Value.S32, ==, 15);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_INT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_INT);
    munit_assert_int16(sFrame.CR.Value.S16, ==, 15);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_SINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_SINT);
    munit_assert_int8(sFrame.CR.Value.S8, ==, 15);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_ULINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sFrame.CR.Value.U64, ==, 15);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UDINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 15);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UINT);
    munit_assert_uint16(sFrame.CR.Value.U16, ==, 15);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_USINT, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_USINT);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 15);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LWORD, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sFrame.CR.Value.B64, ==, 15);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DWORD, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sFrame.CR.Value.B32, ==, 15);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_WORD, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_WORD);
    munit_assert_uint16(sFrame.CR.Value.B16, ==, 15);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BYTE, 7);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 15);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL, 1);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_or(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_or(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    return MUNIT_OK;
}


MunitResult
test_operator_xor(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;
    int nIndex;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    for(nIndex = 0; _Types[nIndex] != TYPE_NONE; ++nIndex) {
        value_assign(&sFrame.CR, _Types[nIndex]);
        value_assign(&sValue, _Types[nIndex]);
        munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    }

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LINT);
    munit_assert_int64(sFrame.CR.Value.S64, ==, 7);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DINT);
    munit_assert_int32(sFrame.CR.Value.S32, ==, 7);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_INT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_INT);
    munit_assert_int16(sFrame.CR.Value.S16, ==, 7);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_SINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_SINT);
    munit_assert_int8(sFrame.CR.Value.S8, ==, 7);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_ULINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sFrame.CR.Value.U64, ==, 7);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UDINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 7);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_UINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UINT);
    munit_assert_uint16(sFrame.CR.Value.U16, ==, 7);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_USINT, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_USINT);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 7);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_LWORD, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sFrame.CR.Value.B64, ==, 7);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_DWORD, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sFrame.CR.Value.B32, ==, 7);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_WORD, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_WORD);
    munit_assert_uint16(sFrame.CR.Value.B16, ==, 7);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE, 8);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BYTE, 15);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 7);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL, 1);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_xor(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    return MUNIT_OK;
}


