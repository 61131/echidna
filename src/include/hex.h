#ifndef _HEX_H
#define _HEX_H


#include <stdio.h>
#include <stdint.h>

#include <block.h>
#include <ll.h>


typedef struct {

    uint32_t Start;

    uint32_t Address;

    BLOCK Data;
}
HEX_BLOCK;

typedef struct {

    LL Blocks;

    FILE * File;

    uint8_t Alloc;
}
HEX;


void hex_close(HEX *Hex);

void hex_destroy(HEX *Hex);

int hex_get(HEX *Hex, uint32_t Address, size_t Length, void *Data);

void hex_initialise(HEX *Hex);

HEX * hex_new(void);

int hex_pointer(HEX *Hex, uint32_t Address, char **Pointer);

int hex_read(HEX *Hex, char *Path);

int hex_set(HEX *Hex, uint32_t Start, uint32_t Address, size_t Length, void *Data);

int hex_write(HEX *Hex, char *Path);


#endif
