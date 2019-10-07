#ifndef _PROTOBUF_CONFIG_H
#define _PROTOBUF_CONFIG_H


#include <protobuf-c/protobuf-c.h>

#include <config.h>


PROTOBUF_C__BEGIN_DECLS


#define PROTOBUF_CONFIG_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_CONFIG_DESCRIPTOR), NULL, 0, NULL }

#define PROTOBUF_PROGRAM_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_PROGRAM_DESCRIPTOR), NULL, NULL, NULL }

#define PROTOBUF_RESOURCE_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_RESOURCE_DESCRIPTOR), NULL, NULL, 0, NULL, 0, NULL }

#define PROTOBUF_TASK_INITIALISE { PROTOBUF_C_MESSAGE_INIT(&PROTOBUF_TASK_DESCRIPTOR), NULL, 0, 0, 0, 0, 0, 0,NULL }


typedef struct _PROTOBUF_PROGRAM {

    ProtobufCMessage Base;
    char *Name;
    char *POU;
    char *Task;
}
PROTOBUF_PROGRAM;

typedef struct _PROTOBUF_TASK {

    ProtobufCMessage Base;
    char *Name;
    uint32_t Priority;
    protobuf_c_boolean IncludeInterval;
    uint32_t Interval;
    protobuf_c_boolean IncludeSingle;
    uint32_t Single;
    size_t Programs;
    PROTOBUF_PROGRAM **Program;
}
PROTOBUF_TASK;

typedef struct _PROTOBUF_RESOURCE {

    ProtobufCMessage Base;
    char *Name;
    char *Type;
    size_t Tasks;
    PROTOBUF_TASK **Task;
    size_t Programs;
    PROTOBUF_PROGRAM **Program;
}
PROTOBUF_RESOURCE;

typedef struct _PROTOBUF_CONFIG {

    ProtobufCMessage Base;
    char *Name;
    size_t Resources;
    PROTOBUF_RESOURCE **Resource;
}
PROTOBUF_CONFIG;

extern const ProtobufCMessageDescriptor PROTOBUF_CONFIG_DESCRIPTOR;

extern const ProtobufCMessageDescriptor PROTOBUF_PROGRAM_DESCRIPTOR;

extern const ProtobufCMessageDescriptor PROTOBUF_RESOURCE_DESCRIPTOR;

extern const ProtobufCMessageDescriptor PROTOBUF_TASK_DESCRIPTOR;


PROTOBUF_CONFIG * protobuf_config_create(CONFIG *Config);

void protobuf_config_free(PROTOBUF_CONFIG *Config, ProtobufCAllocator *Alloc);

void protobuf_config_initialise(PROTOBUF_CONFIG *Config);

size_t protobuf_config_pack(PROTOBUF_CONFIG *Config, uint8_t *Data);

size_t protobuf_config_size(PROTOBUF_CONFIG *Config);

PROTOBUF_CONFIG * protobuf_config_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);

PROTOBUF_PROGRAM * protobuf_program_create(CONFIG *Program);

void protobuf_program_free(PROTOBUF_PROGRAM *Program, ProtobufCAllocator *Alloc);

void protobuf_program_initialise(PROTOBUF_PROGRAM *Program);

size_t protobuf_program_pack(PROTOBUF_PROGRAM *Program, uint8_t *Data);

size_t protobuf_program_size(PROTOBUF_PROGRAM *Program);

PROTOBUF_PROGRAM * protobuf_program_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);

PROTOBUF_RESOURCE * protobuf_resource_create(CONFIG *Resource);

void protobuf_resource_free(PROTOBUF_RESOURCE *Resource, ProtobufCAllocator *Alloc);

void protobuf_resource_initialise(PROTOBUF_RESOURCE *Resource);

size_t protobuf_resource_pack(PROTOBUF_RESOURCE *Resource, uint8_t *Data);

size_t protobuf_resource_size(PROTOBUF_RESOURCE *Resource);

PROTOBUF_RESOURCE * protobuf_resource_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);

PROTOBUF_TASK * protobuf_task_create(CONFIG *Task);

void protobuf_task_free(PROTOBUF_TASK *Task, ProtobufCAllocator *Alloc);

void protobuf_task_initialise(PROTOBUF_TASK *Task);

size_t protobuf_task_pack(PROTOBUF_TASK *Task, uint8_t *Data);

size_t protobuf_task_size(PROTOBUF_TASK *Task);

PROTOBUF_TASK * protobuf_task_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data);


PROTOBUF_C__END_DECLS


#endif  //  _PROTOBUF_CONFIG_H
