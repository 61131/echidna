#ifndef _PARSE_H
#define _PARSE_H


#include <stdint.h>

#include <token.h>
#include <tree.h>
#include <value.h>


typedef struct _ECHIDNA ECHIDNA;

typedef struct _LEXER_TOKEN LEXER_TOKEN;

typedef struct _PARSE {

    TREE Identifiers;

    TOKEN_LIST Tokens;

    TOKEN_LIST Parse;

    char * File;

    TOKEN * Configuration;

    TOKEN * Resource;

    TOKEN * POU;

    uint8_t Preparse;

    uint8_t State;

    VALUE_TYPE Type;
}
PARSE;


void parse_destroy(PARSE *Parse);

int parse_file(ECHIDNA *Context, char *Path);

int parse_initialise(ECHIDNA *Context, PARSE *Parse);

void parse_reset(ECHIDNA *Context, PARSE *Parse);

int parse_register(PARSE *Parse, int Id, char *Name);

int parse_register_scope(PARSE *Parse, int Id, char *Name);

char * parse_scope(PARSE *Parse, char *Name);

LEXER_TOKEN * parse_search(PARSE *Parse, char *Name);


#endif  /* _PARSE_H */
