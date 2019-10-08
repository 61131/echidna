#include <stdio.h>

#include <suite.h>


static MunitSuite sSuites[] = {
    { "block/", Suite_Block, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "ll/", Suite_List, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "queue/", Suite_Queue, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "sha256/", Suite_Digest, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "stats/", Suite_stats, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "strl/", Suite_Strl, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "unit/", suite_unit, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "value/", Suite_Value, NULL, 1, MUNIT_SUITE_OPTION_NONE },

    { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE }
};

static const MunitSuite sSuite = { "", NULL, sSuites, 1, MUNIT_SUITE_OPTION_NONE };


int
main(int Count, char **Arg) {
    return munit_suite_main(&sSuite, NULL, Count, Arg);
}
