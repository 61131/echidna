#ifndef _HARDWARE_PIFACE_H
#define _HARDWARE_PIFACE_H


#include <ll.h>
#include <value.h>


typedef enum _PIFACE_REG {

    REG_IODIRA = 0,
    REG_IODIRB,
    REG_IPOLA,
    REG_IPOLB,
    REG_GPINTENA,
    REG_GPINTENB,
    REG_DEFVALA,
    REG_DEFVALB,
    REG_INTCONA,
    REG_INTCONB,
    REG_IOCON1,
    REG_IOCON2,
    REG_GPPUA,
    REG_GPPUB,
    REG_INTFA,
    REG_INTFB,
    REG_INTCAPA,
    REG_INTCAPB,
    REG_GPIOA,
    REG_GPIOB,
    REG_OLATA,
    REG_OLATB,

    REG_IOCON = REG_IOCON1,
    REG_OUTPUT = REG_GPIOA,
    REG_INPUT = REG_GPIOB,
}
PIFACE_REG;

typedef struct _PIFACE {

    int Fd;

    int Address;

    int Bits;

    int Speed;
}
PIFACE;


typedef struct _ECHIDNA ECHIDNA;


int piface_initialise(ECHIDNA *Context);

int piface_read(ECHIDNA *Context, const char *Name, LL *pParameters, VALUE *Result, void *User);

int piface_write(ECHIDNA *Context, const char *Name, LL *pParameters, VALUE *Result, void *User);


#endif  //  _HARDWARE_PIFACE_H
