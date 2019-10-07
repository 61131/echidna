#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <block.h>
#include <protobuf.h>
#include <symbol.h>
#include <unit.h>


PROTOBUF_POU * 
protobuf_pou_create(UNIT *Unit) {
    BLOCK *pBlock;
    PROTOBUF_POU *pPOU;

    if((pPOU = calloc(1, sizeof(PROTOBUF_POU))) == NULL)
        return NULL;
    protobuf_pou_initialise(pPOU);
    assert(Unit->POU != NULL);
    if((pPOU->Name = symbol_build_path(Unit->Config, Unit->Resource, Unit->POU)) == NULL)
        goto error;

    pBlock = &Unit->Block;
    if((pPOU->Code.len = pBlock->End) > 0) {
        if((pPOU->Code.data = calloc(1, pPOU->Code.len)) == NULL)
            goto error;
        memcpy(pPOU->Code.data, pBlock->Data, pPOU->Code.len);
    }

    return pPOU;

error:
    protobuf_pou_free(pPOU, NULL);
    return NULL;
}


void
protobuf_pou_free(PROTOBUF_POU *Unit, ProtobufCAllocator *Alloc) {
    if(!Unit)
        return;
    assert(Unit->Base.descriptor == &PROTOBUF_POU_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Unit, Alloc);
}


void
protobuf_pou_initialise(PROTOBUF_POU *Unit) {
    static const PROTOBUF_POU sUnit = PROTOBUF_POU_INITIALISE;
    *Unit = sUnit;
}


size_t
protobuf_pou_pack(PROTOBUF_POU *Unit, uint8_t *Data) {
    assert(Unit != NULL);
    assert(Unit->Base.descriptor == &PROTOBUF_POU_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Unit, Data);
}


size_t
protobuf_pou_size(PROTOBUF_POU *Unit) {
    assert(Unit != NULL);
    assert(Unit->Base.descriptor == &PROTOBUF_POU_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Unit);
}


PROTOBUF_POU *
protobuf_pou_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_POU *) protobuf_c_message_unpack(&PROTOBUF_POU_DESCRIPTOR, Alloc, Length, Data);
}


static const ProtobufCFieldDescriptor _protobuf_pou_field_descriptors[3] = {
    {
        "Name",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_POU, Name),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Type",
        2,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_POU, Type),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Code",
        3,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_BYTES,
        0,
        offsetof(PROTOBUF_POU, Code),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_pou_field_indices[] = { 2, 0, 1 };

static const ProtobufCIntRange _protobuf_pou_ranges[2] = {
    { 1, 0 },
    { 0, 3 }
};

const ProtobufCMessageDescriptor PROTOBUF_POU_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "POU",
    "POU",
    "POU",
    "",
    sizeof(PROTOBUF_POU),
    3,
    _protobuf_pou_field_descriptors,
    _protobuf_pou_field_indices,
    1,  
    _protobuf_pou_ranges,
    (ProtobufCMessageInit) protobuf_pou_initialise,
    NULL,
    NULL,
    NULL
};

