#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_timers[] = {

    { "timers/tof", test_timers_tof, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "timers/ton", test_timers_ton, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "timers/tp", test_timers_tp, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

