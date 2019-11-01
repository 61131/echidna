#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_rtc[] = {

    { "rtc", test_rtc, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

