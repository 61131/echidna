#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>

#include <block.h>
#include <echidna.h>
#include <function.h>
#include <hex.h>
#include <log.h>
#include <protobuf.h>
#include <runtime.h>
#include <value.h>


static int _file_read_function(ECHIDNA *Context, PROTOBUF_POU *POU);

static int _file_read_program(ECHIDNA *Context, PROTOBUF_FILE *File);

static int _file_read_symbol(ECHIDNA *Context, PROTOBUF_FILE *File);


static int
_file_read_function(ECHIDNA *Context, PROTOBUF_POU *POU) {
    assert(POU->Type == TYPE_FUNCTION);
    return function_register(&Context->Functions, POU->Name, TYPE_FUNCTION, runtime_function);
}


static int
_file_read_program(ECHIDNA *Context, PROTOBUF_FILE *File) {
    BLOCK *pBlock;
    PROTOBUF_POU *pPOU;
    UNIT *pUnit;
    char *pPath[3];
    size_t uIndex;
    int nResult;

    for(uIndex = 0; uIndex < File->POUs; ++uIndex) {
        pPOU = File->POU[uIndex];
        pPath[0] = pPath[1] = pPath[2] = NULL;
        symbol_split_path(pPOU->Name, &pPath[0], &pPath[1], &pPath[2]);
        if((pUnit = unit_create(pPath[0], pPath[1], pPath[2])) == NULL)
            goto error;
        pBlock = &pUnit->Block;
        block_size(pBlock, pPOU->Code.len);
        memcpy(pBlock->Data, pPOU->Code.data, pPOU->Code.len);
        pBlock->End = pPOU->Code.len;

        switch(pPOU->Type) {
            case TYPE_FUNCTION:
                nResult = _file_read_function(Context, pPOU);
                break;

            case TYPE_FUNCTION_BLOCK:
            default:
                nResult = 0;
                break;
        }
        if(nResult != 0)
            goto error;
        if((nResult = tree_insert(&Context->POU, pUnit)) != 0)
            goto error;

        if(Context->Verbose > 0) {
            block_dump(pBlock);
            log_debug("%s: %u bytes", pBlock->Name, pBlock->End);
        }
    }
    return 0;

error:
    log_error("Failed to allocate memory: %s", strerror(errno));
    unit_destroy(pPOU);
    return errno;
}


static int
_file_read_symbol(ECHIDNA *Context, PROTOBUF_FILE *File) {
    PROTOBUF_SYMBOL *pSymbol;
    PROTOBUF_VALUE *pValue;
    VALUE sValue;
    char *pMeta;
    size_t uIndex;
    int nResult;

    assert(Context != NULL);
    assert(File != NULL);
    for(uIndex = 0; uIndex < File->Symbols; ++uIndex) {
        pSymbol = File->Symbol[uIndex];
        pValue = pSymbol->Value;
        value_assign(&sValue, pValue->Type & ~ANY_INTERNAL);
        sValue.Type = pValue->Type;
        sValue.Flags = pValue->Flags;
        sValue.Length = pValue->Length;
        assert(sValue.Length == pValue->Value.len);
        memcpy(&sValue.Value.Pointer, pValue->Value.data, pValue->Value.len);

        if(pValue->IncludeMaximum) {
            assert(pValue->Maximum.len == pValue->Length);
            memcpy(&sValue.Maximum.Pointer, pValue->Maximum.data, pValue->Maximum.len);
        }
        if(pValue->IncludeMinimum) {
            assert(pValue->Minimum.len == pValue->Length);
            memcpy(&sValue.Minimum.Pointer, pValue->Minimum.data, pValue->Minimum.len);
        }
        if(pValue->IncludeMeta) { 
            if((pMeta = calloc(pValue->Meta.len, sizeof(char))) == NULL) {
                nResult = errno;
                goto error;
            }
            memcpy(pMeta, pValue->Meta.data, pValue->Meta.len);
        }

        if((nResult = symbol_insert(Context, pSymbol->Configuration,
                pSymbol->Resource,
                pSymbol->POU,
                pSymbol->Name,
                &sValue)) != 0)
            goto error;
    }

    return 0;

error:
    value_destroy(&sValue);
    return nResult;
}


int
file_read(ECHIDNA *Context, char *Path) {
    HEX sInput;
    PROTOBUF_FILE *pFile;
    char *pData;
    size_t uSize;
    int nResult;

    hex_initialise(&sInput);
    if((nResult = hex_read(&sInput, Path)) != 0)
        return nResult;
    pData = NULL;
    if(((uSize = hex_pointer(&sInput, 0, &pData)) == 0) ||
            (pData == NULL))
        goto finish;
    pFile = protobuf_file_unpack(NULL, uSize, (uint8_t *) pData);
    assert(pFile != NULL);

    if(((nResult = _file_read_program(Context, pFile)) != 0) ||
            ((nResult = _file_read_symbol(Context, pFile)) != 0) ||
            ((nResult = config_populate(Context, pFile)) != 0)) 
        goto finish;

finish:
    if(nResult != 0) {
        log_error("Cannot load file: %s", basename(Path));
    }
    hex_destroy(&sInput);
    return nResult;
}


int
file_write(ECHIDNA *Context, char *Path) {
    BLOCK sBlock;
    HEX sOutput;
    PROTOBUF_FILE *pFile;
    struct stat sStat;
    size_t uSize;
    int nResult;

    block_initialise(&sBlock);
    if((pFile = protobuf_file_create(Context)) == NULL)
        return -errno;

    uSize = protobuf_file_size(pFile);
    block_size(&sBlock, uSize);
    protobuf_file_pack(pFile, (uint8_t *) block_pointer(&sBlock));

    for(nResult = 0;;) {
        hex_initialise(&sOutput);
        if(hex_set(&sOutput, 0, 0, uSize, block_pointer(&sBlock)) != uSize) {
            nResult = -EFAULT;
            break;
        }
        nResult = hex_write(&sOutput, Context->Output);
        break;
    }

    hex_destroy(&sOutput);
    protobuf_file_free(pFile, NULL);
    block_destroy(&sBlock);

    if(nResult == 0) {
        if(stat(Context->Output, &sStat) == 0)
            log_info("%s: %u bytes", basename(Context->Output), sStat.st_size);
    }
    return nResult;
}

