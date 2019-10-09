#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_block_append(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_dump(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_end(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_initialise(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_name(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_new(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_pointer(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_read(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_size(const MunitParameter Parameters[], void *Fixture);

MunitResult test_block_write(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
