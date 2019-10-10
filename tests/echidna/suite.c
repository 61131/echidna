#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_echidna[] = {
    { "initialise", test_echidna_initialise, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

