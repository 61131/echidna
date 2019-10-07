#ifndef _RUNTIME_PARAMETER_H
#define _RUNTIME_PARAMETER_H


typedef struct _RUNTIME_PARAMETER RUNTIME_PARAMETER;


void runtime_parameter_destroy(void *Arg);

RUNTIME_PARAMETER * runtime_parameter_new(void);


#endif  //  _RUNTIME_PARAMETER_H
