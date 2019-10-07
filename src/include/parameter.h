#ifndef _PARAMETER_H
#define _PARAMETER_H


#include <function.h>
#include <ll.h>
#include <macros.h>
#include <value.h>


#define parameter_read_values(...) _parameter_read_values(_NARG(__VA_ARGS__), __VA_ARGS__)

#define parameter_write_values(...) _parameter_write_values(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _ECHIDNA ECHIDNA;


/*
    The following data structure is employed for the passing of parameters to 
    functions and function blocks.
*/

typedef struct _PARAMETER {

    const char * Name;

    VALUE Value;
}
PARAMETER;


int _parameter_read_values(size_t Arg, ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, ...);

int _parameter_write_values(size_t Arg, ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, ...);

void parameter_destroy(void *Arg);

int parameter_read(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, const char *Name, VALUE *Value);

int parameter_write(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, const char *Name, VALUE *Value);

PARAMETER * parameter_new(PARAMETER *Parameter);


#endif  //  _PARAMETER_H
