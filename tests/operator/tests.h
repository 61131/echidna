#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_operator_add(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_and(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_boolean(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_div(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_eq(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_ge(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_gt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_le(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_lt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_mod(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_mul(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_ne(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_not(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_or(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_sub(const MunitParameter Parameters[], void *Fixture);

MunitResult test_operator_xor(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
