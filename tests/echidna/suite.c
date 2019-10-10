#include <stdlib.h>
#include <munit/munit.h>

#include <echidna.h>

#include <tests.h>


static void *
suite_echidna_setup(const MunitParameter Parameters[], void *Data) {
    ECHIDNA *pContext;

    pContext = calloc(1, sizeof(*pContext));
    munit_assert_not_null(pContext);
    munit_assert_int(echidna_initialise(pContext), ==, 0);
    return pContext;
}


static void 
suite_echidna_teardown(void *Data) {
    ECHIDNA *pContext;

    munit_assert_not_null(Data);
    pContext = (ECHIDNA *) Data;
    echidna_destroy(pContext);
    free(pContext);
}



MunitTest suite_echidna[] = {
    { "initialise", test_echidna_initialise, suite_echidna_setup, suite_echidna_teardown, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

