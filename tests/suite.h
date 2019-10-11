#ifndef _SUITE_H
#define _SUITE_H


#include <munit/munit.h>


extern MunitTest suite_block[];
extern MunitTest suite_cast[];
extern MunitTest suite_digest[];
extern MunitTest suite_echidna[];
extern MunitTest suite_list[];
extern MunitTest suite_queue[];
extern MunitTest suite_standard_arithmetic[];
extern MunitTest suite_standard_bitstring[];
extern MunitTest suite_stats[];
extern MunitTest suite_strl[];
extern MunitTest suite_tree[];
extern MunitTest suite_value[];
extern MunitTest suite_unit[];


void * suite_setup(const MunitParameter Parameters[], void *Data);

void suite_teardown(void *Data);


#endif  //  _SUITE_H
