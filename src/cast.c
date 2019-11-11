#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <assert.h>

#include <cast.h>
#include <log.h>


int
cast_lreal(VALUE *Value) {
    uint32_t uType;
    double dVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    dVal = 0.0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        return 0;
        case TYPE_REAL:         dVal = (double) Value->Value.Single; break;
        case TYPE_LINT:         dVal = (double) Value->Value.S64; break;
        case TYPE_DINT:         dVal = (double) Value->Value.S32; break;
        case TYPE_INT:          dVal = (double) Value->Value.S16; break;
        case TYPE_SINT:         dVal = (double) Value->Value.S8; break;
        case TYPE_ULINT:        dVal = (double) Value->Value.U64; break;
        case TYPE_UDINT:        dVal = (double) Value->Value.U32; break;
        case TYPE_UINT:         dVal = (double) Value->Value.U16; break;
        case TYPE_USINT:        dVal = (double) Value->Value.U8; break;
        case TYPE_LWORD:        dVal = (double) Value->Value.B64; break;
        case TYPE_DWORD:        dVal = (double) Value->Value.B32; break;
        case TYPE_WORD:         dVal = (double) Value->Value.B16; break;
        case TYPE_BYTE:         dVal = (double) Value->Value.B8; break;
        case TYPE_BOOL:         dVal = (double) Value->Value.B1; break;
        case TYPE_TIME:         dVal = (double) Value->Value.Time; break;
        case TYPE_DATE:         dVal = (double) Value->Value.DateTime; break;
        case TYPE_DT:           dVal = (double) Value->Value.DateTime; break;
        case TYPE_TOD:          dVal = (double) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.Double = dVal;
    Value->Maximum.Double = DBL_MAX;
    Value->Minimum.Double = DBL_MIN;
    Value->Length = sizeof(Value->Value.Double);
    Value->Type = Value->Cast = TYPE_LREAL;
    return 0;
}


int
cast_real(VALUE *Value) {
    uint32_t uType;
    float fVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    fVal = 0.0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        fVal = (float) Value->Value.Double; break;
        case TYPE_REAL:         return 0;
        case TYPE_LINT:         fVal = (float) Value->Value.S64; break;
        case TYPE_DINT:         fVal = (float) Value->Value.S32; break;
        case TYPE_INT:          fVal = (float) Value->Value.S16; break;
        case TYPE_SINT:         fVal = (float) Value->Value.S8; break;
        case TYPE_ULINT:        fVal = (float) Value->Value.U64; break;
        case TYPE_UDINT:        fVal = (float) Value->Value.U32; break;
        case TYPE_UINT:         fVal = (float) Value->Value.U16; break;
        case TYPE_USINT:        fVal = (float) Value->Value.U8; break;
        case TYPE_LWORD:        fVal = (float) Value->Value.B64; break;
        case TYPE_DWORD:        fVal = (float) Value->Value.B32; break;
        case TYPE_WORD:         fVal = (float) Value->Value.B16; break;
        case TYPE_BYTE:         fVal = (float) Value->Value.B8; break;
        case TYPE_BOOL:         fVal = (float) Value->Value.B1; break;
        case TYPE_TIME:         fVal = (float) Value->Value.Time; break;
        case TYPE_DATE:         fVal = (float) Value->Value.DateTime; break;
        case TYPE_DT:           fVal = (float) Value->Value.DateTime; break;
        case TYPE_TOD:          fVal = (float) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.Single = fVal;
    Value->Maximum.Single = FLT_MAX;
    Value->Minimum.Single = FLT_MIN;
    Value->Length = sizeof(Value->Value.Single);
    Value->Type = Value->Cast = TYPE_REAL;
    return 0;
}


int
cast_lint(VALUE *Value) {
    uint32_t uType;
    int64_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int64_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int64_t) Value->Value.Single; break;
        case TYPE_LINT:         return 0;
        case TYPE_DINT:         nVal = (int64_t) Value->Value.S32; break;
        case TYPE_INT:          nVal = (int64_t) Value->Value.S16; break;
        case TYPE_SINT:         nVal = (int64_t) Value->Value.S8; break;
        case TYPE_ULINT:        nVal = (int64_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int64_t) Value->Value.U32; break;
        case TYPE_UINT:         nVal = (int64_t) Value->Value.U16; break;
        case TYPE_USINT:        nVal = (int64_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int64_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int64_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int64_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int64_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int64_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int64_t) Value->Value.Time; break;
        case TYPE_DATE:         nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_DT:           nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_TOD:          nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.S64 = nVal;
    Value->Maximum.S64 = INT64_MAX;
    Value->Minimum.S64 = INT64_MIN;
    Value->Length = sizeof(Value->Value.S64);
    Value->Type = Value->Cast = TYPE_LINT;
    return 0;
}


int
cast_dint(VALUE *Value) {
    uint32_t uType;
    int32_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int32_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int32_t) Value->Value.Single; break;
        case TYPE_LINT:         nVal = (int32_t) Value->Value.S64; break;
        case TYPE_DINT:         return 0;
        case TYPE_INT:          nVal = (int32_t) Value->Value.S16; break;
        case TYPE_SINT:         nVal = (int32_t) Value->Value.S8; break;
        case TYPE_UINT:         nVal = (int32_t) Value->Value.U16; break;
        case TYPE_ULINT:        nVal = (int32_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int32_t) Value->Value.U32; break;
        case TYPE_USINT:        nVal = (int32_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int32_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int32_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int32_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int32_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int32_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int32_t) Value->Value.Time; break;
        case TYPE_DATE:         nVal = (int32_t) Value->Value.DateTime; break;
        case TYPE_DT:           nVal = (int32_t) Value->Value.DateTime; break;
        case TYPE_TOD:          nVal = (int32_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.S32 = nVal;
    Value->Maximum.S32 = INT32_MAX;
    Value->Minimum.S32 = INT32_MIN;
    Value->Length = sizeof( Value->Value.S32 );
    Value->Type = Value->Cast = TYPE_DINT;
    return 0;
}


int
cast_int(VALUE *Value) {
    uint32_t uType;
    int16_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int16_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int16_t) Value->Value.Single; break;
        case TYPE_LINT:         nVal = (int16_t) Value->Value.S64; break;
        case TYPE_DINT:         nVal = (int16_t) Value->Value.S32; break;
        case TYPE_INT:          return 0;
        case TYPE_SINT:         nVal = (int16_t) Value->Value.S8; break;
        case TYPE_ULINT:        nVal = (int16_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int16_t) Value->Value.U32; break;
        case TYPE_UINT:         nVal = (int16_t) Value->Value.U16; break;
        case TYPE_USINT:        nVal = (int16_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int16_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int16_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int16_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int16_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int16_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int16_t) Value->Value.Time; break;
        case TYPE_DATE:         nVal = (int16_t) Value->Value.DateTime; break;
        case TYPE_DT:           nVal = (int16_t) Value->Value.DateTime; break;
        case TYPE_TOD:          nVal = (int16_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.S16 = nVal;
    Value->Maximum.S16 = INT16_MAX;
    Value->Minimum.S16 = INT16_MIN;
    Value->Length = sizeof( Value->Value.S16 );
    Value->Type = Value->Cast = TYPE_INT;
    return 0;
}


int
cast_sint(VALUE *Value) {
    uint32_t uType;
    int8_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int8_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int8_t) Value->Value.Single; break;
        case TYPE_LINT:         nVal = (int8_t) Value->Value.S64; break;
        case TYPE_DINT:         nVal = (int8_t) Value->Value.S32; break;
        case TYPE_INT:          nVal = (int8_t) Value->Value.S16; break;
        case TYPE_SINT:         return 0;
        case TYPE_ULINT:        nVal = (int8_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int8_t) Value->Value.U32; break;
        case TYPE_UINT:         nVal = (int8_t) Value->Value.U16; break;
        case TYPE_USINT:        nVal = (int8_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int8_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int8_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int8_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int8_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int8_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int8_t) Value->Value.Time; break;
        case TYPE_DATE:         nVal = (int8_t) Value->Value.DateTime; break;
        case TYPE_DT:           nVal = (int8_t) Value->Value.DateTime; break;
        case TYPE_TOD:          nVal = (int8_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.S8 = nVal;
    Value->Maximum.S8 = INT8_MAX;
    Value->Minimum.S8 = INT8_MIN;
    Value->Length = sizeof( Value->Value.S8 );
    Value->Type = Value->Cast = TYPE_SINT;
    return 0;
}


int
cast_ulint(VALUE *Value) {
    uint32_t uType;
    uint64_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint64_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint64_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint64_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint64_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint64_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint64_t) Value->Value.S8; break;
        case TYPE_ULINT:        return 0;
        case TYPE_UDINT:        uVal = (uint64_t) Value->Value.U32; break;
        case TYPE_UINT:         uVal = (uint64_t) Value->Value.U16; break;
        case TYPE_USINT:        uVal = (uint64_t) Value->Value.U8; break;
        case TYPE_LWORD:        uVal = (uint64_t) Value->Value.B64; break;
        case TYPE_DWORD:        uVal = (uint64_t) Value->Value.B32; break;
        case TYPE_WORD:         uVal = (uint64_t) Value->Value.B16; break;
        case TYPE_BYTE:         uVal = (uint64_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint64_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint64_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint64_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint64_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint64_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.U64 = uVal;
    Value->Maximum.U64 = UINT64_MAX;
    Value->Minimum.U64 = 0;
    Value->Length = sizeof( Value->Value.U64 );
    Value->Type = Value->Cast = TYPE_ULINT;
    return 0;
}


int
cast_udint(VALUE *Value) {
    uint32_t uType;
    uint32_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint32_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint32_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint32_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint32_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint32_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint32_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint32_t) Value->Value.U64; break;
        case TYPE_UDINT:        return 0;
        case TYPE_UINT:         uVal = (uint32_t) Value->Value.U16; break;
        case TYPE_USINT:        uVal = (uint32_t) Value->Value.U8; break;
        case TYPE_LWORD:        uVal = (uint32_t) Value->Value.B64; break;
        case TYPE_DWORD:        uVal = (uint32_t) Value->Value.B32; break;
        case TYPE_WORD:         uVal = (uint32_t) Value->Value.B16; break;
        case TYPE_BYTE:         uVal = (uint32_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint32_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint32_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint32_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint32_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint32_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.U32 = uVal;
    Value->Maximum.U32 = UINT32_MAX;
    Value->Minimum.U32 = 0;
    Value->Length = sizeof( Value->Value.U32 );
    Value->Type = Value->Cast = TYPE_UDINT;
    return 0;
}


int
cast_uint(VALUE *Value) {
    uint32_t uType;
    uint16_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint16_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint16_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint16_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint16_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint16_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint16_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint16_t) Value->Value.U64; break;
        case TYPE_UDINT:        uVal = (uint16_t) Value->Value.U32; break;
        case TYPE_UINT:         return 0;
        case TYPE_USINT:        uVal = (uint16_t) Value->Value.U8; break;
        case TYPE_LWORD:        uVal = (uint16_t) Value->Value.B64; break;
        case TYPE_DWORD:        uVal = (uint16_t) Value->Value.B32; break;
        case TYPE_WORD:         uVal = (uint16_t) Value->Value.B16; break;
        case TYPE_BYTE:         uVal = (uint16_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint16_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint16_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint16_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint16_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint16_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.U16 = uVal;
    Value->Maximum.U16 = UINT16_MAX;
    Value->Minimum.U16 = 0;
    Value->Length = sizeof( Value->Value.U16 );
    Value->Type = Value->Cast = TYPE_UINT;
    return 0;
}


int
cast_usint(VALUE *Value) {
    uint32_t uType;
    uint8_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint8_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint8_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint8_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint8_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint8_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint8_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint8_t) Value->Value.U64; break;
        case TYPE_UDINT:        uVal = (uint8_t) Value->Value.U32; break;
        case TYPE_UINT:         uVal = (uint8_t) Value->Value.U16; break;
        case TYPE_USINT:        return 0;
        case TYPE_LWORD:        uVal = (uint8_t) Value->Value.B64; break;
        case TYPE_DWORD:        uVal = (uint8_t) Value->Value.B32; break;
        case TYPE_WORD:         uVal = (uint8_t) Value->Value.B16; break;
        case TYPE_BYTE:         uVal = (uint8_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint8_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint8_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint8_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint8_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint8_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.U8 = uVal;
    Value->Maximum.U8 = UINT8_MAX;
    Value->Minimum.U8 = 0;
    Value->Length = sizeof( Value->Value.U8 );
    Value->Type = Value->Cast = TYPE_USINT;
    return 0;
}



int
cast_lword(VALUE *Value) {
    uint32_t uType;
    uint64_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint64_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint64_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint64_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint64_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint64_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint64_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint64_t) Value->Value.U64; break;
        case TYPE_UDINT:        uVal = (uint64_t) Value->Value.U32; break;
        case TYPE_UINT:         uVal = (uint64_t) Value->Value.U16; break;
        case TYPE_USINT:        uVal = (uint64_t) Value->Value.U8; break;
        case TYPE_LWORD:        return 0;
        case TYPE_DWORD:        uVal = (uint64_t) Value->Value.B32; break;
        case TYPE_WORD:         uVal = (uint64_t) Value->Value.B16; break;
        case TYPE_BYTE:         uVal = (uint64_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint64_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint64_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint64_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint64_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint64_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.B64 = uVal;
    Value->Maximum.B64 = UINT64_MAX;
    Value->Minimum.B64 = 0;
    Value->Length = sizeof(Value->Value.B64);
    Value->Type = Value->Cast = TYPE_LWORD;
    return 0;
}


int
cast_dword(VALUE *Value) {
    uint32_t uType;
    uint32_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint32_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint32_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint32_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint32_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint32_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint32_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint32_t) Value->Value.U64; break;
        case TYPE_UDINT:        uVal = (uint32_t) Value->Value.U32; break;
        case TYPE_UINT:         uVal = (uint32_t) Value->Value.U16; break;
        case TYPE_USINT:        uVal = (uint32_t) Value->Value.U8; break;
        case TYPE_LWORD:        uVal = (uint32_t) Value->Value.B64; break;
        case TYPE_DWORD:        return 0;
        case TYPE_WORD:         uVal = (uint32_t) Value->Value.B16; break;
        case TYPE_BYTE:         uVal = (uint32_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint32_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint32_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint32_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint32_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint32_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.B32 = uVal;
    Value->Maximum.B32 = UINT32_MAX;
    Value->Minimum.B32 = 0;
    Value->Length = sizeof(Value->Value.B32);
    Value->Type = Value->Cast = TYPE_DWORD;
    return 0;
}


int
cast_word(VALUE *Value) {
    uint32_t uType;
    uint16_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint16_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint16_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint16_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint16_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint16_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint16_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint16_t) Value->Value.U64; break;
        case TYPE_UDINT:        uVal = (uint16_t) Value->Value.U32; break;
        case TYPE_UINT:         uVal = (uint16_t) Value->Value.U16; break;
        case TYPE_USINT:        uVal = (uint16_t) Value->Value.U8; break;
        case TYPE_LWORD:        uVal = (uint16_t) Value->Value.B64; break;
        case TYPE_DWORD:        uVal = (uint16_t) Value->Value.B32; break;
        case TYPE_WORD:         return 0;
        case TYPE_BYTE:         uVal = (uint16_t) Value->Value.B8; break;
        case TYPE_BOOL:         uVal = (uint16_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint16_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint16_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint16_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint16_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.B16 = uVal;
    Value->Maximum.B16 = UINT16_MAX;
    Value->Minimum.B16 = 0;
    Value->Length = sizeof(Value->Value.B16);
    Value->Type = Value->Cast = TYPE_WORD;
    return 0;
}


int
cast_byte(VALUE *Value) {
    uint32_t uType;
    uint8_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint8_t) Value->Value.Double; break;
        case TYPE_REAL:         uVal = (uint8_t) Value->Value.Single; break;
        case TYPE_LINT:         uVal = (uint8_t) Value->Value.S64; break;
        case TYPE_DINT:         uVal = (uint8_t) Value->Value.S32; break;
        case TYPE_INT:          uVal = (uint8_t) Value->Value.S16; break;
        case TYPE_SINT:         uVal = (uint8_t) Value->Value.S8; break;
        case TYPE_ULINT:        uVal = (uint8_t) Value->Value.U64; break;
        case TYPE_UDINT:        uVal = (uint8_t) Value->Value.U32; break;
        case TYPE_UINT:         uVal = (uint8_t) Value->Value.U16; break;
        case TYPE_USINT:        uVal = (uint8_t) Value->Value.U8; break;
        case TYPE_LWORD:        uVal = (uint8_t) Value->Value.B64; break;
        case TYPE_DWORD:        uVal = (uint8_t) Value->Value.B32; break;
        case TYPE_WORD:         uVal = (uint8_t) Value->Value.B16; break;
        case TYPE_BYTE:         return 0;
        case TYPE_BOOL:         uVal = (uint8_t) Value->Value.B1; break;
        case TYPE_TIME:         uVal = (uint8_t) Value->Value.Time; break;
        case TYPE_DATE:         uVal = (uint8_t) Value->Value.DateTime; break;
        case TYPE_DT:           uVal = (uint8_t) Value->Value.DateTime; break;
        case TYPE_TOD:          uVal = (uint8_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.B8 = uVal;
    Value->Maximum.B8 = UINT8_MAX;
    Value->Minimum.B8 = 0;
    Value->Length = sizeof(Value->Value.B8);
    Value->Type = Value->Cast = TYPE_BYTE;
    return 0;
}


int
cast_bool(VALUE *Value) {
    uint32_t uType;
    uint8_t uVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    uVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        uVal = (uint8_t)(Value->Value.Double != 0.0); break;
        case TYPE_REAL:         uVal = (uint8_t)(Value->Value.Single != 0.0); break;
        case TYPE_LINT:         uVal = (uint8_t)(Value->Value.S64 != 0); break;
        case TYPE_DINT:         uVal = (uint8_t)(Value->Value.S32 != 0); break;
        case TYPE_INT:          uVal = (uint8_t)(Value->Value.S16 != 0); break;
        case TYPE_SINT:         uVal = (uint8_t)(Value->Value.S8 != 0); break;
        case TYPE_ULINT:        uVal = (uint8_t)(Value->Value.U64 != 0); break;
        case TYPE_UDINT:        uVal = (uint8_t)(Value->Value.U32 != 0); break;
        case TYPE_UINT:         uVal = (uint8_t)(Value->Value.U16 != 0); break;
        case TYPE_USINT:        uVal = (uint8_t)(Value->Value.U8 != 0); break;
        case TYPE_LWORD:        uVal = (uint8_t)(Value->Value.B64 != 0); break;
        case TYPE_DWORD:        uVal = (uint8_t)(Value->Value.B32 != 0); break;
        case TYPE_WORD:         uVal = (uint8_t)(Value->Value.B16 != 0); break;
        case TYPE_BYTE:         uVal = (uint8_t)(Value->Value.B8 != 0); break;
        case TYPE_TIME:         uVal = (uint8_t)(Value->Value.Time != 0.0); break;
        case TYPE_BOOL:         return 0;
        case TYPE_DATE:         uVal = (uint8_t)(Value->Value.DateTime != 0); break;
        case TYPE_DT:           uVal = (uint8_t)(Value->Value.DateTime != 0); break;
        case TYPE_TOD:          uVal = (uint8_t)(Value->Value.DateTime != 0); break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.B1 = uVal;
    Value->Maximum.B1 = 1;
    Value->Minimum.B1 = 0;
    Value->Length = sizeof(/* Value->Value.B1 */ uint8_t);
    Value->Type = Value->Cast = TYPE_BOOL;
    return 0;
}


int 
cast_string(VALUE *Value) {
    errno = EINVAL;
    return -1;
}


int 
cast_wstring(VALUE *Value) {
    errno = EINVAL;
    return -1;
}


int
cast_time(VALUE *Value) {
    uint32_t uType;
    float fVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    fVal = 0.0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        fVal = (float) Value->Value.Double; break;
        case TYPE_REAL:         fVal = (float) Value->Value.Single; break;
        case TYPE_LINT:         fVal = (float) Value->Value.S64; break;
        case TYPE_DINT:         fVal = (float) Value->Value.S32; break;
        case TYPE_INT:          fVal = (float) Value->Value.S16; break;
        case TYPE_SINT:         fVal = (float) Value->Value.S8; break;
        case TYPE_ULINT:        fVal = (float) Value->Value.U64; break;
        case TYPE_UDINT:        fVal = (float) Value->Value.U32; break;
        case TYPE_UINT:         fVal = (float) Value->Value.U16; break;
        case TYPE_USINT:        fVal = (float) Value->Value.U8; break;
        case TYPE_LWORD:        fVal = (float) Value->Value.B64; break;
        case TYPE_DWORD:        fVal = (float) Value->Value.B32; break;
        case TYPE_WORD:         fVal = (float) Value->Value.B16; break;
        case TYPE_BYTE:         fVal = (float) Value->Value.B8; break;
        case TYPE_BOOL:         fVal = (float) Value->Value.B1; break;
        case TYPE_TIME:         return 0;
        case TYPE_DATE:         fVal = (float) Value->Value.DateTime; break;
        case TYPE_DT:           fVal = (float) Value->Value.DateTime; break;
        case TYPE_TOD:          fVal = (float) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.Time = fVal;
    Value->Maximum.Time = FLT_MAX;
    Value->Minimum.Time = FLT_MIN;
    Value->Length = sizeof(Value->Value.Time);
    Value->Type = Value->Cast = TYPE_TIME;
    return 0;
}


int 
cast_date(VALUE *Value) {
    uint32_t uType;
    int64_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int64_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int64_t) Value->Value.Single; break;
        case TYPE_LINT:         nVal = (int64_t) Value->Value.S64; break;
        case TYPE_DINT:         nVal = (int64_t) Value->Value.S32; break;
        case TYPE_INT:          nVal = (int64_t) Value->Value.S16; break;
        case TYPE_SINT:         nVal = (int64_t) Value->Value.S8; break;
        case TYPE_ULINT:        nVal = (int64_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int64_t) Value->Value.U32; break;
        case TYPE_UINT:         nVal = (int64_t) Value->Value.U16; break;
        case TYPE_USINT:        nVal = (int64_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int64_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int64_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int64_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int64_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int64_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int64_t) Value->Value.Time; break;
        case TYPE_DATE:         return 0;
        case TYPE_DT:           nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_TOD:          nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.DateTime = nVal;
    Value->Maximum.DateTime = 0;
    Value->Minimum.DateTime = 0;
    Value->Length = sizeof(Value->Value.DateTime);
    Value->Type = Value->Cast = TYPE_DATE;
    return 0;
}


int 
cast_dt(VALUE *Value) {
    uint32_t uType;
    int64_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int64_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int64_t) Value->Value.Single; break;
        case TYPE_LINT:         nVal = (int64_t) Value->Value.S64; break;
        case TYPE_DINT:         nVal = (int64_t) Value->Value.S32; break;
        case TYPE_INT:          nVal = (int64_t) Value->Value.S16; break;
        case TYPE_SINT:         nVal = (int64_t) Value->Value.S8; break;
        case TYPE_ULINT:        nVal = (int64_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int64_t) Value->Value.U32; break;
        case TYPE_UINT:         nVal = (int64_t) Value->Value.U16; break;
        case TYPE_USINT:        nVal = (int64_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int64_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int64_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int64_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int64_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int64_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int64_t) Value->Value.Time; break;
        case TYPE_DATE:         nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_DT:           return 0;
        case TYPE_TOD:          nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.DateTime = nVal;
    Value->Maximum.DateTime = 0;
    Value->Minimum.DateTime = 0;
    Value->Length = sizeof(Value->Value.DateTime);
    Value->Type = Value->Cast = TYPE_DT;
    return 0;
}


int 
cast_tod(VALUE *Value) {
    uint32_t uType;
    int64_t nVal;

    if(!Value) {
        errno = EINVAL;
        return -1;
    }

    nVal = 0;
    if((uType = Value->Type) == TYPE_DERIVED)
        uType = Value->Cast;

    uType &= ~ANY_INTERNAL;
    switch(uType) {
        case TYPE_LREAL:        nVal = (int64_t) Value->Value.Double; break;
        case TYPE_REAL:         nVal = (int64_t) Value->Value.Single; break;
        case TYPE_LINT:         nVal = (int64_t) Value->Value.S64; break;
        case TYPE_DINT:         nVal = (int64_t) Value->Value.S32; break;
        case TYPE_INT:          nVal = (int64_t) Value->Value.S16; break;
        case TYPE_SINT:         nVal = (int64_t) Value->Value.S8; break;
        case TYPE_ULINT:        nVal = (int64_t) Value->Value.U64; break;
        case TYPE_UDINT:        nVal = (int64_t) Value->Value.U32; break;
        case TYPE_UINT:         nVal = (int64_t) Value->Value.U16; break;
        case TYPE_USINT:        nVal = (int64_t) Value->Value.U8; break;
        case TYPE_LWORD:        nVal = (int64_t) Value->Value.B64; break;
        case TYPE_DWORD:        nVal = (int64_t) Value->Value.B32; break;
        case TYPE_WORD:         nVal = (int64_t) Value->Value.B16; break;
        case TYPE_BYTE:         nVal = (int64_t) Value->Value.B8; break;
        case TYPE_BOOL:         nVal = (int64_t) Value->Value.B1; break;
        case TYPE_TIME:         nVal = (int64_t) Value->Value.Time; break;
        case TYPE_DATE:         nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_DT:           nVal = (int64_t) Value->Value.DateTime; break;
        case TYPE_TOD:          return 0;
        case TYPE_STRING:       
        case TYPE_WSTRING:      
            errno = EINVAL;
            return -1;

        default:
            break;
    }

    if(Value->Type == TYPE_DERIVED) {
        if(Value->Meta)
            free(Value->Meta);
        Value->Meta = NULL;
    }
    Value->Value.DateTime = nVal;
    Value->Maximum.DateTime = 0;
    Value->Minimum.DateTime = 0;
    Value->Length = sizeof(Value->Value.DateTime);
    Value->Type = Value->Cast = TYPE_TOD;
    return 0;
}
