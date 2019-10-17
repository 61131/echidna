#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <runtime.h>

#include <standard/string.h>


MunitResult 
test_string_concat(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_concat(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_delete(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_delete(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_find(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_find(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_insert(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_insert(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_left(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_left(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_len(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_len(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_mid(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_mid(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_replace(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_replace(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}


MunitResult 
test_string_right(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_int(standard_right(NULL, NULL, NULL, NULL, NULL), ==, ERROR_UNIMPLEMENTED);
    return MUNIT_OK;
}



