#ifndef _FRAME_H
#define _FRAME_H


#include <stdint.h>
#include <stdarg.h>

#include <block.h>
#include <ll.h>
#include <macros.h>
#include <unit.h>
#include <value.h>


#define FRAME_MAX               (32)

#define frame_initialise(...)   _frame_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define frame_push(...)         _frame_push(_NARG(__VA_ARGS__), __VA_ARGS__)


enum {

    FRAME_CD = 0,
    FRAME_CLK,
    FRAME_CU,
    FRAME_IN,
    FRAME_PT,
    FRAME_PV,
    FRAME_R,
    FRAME_R1,
    FRAME_S,
    FRAME_S1
};

typedef struct _RUNTIME_CONTEXT RUNTIME_CONTEXT;

typedef struct _RT_FUNCTION RT_FUNCTION;

typedef struct _FRAME {

    uint32_t PC;                //  Program counter (PC)

    uint32_t ER;                //  Error register (ER)

    uint32_t BC;                //  Current bytecode (BC)

    VALUE CR;                   //  Current register (CR)

    VALUE_TYPE Type;            //  Current type (Type)

    VALUE Inputs[10];           //  Input parameters specified in current frame

    UNIT * POU;                 //  Current program organisation unit (POU)

    struct _RT_FUNCTION * Function;

    uint32_t Parameter;         //  Parameter index

    LL Parameters;              //  Parameters to current POU

    BLOCK Data;
}
FRAME;


void _frame_initialise(size_t Arg, FRAME *Frame, ...);

int _frame_push(size_t Arg, RUNTIME_CONTEXT *Context, ...);

FRAME * frame_current(RUNTIME_CONTEXT *Context); 

void frame_next(RUNTIME_CONTEXT *Context);

int frame_pop(RUNTIME_CONTEXT *Context);

FRAME * frame_previous(RUNTIME_CONTEXT *Context); 

void frame_restore(RUNTIME_CONTEXT *Context);

void frame_store(RUNTIME_CONTEXT *Context);


#endif  //  _FRAME_H
