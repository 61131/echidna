#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <munit/munit.h>

#include <value.h>


MunitResult
test_value_initialise(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;

    value_initialise(&sValue);
    munit_assert_uint32(sValue.Type, ==, TYPE_NONE);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, 0);
    munit_assert_int64(sValue.Index.Lower, ==, 0);
    munit_assert_int64(sValue.Index.Upper, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    value_initialise(NULL);
    value_destroy(NULL);

    return MUNIT_OK;
}


MunitResult
test_value_strtotype(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;

    //  TYPE_LREAL
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "LREAL"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_LREAL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(double));
    munit_assert_double(sValue.Maximum.Double, ==, DBL_MAX);
    munit_assert_double(sValue.Minimum.Double, ==, DBL_MIN);
    munit_assert_double(sValue.Value.Double, ==, 0.0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_REAL
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "REAL"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_REAL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(float));
    munit_assert_float(sValue.Maximum.Single, ==, FLT_MAX);
    munit_assert_float(sValue.Minimum.Single, ==, FLT_MIN);
    munit_assert_float(sValue.Value.Single, ==, 0.0f);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_LINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "LINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_LINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int64_t));
    munit_assert_int64(sValue.Maximum.S64, ==, INT64_MAX);
    munit_assert_int64(sValue.Minimum.S64, ==, INT64_MIN);
    munit_assert_int64(sValue.Value.S64, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_DINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "DINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_DINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int32_t));
    munit_assert_int32(sValue.Maximum.S32, ==, INT32_MAX);
    munit_assert_int32(sValue.Minimum.S32, ==, INT32_MIN);
    munit_assert_int32(sValue.Value.S32, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_INT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "INT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_INT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int16_t));
    munit_assert_int16(sValue.Maximum.S16, ==, INT16_MAX);
    munit_assert_int16(sValue.Minimum.S16, ==, INT16_MIN);
    munit_assert_int16(sValue.Value.S16, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_SINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "SINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_SINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int8_t));
    munit_assert_int8(sValue.Maximum.S8, ==, INT8_MAX);
    munit_assert_int8(sValue.Minimum.S8, ==, INT8_MIN);
    munit_assert_int8(sValue.Value.S8, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_ULINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "ULINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_ULINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint64_t));
    munit_assert_uint64(sValue.Maximum.U64, ==, UINT64_MAX);
    munit_assert_uint64(sValue.Minimum.U64, ==, 0);
    munit_assert_uint64(sValue.Value.U64, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_UDINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "UDINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint32_t));
    munit_assert_uint32(sValue.Maximum.U32, ==, UINT32_MAX);
    munit_assert_uint32(sValue.Minimum.U32, ==, 0);
    munit_assert_uint32(sValue.Value.U32, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_UINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "UINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_UINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint16_t));
    munit_assert_uint16(sValue.Maximum.U16, ==, UINT16_MAX);
    munit_assert_uint16(sValue.Minimum.U16, ==, 0);
    munit_assert_uint16(sValue.Value.U16, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_USINT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "USINT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_USINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.U8, ==, UINT8_MAX);
    munit_assert_uint8(sValue.Minimum.U8, ==, 0);
    munit_assert_uint8(sValue.Value.U8, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_LWORD
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "LWORD"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_LWORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint64_t));
    munit_assert_uint64(sValue.Maximum.B64, ==, UINT64_MAX);
    munit_assert_uint64(sValue.Minimum.B64, ==, 0);
    munit_assert_uint64(sValue.Value.B64, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_DWORD
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "DWORD"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint32_t));
    munit_assert_uint32(sValue.Maximum.B32, ==, UINT32_MAX);
    munit_assert_uint32(sValue.Minimum.B32, ==, 0);
    munit_assert_uint32(sValue.Value.B32, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_WORD
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "WORD"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_WORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint16_t));
    munit_assert_uint16(sValue.Maximum.B16, ==, UINT16_MAX);
    munit_assert_uint16(sValue.Minimum.B16, ==, 0);
    munit_assert_uint16(sValue.Value.B16, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_BYTE
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "BYTE"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_BYTE);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B8, ==, UINT8_MAX);
    munit_assert_uint8(sValue.Minimum.B8, ==, 0);
    munit_assert_uint8(sValue.Value.B8, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_BOOL
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "BOOL"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B1, ==, 1);
    munit_assert_uint8(sValue.Minimum.B1, ==, 0);
    munit_assert_uint8(sValue.Value.B1, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TRUE
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "TRUE"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B1, ==, 1);
    munit_assert_uint8(sValue.Minimum.B1, ==, 1);
    munit_assert_uint8(sValue.Value.B1, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  FALSE
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "FALSE"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B1, ==, 0);
    munit_assert_uint8(sValue.Minimum.B1, ==, 0);
    munit_assert_uint8(sValue.Value.B1, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_TIME
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "TIME"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_TIME);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(float));
    munit_assert_float(sValue.Maximum.Single, ==, FLT_MAX);
    munit_assert_float(sValue.Minimum.Single, ==, FLT_MIN);
    munit_assert_float(sValue.Value.Single, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_DATE
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "DATE"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_DATE);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(time_t));
    munit_assert_uint64((uint64_t) sValue.Maximum.DateTime, ==, 0);
    munit_assert_uint64((uint64_t) sValue.Minimum.DateTime, ==, 0);
    munit_assert_uint64((uint64_t) sValue.Value.DateTime, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_DT
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "DATE_AND_TIME"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_DT);
    munit_assert_int(value_strtotype(&sValue, "DT"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_DT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(time_t));
    munit_assert_uint64((uint64_t) sValue.Maximum.DateTime, ==, 0);
    munit_assert_uint64((uint64_t) sValue.Minimum.DateTime, ==, 0);
    munit_assert_uint64((uint64_t) sValue.Value.DateTime, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_TOD
    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "TIME_OF_DAY"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_TOD);
    munit_assert_int(value_strtotype(&sValue, "TOD"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_TOD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(time_t));
    munit_assert_uint64((uint64_t) sValue.Maximum.DateTime, ==, 0);
    munit_assert_uint64((uint64_t) sValue.Minimum.DateTime, ==, 0);
    munit_assert_uint64((uint64_t) sValue.Value.DateTime, ==, 0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    value_initialise(&sValue);
    munit_assert_int(value_strtotype(&sValue, "OTHER"), ==, -1);

    return MUNIT_OK;
}


MunitResult
test_value_strtoval(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;
    char *sStr[8];
    int nIndex;

    munit_assert_int(value_strtoval(NULL, TYPE_NONE, ""), !=, 0);
    munit_assert_int(value_strtoval(&sValue, TYPE_NONE, ""), !=, 0);

    //  TYPE_LREAL
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_LREAL, "-1.0"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_LREAL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(double));
    munit_assert_double(sValue.Maximum.Double, ==, DBL_MAX);
    munit_assert_double(sValue.Minimum.Double, ==, DBL_MIN);
    munit_assert_double(sValue.Value.Double, ==, -1.0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_REAL
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_REAL, "-1.0"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_REAL);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(float));
    munit_assert_float(sValue.Maximum.Single, ==, FLT_MAX);
    munit_assert_float(sValue.Minimum.Single, ==, FLT_MIN);
    munit_assert_float(sValue.Value.Single, ==, -1.0f);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_LINT
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_LINT, "-1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_LINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(int64_t));
    munit_assert_int64(sValue.Maximum.S64, ==, INT64_MAX);
    munit_assert_int64(sValue.Minimum.S64, ==, INT64_MIN);
    munit_assert_int64(sValue.Value.S64, ==, -1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_DINT
    sStr[0] = "65536";
    sStr[1] = "65_536";
    sStr[2] = "2#10000000000000000";
    sStr[3] = "2#1_00000000_00000000";
    sStr[4] = "8#200000";
    sStr[5] = "8#0020_0000";
    sStr[6] = "16#10000";
    sStr[7] = "16#1_0000";
    for(nIndex = 0; nIndex < 8; ++nIndex) {
        value_initialise(&sValue);
        munit_assert_int(value_strtoval(&sValue, TYPE_DINT, sStr[nIndex]), ==, 0);
        munit_assert_uint32(sValue.Type, ==, TYPE_DINT);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(int32_t));
        munit_assert_int32(sValue.Maximum.S32, ==, INT32_MAX);
        munit_assert_int32(sValue.Minimum.S32, ==, INT32_MIN);
        munit_assert_int32(sValue.Value.S32, ==, 65536);
        value_destroy(&sValue);
    }

    //  TYPE_INT
    sStr[0] = "4096";
    sStr[1] = "4_096";
    sStr[2] = "2#1000000000000";
    sStr[3] = "2#00010000_00000000";
    sStr[4] = "8#10000";
    sStr[5] = "8#1_0000";
    sStr[6] = "16#1000";
    sStr[7] = "16#0000_1000";
    for(nIndex = 0; nIndex < 8; ++nIndex) {
        value_initialise(&sValue);
        munit_assert_int(value_strtoval(&sValue, TYPE_INT, sStr[nIndex]), ==, 0);
        munit_assert_uint32(sValue.Type, ==, TYPE_INT);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(int16_t));
        munit_assert_int16(sValue.Maximum.S16, ==, INT16_MAX);
        munit_assert_int16(sValue.Minimum.S16, ==, INT16_MIN);
        munit_assert_int16(sValue.Value.S16, ==, 4096);
        value_destroy(&sValue);
    }

    //  TYPE_SINT
    sStr[0] = "64";
    sStr[1] = "6_4";
    sStr[2] = "2#01000000";
    sStr[3] = "2#0100_0000";
    sStr[4] = "8#0100";
    sStr[5] = "8#01_00";
    sStr[6] = "16#40";
    sStr[7] = "16#4_0";
    for(nIndex = 0; nIndex < 8; ++nIndex) {
        value_initialise(&sValue);
        munit_assert_int(value_strtoval(&sValue, TYPE_SINT, sStr[nIndex]), ==, 0);
        munit_assert_uint32(sValue.Type, ==, TYPE_SINT);
        munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(int8_t));
        munit_assert_int8(sValue.Maximum.S8, ==, INT8_MAX);
        munit_assert_int8(sValue.Minimum.S8, ==, INT8_MIN);
        munit_assert_int8(sValue.Value.S8, ==, 64);
        value_destroy(&sValue);
    }

    //  TYPE_ULINT
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_ULINT, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_ULINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint64_t));
    munit_assert_uint64(sValue.Maximum.U64, ==, UINT64_MAX);
    munit_assert_uint64(sValue.Minimum.U64, ==, 0);
    munit_assert_uint64(sValue.Value.U64, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_UDINT
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_UDINT, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_UDINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint32_t));
    munit_assert_uint32(sValue.Maximum.U32, ==, UINT32_MAX);
    munit_assert_uint32(sValue.Minimum.U32, ==, 0);
    munit_assert_uint32(sValue.Value.U32, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_UINT
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_UINT, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_UINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint16_t));
    munit_assert_uint16(sValue.Maximum.U16, ==, UINT16_MAX);
    munit_assert_uint16(sValue.Minimum.U16, ==, 0);
    munit_assert_uint16(sValue.Value.U16, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_USINT
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_USINT, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_USINT);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.U8, ==, UINT8_MAX);
    munit_assert_uint8(sValue.Minimum.U8, ==, 0);
    munit_assert_uint8(sValue.Value.U8, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_LWORD
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_LWORD, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_LWORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint64_t));
    munit_assert_uint64(sValue.Maximum.B64, ==, UINT64_MAX);
    munit_assert_uint64(sValue.Minimum.B64, ==, 0);
    munit_assert_uint64(sValue.Value.B64, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_DWORD
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_DWORD, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_DWORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint32_t));
    munit_assert_uint32(sValue.Maximum.B32, ==, UINT32_MAX);
    munit_assert_uint32(sValue.Minimum.B32, ==, 0);
    munit_assert_uint32(sValue.Value.B32, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_WORD
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_WORD, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_WORD);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint16_t));
    munit_assert_uint16(sValue.Maximum.B16, ==, UINT16_MAX);
    munit_assert_uint16(sValue.Minimum.B16, ==, 0);
    munit_assert_uint16(sValue.Value.B16, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_BYTE
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_BYTE, "1"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_BYTE);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(uint8_t));
    munit_assert_uint8(sValue.Maximum.B8, ==, UINT8_MAX);
    munit_assert_uint8(sValue.Minimum.B8, ==, 0);
    munit_assert_uint8(sValue.Value.B8, ==, 1);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    //  TYPE_BOOL
    sStr[0] = "0";
    sStr[1] = "1";
    sStr[2] = "2";
    for(nIndex = 0; nIndex < 3; ++nIndex) {
        value_initialise(&sValue);
        munit_assert_int(value_strtoval(&sValue, TYPE_BOOL, sStr[nIndex]), ==, 0);
        munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
        munit_assert_uint32(sValue.Flags, ==, TYPE_NONE);
        munit_assert_int(sValue.Length, ==, sizeof(int8_t));
        munit_assert_uint8(sValue.Maximum.B1, ==, 1);
        munit_assert_uint8(sValue.Minimum.B1, ==, 0);
        munit_assert_uint8(sValue.Value.B1, ==, (nIndex != 0));
        value_destroy(&sValue);
    }

    //  TYPE_TIME
    value_initialise(&sValue);
    munit_assert_int(value_strtoval(&sValue, TYPE_TIME, "1.0"), ==, 0);
    munit_assert_uint32(sValue.Type, ==, TYPE_TIME);
    munit_assert_uint32(sValue.Flags, ==, FLAG_NONE);
    munit_assert_int(sValue.Length, ==, sizeof(float));
    munit_assert_float(sValue.Maximum.Single, ==, FLT_MAX);
    munit_assert_float(sValue.Minimum.Single, ==, FLT_MIN);
    munit_assert_float(sValue.Value.Single, ==, 1.0);
    munit_assert_null(sValue.Meta);
    value_destroy(&sValue);

    return MUNIT_OK;
}


MunitResult
test_value_type(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_uint32(TYPE_NONE, ==, 0);
    munit_assert_uint32(ANY, ==, 0xffffffff);

    //  ANY_ELEMENTARY
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_LREAL, ==, TYPE_LREAL);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_REAL, ==, TYPE_REAL);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_LINT, ==, TYPE_LINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_DINT, ==, TYPE_DINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_INT, ==, TYPE_INT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_SINT, ==, TYPE_SINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_ULINT, ==, TYPE_ULINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_UDINT, ==, TYPE_UDINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_UINT, ==, TYPE_UINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_USINT, ==, TYPE_USINT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_LWORD, ==, TYPE_LWORD);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_DWORD, ==, TYPE_DWORD);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_WORD, ==, TYPE_WORD);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_BYTE, ==, TYPE_BYTE);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_BOOL, ==, TYPE_BOOL);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_TIME, ==, TYPE_TIME);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_DATE, ==, TYPE_DATE);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_DT, ==, TYPE_DT);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_TOD, ==, TYPE_TOD);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_STRING, ==, TYPE_STRING);
    munit_assert_uint32(ANY_ELEMENTARY & TYPE_WSTRING, ==, TYPE_WSTRING);

    //  ANY_MAGNITUDE
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_LREAL, ==, TYPE_LREAL);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_REAL, ==, TYPE_REAL);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_LINT, ==, TYPE_LINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_DINT, ==, TYPE_DINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_INT, ==, TYPE_INT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_SINT, ==, TYPE_SINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_ULINT, ==, TYPE_ULINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_UDINT, ==, TYPE_UDINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_UINT, ==, TYPE_UINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_USINT, ==, TYPE_USINT);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_LWORD, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_DWORD, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_WORD, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_BYTE, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_BOOL, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_TIME, ==, TYPE_TIME);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_DATE, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_DT, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_TOD, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_STRING, ==, 0);
    munit_assert_uint32(ANY_MAGNITUDE & TYPE_WSTRING, ==, 0);

    //  ANY_NUM
    munit_assert_uint32(ANY_NUM & TYPE_LREAL, ==, TYPE_LREAL);
    munit_assert_uint32(ANY_NUM & TYPE_REAL, ==, TYPE_REAL);
    munit_assert_uint32(ANY_NUM & TYPE_LINT, ==, TYPE_LINT);
    munit_assert_uint32(ANY_NUM & TYPE_DINT, ==, TYPE_DINT);
    munit_assert_uint32(ANY_NUM & TYPE_INT, ==, TYPE_INT);
    munit_assert_uint32(ANY_NUM & TYPE_SINT, ==, TYPE_SINT);
    munit_assert_uint32(ANY_NUM & TYPE_ULINT, ==, TYPE_ULINT);
    munit_assert_uint32(ANY_NUM & TYPE_UDINT, ==, TYPE_UDINT);
    munit_assert_uint32(ANY_NUM & TYPE_UINT, ==, TYPE_UINT);
    munit_assert_uint32(ANY_NUM & TYPE_USINT, ==, TYPE_USINT);
    munit_assert_uint32(ANY_NUM & TYPE_LWORD, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_DWORD, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_WORD, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_BYTE, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_BOOL, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_TIME, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_DATE, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_DT, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_TOD, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_STRING, ==, 0);
    munit_assert_uint32(ANY_NUM & TYPE_WSTRING, ==, 0);

    //  ANY_REAL
    munit_assert_uint32(ANY_REAL & TYPE_LREAL, ==, TYPE_LREAL);
    munit_assert_uint32(ANY_REAL & TYPE_REAL, ==, TYPE_REAL);
    munit_assert_uint32(ANY_REAL & TYPE_LINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_DINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_INT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_SINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_ULINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_UDINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_UINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_USINT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_LWORD, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_DWORD, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_WORD, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_BYTE, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_BOOL, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_TIME, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_DATE, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_DT, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_TOD, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_STRING, ==, 0);
    munit_assert_uint32(ANY_REAL & TYPE_WSTRING, ==, 0);

    //  ANY_INT
    munit_assert_uint32(ANY_INT & TYPE_LREAL, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_REAL, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_LINT, ==, TYPE_LINT);
    munit_assert_uint32(ANY_INT & TYPE_DINT, ==, TYPE_DINT);
    munit_assert_uint32(ANY_INT & TYPE_INT, ==, TYPE_INT);
    munit_assert_uint32(ANY_INT & TYPE_SINT, ==, TYPE_SINT);
    munit_assert_uint32(ANY_INT & TYPE_ULINT, ==, TYPE_ULINT);
    munit_assert_uint32(ANY_INT & TYPE_UDINT, ==, TYPE_UDINT);
    munit_assert_uint32(ANY_INT & TYPE_UINT, ==, TYPE_UINT);
    munit_assert_uint32(ANY_INT & TYPE_USINT, ==, TYPE_USINT);
    munit_assert_uint32(ANY_INT & TYPE_LWORD, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_DWORD, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_WORD, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_BYTE, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_BOOL, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_TIME, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_DATE, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_DT, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_TOD, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_STRING, ==, 0);
    munit_assert_uint32(ANY_INT & TYPE_WSTRING, ==, 0);

    //  ANY_BIT
    munit_assert_uint32(ANY_BIT & TYPE_LREAL, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_REAL, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_LINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_DINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_INT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_SINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_ULINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_UDINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_UINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_USINT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_LWORD, ==, TYPE_LWORD);
    munit_assert_uint32(ANY_BIT & TYPE_DWORD, ==, TYPE_DWORD);
    munit_assert_uint32(ANY_BIT & TYPE_WORD, ==, TYPE_WORD);
    munit_assert_uint32(ANY_BIT & TYPE_BYTE, ==, TYPE_BYTE);
    munit_assert_uint32(ANY_BIT & TYPE_BOOL, ==, TYPE_BOOL);
    munit_assert_uint32(ANY_BIT & TYPE_TIME, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_DATE, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_DT, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_TOD, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_STRING, ==, 0);
    munit_assert_uint32(ANY_BIT & TYPE_WSTRING, ==, 0);

    //  ANY_STRING
    munit_assert_uint32(ANY_STRING & TYPE_LREAL, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_REAL, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_LINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_DINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_INT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_SINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_ULINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_UDINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_UINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_USINT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_LWORD, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_DWORD, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_WORD, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_BYTE, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_BOOL, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_TIME, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_DATE, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_DT, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_TOD, ==, 0);
    munit_assert_uint32(ANY_STRING & TYPE_STRING, ==, TYPE_STRING);
    munit_assert_uint32(ANY_STRING & TYPE_WSTRING, ==, TYPE_WSTRING);

    //  ANY_DATE
    munit_assert_uint32(ANY_DATE & TYPE_LREAL, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_REAL, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_LINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_DINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_INT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_SINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_ULINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_UDINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_UINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_USINT, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_LWORD, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_DWORD, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_WORD, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_BYTE, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_BOOL, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_TIME, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_DATE, ==, TYPE_DATE);
    munit_assert_uint32(ANY_DATE & TYPE_DT, ==, TYPE_DT);
    munit_assert_uint32(ANY_DATE & TYPE_TOD, ==, TYPE_TOD);
    munit_assert_uint32(ANY_DATE & TYPE_STRING, ==, 0);
    munit_assert_uint32(ANY_DATE & TYPE_WSTRING, ==, 0);

    return MUNIT_OK;
}


MunitResult
test_value_typetostr(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_string_equal(value_typetostr(TYPE_LREAL), "LREAL");
    munit_assert_string_equal(value_typetostr(TYPE_REAL), "REAL");
    munit_assert_string_equal(value_typetostr(TYPE_LINT), "LINT");
    munit_assert_string_equal(value_typetostr(TYPE_DINT), "DINT");
    munit_assert_string_equal(value_typetostr(TYPE_INT), "INT");
    munit_assert_string_equal(value_typetostr(TYPE_SINT), "SINT");
    munit_assert_string_equal(value_typetostr(TYPE_ULINT), "ULINT");
    munit_assert_string_equal(value_typetostr(TYPE_UDINT), "UDINT");
    munit_assert_string_equal(value_typetostr(TYPE_UINT), "UINT");
    munit_assert_string_equal(value_typetostr(TYPE_USINT), "USINT");
    munit_assert_string_equal(value_typetostr(TYPE_LWORD), "LWORD");
    munit_assert_string_equal(value_typetostr(TYPE_DWORD), "DWORD");
    munit_assert_string_equal(value_typetostr(TYPE_WORD), "WORD");
    munit_assert_string_equal(value_typetostr(TYPE_BYTE), "BYTE");
    munit_assert_string_equal(value_typetostr(TYPE_BOOL), "BOOL");
    munit_assert_string_equal(value_typetostr(TYPE_TIME), "TIME");
    munit_assert_string_equal(value_typetostr(TYPE_DATE), "DATE");
    munit_assert_string_equal(value_typetostr(TYPE_DT), "DATE_AND_TIME");
    munit_assert_string_equal(value_typetostr(TYPE_TOD), "TIME_OF_DAY");
    munit_assert_string_equal(value_typetostr(TYPE_FUNCTION_BLOCK), "FUNCTION_BLOCK");
    munit_assert_string_equal(value_typetostr(TYPE_FUNCTION), "FUNCTION");
    munit_assert_string_equal(value_typetostr(TYPE_LABEL), "LABEL");
    munit_assert_string_equal(value_typetostr(_TYPE_PROGRAM), "PROGRAM");
    munit_assert_string_equal(value_typetostr(TYPE_NONE), "(NONE)");
    //  TODO: Handle ANY_ types?!
    munit_assert_string_equal(value_typetostr(ANY), "(ERROR)");

    return MUNIT_OK;
}


MunitResult
test_value_typetosize(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(value_typetosize(TYPE_LREAL), ==, sizeof(double));
    munit_assert_int(value_typetosize(TYPE_REAL), ==, sizeof(float));
    munit_assert_int(value_typetosize(TYPE_LINT), ==, sizeof(int64_t));
    munit_assert_int(value_typetosize(TYPE_DINT), ==, sizeof(int32_t));
    munit_assert_int(value_typetosize(TYPE_INT), ==, sizeof(int16_t));
    munit_assert_int(value_typetosize(TYPE_SINT), ==, sizeof(int8_t));
    munit_assert_int(value_typetosize(TYPE_ULINT), ==, sizeof(uint64_t));
    munit_assert_int(value_typetosize(TYPE_UDINT), ==, sizeof(uint32_t));
    munit_assert_int(value_typetosize(TYPE_UINT), ==, sizeof(uint16_t));
    munit_assert_int(value_typetosize(TYPE_USINT), ==, sizeof(uint8_t));
    munit_assert_int(value_typetosize(TYPE_LWORD), ==, sizeof(uint64_t));
    munit_assert_int(value_typetosize(TYPE_DWORD), ==, sizeof(uint32_t));
    munit_assert_int(value_typetosize(TYPE_WORD), ==, sizeof(uint16_t));
    munit_assert_int(value_typetosize(TYPE_BYTE), ==, sizeof(uint8_t));
    munit_assert_int(value_typetosize(TYPE_BOOL), ==, sizeof(uint8_t));
    munit_assert_int(value_typetosize(TYPE_TIME), ==, sizeof(float));
    munit_assert_int(value_typetosize(TYPE_DATE), ==, sizeof(time_t));
    munit_assert_int(value_typetosize(TYPE_DT), ==, sizeof(time_t));
    munit_assert_int(value_typetosize(TYPE_TOD), ==, sizeof(time_t));
    munit_assert_int(value_typetosize(TYPE_INPUT), ==, 0);
    munit_assert_int(value_typetosize(TYPE_IN_OUT), ==, 0);
    munit_assert_int(value_typetosize(TYPE_OUTPUT), ==, 0);
    munit_assert_int(value_typetosize(TYPE_LABEL), ==, sizeof(uint32_t));

    return MUNIT_OK;
}

