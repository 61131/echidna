#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>

#include <ll.h>
#include <value.h>


MunitResult test_type_bcd(const MunitParameter Parameters[], void *Fixture);

MunitResult test_type_conversion(const MunitParameter Parameters[], void *Fixture);

MunitResult test_type_trunc(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
