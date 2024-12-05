#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#include <libgen.h>
#else
#include "deps.h"
#endif
#include <limits.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <hex.h>
#include <log.h>


#define HEX2(x)                 ((_hex_byte((x)[0]) << 4) + _hex_byte((x)[1]))

#define HEX4(x)                 ((HEX2(x) << 8) + HEX2((x) + 2 ))


enum {
    _HEX_DATA = 0,
    _HEX_EOFR = 1,
    _HEX_ESAR = 2,
    _HEX_SSAR = 3,
    _HEX_ELAR = 4,
    _HEX_SLAR = 5,
};

static int _hex_byte(char Byte);

static void _hex_destroy(void *Data);

/* static */ int _hex_read(HEX *Hex);

/* static */ int _hex_write(HEX *Hex);


static int 
_hex_byte(char Byte) {
    char nLower;

    switch((nLower = tolower(Byte))) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return (nLower - '0');
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return (nLower - 'a' + 10);
    }
    return -1;
}


static void
_hex_destroy(void *Data) {
    HEX_BLOCK *pBlock;

    if(!(pBlock = (HEX_BLOCK *) Data))
        return;
    block_destroy(&pBlock->Data);
    free(pBlock);
}


int 
_hex_read(HEX *Hex) {
    char *pBuffer, sBuffer[8];
    uint32_t uExtended, uSegment, uStart;
    uint16_t uOffset;
    uint8_t uChecksum, uLength, uType;
    int nBuffer, nByte, nCount, nIndex, nResult;

    pBuffer = NULL;
    nBuffer = 0;
    uStart = uExtended = uSegment = 0;

    if(fseek(Hex->File, 0, SEEK_SET) < 0) 
        return -errno;

    nResult = -EINVAL;
    while((nByte = fgetc(Hex->File)) != EOF) {
        if((nByte == '\r') ||
                (nByte == '\n')) 
            continue;
        if(nByte != ':') 
            goto finish;

        if(fread(sBuffer, 1, sizeof(sBuffer), Hex->File) != sizeof(sBuffer)) 
            goto finish;
        for(nIndex = 0; nIndex < sizeof(sBuffer); ++nIndex) {
            if(_hex_byte(sBuffer[nIndex]) < 0) 
                goto finish;
        }

        uLength = HEX2(sBuffer + 0);
        uOffset = HEX4(sBuffer + 2);
        uType = HEX2(sBuffer + 6);

        if((nCount = (uLength << 1) + 2) > nBuffer) {
            char* pTemp;
            pTemp = realloc(pBuffer, nCount);
            if(pTemp == NULL)
                goto finish;
            pBuffer = pTemp;
            nBuffer = nCount;
        }
        if(fread(pBuffer, 1, nCount, Hex->File) != nCount) 
            goto finish;
        for(nIndex = 0; nIndex < nCount; ++nIndex) {
            if(_hex_byte(pBuffer[nIndex]) < 0) 
                goto finish;
        }

        uChecksum = uLength + ((uOffset >> 8) & 0xff) + (uOffset & 0xff) + uType;
        for(nIndex = 0; nIndex < (uLength + 1); ++nIndex) 
            uChecksum += HEX2(pBuffer + (nIndex << 1));

        if(uChecksum != 0) 
            goto finish;

        switch(uType) {
            case _HEX_DATA: /* Data record */
                for(nIndex = 0; nIndex < uLength; ++nIndex)
                    pBuffer[nIndex] = HEX2(pBuffer + (nIndex << 1));

                if( ( nResult = hex_set(Hex, 
                        uStart,
                        uSegment + uExtended + uOffset, 
                        uLength, 
                        pBuffer)) != uLength)
                    goto finish;

                break;

            case _HEX_EOFR: /* End record */
                nResult = 0;
                goto finish;

            case _HEX_ESAR: /* Extended address record */
                if(uLength != 2) {
                    nResult = -EINVAL;
                    goto finish;
                }
                uSegment = HEX4(pBuffer) << 4;
                break;

            case _HEX_SSAR: /* Extended start address record */
                if(uLength != 4) {
                    nResult = -EINVAL;
                    goto finish;
                }
                uStart += (HEX4(pBuffer) << 16) + HEX4(pBuffer + 4);
                break;

            case _HEX_ELAR: /* Extended linear address record */
                if(uLength != 2) {
                    nResult = -EINVAL;
                    goto finish;
                }
                uExtended = HEX4(pBuffer) << 16;
                break;

            case _HEX_SLAR: /* Extended linear start address record */
                if((uLength != 2) &&
                        (uLength != 4)) {
                    nResult = -EINVAL;
                    goto finish;
                }
                if(uLength == 2)
                    uStart += (HEX4(pBuffer) << 16);
                else
                    uStart = (HEX4(pBuffer) << 16) + HEX4(pBuffer + 4);
                break;

            default:
                nResult = -EINVAL;
                goto finish;
        }
    }

    nResult = 0;

finish:
    if(pBuffer)
        free(pBuffer);
    return nResult;
}


int
_hex_write(HEX *Hex) {
    HEX_BLOCK *pBlock;
    char sBuffer[LINE_MAX];
    uint32_t uIndex, uLength;
    uint8_t uByte, uChecksum;

    ll_reset(&Hex->Blocks);
    while((pBlock = ll_iterate(&Hex->Blocks)) != NULL) {
        for(uIndex = 0; uIndex < pBlock->Data.End;) {
            uLength = ((pBlock->Data.End - uIndex) > 16 ) ? 16 : (pBlock->Data.End - uIndex);

            snprintf(sBuffer, sizeof(sBuffer), ":%02x%02x%02x%02x",
                    uLength,
                    ((uIndex >> 8) & 0xff),
                    (uIndex & 0xff),
                    _HEX_DATA);

            if(fwrite(sBuffer, 1, strlen(sBuffer), Hex->File) != strlen(sBuffer)) 
                return -errno;

            uChecksum = uLength + ((uIndex >> 8 ) & 0xff) + (uIndex & 0xff) + _HEX_DATA;
            for(; uLength > 0; --uLength) {
                uByte = (pBlock->Data.Data[uIndex] & 0xff);
                snprintf(sBuffer, sizeof(sBuffer), "%02x", uByte);
                if(fwrite(sBuffer, 1, 2, Hex->File) != 2)
                    return -errno;
                uChecksum += uByte;
                ++uIndex;
            }

            uChecksum = 0x100 - (uChecksum & 0xff);
            snprintf(sBuffer, sizeof(sBuffer), "%02x\n", uChecksum);
            if(fwrite(sBuffer, 1, strlen(sBuffer), Hex->File) != strlen(sBuffer))
                return -errno;
        }
    }

    snprintf(sBuffer, sizeof(sBuffer), ":000000%02x%02x\n", _HEX_EOFR, 0x100 - _HEX_EOFR);
    if(fwrite(sBuffer, 1, strlen(sBuffer), Hex->File) != strlen(sBuffer))
        return -errno;

    return 0;
}


void 
hex_destroy(HEX *Hex) {
    ll_destroy(&Hex->Blocks, _hex_destroy);
    if(Hex->File)
        fclose(Hex->File);
    if(Hex->Alloc)
        free(Hex);
}


int 
hex_get(HEX *Hex, uint32_t Address, size_t Length, void *Data) {
    HEX_BLOCK *pBlock;
    uint32_t uIndex;

    if(!Data)
        return -EINVAL;

    ll_reset(&Hex->Blocks);
    while((pBlock = ll_iterate(&Hex->Blocks)) != NULL) {
        if(((pBlock->Start + pBlock->Address) <= Address) &&
                (Address < (pBlock->Start + pBlock->Address + pBlock->Data.End)))
            break;
    }
    if(!pBlock)
        return -ENOENT;

    uIndex = Address - (pBlock->Start + pBlock->Address);
    return block_read(&pBlock->Data, uIndex, Length, Data);
}


void 
hex_initialise(HEX *Hex) {
    ll_initialise(&Hex->Blocks);
    Hex->File = NULL;
    Hex->Alloc = 0;
}


HEX *
hex_new( void ) {
    HEX *pHex;

    if((pHex = (HEX *) calloc(1, sizeof(HEX))) == NULL)
        return NULL;
    hex_initialise(pHex);
    pHex->Alloc = 1;

    return pHex;
}


int 
hex_pointer(HEX *Hex, uint32_t Address, char **Pointer) {
    HEX_BLOCK *pBlock;
    LL_ITER sIt;
    uint32_t uAddress, uIndex;

    assert(Hex != NULL);

    *Pointer = NULL;
    for(pBlock = ll_iterate_first(&sIt, &Hex->Blocks);
            pBlock;
            pBlock = ll_iterate_next(&sIt)) {
        uAddress = pBlock->Start + pBlock->Address;
        if((uAddress <= Address) &&
                (Address < (uAddress + pBlock->Data.End)))
            break;
    }
    if(!pBlock)
        return 0;

    uIndex = Address - uAddress;
    *Pointer = &pBlock->Data.Data[Address - uAddress];
    return (pBlock->Start + pBlock->Data.End - uIndex);
}


int 
hex_read(HEX *Hex, char *Path) {
    int nResult;

    if((Hex->File = fopen(Path, "r")) == NULL) {
        log_error("%s: %s", basename(Path), strerror(errno));
        return -errno;
    }
    nResult = _hex_read(Hex);
    fclose(Hex->File);
    Hex->File = NULL;

    return nResult;
}


int 
hex_set(HEX *Hex, uint32_t Start, uint32_t Address, size_t Length, void *Data) {
    HEX_BLOCK *pBlock;
    int nResult;

    ll_reset(&Hex->Blocks);
    while((pBlock = ll_iterate(&Hex->Blocks)) != NULL) {
        if(((pBlock->Start + pBlock->Address) <= (Start + Address)) &&
                ((Start + Address) <= (pBlock->Start + pBlock->Address + pBlock->Data.End)))
            break;
    }
    if(!pBlock) {
        if((pBlock = (HEX_BLOCK *) calloc(1, sizeof(HEX_BLOCK))) == NULL)
            return -errno;
        block_initialise(&pBlock->Data);
        pBlock->Start = Start;
        pBlock->Address = Address;

        if((nResult = ll_insert(&Hex->Blocks, pBlock)) != 0) {
            free(pBlock);
            return nResult;
        }
    }
   
    return block_write(&pBlock->Data, Address - pBlock->Address, Length, Data);
}


int
hex_write(HEX *Hex, char *Path) {
    int nResult;

    if((Hex->File = fopen(Path, "w+")) == NULL) {
        log_error("%s: %s", basename(Path), strerror(errno));
        return -errno;
    }
    nResult = _hex_write(Hex);
    fclose(Hex->File);
    Hex->File = NULL;

    return nResult;
}

