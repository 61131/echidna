#include <munit/munit.h>

#include <tests.h>


MunitTest suite_unit[] = {

    { "create", test_unit_create, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "initialise", test_unit_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "new", test_unit_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

