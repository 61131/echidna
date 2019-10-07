#ifndef _PROTOBUF_SYMBOL_H
#define _PROTOBUF_SYMBOL_H


#include <protobuf-c/protobuf-c.h>

#include <symbol.h>
#include <protobuf/value.h>


PROTOBUF_C__BEGIN_DECLS


#define PROTOBUF_SYMBOL_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_SYMBOL_DESCRIPTOR), 0, 0, NULL, NULL, NULL, NULL, NULL }


typedef struct _PROTOBUF_SYMBOL {

    ProtobufCMessage Base;
    uint32_t Id;
    uint32_t Offset;
    PROTOBUF_VALUE *Value;
    char *Name;
    char *POU;
    char *Resource;
    char *Configuration;
}
PROTOBUF_SYMBOL;

extern const ProtobufCMessageDescriptor PROTOBUF_SYMBOL_DESCRIPTOR;


PROTOBUF_SYMBOL * protobuf_symbol_create(SYMBOL *Symbol);

void protobuf_symbol_free(PROTOBUF_SYMBOL *Symbol, ProtobufCAllocator *Alloc);

void protobuf_symbol_initialise(PROTOBUF_SYMBOL *Symbol);

size_t protobuf_symbol_pack(PROTOBUF_SYMBOL *Symbol, uint8_t *Data);

size_t protobuf_symbol_size(PROTOBUF_SYMBOL *Symbol);

PROTOBUF_SYMBOL * protobuf_symbol_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);


PROTOBUF_C__END_DECLS


#endif  //  _PROTOBUF_SYMBOL_H
