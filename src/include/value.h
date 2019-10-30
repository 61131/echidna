#ifndef _VALUE_H
#define _VALUE_H


#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

#include <macros.h>


#define VALUE_STRING_MAX        (255)

#define value_assign(...)       _value_assign(_NARG(__VA_ARGS__), __VA_ARGS__)

#define value_cast(...)         _value_cast(_NARG(__VA_ARGS__), __VA_ARGS__)

#define value_destroy(...)      _value_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef enum _VALUE_TYPE {

    TYPE_NONE                   = 0x00000000,
    TYPE_LREAL                  = 0x00100000,
    TYPE_REAL                   = 0x00080000,
    TYPE_LINT                   = 0x00040000,
    TYPE_DINT                   = 0x00020000,
    TYPE_INT                    = 0x00010000,
    TYPE_SINT                   = 0x00008000,
    TYPE_ULINT                  = 0x00004000,
    TYPE_UDINT                  = 0x00002000,
    TYPE_UINT                   = 0x00001000,
    TYPE_USINT                  = 0x00000800,
    TYPE_TIME                   = 0x00000400,
    TYPE_LWORD                  = 0x00000200,
    TYPE_DWORD                  = 0x00000100,
    TYPE_WORD                   = 0x00000080,
    TYPE_BYTE                   = 0x00000040,
    TYPE_BOOL                   = 0x00000020,
    TYPE_STRING                 = 0x00000010,
    TYPE_WSTRING                = 0x00000008,
    TYPE_DATE                   = 0x00000004,
    TYPE_DT                     = 0x00000002,
    TYPE_TOD                    = 0x00000001,

    TYPE_ARRAY                  = 0x01000000,
    TYPE_DERIVED                = 0x00800000,
    TYPE_ENUMERATED             = 0x00600000,
    TYPE_SUBRANGE               = 0x00400000,
    TYPE_STRUCTURED             = 0x00200000,
    
    TYPE_FUNCTION_BLOCK         = 0x08000000,
    TYPE_FUNCTION               = 0x06000000,
    TYPE_LABEL                  = 0x04000000,
    _TYPE_PROGRAM               = 0x02000000,
    TYPE_INPUT                  = 0x10000000,   /* For specification of POU parameters */
    TYPE_OUTPUT                 = 0x20000000,   /* For specification of POU parameters */
    TYPE_IN_OUT                 = 0x30000000,   /* For specification of POU parameters */
    TYPE_NEGATED                = 0x10000000,
    TYPE_PARAMETER              = 0x40000000,
    TYPE_VARIABLE               = 0x80000000,
    
    ANY                         = 0xffffffff,
    ANY_DERIVED                 = 0x01e00000,
    ANY_ELEMENTARY              = 0x001fffff,
    ANY_MAGNITUDE               = 0x001ffc00,
    ANY_NUM                     = 0x001ff800,
    ANY_REAL                    = 0x00180000,
    ANY_INT                     = 0x0007f800,
    ANY_BIT                     = 0x000003e0,
    ANY_STRING                  = 0x00000018,
    ANY_DATE                    = 0x00000007,
    ANY_INTERNAL                = 0xfe000000,
}
VALUE_TYPE;

typedef enum _VALUE_FLAG {
    FLAG_NONE                   = (0<<0),       /* 0 */
    FLAG_ARRAY                  = (1<<0),       /* 1 */
    FLAG_ASSIGN                 = (1<<1),       /* 2 */
    FLAG_CONSTANT               = (1<<2),       /* 4 */
    FLAG_NON_RETAIN             = (1<<3),       /* 8 */
    FLAG_READ_ONLY              = (1<<4),       /* 16 */
    FLAG_RETAIN                 = (1<<5),       /* 32 */
    FLAG_SUBRANGE               = (1<<6),       /* 64 */
    FLAG_F_EDGE                 = (1<<7),       /* 128 */
    FLAG_R_EDGE                 = (1<<8),       /* 256 */
}
VALUE_FLAG;

typedef union _VALUE_UNION {

    uint8_t B1;
    
    int8_t S8;
    
    int16_t S16;
    
    int32_t S32;
    
    int64_t S64;
    
    uint8_t U8;
    
    uint16_t U16;
    
    uint32_t U32;
    
    uint64_t U64;
    
    float Single;
    
    double Double;
    
    void * Pointer;
    
    uint8_t B8;
    
    uint16_t B16;
    
    uint32_t B32;
    
    uint64_t B64;

    float Time;

    time_t DateTime;
}
VALUE_UNION;

typedef struct _VALUE {

    VALUE_TYPE Type;    

    VALUE_TYPE Cast;

    ssize_t Length;

    uint32_t Flags;

    VALUE_UNION Maximum;
        
    VALUE_UNION Minimum;

    VALUE_UNION Value;

    void * Meta;

    struct {

        int64_t Lower;

        int64_t Upper;
    }
    Index;
}
VALUE;


void _value_assign(size_t Arg, ...);

int _value_cast(size_t Arg, VALUE *Value, VALUE_TYPE Type, ...);

void _value_destroy(size_t Arg, VALUE *Value, ...);

int value_allocate(VALUE *Value, VALUE_TYPE Type, size_t Length);

int value_copy(VALUE *Dest, VALUE *Src);

void value_initialise(VALUE *Value);

int value_istype(VALUE *Value, VALUE_TYPE Type);

int value_strtotype(VALUE *Value, char *Str);

int value_strtoval(VALUE *Value, VALUE_TYPE Type, char *Str);

int value_typetosize(VALUE_TYPE Type);

const char * value_typetostr(VALUE_TYPE Type);


#endif  /* _VALUE_H */

