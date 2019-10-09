#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <munit/munit.h>

#include <cast.h>


MunitResult
test_cast_error(const MunitParameter Parameters[], void *Fixture) {

    errno = 0;
    munit_assert_int(cast_lreal(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_real(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_lint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_dint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_int(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_sint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_ulint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_udint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_uint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_usint(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_lword(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_dword(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_word(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_byte(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_bool(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);
    errno = 0;
    munit_assert_int(cast_time(NULL), ==, -1);
    munit_assert_int(errno, ==, EINVAL);

    return MUNIT_OK;
}
