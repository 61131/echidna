#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_bitstring_rol(const MunitParameter Parameters[], void *Fixture);

MunitResult test_bitstring_ror(const MunitParameter Parameters[], void *Fixture);

MunitResult test_bitstring_shl(const MunitParameter Parameters[], void *Fixture);

MunitResult test_bitstring_shr(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
