#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <frame.h>
#include <operator.h>
#include <value.h>


MunitResult
test_operator_eq(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    //  TYPE_LREAL
    value_assign(&sFrame.CR, TYPE_LREAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LREAL);
    value_assign(&sValue, TYPE_LREAL);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LREAL, 0.0);
    value_assign(&sValue, TYPE_LREAL, 1.0);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_REAL
    value_assign(&sFrame.CR, TYPE_REAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_REAL);
    value_assign(&sValue, TYPE_REAL);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_REAL, 0.0);
    value_assign(&sValue, TYPE_REAL, 1.0);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LINT);
    value_assign(&sValue, TYPE_LINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LINT, 0);
    value_assign(&sValue, TYPE_LINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DINT);
    value_assign(&sValue, TYPE_DINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_DINT, 0);
    value_assign(&sValue, TYPE_DINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_INT);
    value_assign(&sValue, TYPE_INT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_INT, 0);
    value_assign(&sValue, TYPE_INT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_SINT);
    value_assign(&sValue, TYPE_SINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_SINT, 0);
    value_assign(&sValue, TYPE_SINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_ULINT);
    value_assign(&sValue, TYPE_ULINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_ULINT, 0);
    value_assign(&sValue, TYPE_ULINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UDINT);
    value_assign(&sValue, TYPE_UDINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_UDINT, 0);
    value_assign(&sValue, TYPE_UDINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UINT);
    value_assign(&sValue, TYPE_UINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_UINT, 0);
    value_assign(&sValue, TYPE_UINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_USINT);
    value_assign(&sValue, TYPE_USINT);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_USINT, 0);
    value_assign(&sValue, TYPE_USINT, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LWORD);
    value_assign(&sValue, TYPE_LWORD);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LWORD, 0);
    value_assign(&sValue, TYPE_LWORD, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DWORD);
    value_assign(&sValue, TYPE_DWORD);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_DWORD, 0);
    value_assign(&sValue, TYPE_DWORD, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_WORD);
    value_assign(&sValue, TYPE_WORD);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_WORD, 0);
    value_assign(&sValue, TYPE_WORD, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BYTE);
    value_assign(&sValue, TYPE_BYTE);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BYTE, 0);
    value_assign(&sValue, TYPE_BYTE, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BOOL);
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_TIME
    value_assign(&sFrame.CR, TYPE_TIME);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_TIME);
    value_assign(&sValue, TYPE_TIME);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_TIME, 0.0);
    value_assign(&sValue, TYPE_TIME, 1.0);
    munit_assert_int(operator_eq(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    return MUNIT_OK;
}


MunitResult
test_operator_ge(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    //  TYPE_LREAL
    value_assign(&sFrame.CR, TYPE_LREAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LREAL);
    value_assign(&sValue, TYPE_LREAL);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LREAL, 0.0);
    value_assign(&sValue, TYPE_LREAL, 1.0);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_REAL
    value_assign(&sFrame.CR, TYPE_REAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_REAL);
    value_assign(&sValue, TYPE_REAL);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_REAL, 0.0);
    value_assign(&sValue, TYPE_REAL, 1.0);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LINT);
    value_assign(&sValue, TYPE_LINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LINT, 0);
    value_assign(&sValue, TYPE_LINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DINT);
    value_assign(&sValue, TYPE_DINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_DINT, 0);
    value_assign(&sValue, TYPE_DINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_INT);
    value_assign(&sValue, TYPE_INT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_INT, 0);
    value_assign(&sValue, TYPE_INT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_SINT);
    value_assign(&sValue, TYPE_SINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_SINT, 0);
    value_assign(&sValue, TYPE_SINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_ULINT);
    value_assign(&sValue, TYPE_ULINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_ULINT, 0);
    value_assign(&sValue, TYPE_ULINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UDINT);
    value_assign(&sValue, TYPE_UDINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_UDINT, 0);
    value_assign(&sValue, TYPE_UDINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UINT);
    value_assign(&sValue, TYPE_UINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_UINT, 0);
    value_assign(&sValue, TYPE_UINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_USINT);
    value_assign(&sValue, TYPE_USINT);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_USINT, 0);
    value_assign(&sValue, TYPE_USINT, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LWORD);
    value_assign(&sValue, TYPE_LWORD);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LWORD, 0);
    value_assign(&sValue, TYPE_LWORD, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DWORD);
    value_assign(&sValue, TYPE_DWORD);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_DWORD, 0);
    value_assign(&sValue, TYPE_DWORD, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_WORD);
    value_assign(&sValue, TYPE_WORD);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_WORD, 0);
    value_assign(&sValue, TYPE_WORD, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BYTE);
    value_assign(&sValue, TYPE_BYTE);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BYTE, 0);
    value_assign(&sValue, TYPE_BYTE, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BOOL);
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_TIME
    value_assign(&sFrame.CR, TYPE_TIME);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_TIME);
    value_assign(&sValue, TYPE_TIME);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_TIME, 0.0);
    value_assign(&sValue, TYPE_TIME, 1.0);
    munit_assert_int(operator_ge(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    return MUNIT_OK;
}


MunitResult
test_operator_gt(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_OK;
}


MunitResult
test_operator_le(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    //  TYPE_LREAL
    value_assign(&sFrame.CR, TYPE_LREAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LREAL);
    value_assign(&sValue, TYPE_LREAL);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LREAL, 1.0);
    value_assign(&sValue, TYPE_LREAL, 0.0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_REAL
    value_assign(&sFrame.CR, TYPE_REAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_REAL);
    value_assign(&sValue, TYPE_REAL);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_REAL, 1.0);
    value_assign(&sValue, TYPE_REAL, 0.0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LINT);
    value_assign(&sValue, TYPE_LINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LINT, 1);
    value_assign(&sValue, TYPE_LINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DINT);
    value_assign(&sValue, TYPE_DINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_DINT, 1);
    value_assign(&sValue, TYPE_DINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_INT);
    value_assign(&sValue, TYPE_INT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_INT, 1);
    value_assign(&sValue, TYPE_INT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_SINT);
    value_assign(&sValue, TYPE_SINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_SINT, 1);
    value_assign(&sValue, TYPE_SINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_ULINT);
    value_assign(&sValue, TYPE_ULINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_ULINT, 1);
    value_assign(&sValue, TYPE_ULINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UDINT);
    value_assign(&sValue, TYPE_UDINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_UDINT, 1);
    value_assign(&sValue, TYPE_UDINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UINT);
    value_assign(&sValue, TYPE_UINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_UINT, 1);
    value_assign(&sValue, TYPE_UINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_USINT);
    value_assign(&sValue, TYPE_USINT);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_USINT, 1);
    value_assign(&sValue, TYPE_USINT, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LWORD);
    value_assign(&sValue, TYPE_LWORD);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_LWORD, 1);
    value_assign(&sValue, TYPE_LWORD, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DWORD);
    value_assign(&sValue, TYPE_DWORD);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_DWORD, 1);
    value_assign(&sValue, TYPE_DWORD, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_WORD);
    value_assign(&sValue, TYPE_WORD);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_WORD, 1);
    value_assign(&sValue, TYPE_WORD, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BYTE);
    value_assign(&sValue, TYPE_BYTE);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BYTE, 1);
    value_assign(&sValue, TYPE_BYTE, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BOOL);
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_BOOL, 1);
    value_assign(&sValue, TYPE_BOOL, 0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    //  TYPE_TIME
    value_assign(&sFrame.CR, TYPE_TIME);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_le(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_TIME);
    value_assign(&sValue, TYPE_TIME);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);
    value_assign(&sFrame.CR, TYPE_TIME, 1.0);
    value_assign(&sValue, TYPE_TIME, 0.0);
    munit_assert_int(operator_le(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);

    return MUNIT_OK;
}


MunitResult
test_operator_lt(const MunitParameter Parameters[], void *Fixture) {
    return MUNIT_OK;
}


MunitResult
test_operator_ne(const MunitParameter Parameters[], void *Fixture) {
    FRAME sFrame;
    VALUE sValue;

    frame_initialise(&sFrame);
    value_initialise(&sValue);

    //  TYPE_LREAL
    value_assign(&sFrame.CR, TYPE_LREAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LREAL);
    value_assign(&sValue, TYPE_LREAL);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_LREAL, 0.0);
    value_assign(&sValue, TYPE_LREAL, 1.0);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_REAL
    value_assign(&sFrame.CR, TYPE_REAL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_REAL);
    value_assign(&sValue, TYPE_REAL);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_REAL, 0.0);
    value_assign(&sValue, TYPE_REAL, 1.0);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_LINT
    value_assign(&sFrame.CR, TYPE_LINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LINT);
    value_assign(&sValue, TYPE_LINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_LINT, 0);
    value_assign(&sValue, TYPE_LINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_DINT
    value_assign(&sFrame.CR, TYPE_DINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DINT);
    value_assign(&sValue, TYPE_DINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_DINT, 0);
    value_assign(&sValue, TYPE_DINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_INT
    value_assign(&sFrame.CR, TYPE_INT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_INT);
    value_assign(&sValue, TYPE_INT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_INT, 0);
    value_assign(&sValue, TYPE_INT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_SINT
    value_assign(&sFrame.CR, TYPE_SINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_SINT);
    value_assign(&sValue, TYPE_SINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_SINT, 0);
    value_assign(&sValue, TYPE_SINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_ULINT
    value_assign(&sFrame.CR, TYPE_ULINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_ULINT);
    value_assign(&sValue, TYPE_ULINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_ULINT, 0);
    value_assign(&sValue, TYPE_ULINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_UDINT
    value_assign(&sFrame.CR, TYPE_UDINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UDINT);
    value_assign(&sValue, TYPE_UDINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_UDINT, 0);
    value_assign(&sValue, TYPE_UDINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_UINT
    value_assign(&sFrame.CR, TYPE_UINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_UINT);
    value_assign(&sValue, TYPE_UINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_UINT, 0);
    value_assign(&sValue, TYPE_UINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_USINT
    value_assign(&sFrame.CR, TYPE_USINT);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_USINT);
    value_assign(&sValue, TYPE_USINT);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_USINT, 0);
    value_assign(&sValue, TYPE_USINT, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_LWORD
    value_assign(&sFrame.CR, TYPE_LWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_LWORD);
    value_assign(&sValue, TYPE_LWORD);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_LWORD, 0);
    value_assign(&sValue, TYPE_LWORD, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_DWORD
    value_assign(&sFrame.CR, TYPE_DWORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_DWORD);
    value_assign(&sValue, TYPE_DWORD);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_DWORD, 0);
    value_assign(&sValue, TYPE_DWORD, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_WORD
    value_assign(&sFrame.CR, TYPE_WORD);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_WORD);
    value_assign(&sValue, TYPE_WORD);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_WORD, 0);
    value_assign(&sValue, TYPE_WORD, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_BYTE
    value_assign(&sFrame.CR, TYPE_BYTE);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BYTE);
    value_assign(&sValue, TYPE_BYTE);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_BYTE, 0);
    value_assign(&sValue, TYPE_BYTE, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_BOOL
    value_assign(&sFrame.CR, TYPE_BOOL);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_BOOL);
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_BOOL, 0);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    //  TYPE_TIME
    value_assign(&sFrame.CR, TYPE_TIME);
    sValue.Type = TYPE_STRING;
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, ERROR_OPERAND_TYPE);
    value_assign(&sFrame.CR, TYPE_TIME);
    value_assign(&sValue, TYPE_TIME);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 0);
    value_assign(&sFrame.CR, TYPE_TIME, 0.0);
    value_assign(&sValue, TYPE_TIME, 1.0);
    munit_assert_int(operator_ne(&sFrame, &sValue), ==, 0);
    munit_assert_uint32(sFrame.CR.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sFrame.CR.Value.B1, ==, 1);

    return MUNIT_OK;
}
