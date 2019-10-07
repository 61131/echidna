#ifndef _BYTECODE_STACK_H
#define _BYTECODE_STACK_H


#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include <bytecode.h>
#include <macros.h>
#include <token.h>
#include <value.h>


#define bytecode_stack_initialise(...) _bytecode_stack_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _BYTECODE_STACK {

    TOKEN_LIST * List;

    uint32_t BC;

    VALUE_TYPE Type;

    VALUE CR;

    int Position;

    int Id;

    uint32_t Line;

    uint32_t Column;
}
BYTECODE_STACK;


void _bytecode_stack_initialise(size_t Arg, BYTECODE_STACK *Stack, TOKEN_LIST *List, ...);

int bytecode_stack_cast(BYTECODE_STACK *Stack, TOKEN *Token);

void bytecode_stack_set(BYTECODE_STACK *Stack, TOKEN *Token);

void bytecode_stack_type(BYTECODE_STACK *Stack, TOKEN *Token);


#endif  //  _BYTECODE_STACK_H
