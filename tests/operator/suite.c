#include <munit/munit.h>

#include <tests.h>


MunitTest suite_operator[] = {

    { "comparison/eq", test_operator_eq, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/ge", test_operator_ge, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/gt", test_operator_gt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/le", test_operator_le, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/lt", test_operator_lt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "comparison/ne", test_operator_ne, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

