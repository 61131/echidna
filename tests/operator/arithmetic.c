#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <frame.h>
#include <operator.h>
#include <value.h>


MunitResult
test_operator_add(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    //  TYPE_LREAL
    value_assign(&sFrame.CR, TYPE_LREAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LREAL);
    value_assign(&sValue, TYPE_LREAL, 7.0);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LREAL);
    munit_assert_double(sFrame.CR.Value.Double, ==, 7.0);

    //  TYPE_REAL
    value_assign(&sFrame.CR, TYPE_REAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_REAL);
    value_assign(&sValue, TYPE_REAL, 7.0);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_REAL);
    munit_assert_float(sFrame.CR.Value.Single, ==, 7.0f);

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LINT);
    sFrame.CR.Maximum.S64 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_LINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LINT);
    munit_assert_int64(sFrame.CR.Value.S64, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LINT);
    munit_assert_int64(sFrame.CR.Value.S64, ==, 10);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DINT);
    sFrame.CR.Maximum.S32 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_DINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DINT);
    munit_assert_int32(sFrame.CR.Value.S32, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DINT);
    munit_assert_int32(sFrame.CR.Value.S32, ==, 10);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_INT);
    sFrame.CR.Maximum.S16 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_INT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_INT);
    munit_assert_int16(sFrame.CR.Value.S16, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_INT);
    munit_assert_int16(sFrame.CR.Value.S16, ==, 10);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_SINT);
    sFrame.CR.Maximum.S8 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_SINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_SINT);
    munit_assert_int8(sFrame.CR.Value.S8, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_SINT);
    munit_assert_int8(sFrame.CR.Value.S8, ==, 10);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_ULINT);
    sFrame.CR.Maximum.U64 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_ULINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sFrame.CR.Value.U64, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_ULINT);
    munit_assert_uint64(sFrame.CR.Value.U64, ==, 10);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UDINT);
    sFrame.CR.Maximum.U32 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_UDINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sFrame.CR.Value.U32, ==, 10);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UINT);
    sFrame.CR.Maximum.U16 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_UINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UINT);
    munit_assert_uint16(sFrame.CR.Value.U16, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_UINT);
    munit_assert_uint16(sFrame.CR.Value.U16, ==, 10);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_USINT);
    sFrame.CR.Maximum.U8 = 10;
    sFrame.CR.Flags |= FLAG_SUBRANGE;
    value_assign(&sValue, TYPE_USINT, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_USINT);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_USINT);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 10);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LWORD);
    value_assign(&sValue, TYPE_LWORD, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_LWORD);
    munit_assert_uint64(sFrame.CR.Value.B64, ==, 7);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DWORD);
    value_assign(&sValue, TYPE_DWORD, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sFrame.CR.Value.B32, ==, 7);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_WORD);
    value_assign(&sValue, TYPE_WORD,7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_WORD);
    munit_assert_uint16(sFrame.CR.Value.B16, ==, 7);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BYTE);
    value_assign(&sValue, TYPE_BYTE, 7);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BYTE);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 7);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BOOL);
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_TIME
    value_assign(&sFrame.CR, TYPE_TIME);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_add(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_TIME);
    value_assign(&sValue, TYPE_TIME, 7.0);
    munit_assert_int(operator_add(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_TIME);
    munit_assert_float(sFrame.CR.Value.Time, ==, 7.0);

    return MUNIT_OK;
}


MunitResult
test_operator_div(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_OK;
}


MunitResult
test_operator_mod(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_OK;
}


MunitResult
test_operator_mul(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_OK;
}


MunitResult
test_operator_sub(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_OK;
}


