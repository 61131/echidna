#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <strl.h>


MunitResult
test_strl_basic(const MunitParameter Parameters[], void *Fixture) {
    char sBuffer[5];

    munit_assert_size(strlcpy(sBuffer, "ab", sizeof(sBuffer)), ==, 2);
    munit_assert_size(strlcat(sBuffer, "cd", sizeof(sBuffer)), ==, 4);
    munit_assert_string_equal(sBuffer, "abcd");

    munit_assert_size(strlcpy(sBuffer, "abcd", sizeof(sBuffer)), ==, 4);
    munit_assert_size(strlcat(sBuffer, "efgh", sizeof(sBuffer)), ==, 8);
    munit_assert_string_equal(sBuffer, "abcd");

    //  This is an odd scenario where the destination buffer is already full, _without_ 
    //  a trailing '\0' character.
    munit_assert_size(strlcpy(sBuffer, "abcd", sizeof(sBuffer)), ==, 4);
    munit_assert_size(strlcat(sBuffer, "efgh", 4), ==, 8);

    munit_assert_size(strlcpy(NULL, "abc", sizeof(sBuffer)), ==, 0);
    munit_assert_size(strlcat(NULL, "abc", sizeof(sBuffer)), ==, 0);
    munit_assert_size(strlcpy(sBuffer, NULL, sizeof(sBuffer)), ==, 0);
    munit_assert_size(strlcat(sBuffer, NULL, sizeof(sBuffer)), ==, 0);

    return MUNIT_OK;
}
