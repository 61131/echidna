#ifndef _UNIT_H
#define _UNIT_H


#include <stdint.h>
#include <stdarg.h>

#include <block.h>
#include <ll.h>
#include <macros.h>


#define unit_initialise(...)    _unit_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)


/*
    The following data structure has been created to represent and contain parameters 
    and attributes associated with program organisation units (POUs). The block data
    structure was employed previously, but as the complexity of POU implementation 
    increased, the requirements of representation surpassed that which could be 
    readily accommodated by this generic data structure.
*/

typedef struct _UNIT {

    BLOCK Block;

    char * Config;

    char * Resource;

    char * POU;

    LL Symbols;

    size_t Size;

    uint8_t Alloc;
}
UNIT;


void _unit_initialise(size_t Arg, UNIT *POU, ...);

int unit_compare(void *A, void *B);

UNIT * unit_create(char *Config, char *Resource, char *Name);

void unit_destroy(void *Arg);

UNIT * unit_new(void);


#endif  //  _UNIT_H
