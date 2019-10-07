#ifndef _STATS_H
#define _STATS_H


#include <stdint.h>


typedef struct _STATS {

    uint64_t Cycle;

    uint64_t Overrun;

    double Start;

    double Latency;

    double Execution;

    double LatencyStart;

    double LatencyEnd;

    double Maximum;

    double ExecutionStart;

    /* double ExecutionEnd; */
}
STATS;


void stats_initialise(STATS *Stats);


#endif  /* _STATS_H */
