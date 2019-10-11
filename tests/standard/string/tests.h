#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_string_concat(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_delete(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_find(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_insert(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_left(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_len(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_mid(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_replace(const MunitParameter Parameters[], void *Fixture);

MunitResult test_string_right(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
