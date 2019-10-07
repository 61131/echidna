#ifndef _RUNTIME_CALL_H
#define _RUNTIME_CALL_H


#include <runtime.h>


typedef struct _RUNTIME_CONTEXT RUNTIME_CONTEXT;

typedef struct _RUNTIME_FUNCTION RUNTIME_FUNCTION;


RUNTIME_FUNCTION * runtime_call_instance(RUNTIME_CONTEXT *Context);


#endif  //  _RUNTIME_CALL_H
