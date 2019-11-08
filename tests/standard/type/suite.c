#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_type[] = {
    { "type/bcd", test_type_bcd, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "type/conversion", test_type_conversion, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "type/trunc", test_type_trunc, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

