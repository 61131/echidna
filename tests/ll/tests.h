#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_ll_copy(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_delete(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_initialise(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_insert_head(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_insert_tail(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_iterate_first(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_iterate_last(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_merge(const MunitParameter Parameters[], void *Fixture);

MunitResult test_ll_new(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
