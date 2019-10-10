#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_arithmetic[] = {
    { "arithmetic/add", test_arithmetic_add, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/div", test_arithmetic_div, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/expt", test_arithmetic_expt, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/mod", test_arithmetic_mod, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/mul", test_arithmetic_mul, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/sub", test_arithmetic_sub, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

