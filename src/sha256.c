#include <string.h>
#include <assert.h>

#include <sha256.h>


#define ROR(w, s)               \
    ((((unsigned long)(w) & 0xFFFFFFFFUL) >> (unsigned long)((s) & 31)) | \
    ((((unsigned long)(w)) << (unsigned long)(32 - ((s) & 31))) & 0xFFFFFFFFUL))

#define Ch(x, y, z)             ((z) ^ ((x) & ((y) ^ (z))))
#define Maj(x, y, z)            ((((x) | (y)) & (z)) | ((x) & (y)))
#define S(x, n)                 ROR(x, n)
#define R(x, n)                 (((x) & 0xFFFFFFFFUL) >> (n))
#define S0(x)                   (S((x), 2) ^ S((x), 13) ^ S((x), 22))
#define S1(x)                   (S((x), 6) ^ S((x), 11) ^ S((x), 25))
#define R0(x)                   (S((x), 7) ^ S((x), 18) ^ R((x), 3))
#define R1(x)                   (S((x), 17) ^ S((x), 19) ^ R((x), 10))

#define _MIN(x, y)              (((x) < (y)) ? (x) : (y))

#define _BLOCK_SIZE             (64)

/* Constants for SHA256 from FIPS 180-2:4.2.2.  */

static const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


static void _sha256_compress(SHA256 *Digest, uint8_t *Buffer);


static void 
_sha256_compress(SHA256 *Digest, uint8_t *Buffer) {
    uint32_t S[8], W[64], T, T0, T1;
    int nIndex;

    assert(Digest != NULL);
    assert(Buffer != NULL);

    for(nIndex = 0; nIndex < 8; ++nIndex) 
        S[nIndex] = Digest->State[nIndex];

    for(nIndex = 0; nIndex < 16; ++nIndex)
        W[nIndex] = SHA256_BE32_GET(Buffer + (nIndex * sizeof(uint32_t)));

    for(nIndex = 16; nIndex < 64; ++nIndex)
        W[nIndex] = R1(W[nIndex - 2]) + W[nIndex - 7] + R0(W[nIndex - 15]) + W[nIndex - 16];

    for(nIndex = 0; nIndex < 64; ++nIndex) {
        T0 = S[7] + S1(S[4]) + Ch(S[4], S[5], S[6]) + K[nIndex] + W[nIndex];
        T1 = S0(S[0]) + Maj(S[0], S[1], S[2]);
        S[3] += T0;
        S[7] = T0 + T1;

        T = S[7]; 
        S[7] = S[6]; 
        S[6] = S[5]; 
        S[5] = S[4]; 
        S[4] = S[3]; 
        S[3] = S[2]; 
        S[2] = S[1]; 
        S[1] = S[0]; 
        S[0] = T;
    }

    for(nIndex = 0; nIndex < 8; ++nIndex)
        Digest->State[nIndex] = Digest->State[nIndex] + S[nIndex];
}


void 
sha256_final(SHA256 *Digest, char *Buffer) {
    size_t uIndex;

    assert(Digest != NULL);
    assert(Digest->Current < sizeof(Digest->Buffer));
    assert(Buffer != NULL);

    Digest->Length += Digest->Current;
    Digest->Buffer[Digest->Current++] = (uint8_t) 0x80;

    if(Digest->Current > 56) {
        while(Digest->Current < _BLOCK_SIZE)
            Digest->Buffer[Digest->Current++] = (uint8_t) 0;
        _sha256_compress(Digest, Digest->Buffer);
        Digest->Current = 0;
    }

    while(Digest->Current < 56)
        Digest->Buffer[Digest->Current++] = (uint8_t) 0;

    Digest->Length <<= 3;   //  Bytes -> Bits
    SHA256_BE64_PUT(Digest->Buffer + 56, Digest->Length);
    _sha256_compress(Digest, Digest->Buffer);

    for(uIndex = 0; uIndex < 8; ++uIndex)
        SHA256_BE32_PUT(Buffer + (uIndex * sizeof(uint32_t)), Digest->State[uIndex]);
}


void 
sha256_initialise(SHA256 *Digest) {
    assert(Digest != NULL);
    Digest->State[0] = 0x6a09e667ul;
    Digest->State[1] = 0xbb67ae85ul;
    Digest->State[2] = 0x3c6ef372ul;
    Digest->State[3] = 0xa54ff53aul;
    Digest->State[4] = 0x510e527ful;
    Digest->State[5] = 0x9b05688cul;
    Digest->State[6] = 0x1f83d9abul;
    Digest->State[7] = 0x5be0cd19ul;
    Digest->Current = 0;
    Digest->Length = 0;
}


void
sha256_update(SHA256 *Digest, const char *Data, size_t Length) {
    size_t uCount;

    assert(Digest != NULL);
    assert(Digest->Current <= sizeof(Digest->Buffer));

    while(Length > 0) {
        if((Digest->Current == 0) &&
                (Length >= _BLOCK_SIZE)) {
            _sha256_compress(Digest, (uint8_t *) Data);
            Digest->Length += _BLOCK_SIZE;
            Data += _BLOCK_SIZE;
            Length -= _BLOCK_SIZE;
        }
        else {
            uCount = _MIN(Length, (_BLOCK_SIZE - Digest->Current));
            memcpy(Digest->Buffer + Digest->Current, Data, uCount);
            Digest->Current += uCount;
            Data += uCount;
            Length -= uCount;
            if(Digest->Current == _BLOCK_SIZE) {
                _sha256_compress(Digest, Digest->Buffer);
                Digest->Length += _BLOCK_SIZE;
                Digest->Current = 0;
            }
        }
    }
}


