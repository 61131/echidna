#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <munit/munit.h>

#include <value.h>


MunitResult
test_value_assign(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;
    VALUE_TYPE sType[6];
    int nIndex;

    value_assign(&sValue);
    value_assign(NULL, TYPE_BOOL);

    //  ANY_NUM, ANY_REAL, TYPE_LREAL
    sType[0] = ANY_NUM;
    sType[1] = ANY_REAL;
    sType[2] = TYPE_LREAL;
    for(nIndex = 0; nIndex < 3; ++nIndex) {
        value_assign(&sValue, sType[nIndex]);
        munit_assert_uint32(sValue.Type, ==, sType[nIndex]);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(double));
        munit_assert_double(sValue.Maximum.Double, ==, DBL_MAX);
        munit_assert_double(sValue.Minimum.Double, ==, DBL_MIN);
        munit_assert_double(sValue.Value.Double, ==, 0.0);
        munit_assert_null(sValue.Meta);
        value_destroy(&sValue);
        value_assign(&sValue, sType[nIndex], 1.0);
        munit_assert_double(sValue.Value.Double, ==, 1.0);
        value_destroy(&sValue);
    }

    //  TYPE_REAL
    value_assign(&sValue, TYPE_REAL);
    munit_assert_uint32(sValue.Type, ==, TYPE_REAL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(float));
    munit_assert_float(sValue.Maximum.Single, ==, FLT_MAX);
    munit_assert_float(sValue.Minimum.Single, ==, FLT_MIN);
    munit_assert_float(sValue.Value.Single, ==, 0.0f);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_REAL, 1.0f);
    munit_assert_float(sValue.Value.Single, ==, 1.0f);
    value_destroy(&sValue);

    //  ANY_INT, TYPE_LINT
    sType[0] = ANY_INT;
    sType[1] = TYPE_LINT;
    for(nIndex = 0; nIndex < 2; ++nIndex) {
        value_assign(&sValue, sType[nIndex]);
        munit_assert_uint32(sValue.Type, ==, sType[nIndex]);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(int64_t));
        munit_assert_int64(sValue.Maximum.S64, ==, INT64_MAX);
        munit_assert_int64(sValue.Minimum.S64, ==, INT64_MIN);
        munit_assert_int64(sValue.Value.S64, ==, 0);
        munit_assert_null(sValue.Meta);
        value_destroy(&sValue);
        value_assign(&sValue, sType[nIndex], 1);
        munit_assert_int64(sValue.Value.S64, ==, 1);
        value_destroy(&sValue);
    }

    //  TYPE_DINT
    value_assign(&sValue, TYPE_DINT);
    munit_assert_uint32(sValue.Type, ==, TYPE_DINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int32_t));
    munit_assert_int32(sValue.Maximum.S32, ==, INT32_MAX);
    munit_assert_int32(sValue.Minimum.S32, ==, INT32_MIN);
    munit_assert_int32(sValue.Value.S32, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_DINT, 1);
    munit_assert_int32(sValue.Value.S32, ==, 1);
    value_destroy(&sValue);

    //  TYPE_INT
    value_assign(&sValue, TYPE_INT);
    munit_assert_uint32(sValue.Type, ==, TYPE_INT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int16_t));
    munit_assert_int16(sValue.Maximum.S16, ==, INT16_MAX);
    munit_assert_int16(sValue.Minimum.S16, ==, INT16_MIN);
    munit_assert_int16(sValue.Value.S16, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_INT, 1);
    munit_assert_int16(sValue.Value.S16, ==, 1);
    value_destroy(&sValue);

    //  TYPE_SINT
    value_assign(&sValue, TYPE_SINT);
    munit_assert_uint32(sValue.Type, ==, TYPE_SINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int8_t));
    munit_assert_int8(sValue.Maximum.S8, ==, INT8_MAX);
    munit_assert_int8(sValue.Minimum.S8, ==, INT8_MIN);
    munit_assert_int8(sValue.Value.S8, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_SINT, 1);
    munit_assert_int8(sValue.Value.S8, ==, 1);
    value_destroy(&sValue);

    //  TYPE_ULINT
    value_assign(&sValue, TYPE_ULINT);
    munit_assert_uint32(sValue.Type, ==, TYPE_ULINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint64_t));
    munit_assert_uint64(sValue.Maximum.U64, ==, UINT64_MAX);
    munit_assert_uint64(sValue.Minimum.U64, ==, 0);
    munit_assert_uint64(sValue.Value.U64, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_ULINT, 1);
    munit_assert_uint64(sValue.Value.U64, ==, 1);
    value_destroy(&sValue);

    //  TYPE_UDINT
    value_assign(&sValue, TYPE_UDINT);
    munit_assert_uint32(sValue.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint32_t));
    munit_assert_uint32(sValue.Maximum.U32, ==, UINT32_MAX);
    munit_assert_uint32(sValue.Minimum.U32, ==, 0);
    munit_assert_uint32(sValue.Value.U32, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_UDINT, 1);
    munit_assert_uint32(sValue.Value.U32, ==, 1);
    value_destroy(&sValue);

    //  TYPE_UINT
    value_assign(&sValue, TYPE_UINT);
    munit_assert_uint32(sValue.Type, ==, TYPE_UINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint16_t));
    munit_assert_uint16(sValue.Maximum.U16, ==, UINT16_MAX);
    munit_assert_uint16(sValue.Minimum.U16, ==, 0);
    munit_assert_uint16(sValue.Value.U16, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_UINT, 1);
    munit_assert_uint16(sValue.Value.U16, ==, 1);
    value_destroy(&sValue);

    //  TYPE_USINT
    value_assign(&sValue, TYPE_USINT);
    munit_assert_uint32(sValue.Type, ==, TYPE_USINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.U8, ==, UINT8_MAX);
    munit_assert_uint8(sValue.Minimum.U8, ==, 0);
    munit_assert_uint8(sValue.Value.U8, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_USINT, 1);
    munit_assert_uint8(sValue.Value.U8, ==, 1);
    value_destroy(&sValue);

    //  ANY_BIT, TYPE_LWORD
    sType[0] = ANY_BIT;
    sType[1] = TYPE_LWORD;
    for(nIndex = 0; nIndex < 2; ++nIndex) {
        value_assign(&sValue, sType[nIndex]);
        munit_assert_uint32(sValue.Type, ==, sType[nIndex]);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(uint64_t));
        munit_assert_uint64(sValue.Maximum.B64, ==, UINT64_MAX);
        munit_assert_uint64(sValue.Minimum.B64, ==, 0);
        munit_assert_uint64(sValue.Value.B64, ==, 0);
        munit_assert_null(sValue.Meta);
        value_destroy(&sValue);
        value_assign(&sValue, sType[nIndex], 1);
        munit_assert_uint64(sValue.Value.B64, ==, 1);
        value_destroy(&sValue);
    }

    //  TYPE_DWORD
    value_assign(&sValue, TYPE_DWORD);
    munit_assert_uint32(sValue.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint32_t));
    munit_assert_uint32(sValue.Maximum.B32, ==, UINT32_MAX);
    munit_assert_uint32(sValue.Minimum.B32, ==, 0);
    munit_assert_uint32(sValue.Value.B32, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_DWORD, 1);
    munit_assert_uint32(sValue.Value.B32, ==, 1);
    value_destroy(&sValue);

    //  TYPE_WORD
    value_assign(&sValue, TYPE_WORD);
    munit_assert_uint32(sValue.Type, ==, TYPE_WORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint16_t));
    munit_assert_uint16(sValue.Maximum.B16, ==, UINT16_MAX);
    munit_assert_uint16(sValue.Minimum.B16, ==, 0);
    munit_assert_uint16(sValue.Value.B16, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_WORD, 1);
    munit_assert_uint16(sValue.Value.B16, ==, 1);
    value_destroy(&sValue);

    //  TYPE_BYTE
    value_assign(&sValue, TYPE_BYTE);
    munit_assert_uint32(sValue.Type, ==, TYPE_BYTE);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B8, ==, UINT8_MAX);
    munit_assert_uint8(sValue.Minimum.B8, ==, 0);
    munit_assert_uint8(sValue.Value.B8, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_BYTE, 1);
    munit_assert_uint8(sValue.Value.B8, ==, 1);
    value_destroy(&sValue);

    //  TYPE_BOOL
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B1, ==, 1);
    munit_assert_uint8(sValue.Minimum.B1, ==, 0);
    munit_assert_uint8(sValue.Value.B1, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_BOOL, 1);
    munit_assert_uint8(sValue.Value.B1, ==, 1);
    value_destroy(&sValue);

    //  TYPE_TIME
    value_assign(&sValue, TYPE_TIME);
    munit_assert_uint32(sValue.Type, ==, TYPE_TIME);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(float));
    munit_assert_float(sValue.Maximum.Time, ==, FLT_MAX);
    munit_assert_float(sValue.Minimum.Time, ==, FLT_MIN);
    munit_assert_float(sValue.Value.Time, ==, 0.0f);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_TIME, 1.0f);
    munit_assert_float(sValue.Value.Time, ==, 1.0f);
    value_destroy(&sValue);

    //  ANY_DATE, TYPE_DATE, TYPE_DT, TYPE_TOD
    sType[0] = ANY_DATE;
    sType[1] = TYPE_DATE;
    sType[2] = TYPE_DT;
    sType[3] = TYPE_TOD;
    for(nIndex = 0; nIndex < 4; ++nIndex) {
        value_assign(&sValue, sType[nIndex]);
        munit_assert_uint32(sValue.Type, ==, sType[nIndex]);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(time_t));
        munit_assert_uint64((uint64_t) sValue.Maximum.DateTime, ==, 0);
        munit_assert_uint64((uint64_t) sValue.Minimum.DateTime, ==, 0);
        munit_assert_uint64((uint64_t) sValue.Value.DateTime, ==, 0);
        munit_assert_null(sValue.Meta);
    }

     
    //  TYPE_NONE
    value_assign(&sValue, TYPE_NONE);
    munit_assert_uint32(sValue.Type, ==, TYPE_NONE);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, 0);
    munit_assert_uint64(sValue.Maximum.B64, ==, 0);
    munit_assert_uint64(sValue.Minimum.B64, ==, 0);
    munit_assert_uint64(sValue.Value.B64, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_ENUMERATED
    //  TYPE_FUNCTION
    //  TYPE_FUNCTION_BLOCK
    //  TYPE_LABEL
    //  _TYPE_PROGRAM
    value_assign(&sValue, TYPE_LABEL);
    munit_assert_uint32(sValue.Type, ==, TYPE_LABEL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_LABEL, NULL);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);
    value_assign(&sValue, TYPE_LABEL, "_label");
    munit_assert_not_null(sValue.Meta);
    munit_assert_string_equal(sValue.Meta, "_label");
    value_destroy(&sValue, NULL);

    //  TYPE_STRING
    //  TYPE_WSTRING
    sType[0] = TYPE_STRING;
    sType[1] = TYPE_WSTRING;
    for(nIndex = 0; nIndex < 2; ++nIndex) {
        value_assign(&sValue, sType[nIndex]);
        munit_assert_uint32(sValue.Type, ==, sType[nIndex]);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, 0);
        munit_assert_null(sValue.Meta);
    }

    return MUNIT_OK;
}


