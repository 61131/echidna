#include <munit/munit.h>

#include <tests.h>


MunitTest suite_block[] = {

    { "append", test_block_append, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "dump", test_block_dump, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "end", test_block_end, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "initialise", test_block_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "name", test_block_name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "new", test_block_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "pointer", test_block_pointer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "read", test_block_read, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "size", test_block_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "write", test_block_write, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

