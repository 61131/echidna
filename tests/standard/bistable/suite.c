#include <munit/munit.h>

#include <tests.h>
#include <suite.h>


MunitTest suite_standard_bistable[] = {

    { "bistable/rs", test_bistable_rs, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "bistable/sr", test_bistable_sr, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

