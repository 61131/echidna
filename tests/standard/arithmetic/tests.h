#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_arithmetic_add(const MunitParameter Parameters[], void *Fixture);

MunitResult test_arithmetic_div(const MunitParameter Parameters[], void *Fixture);

MunitResult test_arithmetic_expt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_arithmetic_mod(const MunitParameter Parameters[], void *Fixture);

MunitResult test_arithmetic_mul(const MunitParameter Parameters[], void *Fixture);

MunitResult test_arithmetic_sub(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
