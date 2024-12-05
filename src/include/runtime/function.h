#ifndef _RUNTIME_FUNCTION_H
#define _RUNTIME_FUNCTION_H


#include <stdint.h>

#include <function.h>
#include <ll.h>
#include <unit.h>
#include <value.h>


typedef struct _ECHIDNA ECHIDNA;

typedef struct _RT_FUNCTION RT_FUNCTION;


int runtime_function(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int runtime_function_block(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

void runtime_function_destroy(void *Arg);

RT_FUNCTION * runtime_function_new(VALUE_TYPE Type, UNIT *POU, uint32_t PC);


#endif  //  _RUNTIME_FUNCTION_H
