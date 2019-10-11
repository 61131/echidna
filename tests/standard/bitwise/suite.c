#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_bitwise[] = {

    { "bitwise/and", test_bitwise_and, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "bitwise/or", test_bitwise_or, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "bitwise/xor", test_bitwise_xor, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

