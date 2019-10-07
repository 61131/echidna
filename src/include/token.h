#ifndef _TOKEN_H
#define _TOKEN_H

/*
    This header file and corresponding source are intended to implement the 
    primary data structures and functions used when parsing source files. This 
    implementation greatly simplifies that implemented within the master branch
    by reducing the number of token types to merely two - TOKEN and LIST.
*/

#include <stdint.h>

#include <ll.h>
#include <macros.h>
#include <tree.h>
#include <value.h>


#define token_cast(...)         _token_cast(_NARG(__VA_ARGS__), __VA_ARGS__)

#define token_destroy(...)      _token_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)

#define token_list_cast(...)    _token_list_cast(_NARG(__VA_ARGS__), __VA_ARGS__)

#define token_list_insert(...)  _token_list_insert(_NARG(__VA_ARGS__), __VA_ARGS__)

#define token_list_merge(...)   _token_list_merge(_NARG(__VA_ARGS__), __VA_ARGS__)

#define token_list_new(...)     _token_list_new(_NARG(__VA_ARGS__), __VA_ARGS__)

#define token_new(...)          _token_new(_NARG(__VA_ARGS__), __VA_ARGS__)

#define TOKEN_NAME(x)           ((x) ? (((TOKEN *) (x))->Name) : NULL)


typedef enum _TOKEN_TYPE {
    TYPE_TOKEN,
    TYPE_LIST,
}
TOKEN_TYPE;

typedef struct _TOKEN {

    TOKEN_TYPE Type;

    uint8_t Alloc;

    uint32_t Id;

    uint32_t Line;

    uint32_t Column;

    char * Name;

    void * Scope;

    VALUE Value;
}
TOKEN;

typedef struct _TOKEN_LIST {

    TOKEN Token;

    LL List;
}
TOKEN_LIST;


TOKEN * _token_cast(size_t Arg, TOKEN *Token, uint32_t Id, ...);

void _token_destroy(size_t Arg, ...);

TOKEN_LIST * _token_list_cast(size_t Arg, TOKEN_LIST *List, uint32_t Id, ...);

void _token_list_destroy(size_t Arg, ...);

int _token_list_insert(size_t Arg, TOKEN_LIST *List, void *Item, ...);

void _token_list_merge(size_t Arg, TOKEN_LIST *List, ...);

TOKEN_LIST * _token_list_new(size_t Arg, ...);

TOKEN * _token_new(size_t Arg, ...);

void token_initialise(TOKEN *Token);

TOKEN_LIST * token_list_convert(TOKEN *Token);

void token_list_initialise(TOKEN_LIST *List);

TOKEN * token_list_iterate(TOKEN_LIST *List);

void token_list_reset(TOKEN_LIST *List);

int token_list_unique(TOKEN_LIST *List);



#endif  /* _TOKEN_H */



