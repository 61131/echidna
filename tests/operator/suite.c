#include <munit/munit.h>

#include <tests.h>
#include <suite.h>


MunitTest suite_operator[] = {

    { "arithmetic/add", test_operator_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/div", test_operator_div, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/mod", test_operator_mod, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/mul", test_operator_mul, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "arithmetic/sub", test_operator_sub, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "boolean", test_operator_boolean, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/eq", test_operator_eq, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/ge", test_operator_ge, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/gt", test_operator_gt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/le", test_operator_le, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/lt", test_operator_lt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/ne", test_operator_ne, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "logical/and", test_operator_and, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "logical/not", test_operator_not, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "logical/or", test_operator_or, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "logical/xor", test_operator_xor, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

