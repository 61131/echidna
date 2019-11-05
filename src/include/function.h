#ifndef _FUNCTION_H
#define _FUNCTION_H


#include <stdint.h>
#include <stdlib.h>

#include <ll.h>
#include <macros.h>
#include <value.h>


#define function_register(...)  _function_register(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _ECHIDNA ECHIDNA;

typedef struct _FUNCTION_BLOCK_FIELD {

    const char * Name;

    VALUE_TYPE Type;

    size_t Offset;

    void * Meta;
}
FUNCTION_BLOCK_FIELD;

/*
    The more obscure data structure names of _FUNCTION and _FUNCTION_BLOCK are 
    employed due to the equivalent without the leading underscore clashing with
    token definitions within the IEC 61131-3 grammar.
*/

typedef struct __FUNCTION_BLOCK _FUNCTION_BLOCK;

struct __FUNCTION_BLOCK {

    const char * Name;

    size_t Size;

    size_t Count;

    FUNCTION_BLOCK_FIELD * Fields;

    void *(*Initialise)(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

    void (*Destroy)(ECHIDNA *Context, char *Instance, void *User);

    int (*Execute)(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);
};

typedef int (*_FUNCTION)(ECHIDNA *Context, const char *Name, LL *pParameters, VALUE *Result, void *User);

typedef struct _FUNCTION_REGISTER {

    uint32_t Id;

    const char * Name;

    VALUE_TYPE Type;

    _FUNCTION_BLOCK * Block;

    _FUNCTION Function;

    void * Context;

    int Size;
}
FUNCTION_REGISTER;

typedef struct _FUNCTIONS {

    FUNCTION_REGISTER ** Function;

    size_t Count;

    char Signature[65];     //  ((SHA256_LENGTH << 1) + 1)

    uint8_t Lock;
}
FUNCTIONS;


int _function_register(size_t Arg, FUNCTIONS *Context, const char *Name, VALUE_TYPE Type, ...);

void function_destroy(void *Arg);

void function_initialise(FUNCTIONS *Context);

FUNCTION_REGISTER * function_search(FUNCTIONS *Context, const char *Name);

void function_table_build(FUNCTIONS *Context);


#endif  /* _FUNCTION_H */
