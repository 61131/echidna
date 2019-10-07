#ifndef _LEXER_H
#define _LEXER_H


#include <stdint.h>

#include <grammar.h>


typedef struct _LEXER_TOKEN {

    const char * Text;

    int Id;
}
LEXER_TOKEN;


extern YYSTYPE yylval;

int yylex_destroy(void);


void lexer_destroy(LEXER_TOKEN *Token);

LEXER_TOKEN * lexer_new(int Id, const char *Str);

void lexer_start(void *Context);


#endif  /* _LEXER_H */


