#ifndef _SYMBOL_H
#define _SYMBOL_H


#include <stdint.h>

#include <function.h>
#include <macros.h>
#include <parse.h>
#include <tree.h>
#include <value.h>


#define SYMBOL_NAME_MAX         (255)

/*
    The following define specifies the depth of the stack to be used when 
    attempting to resolve the size required within the symbol table for each 
    program organisation unit.
*/

#define SYMBOL_STACK_MAX        (16)

#define symbol_build_path(...)  _symbol_build_path(_NARG(__VA_ARGS__), __VA_ARGS__)

#define symbol_split_path(...)  _symbol_split_path(_NARG(__VA_ARGS__), __VA_ARGS__)

#define symbol_table_initialise(...)    _symbol_table_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define symbol_table_iterate(...)       _symbol_table_iterate(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _ECHIDNA ECHIDNA;

typedef struct _SYMBOL {
    
    char * Name;

    char * POU;

    char * Resource;

    char * Configuration;

    char * Path;

    int32_t Id;

    int32_t Offset;

    int32_t Ref;                //  TODO: Suppress inclusion in symbol table based on reference count

    VALUE Value;

    /*
        The following members of this data structure are employed in association with 
        instances of function blocks.
    */

    FUNCTION_REGISTER * Function;

    void * Context;
}
SYMBOL;

typedef struct _SYMBOLS {

    SYMBOL ** Symbol;

    size_t Count;

    size_t Index;

    size_t Size;
}
SYMBOLS;

typedef struct _SYMBOL_STACK {

    uint32_t Index;

    size_t Size;

    char * POU;

    SYMBOL * Symbol;
}
SYMBOL_STACK;


char * _symbol_build_path(size_t Arg, ...);

int _symbol_offset(size_t Arg, PARSE *Parse, ...);

int _symbol_split_path(size_t Arg, char *Path, ...);

int _symbol_table_initialise(size_t Arg, ECHIDNA *Context, ...);

SYMBOL * _symbol_table_iterate(size_t Arg, ECHIDNA *Context, ...);

void symbol_destroy(ECHIDNA *Context, SYMBOL *Symbol);

int symbol_insert(ECHIDNA *Context, char *Config, char *Resource, char *POU, char *Name, VALUE *Value);

SYMBOL * symbol_search(ECHIDNA *Context, char *Config, char *Resource, char *POU, char *Name);

int symbol_table_build(ECHIDNA *Context);

void symbol_table_destroy(ECHIDNA *Context);

void symbol_table_reset(ECHIDNA *Context);

unsigned int symbol_table_size(ECHIDNA *Context);


#endif  /* _SYMBOL_H */


