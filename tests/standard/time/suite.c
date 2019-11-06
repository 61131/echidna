#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_time[] = {
    { "time/add_dttime", test_time_add_dttime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/add_time", test_time_add_time, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/add_todtime", test_time_add_todtime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/divtime", test_time_divtime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/multime", test_time_multime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/sub_datedate", test_time_sub_datedate, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/sub_dtdt", test_time_sub_dtdt, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/sub_dttime", test_time_sub_dttime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/sub_time", test_time_sub_time, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/sub_todtime", test_time_sub_todtime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "time/sub_todtod", test_time_sub_todtod, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

