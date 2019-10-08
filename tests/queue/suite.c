#include <munit/munit.h>

#include <tests.h>


MunitTest Suite_Queue[] = {
    { "initialise", test_queue_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "new", test_queue_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "operations", test_queue_operations, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "priority/equal", test_priority_equal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "priority/negative", test_priority_negative, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "priority/ordered", test_priority_ordered, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "size", test_queue_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

