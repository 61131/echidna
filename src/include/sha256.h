#ifndef _SHA256_H
#define _SHA256_H


#include <stdint.h>
#include <stdlib.h>


#define SHA256_BE32_GET(x) \
        ((((uint32_t)(x)[0]) << 24) | \
         (((uint32_t)(x)[1]) << 16) | \
         (((uint32_t)(x)[2]) << 8) | \
         ((uint32_t)(x)[3]))

#define SHA256_BE32_PUT(a, x) \
        do { \
            (a)[0] = (uint8_t)((((uint32_t)(x)) >> 24) & 0xff); \
            (a)[1] = (uint8_t)((((uint32_t)(x)) >> 16) & 0xff); \
            (a)[2] = (uint8_t)((((uint32_t)(x)) >> 8) & 0xff); \
            (a)[3] = (uint8_t)(((uint32_t)(x)) & 0xff); \
        } while(0)

#define SHA256_BE64_GET(x)

#define SHA256_BE64_PUT(a, x) \
        do { \
            (a)[0] = (uint8_t)(((uint64_t)(x)) >> 56); \
            (a)[1] = (uint8_t)(((uint64_t)(x)) >> 48); \
            (a)[2] = (uint8_t)(((uint64_t)(x)) >> 40); \
            (a)[3] = (uint8_t)(((uint64_t)(x)) >> 32); \
            (a)[4] = (uint8_t)(((uint64_t)(x)) >> 24); \
            (a)[5] = (uint8_t)(((uint64_t)(x)) >> 16); \
            (a)[6] = (uint8_t)(((uint64_t)(x)) >> 8); \
            (a)[7] = (uint8_t)(((uint64_t)(x)) & 0xff); \
        } while(0)


typedef struct _SHA256 {

    uint8_t Buffer[64];

    uint32_t Current;

    uint64_t Length;

    uint32_t State[8];
}
SHA256;


void sha256_final(SHA256 *Digest, char *Buffer);

void sha256_initialise(SHA256 *Digest);

void sha256_update(SHA256 *Digest, const char *Data, size_t Length);


#endif
