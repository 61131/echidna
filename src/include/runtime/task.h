#ifndef _RUNTIME_TASK_H
#define _RUNTIME_TASK_H


#include <ev.h>


typedef struct _RUNTIME RUNTIME;

typedef struct _RUNTIME_CONTEXT RUNTIME_CONTEXT;


void runtime_task_callback(struct ev_loop *Loop, ev_timer *Timer, int Events);

int runtime_task_interval(RUNTIME *Run, RUNTIME_CONTEXT *Context);

void runtime_task_limit(RUNTIME *Run, RUNTIME_CONTEXT *Context);

int runtime_task_single(RUNTIME *Run, RUNTIME_CONTEXT *Context);

void runtime_task_stop(RUNTIME *Run, RUNTIME_CONTEXT *Context);


#endif  //  _RUNTIME_TASK_H
