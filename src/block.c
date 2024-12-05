#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#else
#include "deps.h"
#endif
#include <errno.h>
#include <assert.h>

#include <log.h>
#include <block.h>


size_t
_block_end(size_t Arg, BLOCK *Block, ...) {
    va_list sArg;

    if(Arg > 1) {
        va_start(sArg, Block);
        Block->End = (size_t) va_arg(sArg, int);

        /*
            The following allows the specification of the block end to additionally perform 
            a re-size of the block buffer where i) there is no buffer allocated or associated 
            with the block, or ii) a dynamically allocated buffer, managed by this function 
            code, is associated with the block.
        */

        if((Block->Size == 0) &&
                (Block->Data == NULL) &&
                (Block->End > Block->Size))
            block_size(Block, Block->End);
        if((Block->Size != 0) &&
                (Block->End > Block->Size))
            block_size(Block, Block->End);

        va_end(sArg);
    }
    return Block->End;
}


void
_block_initialise(size_t Arg, BLOCK *Block, ...) {
    va_list sArg;

    if(Block == NULL)
        return;
    Block->Data = Block->Name = NULL;
    Block->End = Block->Size = 0;
    Block->Alloc = 0;
    if(Arg > 1) {
        va_start(sArg, Block);
        Block->Name = va_arg(sArg, char *);
        va_end(sArg);
    }
}


char *
_block_name(size_t Arg, BLOCK *Block, ...) {
    va_list sArg;

    assert(Block != NULL);
    if(Arg > 1) {
        va_start(sArg, Block);
        Block->Name = va_arg(sArg, char *);
        va_end(sArg);
    }
    return Block->Name;
}


char *
_block_pointer(size_t Arg, BLOCK *Block, ...) {
    va_list sArg;

    assert(Block != NULL);
    if(Arg > 1) {
        va_start(sArg, Block);
        Block->Data = va_arg(sArg, char *);
        va_end(sArg);
    }
    return Block->Data;
}


ssize_t
_block_size(size_t Arg, BLOCK *Block, ...) {
    va_list sArg;
    size_t uAlloc, uSize;

    assert(Block != NULL);
    if(Arg > 1) {
        va_start(sArg, Block);
        uSize = (size_t) va_arg(sArg, int);
        va_end(sArg);

        if(uSize > Block->Size) {
            char* Data;
            uAlloc = (((uSize / BLOCK_BLK_SIZE) * BLOCK_BLK_SIZE) +
                    (((uSize % BLOCK_BLK_SIZE) > 0) ? BLOCK_BLK_SIZE : 0));

            errno = 0;
            Data = realloc(Block->Data, uAlloc);
            if(Data == NULL) {
                log_critical("Failed to allocate memory: %s", strerror(errno));
                return -1;
            }
            Block->Data = Data;
            memset(&Block->Data[Block->Size], 0, uAlloc - Block->Size);
            uSize = uAlloc;
        }
        Block->Size = uSize;
    }
    return (ssize_t) Block->Size;
}


int
block_append(BLOCK *Block, size_t Count, char *Data) {
    return block_write(Block, Block->End, Count, Data);
}


int
block_compare(void *A, void *B) {
    BLOCK *pBlockA, *pBlockB;

    pBlockA = (BLOCK *) A;
    assert(pBlockA != NULL);
    pBlockB = (BLOCK *) B;
    assert(pBlockB != NULL);
    return strcasecmp(pBlockA->Name, pBlockB->Name);
}


void 
block_destroy(void *Arg) {
    BLOCK *pBlock;

    if((pBlock = (BLOCK *) Arg) == NULL)
        return;

    //  The following test is important to ensure that this code only frees that which 
    //  it has allocated.

    if((pBlock->Size > 0) &&
            (pBlock->Data != NULL)) 
        free(pBlock->Data);
    pBlock->End = pBlock->Size = 0;
    if(pBlock->Alloc) 
        free(pBlock);
}


void
block_dump(BLOCK *Block) {
    size_t nBlock, nIndex, nOffset;

    assert(Block != NULL);
    if(Block->Name != NULL)
        printf("; %s (%p)\n", Block->Name, Block);

    nOffset = 0;
    while(nOffset < Block->End) {
        printf("%08x  ", (unsigned int) nOffset);
        for(nBlock = 0; nBlock < 2; ++nBlock) {
            for(nIndex = 0; nIndex < 8; ++nIndex) {
                if((nOffset + nIndex) < Block->End)
                    printf("%02x ", (unsigned int) (Block->Data[nOffset + nIndex] & 0xff));
                else
                    printf("   ");
            }
            nOffset += nIndex;
            printf(" ");
        }
        printf("\n");
    }
    (void) fflush(stdout);
}


BLOCK *
block_new(void) {
    BLOCK *pBlock;

    errno = 0;
    if((pBlock = calloc(1, sizeof(BLOCK))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    block_initialise(pBlock);
    pBlock->Alloc = 1;
    return pBlock;
}


int
block_read(BLOCK *Block, size_t Index, size_t Count, char *Data) {
    assert(Block != NULL);
    if(Index > Block->End) {
        errno = ERANGE;
        return -1;
    }
    if((Index + Count) > Block->End)
        Count = Block->End - Index;
    if(Count > 0)
        memcpy(Data, &Block->Data[Index], Count);

    return (int) Count;
}


int
block_write(BLOCK *Block, size_t Index, size_t Count, char *Data) {
    size_t uSize;

    assert(Block != NULL);
    if((Index + Count) > Block->Size) {
        char* Data;
        uSize = (((Index + Count) / BLOCK_BLK_SIZE) * BLOCK_BLK_SIZE) +
                ((((Index + Count) % BLOCK_BLK_SIZE) > 0) ? 
                        BLOCK_BLK_SIZE :
                        0);
        errno = 0;
        Data = (char*)realloc(Block->Data, uSize);
        if(Data == NULL) {
            log_critical("Failed to allocate memory: %s", strerror(errno));
            return -1;
        }
        Block->Data = Data;
        Block->Size = uSize;
    }
    if(Data)
        memcpy(&Block->Data[Index], Data, Count);
    if((Index + Count) > Block->End)
        Block->End = Index + Count;

    return (int) Count;
}



