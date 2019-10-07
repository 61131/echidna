#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <config.h>
#include <echidna.h>
#include <log.h>
#include <protobuf.h>


static int _protobuf_file_config(ECHIDNA *Context, PROTOBUF_FILE *File);

static int _protobuf_file_program(ECHIDNA *Context, PROTOBUF_FILE *File);

static int _protobuf_file_symbol(ECHIDNA *Context, PROTOBUF_FILE *File);


static int 
_protobuf_file_config(ECHIDNA *Context, PROTOBUF_FILE *File) {
    CONFIG *pConfig;
    LL_ITER sIt;
    size_t uIndex, uSize;
    int nResult;

    if((uSize = Context->Config.Size) == 0)
        return 0;
    if((File->Config = calloc(uSize, sizeof(PROTOBUF_CONFIG *))) == NULL)
        return errno;

    uIndex = 0;
    for(pConfig = ll_iterate_first(&sIt, &Context->Config);
            pConfig;
            pConfig = ll_iterate_next(&sIt)) {
        if((File->Config[uIndex++] = protobuf_config_create(pConfig)) == NULL) {
            nResult = errno;
            goto error;
        }
    }
    File->Configs = uSize;
    return 0;

error:
    log_error("Failed to allocate memory: %s", strerror(nResult));
    if(File->Config)
        free(File->Config);
    return nResult;
}


static int
_protobuf_file_program(ECHIDNA *Context, PROTOBUF_FILE *File) {
    FUNCTION_REGISTER *pFunction;
    PROTOBUF_POU *pProgram;
    TREE_ITER sIt;
    UNIT *pPOU;
    size_t uIndex, uSize;
    int nResult;

    if((uSize = Context->POU.Size) == 0)
        return 0;
    if((File->POU = calloc(uSize, sizeof(PROTOBUF_POU *))) == NULL)
        return errno;

    uIndex = 0;
    for(pPOU = tree_iterate_first(&sIt, &Context->POU);
            pPOU;
            pPOU = tree_iterate_next(&sIt)) {

        if((pProgram = protobuf_pou_create(pPOU)) == NULL) {
            nResult = errno;
            goto error;
        }
        if((pFunction = function_search(&Context->Functions, pPOU->POU)) != NULL)
            pProgram->Type = pFunction->Type;
        File->POU[uIndex++] = pProgram;
    }
    File->POUs = uSize;
    return 0;

error:
    log_error("Failed to allocate memory: %s", strerror(nResult));
    if(File->POU)
        free(File->POU);
    return nResult;
}


static int
_protobuf_file_symbol(ECHIDNA *Context, PROTOBUF_FILE *File) {
    SYMBOL *pSymbol;
    size_t uIndex, uSize;
    int nResult;

    if((uSize = Context->Symbols.Count) == 0)
        return 0;
    if((File->Symbol = calloc(uSize, sizeof(PROTOBUF_SYMBOL *))) == NULL)
        return errno;

    for(uIndex = 0; uIndex < uSize; ++uIndex) {
        pSymbol = Context->Symbols.Symbol[uIndex];
        if((File->Symbol[uIndex] = protobuf_symbol_create(pSymbol)) == NULL) {
            nResult = errno;
            goto error;
        }
    }

    File->Symbols = uSize;
    return 0;

error:
    log_error("Failed to allocate memory: %s", strerror(nResult));
    if(File->Symbol)
        free(File->Symbol);
    return nResult;
}


PROTOBUF_FILE *
protobuf_file_create(ECHIDNA *Context) {
    PROTOBUF_FILE *pFile;
    int nResult;

    if((pFile = calloc(1, sizeof(PROTOBUF_FILE))) == NULL)
        goto error;
    protobuf_file_initialise(pFile);
    if(((nResult = _protobuf_file_config(Context, pFile)) != 0) ||
            ((nResult = _protobuf_file_program(Context, pFile)) != 0) ||
            ((nResult = _protobuf_file_symbol(Context, pFile)) != 0))
        goto error;

    return pFile;

error:
    log_critical("Failed to allocate memory: %s", strerror(nResult));
    protobuf_file_free(pFile, NULL);
    return NULL;
}


void
protobuf_file_free(PROTOBUF_FILE *File, ProtobufCAllocator *Alloc) {
    if(!File)
        return;
    assert(File->Base.descriptor == &PROTOBUF_FILE_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) File, Alloc);
}


void 
protobuf_file_initialise(PROTOBUF_FILE *File) {
    static const PROTOBUF_FILE sFile = PROTOBUF_FILE_INITIALISE;
    *File = sFile;
}


size_t
protobuf_file_pack(PROTOBUF_FILE *File, uint8_t *Data) {
    assert(File != NULL);
    assert(File->Base.descriptor == &PROTOBUF_FILE_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) File, Data);
}


size_t 
protobuf_file_size(PROTOBUF_FILE *File) {
    assert(File != NULL);
    assert(File->Base.descriptor == &PROTOBUF_FILE_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) File);
}


PROTOBUF_FILE *
protobuf_file_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_FILE *) protobuf_c_message_unpack(&PROTOBUF_FILE_DESCRIPTOR, Alloc, Length, Data);
}


static const uint32_t _protobuf_magic_default = 61131u;

static const uint32_t _protobuf_format_default = 0u;

static const ProtobufCFieldDescriptor _protobuf_file_field_descriptors[5] = {
    {
        "Magic",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_FILE, Magic),
        NULL,
        &_protobuf_magic_default,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Format",
        2,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_FILE, Format),
        NULL,
        &_protobuf_format_default,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Symbols",
        3,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_FILE, Symbols),
        offsetof(PROTOBUF_FILE, Symbol),
        &PROTOBUF_SYMBOL_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "POUs",
        4,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_FILE, POUs),
        offsetof(PROTOBUF_FILE, POU),
        &PROTOBUF_POU_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL, 
        NULL
    },
    {
        "Configurations",
        5,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_FILE, Configs),
        offsetof(PROTOBUF_FILE, Config),
        &PROTOBUF_CONFIG_DESCRIPTOR,
        NULL, 
        0,
        0,
        NULL,
        NULL
    }
};

static const unsigned _protobuf_file_indices[] = { 4, 1, 0, 3, 2 };

static const ProtobufCIntRange _protobuf_file_ranges[2] = {
    { 1, 0 },
    { 0, 5 },
};

const ProtobufCMessageDescriptor PROTOBUF_FILE_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "File",
    "File",
    "File",
    "",
    sizeof(PROTOBUF_FILE),
    5,
    _protobuf_file_field_descriptors,
    _protobuf_file_indices,
    1,  
    _protobuf_file_ranges,
    (ProtobufCMessageInit) protobuf_file_initialise,
    NULL,
    NULL,
    NULL
};

