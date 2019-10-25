#ifndef _ECHIDNA_H
#define _ECHIDNA_H


#include <callback.h>
#include <function.h>
#include <ll.h>
#include <macros.h>
#include <parse.h>
#include <runtime.h>
#include <symbol.h>
#include <tree.h>


#define echidna_callback(...)   _echidna_callback(_NARG(__VA_ARGS__), __VA_ARGS__)

#define echidna_initialise(...) _echidna_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define echidna_register(...)   _echidna_register(_NARG(__VA_ARGS__), __VA_ARGS__)


enum {
    OPTION_NONE                 = (0<<0),
    OPTION_DAEMON               = (1<<1),
    OPTION_COMPILE              = (1<<2),
    OPTION_NOFILE               = (1<<3),
    OPTION_NOSIGNAL             = (1<<4),
    OPTION_RUN                  = (1<<5),
};

typedef struct _ECHIDNA {

    char * Name;

    char * Output;

    uint8_t Align;

    uint8_t Option;

    uint8_t Verbose;

    LL Callbacks;

    LL Config;

    TREE POU;

    FUNCTIONS Functions;

    SYMBOLS Symbols;

    PARSE Parse;

    RUNTIME * VM;

    /*
        The following member is employed to provide a monotonic time-stamp, relative 
        to the start of the virtual machine run-time, of the start of the current 
        cycle of execution. This is intended to be employed through the echidna_time 
        function where such time reference is required within C-based functions and 
        function blocks.
    */

    double Time;
}
ECHIDNA;


int _echidna_callback(size_t Arg, ECHIDNA *Context, CALLBACK_TYPE Type, ...);

int _echidna_initialise(size_t Arg, ECHIDNA *Context, ...);

int _echidna_register(size_t Arg, ECHIDNA *Context, const char *Name, VALUE_TYPE Type, ...);

int echidna_compile(ECHIDNA *Context);

void echidna_destroy(ECHIDNA *Context);

int echidna_open(ECHIDNA *Context, char *Path);

int echidna_run(ECHIDNA *Context);

double echidna_time(ECHIDNA *Context);


#endif  /* _ECHIDNA_H */

