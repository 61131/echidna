#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_value_assign(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_initialise(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_istype(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_strtotype(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_strtoval(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_type(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_typetostr(const MunitParameter Parameters[], void *Fixture);

MunitResult test_value_typetosize(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
