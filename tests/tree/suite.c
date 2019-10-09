#include <munit/munit.h>

#include <tests.h>


MunitTest suite_tree[] = {
    { "initialise", test_tree_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "new", test_tree_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

