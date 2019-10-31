#include <munit/munit.h>

#include <tests.h>
#include <suite.h>


MunitTest suite_grammar[] = {
    { "comments", test_grammar_comments, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "divide", test_grammar_divide, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "function", test_grammar_function, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/bitstring", test_grammar_literals_bitstring, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/boolean", test_grammar_literals_boolean, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/datetime", test_grammar_literals_datetime, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/integer", test_grammar_literals_integer, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/real", test_grammar_literals_real, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/time", test_grammar_literals_time, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "modulus", test_grammar_modulus, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "subrange", test_grammar_subrange, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

