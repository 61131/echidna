#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_queue_initialise(const MunitParameter Parameters[], void *Fixture);

MunitResult test_queue_new(const MunitParameter Parameters[], void *Fixture);

MunitResult test_queue_operations(const MunitParameter Parameters[], void *Fixture);

MunitResult test_queue_size(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
