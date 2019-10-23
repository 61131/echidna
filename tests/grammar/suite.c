#include <munit/munit.h>

#include <tests.h>

#include <suite.h>


MunitTest suite_grammar[] = {
    { "comments", test_grammar_comments, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/boolean", test_grammar_literals_boolean, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/integer", test_grammar_literals_integer, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/real", test_grammar_literals_real, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/time", test_grammar_literals_time, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "literals/type", test_grammar_literals_type, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

