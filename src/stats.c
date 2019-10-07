#include <ev.h>

#include <stats.h>


void
stats_initialise(STATS *Stats) {
    Stats->Cycle = Stats->Overrun = 0;
    Stats->Latency = Stats->Execution = 0.0;
    Stats->LatencyStart = 0.0;
    Stats->LatencyEnd = 0.0;
    Stats->Maximum = 0.0;
    Stats->ExecutionStart = 0.0;
    /* Stats->ExecutionEnd = 0.0; */
    Stats->Start = ev_time();
}
