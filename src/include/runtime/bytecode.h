#ifndef _RUNTIME_BYTECODE_H
#define _RUNTIME_BYTECODE_H


#include <frame.h>


typedef struct _RUNTIME_CONTEXT RUNTIME_CONTEXT;


int runtime_bytecode_execute(RUNTIME_CONTEXT *Context);

int runtime_bytecode_operand(FRAME *Frame);


#endif  //  _RUNTIME_BYTECODE_H
