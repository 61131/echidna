#include <munit/munit.h>

#include <tests.h>


MunitTest Suite_stats[] = {
    { "initialise", test_stats_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

