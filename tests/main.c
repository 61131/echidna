#include <stdio.h>

#include <echidna.h>
#include <log.h>

#include <suite.h>


extern int _parse_file(ECHIDNA *Context, FILE *File);


static MunitSuite sSuites[] = {

    { "block/", suite_block, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "callback/", suite_callback, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "cast/", suite_cast, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "echidna/", suite_echidna, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "grammar/", suite_grammar, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "ll/", suite_list, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "operator/", suite_operator, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "queue/", suite_queue, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "sha256/", suite_digest, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_arithmetic, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_bitstring, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_bitwise, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_comparison, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_counters, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_edge, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_numeric, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "standard/", suite_standard_select, NULL, 1, MUNIT_SUITE_OPTION_NONE },
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
test_parse(ECHIDNA *Context, char *Source) {
    FILE *pFile;
    int nLength, nResult;

    munit_assert_not_null(Context);
    munit_assert_not_null(Source);
    munit_assert_int((nLength = strlen(Source)), >, 0);
    munit_assert_not_null((pFile = fmemopen(Source, nLength, "r")));
    nResult = _parse_file(Context, pFile);
    fclose(pFile);
    return (nResult != 0) ? -1 : 0;
}


int
main(int Count, char **Arg) {
    log_level = LOG_CRIT;
    return munit_suite_main(&sSuite, NULL, Count, Arg);
}
