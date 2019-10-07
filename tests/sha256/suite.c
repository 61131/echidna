#include <munit/munit.h>

#include <tests.h>


MunitTest Suite_Digest[] = {
    { "generate", test_sha256_generate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

