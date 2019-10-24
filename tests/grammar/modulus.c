#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#include <munit/munit.h>

#include <grammar.h>
#include <parse.h>
#include <token.h>

#include <suite.h>

//  xxd -i src/modulus.txt

static char _Source[] = {
    0x50, 0x52, 0x4f, 0x47, 0x52, 0x41, 0x4d, 0x20, 
    0x6d, 0x6f, 0x64, 0x75, 0x6c, 0x75, 0x73, 0x0a, 
    0x56, 0x41, 0x52, 0x20, 0x74, 0x65, 0x73, 0x74,
    0x3a, 0x20, 0x58, 0x58, 0x58, 0x58, 0x58, 0x20,     //  XXXXX
    0x3b, 0x20, 0x45, 0x4e, 0x44, 0x5f, 0x56, 0x41, 
    0x52, 0x0a, 0x0a, 0x4c, 0x44, 0x20, 0x74, 0x65,
    0x73, 0x74, 0x0a, 0x4d, 0x4f, 0x44, 0x20, 0x30, 
    0x0a, 0x53, 0x54, 0x20, 0x74, 0x65, 0x73, 0x74, 
    0x0a, 0x0a, 0x45, 0x4e, 0x44, 0x5f, 0x50, 0x52,
    0x4f, 0x47, 0x52, 0x41, 0x4d, 0x0a, 0x00
};


MunitResult
test_grammar_modulus(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;
    PARSE *pParse;
    int nIndex;

    char * sType[] = {
        "LINT ",
        "DINT ",
        "INT  ",
        "SINT ",
        "ULINT",
        "UDINT",
        "UINT ",
        "USINT",
        "LWORD",
        "DWORD",
        "WORD ",
        "BYTE ",
        NULL,
    };

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    for(nIndex = 0; sType[nIndex] != NULL; ++nIndex) {
        strncpy(&_Source[26], sType[nIndex], 5);    //  Overwrite variable type
        fprintf(stderr, "%s", _Source);
        munit_assert_int(test_parse(pContext, _Source), !=, 0);
        munit_assert_not_null(pParse = &pContext->Parse);
        parse_reset(pContext, pParse);
    }

    return MUNIT_OK;
}


