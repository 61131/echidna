#include <stdio.h>

#include <echidna.h>
#include <log.h>

#include <suite.h>


static MunitSuite sSuites[] = {

    { "block/", suite_block, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "cast/", suite_cast, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "echidna/", suite_echidna, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "ll/", suite_list, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "queue/", suite_queue, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "sha256/", suite_digest, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_arithmetic, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_bitstring, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_bitwise, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_comparison, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_numeric, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_string, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "stats/", suite_stats, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "strl/", suite_strl, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "tree/", suite_tree, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "unit/", suite_unit, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "value/", suite_value, NULL, 1, MUNIT_SUITE_OPTION_NONE },

    { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE }
};

static const MunitSuite sSuite = { "", NULL, sSuites, 1, MUNIT_SUITE_OPTION_NONE };


void *
suite_setup(const MunitParameter Parameters[], void *Data) {
    ECHIDNA *pContext;

    pContext = calloc(1, sizeof(*pContext));
    munit_assert_not_null(pContext);
    munit_assert_int(echidna_initialise(pContext), ==, 0);
    return pContext;
}


void
suite_teardown(void *Data) {
    ECHIDNA *pContext;

    munit_assert_not_null(Data);
    pContext = (ECHIDNA *) Data;
    echidna_destroy(pContext);
    free(pContext);
}


int
main(int Count, char **Arg) {
    log_level = LOG_CRIT;
    return munit_suite_main(&sSuite, NULL, Count, Arg);
}
