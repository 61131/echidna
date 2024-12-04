#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <config.h>
#include <log.h>
#include <protobuf.h>


PROTOBUF_CONFIG *
protobuf_config_create(CONFIG *Config) {
    CONFIG *pElement;
    PROTOBUF_CONFIG *pConfig;
    PROTOBUF_RESOURCE *pResource;
    size_t uSize;

    assert(Config != NULL);
    assert(Config->Type == TYPE_CONFIG);
    if((pConfig = calloc(1, sizeof(PROTOBUF_CONFIG))) == NULL)
        goto error;
    protobuf_config_initialise(pConfig);
    assert(Config->Name != NULL);
    pConfig->Name = strdup(Config->Name);

    ll_reset(&Config->List);
    while((pElement = ll_iterate(&Config->List)) != NULL) {
        PROTOBUF_RESOURCE** Resources;
        assert(pElement->Type == TYPE_RESOURCE);
        if((pResource = protobuf_resource_create(pElement)) == NULL)
            goto error;
        uSize = (pConfig->Resources + 1) * sizeof(PROTOBUF_RESOURCE *);
        Resources = realloc(pConfig->Resource, uSize);
        if(Resources == NULL) {
            protobuf_resource_free(pResource, NULL);
            goto error;
        }
        pConfig->Resource = Resources;
        pConfig->Resource[pConfig->Resources++] = pResource;
    }

    return pConfig;

error:
    protobuf_config_free(pConfig, NULL);
    return NULL;
}


void
protobuf_config_free(PROTOBUF_CONFIG *Config, ProtobufCAllocator *Alloc) {
    if(!Config)
        return;
    assert(Config->Base.descriptor == &PROTOBUF_CONFIG_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Config, Alloc);
}


void
protobuf_config_initialise(PROTOBUF_CONFIG *Config) {
    static const PROTOBUF_CONFIG sConfig = PROTOBUF_CONFIG_INITIALISE;
    *Config = sConfig;
}


size_t
protobuf_config_pack(PROTOBUF_CONFIG *Config, uint8_t *Data) {
    assert(Config != NULL);
    assert(Config->Base.descriptor == &PROTOBUF_CONFIG_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Config, Data);
}


size_t
protobuf_config_size(PROTOBUF_CONFIG *Config) {
    assert(Config != NULL);
    assert(Config->Base.descriptor == &PROTOBUF_CONFIG_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Config);
}


PROTOBUF_CONFIG *
protobuf_config_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_CONFIG *) protobuf_c_message_unpack(&PROTOBUF_CONFIG_DESCRIPTOR, Alloc, Length, Data);
}


PROTOBUF_PROGRAM *
protobuf_program_create(CONFIG *Program) {
    PROTOBUF_PROGRAM *pProgram;
    UNIT *pPOU;

    assert(Program != NULL);
    assert(Program->Type == TYPE_PROGRAM);
    if((pProgram = calloc(1, sizeof(PROTOBUF_PROGRAM))) == NULL)
        return NULL;
    protobuf_program_initialise(pProgram);
    assert(Program->Name != NULL);
    if((pProgram->Name = strdup(Program->Name)) == NULL)
        goto error;
    if(Program->Task != NULL) {
        if((pProgram->Task = strdup(Program->Task)) == NULL)
            goto error;
    }
    assert(Program->List.Size == 1);

    ll_reset(&Program->List);
    if((pPOU = ll_iterate(&Program->List)) == NULL) 
        goto error;
    pProgram->POU = strdup(pPOU->Block.Name);

    return pProgram;

error:
    protobuf_program_free(pProgram, NULL);
    return NULL;
}


void 
protobuf_program_free(PROTOBUF_PROGRAM *Program, ProtobufCAllocator *Alloc) {
    if(!Program)
        return;
    assert(Program->Base.descriptor == &PROTOBUF_PROGRAM_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Program, Alloc);
}


void 
protobuf_program_initialise(PROTOBUF_PROGRAM *Program) {
    static const PROTOBUF_PROGRAM sProgram = PROTOBUF_PROGRAM_INITIALISE;
    *Program = sProgram;
}


size_t 
protobuf_program_pack(PROTOBUF_PROGRAM *Program, uint8_t *Data) {
    assert(Program != NULL);
    assert(Program->Base.descriptor == &PROTOBUF_PROGRAM_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Program, Data);
}


size_t 
protobuf_program_size(PROTOBUF_PROGRAM *Program) {
    assert(Program != NULL);
    assert(Program->Base.descriptor == &PROTOBUF_PROGRAM_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Program);
}


PROTOBUF_PROGRAM * 
protobuf_program_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_PROGRAM *) protobuf_c_message_unpack(&PROTOBUF_PROGRAM_DESCRIPTOR, Alloc, Length, Data);
}


PROTOBUF_RESOURCE *
protobuf_resource_create(CONFIG *Resource) {
    CONFIG *pElement;
    PROTOBUF_PROGRAM *pProgram;
    PROTOBUF_PROGRAM** pPrograms;
    PROTOBUF_RESOURCE *pResource;
    PROTOBUF_TASK *pTask;
    PROTOBUF_TASK **pTasks;
    size_t uSize;

    assert(Resource != NULL);
    assert(Resource->Type == TYPE_RESOURCE);
    if((pResource = calloc(1, sizeof(PROTOBUF_RESOURCE))) == NULL)
        return NULL;
    protobuf_resource_initialise(pResource);
    assert(Resource->Name != NULL);
    pResource->Name = strdup(Resource->Name);

    ll_reset(&Resource->List);
    while((pElement = ll_iterate(&Resource->List)) != NULL) {
        switch(pElement->Type) {
            case TYPE_PROGRAM:
                if((pProgram = protobuf_program_create(pElement)) == NULL)
                    goto error;
                uSize = (pResource->Programs + 1) * sizeof(PROTOBUF_PROGRAM *);
                pPrograms = realloc(pResource->Program, uSize);
                if(pPrograms == NULL) {
                    protobuf_program_free(pProgram, NULL);
                    goto error;
                }
                pResource->Program = pPrograms;
                pResource->Program[pResource->Programs++] = pProgram;
                break;

            case TYPE_TASK:
                if((pTask = protobuf_task_create(pElement)) == NULL)
                    goto error;
                uSize = (pResource->Tasks + 1) * sizeof(PROTOBUF_TASK *);
                pTasks = realloc(pResource->Task, uSize);
                if(pTasks == NULL) {
                    protobuf_task_free(pTask, NULL);
                    goto error;
                }
                pResource->Task = pTasks;
                pResource->Task[pResource->Tasks++] = pTask;
                break;

            default:
                assert(0);
        }
    }

    return pResource;

error:
    protobuf_resource_free(pResource, NULL);
    return NULL;
}


void 
protobuf_resource_free(PROTOBUF_RESOURCE *Resource, ProtobufCAllocator *Alloc) {
    if(!Resource)
        return;
    assert(Resource->Base.descriptor == &PROTOBUF_RESOURCE_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Resource, Alloc);
}


void 
protobuf_resource_initialise(PROTOBUF_RESOURCE *Resource) {
    static const PROTOBUF_RESOURCE sResource = PROTOBUF_RESOURCE_INITIALISE;
    *Resource = sResource;
}


size_t
protobuf_resource_pack(PROTOBUF_RESOURCE *Resource, uint8_t *Data) {
    assert(Resource != NULL);
    assert(Resource->Base.descriptor == &PROTOBUF_RESOURCE_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Resource, Data);
}


size_t 
protobuf_resource_size(PROTOBUF_RESOURCE *Resource) {
    assert(Resource != NULL);
    assert(Resource->Base.descriptor == &PROTOBUF_RESOURCE_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Resource);
}


PROTOBUF_RESOURCE * 
protobuf_resource_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_RESOURCE *) protobuf_c_message_unpack(&PROTOBUF_RESOURCE_DESCRIPTOR, Alloc, Length, Data);
}


PROTOBUF_TASK *
protobuf_task_create(CONFIG *Task) {
    PROTOBUF_TASK *pTask;
    SYMBOL *pSymbol;

    assert(Task != NULL);
    assert(Task->Type == TYPE_TASK);
    if((pTask = calloc(1, sizeof(PROTOBUF_TASK))) == NULL)
        return NULL;
    protobuf_task_initialise(pTask);
    assert(Task->Name != NULL);
    if((pTask->Name = strdup(Task->Name)) == NULL)
        goto error;
    pTask->Priority = Task->Priority;
    pTask->IncludeInterval = ((pSymbol = Task->Interval) != NULL);
    if(pTask->IncludeInterval)
        pTask->Interval = pSymbol->Id;
    pTask->IncludeSingle = ((pSymbol = Task->Single) != NULL);
    if(pTask->IncludeSingle)
        pTask->Single = pSymbol->Id;

    return pTask;

error:
    protobuf_task_free(pTask, NULL);
    return NULL;
}


void 
protobuf_task_free(PROTOBUF_TASK *Task, ProtobufCAllocator *Alloc) {
    if(!Task)
        return;
    assert(Task->Base.descriptor == &PROTOBUF_TASK_DESCRIPTOR);
    protobuf_c_message_free_unpacked((ProtobufCMessage *) Task, Alloc);
}


void 
protobuf_task_initialise(PROTOBUF_TASK *Task) {
    static const PROTOBUF_TASK sTask = PROTOBUF_TASK_INITIALISE;
    *Task = sTask;
}


size_t
protobuf_task_pack(PROTOBUF_TASK *Task, uint8_t *Data) {
    assert(Task != NULL);
    assert(Task->Base.descriptor == &PROTOBUF_TASK_DESCRIPTOR);
    return protobuf_c_message_pack((const ProtobufCMessage *) Task, Data);
}


size_t 
protobuf_task_size(PROTOBUF_TASK *Task) {
    assert(Task != NULL);
    assert(Task->Base.descriptor == &PROTOBUF_TASK_DESCRIPTOR);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage *) Task);
}


PROTOBUF_TASK * 
protobuf_task_unpack(ProtobufCAllocator *Alloc, size_t Length, const uint8_t *Data) {
    return (PROTOBUF_TASK *) protobuf_c_message_unpack(&PROTOBUF_TASK_DESCRIPTOR, Alloc, Length, Data);
}


static const ProtobufCFieldDescriptor _protobuf_config_field_descriptors[2] = {
    {
        "Name",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_CONFIG, Name),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Resource",
        2,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_CONFIG, Resources),
        offsetof(PROTOBUF_CONFIG, Resource),
        &PROTOBUF_RESOURCE_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_config_field_indices[] = { 0, 1 };

static const ProtobufCIntRange _protobuf_config_ranges[2] = {
    { 1, 0 },
    { 0, 2 }
};

const ProtobufCMessageDescriptor PROTOBUF_CONFIG_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Config",
    "Config",
    "Config",
    "",
    sizeof(PROTOBUF_CONFIG),
    2,
    _protobuf_config_field_descriptors,
    _protobuf_config_field_indices,
    1,  
    _protobuf_config_ranges,
    (ProtobufCMessageInit) protobuf_config_initialise,
    NULL,
    NULL,
    NULL
};

static const ProtobufCFieldDescriptor _protobuf_program_field_descriptors[3] = {
    {
        "Name",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_PROGRAM, Name),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "POU",
        2,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_PROGRAM, POU),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Task",
        3,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_PROGRAM, Task),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_program_field_indices[] = { 0, 1, 2 };

static const ProtobufCIntRange _protobuf_program_ranges[2] = {
    { 1, 0 },
    { 0, 3 }
};

const ProtobufCMessageDescriptor PROTOBUF_PROGRAM_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Program",
    "Program",
    "Program",
    "",
    sizeof(PROTOBUF_PROGRAM),
    3,
    _protobuf_program_field_descriptors,
    _protobuf_program_field_indices,
    1,  
    _protobuf_program_ranges,
    (ProtobufCMessageInit) protobuf_program_initialise,
    NULL,
    NULL,
    NULL
};

static const ProtobufCFieldDescriptor _protobuf_resource_field_descriptors[4] = {
    {
        "Name",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_RESOURCE, Name),
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
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_RESOURCE, Type),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Task",
        3,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_RESOURCE, Tasks),
        offsetof(PROTOBUF_RESOURCE, Task),
        &PROTOBUF_TASK_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Program",
        4,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_RESOURCE, Programs),
        offsetof(PROTOBUF_RESOURCE, Program),
        &PROTOBUF_PROGRAM_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_resource_field_indices[] = { 0, 3, 2, 1 };

static const ProtobufCIntRange _protobuf_resource_ranges[2] = {
    { 1, 0 },
    { 0, 4 }
};

const ProtobufCMessageDescriptor PROTOBUF_RESOURCE_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Resource",
    "Resource",
    "Resource",
    "",
    sizeof(PROTOBUF_RESOURCE),
    4,
    _protobuf_resource_field_descriptors,
    _protobuf_resource_field_indices,
    1,  
    _protobuf_resource_ranges,
    (ProtobufCMessageInit) protobuf_resource_initialise,
    NULL,
    NULL,
    NULL
};

static const ProtobufCFieldDescriptor _protobuf_task_field_descriptors[5] = {
    {
        "Name",
        1,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_STRING,
        0,
        offsetof(PROTOBUF_TASK, Name),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Priority",
        2,
        PROTOBUF_C_LABEL_REQUIRED,
        PROTOBUF_C_TYPE_UINT32,
        0,
        offsetof(PROTOBUF_TASK, Priority),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Interval",
        3,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_UINT32,
        offsetof(PROTOBUF_TASK, IncludeInterval),
        offsetof(PROTOBUF_TASK, Interval),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Single",
        4,
        PROTOBUF_C_LABEL_OPTIONAL,
        PROTOBUF_C_TYPE_UINT32,
        offsetof(PROTOBUF_TASK, IncludeSingle),
        offsetof(PROTOBUF_TASK, Single),
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
    {
        "Program",
        5,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(PROTOBUF_TASK, Programs),
        offsetof(PROTOBUF_TASK, Program),
        &PROTOBUF_PROGRAM_DESCRIPTOR,
        NULL,
        0,
        0,
        NULL,
        NULL
    },
};

static const unsigned _protobuf_task_field_indices[] = { 2, 0, 1, 4, 3 };

static const ProtobufCIntRange _protobuf_task_ranges[2] = {
    { 1, 0 },
    { 0, 5 },
};

const ProtobufCMessageDescriptor PROTOBUF_TASK_DESCRIPTOR = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "Task",
    "Task",
    "Task",
    "",
    sizeof(PROTOBUF_TASK),
    5,
    _protobuf_task_field_descriptors,
    _protobuf_task_field_indices,
    1,  
    _protobuf_task_ranges,
    (ProtobufCMessageInit) protobuf_task_initialise,
    NULL,
    NULL,
    NULL
};


