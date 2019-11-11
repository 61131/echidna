#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#include <munit/munit.h>

#include <grammar.h>
#include <parse.h>

#include <suite.h>


MunitResult
test_grammar_type(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    PARSE *pParse;
    int nResult;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);
    munit_assert_not_null(pParse = &pContext->Parse);

    nResult = test_parse(pContext, "TYPE TEST INT; END_TYPE");
    munit_assert_int(nResult, !=, 0);
    parse_reset(pContext, pParse);

    return MUNIT_OK;
}


