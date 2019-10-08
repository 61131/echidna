#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_unit_create(const MunitParameter Parameters[], void *Fixture);

MunitResult test_unit_initialise(const MunitParameter Parameters[], void *Fixture);

MunitResult test_unit_new(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
