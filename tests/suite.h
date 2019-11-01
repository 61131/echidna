#ifndef _SUITE_H
#define _SUITE_H


#include <echidna.h>

#include <munit/munit.h>


extern MunitTest suite_block[];

extern MunitTest suite_callback[];

extern MunitTest suite_cast[];

extern MunitTest suite_digest[];

extern MunitTest suite_echidna[];

extern MunitTest suite_grammar[];

extern MunitTest suite_list[];

extern MunitTest suite_operator[];

extern MunitTest suite_queue[];

extern MunitTest suite_standard_arithmetic[];

extern MunitTest suite_standard_bistable[];

extern MunitTest suite_standard_bitstring[];

extern MunitTest suite_standard_bitwise[];

extern MunitTest suite_standard_comparison[];

extern MunitTest suite_standard_counters[];

extern MunitTest suite_standard_edge[];

extern MunitTest suite_standard_numeric[];

extern MunitTest suite_standard_rtc[];

extern MunitTest suite_standard_select[];

extern MunitTest suite_standard_string[];

extern MunitTest suite_stats[];

extern MunitTest suite_strl[];

extern MunitTest suite_tree[];

extern MunitTest suite_value[];

extern MunitTest suite_unit[];


void * suite_setup(const MunitParameter Parameters[], void *Data);

void suite_teardown(void *Data);

int test_parse(ECHIDNA *Context, char *Source);


#endif  //  _SUITE_H
