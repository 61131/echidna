#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <suite.h>


MunitResult
test_grammar_comments(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);
    munit_assert_int(test_parse(pContext, "(* (* Nested comment *) *)"), !=, 0);
    munit_assert_int(test_parse(pContext, "(* Simple comment *)"), ==, 0);

    return MUNIT_OK;
}
