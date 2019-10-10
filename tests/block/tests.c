#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include <munit/munit.h>

#include <block.h>


MunitResult
test_block_append(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;
    char sData[] = "0123456789ABCDEF";
    int nIndex, nResult, nSize;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    munit_assert_size(block_end(&sBlock), ==, 0);
    munit_assert_size(block_size(&sBlock), ==, 0);

    nSize = strlen(sData);
    for(nIndex = 0; nIndex < 3; ++nIndex) {
        nResult = block_append(&sBlock, nSize, sData);
        munit_assert_int(nResult, ==, nSize);
    }
    nSize *= nIndex;
    munit_assert_size(block_end(&sBlock), ==, (size_t) nSize);
    munit_assert_size(block_size(&sBlock), >=, (size_t) nSize);
    block_destroy(&sBlock);

    return MUNIT_OK;
}


MunitResult
test_block_dump(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;
    int nDup, nFd;

    block_initialise(&sBlock);
    munit_assert_size(block_end(&sBlock, 257), ==, 257);
    munit_assert_int(nFd = fileno(stdout), !=, -1);
    munit_assert_int(nDup = dup(nFd), !=, -1);
    close(nFd);
    block_dump(&sBlock);
    munit_assert_not_null(block_name(&sBlock, "Test name"));
    block_dump(&sBlock);
    munit_assert_int(dup2(nDup, nFd), !=, -1);
    close(nDup);

    return MUNIT_OK;
}


MunitResult
test_block_end(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;
    size_t uSize;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    munit_assert_size(sBlock.End, ==, 0);
    munit_assert_size(sBlock.Size, ==, 0);
    munit_assert_size(block_end(&sBlock, 512), ==, 512);
    munit_assert_size(block_end(&sBlock), ==, 512);
    munit_assert_size(sBlock.End, ==, 512);
    munit_assert_size(block_size(&sBlock), >=, 512);
    //  Test automatic block re-size
    uSize = block_size(&sBlock) + 1;
    munit_assert_size(block_end(&sBlock, uSize), ==, uSize);
    block_destroy(&sBlock);

    return MUNIT_OK;
}


MunitResult
test_block_initialise(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    munit_assert_null(sBlock.Data);
    munit_assert_null(sBlock.Name);
    munit_assert_size(sBlock.End, ==, 0);
    munit_assert_size(sBlock.Size, ==, 0);
    munit_assert_int(sBlock.Alloc, ==, 0);
    block_destroy(&sBlock);

    block_initialise(NULL);
    block_destroy(NULL);

    return MUNIT_OK;
}


MunitResult
test_block_name(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock, "Test Block");
    munit_assert_not_null(sBlock.Name);
    munit_assert_not_null(block_name(&sBlock));
    munit_assert_ptr(sBlock.Name, ==, block_name(&sBlock));
    munit_assert_string_equal(block_name(&sBlock), "Test Block");

    munit_assert_not_null(block_name(&sBlock, "Block Name"));
    munit_assert_string_equal(block_name(&sBlock), "Block Name");
    
    block_destroy(&sBlock);

    return MUNIT_OK;
}


MunitResult
test_block_new(const MunitParameter Parameters[], void *Fixture) {
    BLOCK *pBlock;

    munit_assert_not_null(pBlock = block_new());
    munit_assert_null(pBlock->Data);
    munit_assert_null(pBlock->Name);
    munit_assert_size(pBlock->End, ==, 0);
    munit_assert_size(pBlock->Size, ==, 0);
    munit_assert_int(pBlock->Alloc, !=, 0);
    block_destroy(pBlock);

    return MUNIT_OK;
}


MunitResult
test_block_pointer(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;
    char sData[] = "0123456789ABCDEF";

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    munit_assert_ptr(sBlock.Data, ==, block_pointer(&sBlock));
    munit_assert_not_null(block_pointer(&sBlock, sData));
    munit_assert_ptr(block_pointer(&sBlock), ==, sData);
    block_destroy(&sBlock);

    return MUNIT_OK;
}


MunitResult
test_block_read(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;
    char sData[] = "0123456789ABCDEF";
    char sOutput[16];
    int nIndex, nResult;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    block_pointer(&sBlock, sData);
    munit_assert_ptr(block_pointer(&sBlock), ==, sData);
    block_end(&sBlock, strlen(sData));
    nResult = block_read(&sBlock, 12, 16, sOutput);
    munit_assert_int(nResult, ==, 4);

    errno = 0;
    nResult = block_read(&sBlock, 32, 1, sOutput);
    munit_assert_int(nResult, ==, -1);
    munit_assert_int(errno, ==, ERANGE);

    for(nIndex = 0; nIndex < nResult; ++nIndex) 
        munit_assert_char(sOutput[nIndex], ==, ('C' + nIndex));

    block_destroy(&sBlock);

    return MUNIT_OK;
}


MunitResult
test_block_size(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    munit_assert_size(sBlock.End, ==, 0);
    munit_assert_size(sBlock.Size, ==, 0);
    munit_assert_size(block_size(&sBlock, 2049), >=, 2049);
    munit_assert_size(block_size(&sBlock), >=, 2049);
    munit_assert_size(sBlock.Size, >=, 2049);
    munit_assert_size(block_end(&sBlock), ==, 0);
    munit_assert_size(block_size(&sBlock, 512), >=, 512);
    block_destroy(&sBlock);

    return MUNIT_OK;
}


MunitResult
test_block_write(const MunitParameter Parameters[], void *Fixture) {
    BLOCK sBlock;
    char sInput[] = "0123456789ABCDEF";
    char sOutput[8];
    char nValue;
    int nIndex, nResult, nSize;

    memset(&sBlock, 0, sizeof(sBlock));
    block_initialise(&sBlock);
    munit_assert_size(block_end(&sBlock), ==, 0);
    munit_assert_size(block_size(&sBlock), ==, 0);

    nSize = strlen(sInput);
    nResult = block_write(&sBlock, 8, nSize, sInput);
    munit_assert_int(nResult, ==, nSize);
    munit_assert_size(block_end(&sBlock), ==, (8 + nSize));
    nResult = block_read(&sBlock, 4, 8, sOutput);
    munit_assert_int(nResult, ==, 8);

    //  sOutput = "\0\0\0\00123"

    nValue = 0;
    for(nIndex = 0; nIndex < 8; ++nIndex) {
        if(nIndex >= 4)
            nValue = ('0' + nIndex - 4); 
        munit_assert_char(sOutput[nIndex], ==, nValue);
    }

    block_destroy(&sBlock);

    return MUNIT_OK;
}
