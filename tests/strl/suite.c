#include <munit/munit.h>

#include <tests.h>


MunitTest Suite_Strl[] = {
    { "basic", test_strl_basic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

