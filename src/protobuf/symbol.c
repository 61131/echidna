#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <protobuf.h>
#include <symbol.h>


PROTOBUF_SYMBOL *
protobuf_symbol_create(SYMBOL *Symbol) {
    PROTOBUF_SYMBOL *pSymbol;

    if((pSymbol = calloc(1, sizeof(PROTOBUF_SYMBOL))) == NULL)
        return NULL;
    protobuf_symbol_initialise(pSymbol);
    pSymbol->Id = Symbol->Id;
    pSymbol->Offset = Symbol->Offset;

    if(Symbol->Name)
        pSymbol->Name = strdup(Symbol->Name);
    if(Symbol->POU)
        pSymbol->POU = strdup(Symbol->POU);
    if(Symbol->Resource)
        pSymbol->Resource = strdup(Symbol->Resource);
    if(Symbol->Configuration)
        pSymbol->Configuration = strdup(Symbol->Configuration);
    pSymbol->Value = protobuf_value_create(&Symbol->Value);

    return pSymbol;
}


void
protobuf_symbol_free(PROTOBUF_SYMBOL *Symbol, ProtobufCAllocator *Alloc) {
    if(!Symbol)
        return;
    assert(Symbol->Base.descriptor == &PROTOBUF_SYMBOL_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Symbol, Alloc);
}


void
protobuf_symbol_initialise(PROTOBUF_SYMBOL *Symbol) {
    static const PROTOBUF_SYMBOL sSymbol = PROTOBUF_SYMBOL_INITIALISE;
    *Symbol = sSymbol;
}


size_t
protobuf_symbol_pack(PROTOBUF_SYMBOL *Symbol, uint8_t *Data) {
    assert(Symbol != NULL);
    assert(Symbol->Base.descriptor == &PROTOBUF_SYMBOL_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Symbol, Data);
}


size_t
protobuf_symbol_size(PROTOBUF_SYMBOL *Symbol) {
    assert(Symbol != NULL);
    assert(Symbol->Base.descriptor == &PROTOBUF_SYMBOL_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Symbol);
}


PROTOBUF_SYMBOL *
protobuf_symbol_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_SYMBOL *) protobuf_c_message_unpack(&PROTOBUF_SYMBOL_DESCRIPTOR, Alloc, Length, Data);
}


static const ProtobufCFieldDescriptor _protobuf_symbol_field_descriptors[] = {
    {
        "Id",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_SYMBOL, Id),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Offset",
        2,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_SYMBOL, Offset),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Value",
        3,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_MESSAGE,
        0,
        offsetof(PROTOBUF_SYMBOL, Value),
        &PROTOBUF_VALUE_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Name",
        4,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_SYMBOL, Name),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "POU",
        5,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_SYMBOL, POU),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Resource",
        6,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_SYMBOL, Resource),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Configuration",
        7,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_SYMBOL, Configuration),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_symbol_field_indices[] = { 6, 0, 3, 1, 4, 5, 2 };

static const ProtobufCIntRange _protobuf_symbol_ranges[2] = {
    { 1, 0 },
    { 0, 7 },
};

const ProtobufCMessageDescriptor PROTOBUF_SYMBOL_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Symbol",
    "Symbol",
    "Symbol",
    "",
    sizeof(PROTOBUF_SYMBOL),
    7,
    _protobuf_symbol_field_descriptors,
    _protobuf_symbol_field_indices,
    1,  
    _protobuf_symbol_ranges,
    (ProtobufCMessageInit) protobuf_symbol_initialise,
    NULL,
    NULL,
    NULL
};

