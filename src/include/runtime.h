#ifndef _RUNTIME_H
#define _RUNTIME_H


#include <stdint.h>
#include <stdarg.h>
#include <ev.h>

#include <block.h>
#include <config.h>
#include <frame.h>
#include <ll.h>
#include <macros.h>
#include <parameter.h>
#include <queue.h>
#include <stats.h>
#include <symbol.h>
#include <value.h>

#include <runtime/bytecode.h>
#include <runtime/call.h>
#include <runtime/context.h>
#include <runtime/error.h>
#include <runtime/function.h>
#include <runtime/parameter.h>
#include <runtime/task.h>


#define RUNTIME_STACK_MAX       (32)

#define runtime_destroy(...)    _runtime_destroy( _NARG( __VA_ARGS__ ), __VA_ARGS__ )


typedef struct _CONFIG CONFIG;

typedef struct _ECHIDNA ECHIDNA;

typedef struct _SYMBOL SYMBOL;

typedef struct _RUNTIME {

    ECHIDNA * Parent;

    struct ev_loop * Loop;

    struct ev_signal Signal;

    char * Memory;

    LL Context;

    QUEUE Queue;

    uint8_t Alloc;

    uint8_t Exit;
}
RUNTIME;

typedef enum _RUNTIME_STATE {

    STATE_NONE = 0,
    STATE_STOP,
    STATE_IDLE,
    STATE_RUN,
    STATE_STEP,
    STATE_ERROR
}
RUNTIME_STATE;

typedef struct _RUNTIME_PARAMETER {

    VALUE_TYPE Type;

    VALUE Value;

    uint32_t Id;                        //  Symbol identifier
    
    uint32_t Internal;                  //  Reserved identifier

    /*
        Note that the Parameter portion is the only part of this data structure which 
        is passed through to C functions which implement function operations.
    */

    PARAMETER Parameter;
}
RUNTIME_PARAMETER;

/*
    This data structure is employed for each instance of a CAL operator within 
    each program organisation unit (POU). These instances are initialised on the 
    first cycle of execution of each operator. One possible future optimisation
    may be to execute a futile (or quiescent) cycle of run-time operations to 
    initialise these instances before starting proper run-time execution.
*/

typedef struct _RUNTIME_FUNCTION {

    VALUE_TYPE Type;

    void * POU;                         //  POU containing CAL operator

    uint32_t PC;                        //  PC location of CAL operator

    uint32_t End;                       //  PC location of next bytecode

    int32_t Id;                         //  Function identifier

    LL Parameters;                      //  Function parameters, linked-list

    /*
        The following member is a linked-list of pointers to the Parameter member of 
        the function parameters stored in the Parameters member above. It is this list
        which is then passed to C functions to implement function behaviour.
    */

    LL List;
}
RUNTIME_FUNCTION;

typedef struct _RUNTIME_FUNCTIONS {

    RUNTIME_FUNCTION ** Function;

    size_t Count;
}
RUNTIME_FUNCTIONS;

typedef struct _RUNTIME_CONTEXT {

    struct ev_timer Timer;

    struct ev_loop * Loop;

    char * Name;

    RUNTIME * Parent;

    RUNTIME_STATE State;
    
    int Priority;

    SYMBOL * Interval;

    SYMBOL * Single;

    SYMBOL * Limit;             //  Cycle count limit for debugging/unit tests

    double Time;                //  Repeat time for struct ev_timer to simplify retriggering

    uint8_t Edge;               //  Edge state for single input

    struct {

        FRAME Frame[RUNTIME_STACK_MAX];

        size_t Depth;
    }
    Stack;

    RUNTIME_FUNCTIONS Functions;

    LL POU;

    /*
        The Next iterator is intended to be used for iteration through multiple 
        program organisation units that may be associated with this runtime context. 
        While this iteration could be performing using the in-built iterator within 
        the POU (LL) data structure, the Next member below is included such that 
        this functionality is explicitly understood to be a function of the 
        RUNTIME_CONTEXT data structure.
    */

    LL_ITER Next;

    STATS Stats;

    uint8_t Alloc;
}
RUNTIME_CONTEXT;


void _runtime_destroy(size_t Arg, ...);

int runtime_execute(RUNTIME *Run);

int runtime_initialise(RUNTIME *Run);

RUNTIME * runtime_new(ECHIDNA *Context);

int runtime_read(RUNTIME_CONTEXT *Context, size_t Count, char *Buffer);

int runtime_start(RUNTIME *Run, CONFIG *Config);

void runtime_stop(RUNTIME *Run);


#endif  /* _RUNTIME_H */

