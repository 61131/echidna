#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_select[] = {

    { "select/limit", test_select_limit, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "select/max", test_select_max, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "select/min", test_select_min, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "select/mux", test_select_mux, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "select/sel", test_select_select, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

