#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_select_limit(const MunitParameter Parameters[], void *Fixture);

MunitResult test_select_max(const MunitParameter Parameters[], void *Fixture);

MunitResult test_select_min(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
