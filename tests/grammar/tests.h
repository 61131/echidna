#ifndef _TESTS_H
#define _TESTS_H


#include <munit/munit.h>


MunitResult test_grammar_comments(const MunitParameter Parameters[], void *Fixture);

MunitResult test_grammar_literals_boolean(const MunitParameter Parameters[], void *Fixture);

MunitResult test_grammar_literals_integer(const MunitParameter Parameters[], void *Fixture);

MunitResult test_grammar_literals_real(const MunitParameter Parameters[], void *Fixture);

MunitResult test_grammar_literals_time(const MunitParameter Parameters[], void *Fixture);

MunitResult test_grammar_literals_type(const MunitParameter Parameters[], void *Fixture);


#endif  //  _TESTS_H
