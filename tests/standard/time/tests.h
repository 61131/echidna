#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>

#include <ll.h>
#include <value.h>


MunitResult test_time_add_dttime(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_add_time(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_add_todtime(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_concat_datetod(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_divtime(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_multime(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_sub_datedate(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_sub_dtdt(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_sub_dttime(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_sub_time(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_sub_todtime(const MunitParameter Parameters[], void *Fixture);

MunitResult test_time_sub_todtod(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
