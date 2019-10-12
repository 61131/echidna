#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_comparison[] = {

    { "comparison/eq", test_comparison_eq, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/ge", test_comparison_ge, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/gt", test_comparison_gt, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/le", test_comparison_le, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/lt", test_comparison_lt, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/ne", test_comparison_ne, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

