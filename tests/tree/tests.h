#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_tree_initialise(const MunitParameter Parameters[], void *Fixture);

MunitResult test_tree_iterate(const MunitParameter Parameters[], void *Fixture);

MunitResult test_tree_new(const MunitParameter Parameters[], void *Fixture);

MunitResult test_tree_operations(const MunitParameter Parameters[], void *Fixture);

MunitResult test_tree_remove(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
