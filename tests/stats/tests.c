#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <stats.h>


MunitResult
test_stats_initialise(const MunitParameter Parameters[], void *Fixture) {
    STATS sStats;

    stats_initialise(&sStats);
    munit_assert_uint64(sStats.Cycle, ==, 0);
    munit_assert_uint64(sStats.Overrun, ==, 0);
    munit_assert_double(sStats.Execution, ==, 0.0);
    munit_assert_double(sStats.ExecutionStart, ==, 0.0);
    munit_assert_double(sStats.Latency, ==, 0.0);
    munit_assert_double(sStats.LatencyEnd, ==, 0.0);
    munit_assert_double(sStats.LatencyStart, ==, 0.0);
    munit_assert_double(sStats.Maximum, ==, 0.0);
    munit_assert_double(sStats.Start, >=, 0.0);

    return MUNIT_OK;
}
