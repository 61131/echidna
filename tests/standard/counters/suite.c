#include <munit/munit.h>

#include <tests.h>


MunitTest suite_standard_counters[] = {

    { "counters/ctd", test_counters_ctd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "counters/ctu", test_counters_ctu, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "counters/ctu_type", test_counters_ctutype, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

