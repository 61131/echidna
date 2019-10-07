#include <munit/munit.h>

#include <tests.h>


MunitTest Suite_List[] = {
    { "copy", test_ll_copy, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "delete", test_ll_delete, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "initialise", test_ll_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "insert_head", test_ll_insert_head, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "insert_tail", test_ll_insert_tail, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "iterate_first", test_ll_iterate_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "iterate_last", test_ll_iterate_last, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "merge", test_ll_merge, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "new", test_ll_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

