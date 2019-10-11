#include <munit/munit.h>

#include <suite.h>
#include <tests.h>


MunitTest suite_standard_bitstring[] = {

    { "bitstring/rol", test_bitstring_rol, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "bitstring/ror", test_bitstring_ror, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "bitstring/shl", test_bitstring_shl, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "bitstring/shr", test_bitstring_shr, suite_setup, suite_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

