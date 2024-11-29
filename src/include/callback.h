#ifndef _CALLBACK_H
#define _CALLBACK_H


#include <stdlib.h>

#include <macros.h>


#define callback_register(...)  _callback_register(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _ECHIDNA ECHIDNA;

typedef void (*CALLBACK_CALLBACK)(ECHIDNA *Context, void *Arg, void *User);


typedef enum _CALLBACK_TYPE {

    CALLBACK_NONE = 0,
    CALLBACK_CYCLE_START,
    CALLBACK_CYCLE_FINISH,
    CALLBACK_ERROR,
    CALLBACK_TASK_START,
    CALLBACK_TASK_STOP,
}
CALLBACK_TYPE;

int _callback_register(size_t Arg, ECHIDNA *Context, CALLBACK_TYPE Type, ...);

void callback_destroy(void *Arg);

int callback_execute(ECHIDNA *Context, CALLBACK_TYPE Type, void *Arg);


#endif  //  _CALLBACK_H
