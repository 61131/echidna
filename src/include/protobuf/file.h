#ifndef _PROTOBUF_FILE_H
#define _PROTOBUF_FILE_H


#include <protobuf-c/protobuf-c.h>

#include <protobuf/config.h>
#include <protobuf/pou.h>
#include <protobuf/symbol.h>


PROTOBUF_C__BEGIN_DECLS


#define PROTOBUF_FILE_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_FILE_DESCRIPTOR), 61131u, 0u, 0, NULL, 0, NULL, 0, NULL }


typedef struct _PROTOBUF_FILE {

    ProtobufCMessage Base;
    uint32_t Magic;
    uint32_t Format;
    size_t Symbols;
    PROTOBUF_SYMBOL **Symbol;
    size_t POUs;
    PROTOBUF_POU **POU;
    size_t Configs;
    PROTOBUF_CONFIG **Config;
}
PROTOBUF_FILE;

extern const ProtobufCMessageDescriptor PROTOBUF_FILE_DESCRIPTOR;


PROTOBUF_FILE * protobuf_file_create(ECHIDNA *Context);

void protobuf_file_free(PROTOBUF_FILE *File, ProtobufCAllocator *Alloc);

void protobuf_file_initialise(PROTOBUF_FILE *File);

size_t protobuf_file_pack(PROTOBUF_FILE *File, uint8_t *Data);

size_t protobuf_file_size(PROTOBUF_FILE *File);

PROTOBUF_FILE * protobuf_file_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);


PROTOBUF_C__END_DECLS


#endif  //  _PROTOBUF_FILE_H
