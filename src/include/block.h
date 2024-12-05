#ifndef _BLOCK_H
#define _BLOCK_H


#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include <macros.h>

#ifdef _MSC_VER
#define ssize_t ptrdiff_t
#endif

#define BLOCK_BLK_SIZE          (1024)

#define block_end(...)          _block_end(_NARG(__VA_ARGS__), __VA_ARGS__)

#define block_initialise(...)   _block_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define block_name(...)         _block_name(_NARG(__VA_ARGS__), __VA_ARGS__)

#define block_pointer(...)      _block_pointer(_NARG(__VA_ARGS__), __VA_ARGS__)

#define block_size(...)         _block_size(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef struct _BLOCK {

    char * Name;

    char * Data;

    size_t End;

    size_t Size;

    uint8_t Alloc;
}
BLOCK;


size_t _block_end(size_t Arg, BLOCK *Block, ...);

void _block_initialise(size_t Arg, BLOCK *Block, ...);

char * _block_name(size_t Arg, BLOCK *Block, ...);

char * _block_pointer(size_t Arg, BLOCK *Block, ...);

ssize_t _block_size(size_t Arg, BLOCK *Block, ...);

int block_append(BLOCK *Block, size_t Count, char *Data);

int block_compare(void *A, void *B);

void block_destroy(void *Arg);

void block_dump(BLOCK *Block);

BLOCK * block_new(void);

int block_read(BLOCK *Block, size_t Index, size_t Count, char *Data);

int block_write(BLOCK *Block, size_t Index, size_t Count, char *Data);


#endif  /* _BLOCK_H */

