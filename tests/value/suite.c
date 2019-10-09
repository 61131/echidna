#include <munit/munit.h>

#include <tests.h>


MunitTest Suite_Value[] = {
    { "assign", test_value_assign, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "cast", test_value_cast, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "initialise", test_value_initialise, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "istype", test_value_istype, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "strtotype", test_value_strtotype, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "strtoval", test_value_strtoval, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "type", test_value_type, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "typetostr", test_value_typetostr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "typetosize", test_value_typetosize, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

