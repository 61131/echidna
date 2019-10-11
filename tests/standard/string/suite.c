#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_string[] = {

    { "string/concat", test_string_concat, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/delete", test_string_delete, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/find", test_string_find, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/insert", test_string_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/left", test_string_left, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/len", test_string_len, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/mid", test_string_mid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/replace", test_string_replace, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "string/right", test_string_right, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

