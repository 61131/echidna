#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_numeric[] = {

    { "numeric/abs", test_numeric_abs, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/acos", test_numeric_acos, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/asin", test_numeric_asin, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/atan", test_numeric_atan, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/cos", test_numeric_cos, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/exp", test_numeric_exp, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/ln", test_numeric_ln, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/log", test_numeric_log, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/sin", test_numeric_sin, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/sqrt", test_numeric_sqrt, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "numeric/tan", test_numeric_tan, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

