#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <protobuf.h>


void
protobuf_index_free(PROTOBUF_INDEX *Index, ProtobufCAllocator *Alloc) {
    if(!Index)
        return;
    assert(Index->Base.descriptor == &PROTOBUF_INDEX_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Index, Alloc);
}


void
protobuf_index_initialise(PROTOBUF_INDEX *Index) {
    static const PROTOBUF_INDEX sIndex = PROTOBUF_INDEX_INITIALISE;
    *Index = sIndex;
}


size_t
protobuf_index_pack(PROTOBUF_INDEX *Index, uint8_t *Data) {
    assert(Index != NULL);
    assert(Index->Base.descriptor == &PROTOBUF_INDEX_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Index, Data);
}


size_t
protobuf_index_size(PROTOBUF_INDEX *Index) {
    assert(Index != NULL);
    assert(Index->Base.descriptor == &PROTOBUF_INDEX_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Index);
}


PROTOBUF_INDEX *
protobuf_index_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_INDEX *) protobuf_c_message_unpack(&PROTOBUF_INDEX_DESCRIPTOR, Alloc, Length, Data);
}


PROTOBUF_VALUE * 
protobuf_value_create(VALUE *Value) {
    PROTOBUF_INDEX *pArray;
    PROTOBUF_VALUE *pValue;
    char *pMeta;

    if((pValue = calloc(1, sizeof(PROTOBUF_VALUE))) == NULL)
        return NULL;
    protobuf_value_initialise(pValue);
    pValue->Type = Value->Type;
    pValue->Length = Value->Length;
    pValue->Flags = Value->Flags;

    if((pValue->Maximum.len = pValue->Length) > 0) {
        if((pValue->Maximum.data = calloc(1, pValue->Maximum.len)) == NULL)
            goto error;
        memcpy(pValue->Maximum.data, &Value->Value.Pointer, pValue->Maximum.len);
    }
    if((pValue->Minimum.len = pValue->Length) > 0) {
        if((pValue->Minimum.data = calloc(1, pValue->Minimum.len)) == NULL)
            goto error;
        memcpy(pValue->Minimum.data, &Value->Value.Pointer, pValue->Minimum.len);
    }
    if((pValue->Value.len = pValue->Length) > 0) {
        if((pValue->Value.data = calloc(1, pValue->Value.len)) == NULL)
            goto error;
        memcpy(pValue->Value.data, &Value->Value.Pointer, pValue->Value.len);
    }

    pValue->IncludeMeta = (Value->Meta != NULL);
    if(pValue->IncludeMeta) {
        pMeta = (char *) Value->Meta;
        pValue->Meta.len = strlen(pMeta);
        if((pValue->Meta.data = (uint8_t *) strdup(pMeta)) == NULL)
            goto error;
    }

    if((Value->Flags & FLAG_ARRAY) != 0) {
        if((pArray = calloc(1, sizeof(PROTOBUF_INDEX))) == NULL)
            goto error;
        pArray->Lower = Value->Index.Lower;
        pArray->Upper = Value->Index.Upper;
        pValue->Array = pArray;
    }

    return pValue;

error:
    protobuf_value_free(pValue, NULL);
    //  free(pValue) ?!
    return NULL;
}


void 
protobuf_value_free(PROTOBUF_VALUE *Value, ProtobufCAllocator *Alloc) {
    if(!Value)
        return;
    assert(Value->Base.descriptor == &PROTOBUF_VALUE_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Value, Alloc);
}


void
protobuf_value_initialise(PROTOBUF_VALUE *Value) {
    static const PROTOBUF_VALUE sValue = PROTOBUF_VALUE_INITIALISE;
    *Value = sValue;
}


size_t 
protobuf_value_pack(PROTOBUF_VALUE *Value, uint8_t *Data) {
    assert(Value != NULL);
    assert(Value->Base.descriptor == &PROTOBUF_VALUE_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Value, Data);
}


size_t 
protobuf_value_size(PROTOBUF_VALUE *Value) {
    assert(Value != NULL);
    assert(Value->Base.descriptor == &PROTOBUF_VALUE_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Value);
}


PROTOBUF_VALUE * 
protobuf_value_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_VALUE *) protobuf_c_message_unpack(&PROTOBUF_VALUE_DESCRIPTOR, Alloc, Length, Data);
}


static const ProtobufCFieldDescriptor _protobuf_index_field_descriptors[2] = {
    {
        "Lower",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_INT32,
        0,
        offsetof(PROTOBUF_INDEX, Lower),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Upper",
        2,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_INT32,
        0,
        offsetof(PROTOBUF_INDEX, Upper),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_index_field_indices[] = { 0, 1 };

static const ProtobufCIntRange _protobuf_index_ranges[2] = {
    { 1, 0 },
    { 0, 2 },
};

static const ProtobufCFieldDescriptor _protobuf_value_field_descriptors[8] = {
    {
        "Type",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_VALUE, Type),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Length",
        3,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_INT32,
        0,
        offsetof(PROTOBUF_VALUE, Length),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Flags",
        4,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_VALUE, Flags),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Maximum",
        5,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_BYTES,
        offsetof(PROTOBUF_VALUE, IncludeMaximum),
        offsetof(PROTOBUF_VALUE, Maximum),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Minimum",
        6,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_BYTES,
        offsetof(PROTOBUF_VALUE, IncludeMinimum),
        offsetof(PROTOBUF_VALUE, Minimum),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Value",
        7,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_BYTES,
        0,
        offsetof(PROTOBUF_VALUE, Value),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Meta",
        8,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_BYTES,
        offsetof(PROTOBUF_VALUE, IncludeMeta),
        offsetof(PROTOBUF_VALUE, Meta),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Array",
        9,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_MESSAGE,
        0,
        offsetof(PROTOBUF_VALUE, Array),
        &PROTOBUF_INDEX_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_value_field_indices[] = { 7, 2, 1, 3, 6, 4, 0, 5 };

static const ProtobufCIntRange _protobuf_value_ranges[3] = {
    { 1, 0 },
    { 3, 1 },
    { 0, 8 }
};

const ProtobufCMessageDescriptor PROTOBUF_INDEX_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Index",
    "Index",
    "Index",
    "",
    sizeof(PROTOBUF_INDEX),
    2,
    _protobuf_index_field_descriptors,
    _protobuf_index_field_indices,
    1,  
    _protobuf_index_ranges,
    (ProtobufCMessageInit) protobuf_index_initialise,
    NULL,
    NULL,
    NULL
};

const ProtobufCMessageDescriptor PROTOBUF_VALUE_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Value",
    "Value",
    "Value",
    "",
    sizeof(PROTOBUF_VALUE),
    8,
    _protobuf_value_field_descriptors,
    _protobuf_value_field_indices,
    2,  
    _protobuf_value_ranges,
    (ProtobufCMessageInit) protobuf_value_initialise,
    NULL,
    NULL,
    NULL
};

