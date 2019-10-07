#ifndef _RUNTIME_CONTEXT_H
#define _RUNTIME_CONTEXT_H


typedef struct _RUNTIME RUNTIME;

typedef struct _RUNTIME_CONTEXT RUNTIME_CONTEXT;


void runtime_context_destroy(void *Arg);

void runtime_context_initialise(RUNTIME_CONTEXT *Context, RUNTIME *Run);

RUNTIME_CONTEXT * runtime_context_new(RUNTIME *Run);


#endif  //  _RUNTIME_CONTEXT_H
