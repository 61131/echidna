#ifndef _PROTOBUF_POU_H
#define _PROTOBUF_POU_H


#include <protobuf-c/protobuf-c.h>

#include <unit.h>


PROTOBUF_C__BEGIN_DECLS


#define PROTOBUF_POU_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_POU_DESCRIPTOR), NULL, 0, { 0, NULL } }


typedef struct _PROTOBUF_POU {

    ProtobufCMessage Base;
    char *Name;
    uint32_t Type;
    ProtobufCBinaryData Code;
}
PROTOBUF_POU;

extern const ProtobufCMessageDescriptor PROTOBUF_POU_DESCRIPTOR;


PROTOBUF_POU * protobuf_pou_create(UNIT *Unit);

void protobuf_pou_free(PROTOBUF_POU *POU, ProtobufCAllocator *Alloc);

void protobuf_pou_initialise(PROTOBUF_POU *POU);

size_t protobuf_pou_pack(PROTOBUF_POU *POU, uint8_t *Data);

size_t protobuf_pou_size(PROTOBUF_POU *POU);

PROTOBUF_POU * protobuf_pou_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);


PROTOBUF_C__END_DECLS


#endif  //  _PROTOBUF_POU_H
