#include <munit/munit.h>

#include <tests.h>


MunitTest suite_cast[] = {
    { "error", test_cast_error, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "none", test_cast_none, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

