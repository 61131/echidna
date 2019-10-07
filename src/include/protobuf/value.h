#ifndef _PROTOBUF_VALUE_H
#define _PROTOBUF_VALUE_H


#include <protobuf-c/protobuf-c.h>

#include <value.h>

PROTOBUF_C__BEGIN_DECLS


#define PROTOBUF_INDEX_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_INDEX_DESCRIPTOR), 0, 0 }

#define PROTOBUF_VALUE_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_VALUE_DESCRIPTOR), 0, 0, 0, 0, { 0, NULL }, 0, {0, NULL }, { 0, NULL }, 0, { 0, NULL }, NULL }


typedef struct _PROTOBUF_INDEX {

    ProtobufCMessage Base;
    int32_t Lower;
    int32_t Upper;
}
PROTOBUF_INDEX;

typedef struct _PROTOBUF_VALUE {

    ProtobufCMessage Base;
    uint32_t Type;
    int32_t Length;
    uint32_t Flags;
    protobuf_c_boolean IncludeMaximum;
    ProtobufCBinaryData Maximum;
    protobuf_c_boolean IncludeMinimum;
    ProtobufCBinaryData Minimum;
    ProtobufCBinaryData Value;
    protobuf_c_boolean IncludeMeta;
    ProtobufCBinaryData Meta;
    PROTOBUF_INDEX *Array;
}
PROTOBUF_VALUE;

extern const ProtobufCMessageDescriptor PROTOBUF_INDEX_DESCRIPTOR;

extern const ProtobufCMessageDescriptor PROTOBUF_VALUE_DESCRIPTOR;


PROTOBUF_VALUE * protobuf_value_create(VALUE *Value);

void protobuf_value_free(PROTOBUF_VALUE *Value, ProtobufCAllocator *Alloc);

void protobuf_value_initialise(PROTOBUF_VALUE *Value);

size_t protobuf_value_pack(PROTOBUF_VALUE *Value, uint8_t *Data);

size_t protobuf_value_size(PROTOBUF_VALUE *Value);

PROTOBUF_VALUE * protobuf_value_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);


PROTOBUF_C__END_DECLS

#endif  //  _PROTOBUF_VALUE_H
