#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_operator_eq(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_ge(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_gt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_le(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_lt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_ne(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
