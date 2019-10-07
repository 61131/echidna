#ifndef _BYTECODE_LABEL_H
#define _BYTECODE_LABEL_H


#include <stdint.h>


typedef struct _BYTECODE_LABEL {

    char * Name;

    uint32_t PC;

    uint32_t Count;

    uint32_t * Position;
}
BYTECODE_LABEL;


int bytecode_label_compare(void *A, void *B);

void bytecode_label_destroy(void *Arg);

void bytecode_label_initialise(BYTECODE_LABEL *Label, char *Name);

BYTECODE_LABEL * bytecode_label_new(char *Name);


#endif  //  _BYTECODE_LABEL_H
