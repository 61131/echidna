#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <munit/munit.h>

#include <cast.h>


MunitResult
test_cast_error(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;

    //  TYPE_LREAL
    errno = 0;
    munit_assert_int(cast_lreal(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_lreal(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_lreal(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_REAL
    errno = 0;
    munit_assert_int(cast_real(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_real(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_real(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_LINT
    errno = 0;
    munit_assert_int(cast_lint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_lint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_lint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_DINT
    errno = 0;
    munit_assert_int(cast_dint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_dint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_dint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_INT
    errno = 0;
    munit_assert_int(cast_int(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_int(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_int(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_SINT
    errno = 0;
    munit_assert_int(cast_sint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_sint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_sint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_ULINT
    errno = 0;
    munit_assert_int(cast_ulint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_ulint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_ulint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_UDINT
    errno = 0;
    munit_assert_int(cast_udint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_udint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_udint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_UINT
    errno = 0;
    munit_assert_int(cast_uint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_uint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_uint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_USINT
    errno = 0;
    munit_assert_int(cast_usint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_usint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_usint(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_LWORD
    errno = 0;
    munit_assert_int(cast_lword(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_lword(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_lword(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_DWORD
    errno = 0;
    munit_assert_int(cast_dword(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_dword(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_dword(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_WORD
    errno = 0;
    munit_assert_int(cast_word(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_word(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_word(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_BYTE
    errno = 0;
    munit_assert_int(cast_byte(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_byte(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_byte(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_BOOL
    errno = 0;
    munit_assert_int(cast_bool(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_bool(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_bool(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_TIME
    errno = 0;
    munit_assert_int(cast_time(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_initialise(&sValue);
    errno = 0;
    value_assign(&sValue, TYPE_STRING);
    munit_assert_int(cast_bool(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    value_assign(&sValue, TYPE_WSTRING);
    munit_assert_int(cast_bool(&sValue), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    value_destroy(&sValue);

    //  TYPE_STRING
    //  TYPE_WSTRING
    errno = 0;
    munit_assert_int(cast_string(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_wstring(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);

    return MUNIT_OK;
}


MunitResult
test_cast_none(const MunitParameter Parameters[], void *Fixture) {
    VALUE sValue;

    //  TYPE_LREAL
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_LREAL);
    munit_assert_int(cast_lreal(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_REAL
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_REAL);
    munit_assert_int(cast_real(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_LINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_LINT);
    munit_assert_int(cast_lint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_DINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_DINT);
    munit_assert_int(cast_dint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_INT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_INT);
    munit_assert_int(cast_int(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_SINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_SINT);
    munit_assert_int(cast_sint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_ULINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_ULINT);
    munit_assert_int(cast_ulint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_UDINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_UDINT);
    munit_assert_int(cast_udint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_UINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_UINT);
    munit_assert_int(cast_uint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_USINT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_USINT);
    munit_assert_int(cast_usint(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_LWORD
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_LWORD);
    munit_assert_int(cast_lword(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_DWORD
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_DWORD);
    munit_assert_int(cast_dword(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_WORD
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_WORD);
    munit_assert_int(cast_word(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_BYTE
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_BYTE);
    munit_assert_int(cast_byte(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_BOOL
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_BOOL);
    munit_assert_int(cast_bool(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_TIME
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_TIME);
    munit_assert_int(cast_time(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_DATE
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_DATE);
    munit_assert_int(cast_date(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_DT
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_DT);
    munit_assert_int(cast_dt(&sValue), ==, 0);
    value_destroy(&sValue);

    //  TYPE_TOD
    value_initialise(&sValue);
    value_assign(&sValue, TYPE_TOD);
    munit_assert_int(cast_tod(&sValue), ==, 0);
    value_destroy(&sValue);

    return MUNIT_OK;
}

