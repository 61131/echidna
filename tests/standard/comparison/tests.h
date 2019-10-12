#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_comparison_eq(const MunitParameter Parameters[], void *Fixture);

MunitResult test_comparison_ge(const MunitParameter Parameters[], void *Fixture);

MunitResult test_comparison_gt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_comparison_le(const MunitParameter Parameters[], void *Fixture);

MunitResult test_comparison_lt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_comparison_ne(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
