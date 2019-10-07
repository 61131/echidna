#ifndef _CONFIG_H
#define _CONFIG_H


#include <stdint.h>
#include <ev.h>

#include <macros.h>
#include <ll.h>
#include <symbol.h>


#define config_destroy(...)     _config_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)

#define config_initialise(...)  _config_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define config_new(...)         _config_new(_NARG(__VA_ARGS__), __VA_ARGS__)

#define config_program(...)     _config_program(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _ECHIDNA ECHIDNA;

typedef struct _PROTOBUF_FILE PROTOBUF_FILE;

typedef struct _RUNTIME_CONTEXT RUNTIME_CONTEXT;

typedef struct _SYMBOL SYMBOL;

typedef enum _CONFIG_TYPE {

    /* TYPE_NONE = 0, */
    TYPE_CONFIG = 1,
    TYPE_RESOURCE,
    TYPE_TASK,
    TYPE_PROGRAM,
}
CONFIG_TYPE;

typedef struct _CONFIG {

    CONFIG_TYPE Type;

    void * Parent;

    char * Name;

    char * Task;                //  Used by CONFIG_PROGRAM

    int Priority;               //  Used by CONFIG_TASK 

    SYMBOL * Interval;          //  Used by CONFIG_TASK 

    SYMBOL * Single;            //  Used by CONFIG_TASK 

    SYMBOL * Limit;             //  Used by CONFIG_TASK

    RUNTIME_CONTEXT * Context;

    LL List;

    uint8_t Alloc;
}
CONFIG;


void _config_destroy(size_t Arg, ...);

void _config_initialise(size_t Arg, CONFIG *Config, ...);

CONFIG * _config_new(size_t Arg, CONFIG_TYPE Type, ...);

int config_generate(ECHIDNA *Context);

int config_populate(ECHIDNA *Context, PROTOBUF_FILE *File);

const char * config_typetostr(CONFIG_TYPE Type);


#endif  /* _CONFIG_H */

