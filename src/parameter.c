#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#else
#include "deps.h"
#endif
#include <errno.h>
#include <assert.h>

#include <echidna.h>
#include <function.h>
#include <ll.h>
#include <log.h>
#include <parameter.h>
#include <runtime/error.h>
#include <symbol.h>
#include <value.h>


enum { PARAMETER_GET, PARAMETER_SET };


static int _parameter_value(ECHIDNA *Context, int Action, _FUNCTION_BLOCK *Function, char *Instance, const char *Name, VALUE *Value);


static int
_parameter_value(ECHIDNA *Context, int Action, _FUNCTION_BLOCK *Function, char *Instance, const char *Name, VALUE *Value) {
    FUNCTION_BLOCK_FIELD *pField;
    size_t uIndex;

    assert(Instance != NULL);
    assert(Function != NULL);
    assert(Name != NULL);
    assert(Value != NULL);

    for(uIndex = 0; uIndex < Function->Count; ++uIndex) {
        pField = &Function->Fields[uIndex];
        if(strcasecmp(pField->Name, Name) != 0)
            continue;
        switch(Action) {
            case PARAMETER_GET:
                value_assign(Value, (pField->Type & ~ANY_INTERNAL));
                memcpy(&Value->Value.Pointer, &Instance[pField->Offset], Value->Length);
                break;

            case PARAMETER_SET:
                if((pField->Type & Value->Type) != Value->Type)
                    return RT_ERR_PARAMETER_TYPE;
                memcpy(&Instance[pField->Offset], &Value->Value.Pointer, Value->Length);
                break;

            default:
                assert(0);
        }
        return 0;
    }
    return RT_ERR_PARAMETER_UNKNOWN;
}


int
_parameter_read_values(size_t Arg, ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, ...) {
    FUNCTION_BLOCK_FIELD *pField;
    SYMBOL *pSymbol;
    SYMBOLS *pSymbols;
    VALUE *pValue, *pValues;
    VALUE_TYPE uType;
    va_list sArg;
    size_t uIndex;
    int nCount, nId, nSize;

    assert(Context != NULL);
    pSymbols = &Context->Symbols;

    nCount = -1;
    va_start(sArg, Instance);
    switch(Arg) {
        default:
        case 5:
            nCount = va_arg(sArg, int);
            /* break; */
        case 4:
            pValues = va_arg(sArg, VALUE *);
            break;
    }
    va_end(sArg);

    /*
        If execution reaches this point, a pointer to an array of value data structures 
        has been passed to this function should should be populated with the current 
        value of each of the function block member variables. The population of these 
        will be as per the order of field definitions in the original function block 
        registration.
    */

    assert(pValues != NULL);

    for(uIndex = 0; uIndex < Function->Count; ++uIndex) {
        if(uIndex >= (unsigned) nCount) 
            break;
        pField = &Function->Fields[uIndex];
        pValue = &pValues[uIndex];

        memcpy(&nId, &Instance[sizeof(int32_t) * uIndex], sizeof(int32_t));
        if((pField->Type & TYPE_IN_OUT) != 0) {
            assert((unsigned) nId < pSymbols->Count);
            pSymbol = pSymbols->Symbol[nId];
            uType = pSymbol->Value.Type;
        }
        else 
            uType = (unsigned) nId;

        value_initialise(pValue);
        value_assign(pValue, uType);
        if((nSize = value_typetosize(uType)) > 0)
            memcpy(&pValue->Value.Pointer, &Instance[pField->Offset], nSize);
    }

    return 0;
}


int
_parameter_write_values(size_t Arg, ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, ...) {
    FUNCTION_BLOCK_FIELD *pField;
    SYMBOL *pSymbol;
    SYMBOLS *pSymbols;
    VALUE *pValue, *pValues;
    va_list sArg;
    size_t uIndex;
    int nCount, nId;

    nCount = -1;
    pValues = NULL;

    va_start(sArg, Instance);
    switch(Arg) {
        case 5:
            nCount = va_arg(sArg, int);
            /* break; */
        case 4:
            pValues = va_arg(sArg, VALUE *);
            break;

        default:
            break;
    }
    va_end(sArg);

    assert(Context != NULL);
    pSymbols = &Context->Symbols;
    assert(pValues != NULL);

    for(uIndex = 0; uIndex < Function->Count; ++uIndex) {
        if(uIndex >= (unsigned) nCount)
            break;

        pField = &Function->Fields[uIndex];
        pValue = &pValues[uIndex];

        if(pValue->Type == TYPE_NONE)
            continue;
        if((pField->Type & pValue->Type) != pValue->Type) {
            return RT_ERR_PARAMETER_TYPE;
        }

        if((pField->Type & TYPE_IN_OUT) != 0) {
            memcpy(&nId, &Instance[sizeof(int32_t) * uIndex], sizeof(int32_t));
            assert((unsigned) nId < pSymbols->Count);
            pSymbol = pSymbols->Symbol[nId];
            pSymbol->Value.Type = pValue->Type;
        }
        else {
            assert(sizeof(int32_t) == sizeof(VALUE_TYPE));
            memcpy(&Instance[sizeof(int32_t) * uIndex], &pValue->Type, sizeof(VALUE_TYPE));
        }

        memcpy(&Instance[pField->Offset], &pValue->Value.Pointer, pValue->Length);
    }

    return 0;
}


void
parameter_destroy(void *Arg) {
    PARAMETER *pParameter;

    if((pParameter = (PARAMETER *) Arg) == NULL)
        return;
    if(pParameter->Name)
        free((char *) pParameter->Name);
    value_destroy(&pParameter->Value);
}


int
parameter_field_get(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, const char *Name, VALUE *Value) {
    return _parameter_value(Context, PARAMETER_GET, Function, Instance, Name, Value);
}


int
parameter_field_set(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, const char *Name, VALUE *Value) {
    return _parameter_value(Context, PARAMETER_SET, Function, Instance, Name, Value);
}


PARAMETER *
parameter_new(PARAMETER *Parameter) {
    PARAMETER *pParameter;

    errno = 0;
    if((pParameter = calloc(1, sizeof(PARAMETER))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pParameter->Name = NULL;
    value_initialise(&pParameter->Value);

    if(Parameter) {
        if(Parameter->Name)
            pParameter->Name = strdup(Parameter->Name);
        value_copy(&pParameter->Value, &Parameter->Value);
    }
    return pParameter;
}


