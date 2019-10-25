#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>

#include <function.h>
#include <grammar.h>
#include <lexer.h>
#include <ll.h>
#include <log.h>
#include <parameter.h>
#include <runtime.h>
#include <sha256.h>
#include <standard.h>
#include <strl.h>
#include <tree.h>
#include <value.h>


static int _function_compare(const void *A, const void *B);

static int _function_debug( void *pContext, const char *pName, LL *pParameters, VALUE *pResult );

static void _function_destroy(void *Arg);

static int _function_exit( void *pContext, const char *pName, LL *pParameters, VALUE *pResult );

static FUNCTION_REGISTER * _function_new(const char *Name);

static size_t _function_size(ECHIDNA *Context, _FUNCTION_BLOCK *Function);


static int 
_function_compare(const void *A, const void *B) {
    FUNCTION_REGISTER *pFunctionA, *pFunctionB;

    pFunctionA = *(FUNCTION_REGISTER **) A;
    assert(pFunctionA != NULL);
    pFunctionB = *(FUNCTION_REGISTER **) B;
    assert(pFunctionB != NULL);
    return strcasecmp(pFunctionA->Name, pFunctionB->Name);
}


static int 
_function_debug( void *pContext, const char *pName, LL *pParameters, VALUE *pResult ) {
    PARAMETER *pParameter;
    LL_ITER sIter;
    char sLine[LINE_MAX], sValue[32];
    char *pSeparator;

    sLine[0] = '\0';
    for(pParameter = ll_iterate_first(&sIter, pParameters);
            pParameter;
            pParameter = ll_iterate_next(&sIter)) {

        pSeparator = (strlen(sLine) > 0) ? ", " : "";
        switch(pParameter->Value.Type) {
            case TYPE_LREAL:        snprintf(sValue, sizeof(sValue), "%sLREAL %g", pSeparator, pParameter->Value.Value.Double); break;
            case TYPE_REAL:         snprintf(sValue, sizeof(sValue), "%sREAL %g", pSeparator, pParameter->Value.Value.Single); break;
            case TYPE_LINT:         snprintf(sValue, sizeof(sValue), "%sLINT %lld", pSeparator, (long long int) pParameter->Value.Value.S64); break;
            case TYPE_DINT:         snprintf(sValue, sizeof(sValue), "%sDINT %ld", pSeparator, (long int) pParameter->Value.Value.S32); break;
            case TYPE_INT:          snprintf(sValue, sizeof(sValue), "%sINT %d", pSeparator, pParameter->Value.Value.S16); break;
            case TYPE_SINT:         snprintf(sValue, sizeof(sValue), "%sSINT %d", pSeparator, pParameter->Value.Value.S8); break;
            case TYPE_ULINT:        snprintf(sValue, sizeof(sValue), "%sULINT %llu", pSeparator, (long long unsigned int) pParameter->Value.Value.U64); break;
            case TYPE_UDINT:        snprintf(sValue, sizeof(sValue), "%sUDINT %lu", pSeparator, (long unsigned int) pParameter->Value.Value.U32); break;
            case TYPE_UINT:         snprintf(sValue, sizeof(sValue), "%sUINT %u", pSeparator, pParameter->Value.Value.U16); break;
            case TYPE_USINT:        snprintf(sValue, sizeof(sValue), "%sUSINT %u", pSeparator, pParameter->Value.Value.U8); break;
            case TYPE_LWORD:        snprintf(sValue, sizeof(sValue), "%sLWORD %016llx (%llu)", pSeparator, (long long unsigned int) pParameter->Value.Value.B64, (long long unsigned int) pParameter->Value.Value.B64); break;
            case TYPE_DWORD:        snprintf(sValue, sizeof(sValue), "%sDWORD %08lx (%lu)", pSeparator, (long unsigned int) pParameter->Value.Value.B32, (long unsigned int) pParameter->Value.Value.B32); break;
            case TYPE_WORD:         snprintf(sValue, sizeof(sValue), "%sWORD %04x (%u)", pSeparator, pParameter->Value.Value.B16, pParameter->Value.Value.B16); break;
            case TYPE_BYTE:         snprintf(sValue, sizeof(sValue), "%sBYTE %02x (%u)", pSeparator, pParameter->Value.Value.B8, pParameter->Value.Value.B8); break;
            case TYPE_BOOL:         snprintf(sValue, sizeof(sValue), "%sBOOL %s", pSeparator, pParameter->Value.Value.B1 ? "true" : "false"); break;
            case TYPE_TIME:         snprintf(sValue, sizeof(sValue), "%sTIME %gms", pSeparator, pParameter->Value.Value.Time); break;
            default:
                snprintf(sValue, sizeof(sValue), "%s%08x ", pSeparator, pParameter->Value.Type);
                break;
        }
        strlcat(sLine, sValue, sizeof(sLine));
    }
    if(strlen(sLine) > 0)
        log_debug(sLine);
    return 0;
}


static void 
_function_destroy(void *Arg) {
    FUNCTION_REGISTER *pFunction;

    if((pFunction = (FUNCTION_REGISTER *) Arg) == NULL)
        return;
    if(pFunction->Name)
        free((char *) pFunction->Name);
    free(pFunction);
}


static int
_function_exit(void *Context, const char *Name, LL *Parameters, VALUE *Result) {
    ECHIDNA *pContext;

    /*
        This function (_exit) has been included primarily for development and testing 
        purposes and can be used from within IEC 61131-3 code to exit the virtual 
        machine run-time.
    */

    pContext = ( ECHIDNA * ) Context;
    assert(pContext != NULL);

    log_notice("Exit function called, stopping runtime");
    runtime_stop(pContext->VM);

    return 0;
}


static FUNCTION_REGISTER *
_function_new(const char *Name) {
    FUNCTION_REGISTER *pFunction;

    if((pFunction = (FUNCTION_REGISTER *) calloc(1, sizeof(FUNCTION_REGISTER))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    pFunction->Name = (Name != NULL) ? strdup(Name) : NULL;
    pFunction->Id = 0;
    pFunction->Type = 0;
    pFunction->Block = NULL;
    pFunction->Context = NULL;
    pFunction->Size = 0;

    return pFunction;
}


static size_t 
_function_size(ECHIDNA *Context, _FUNCTION_BLOCK *Function) {
    FUNCTION_BLOCK_FIELD *pField;
    size_t uIndex, uSize;

    assert(Context != NULL);
    assert(Function != NULL);

    uSize = sizeof(uint32_t) * Function->Count;
    for(uIndex = 0; uIndex < Function->Count; ++uIndex) {
        pField = &Function->Fields[uIndex];
        pField->Offset = uSize;
        uSize += value_typetosize(pField->Type);
        if((uSize % Context->Align) != 0)
             uSize += (Context->Align - (uSize % Context->Align));
    }
    Function->Size = uSize;
    return Function->Size;
}


int 
_function_register(size_t Arg, FUNCTIONS *Context, const char *Name, VALUE_TYPE Type, ...) {
    ECHIDNA *pContext;
    FUNCTION_REGISTER *pFunction;
    va_list sArg;
    size_t uBytes;
    int nResult;

    if(Arg < 4)
        return EINVAL;

    assert(Context != NULL);
    pContext = container_of(Context, ECHIDNA, Functions);
    assert(pContext != NULL);
    assert(Name != NULL);

    if(Context->Lock)
        return EPERM;
    if(function_search(Context, Name) != NULL)
        return EEXIST;
    if((pFunction = _function_new(Name)) == NULL)
        return errno;

    nResult = 0;
    va_start(sArg, Type);
    switch(Type) {
        case TYPE_FUNCTION:
            pFunction->Function = va_arg(sArg, _FUNCTION);
            if(Arg > 4) 
                pFunction->Context = va_arg(sArg, void *);
            pFunction->Type = TYPE_FUNCTION;
            break;

        case TYPE_FUNCTION_BLOCK:
            pFunction->Block = va_arg(sArg, _FUNCTION_BLOCK *);
            if(Arg > 4)
                pFunction->Context = va_arg(sArg, void *);
            pFunction->Type = TYPE_FUNCTION_BLOCK;

            /*
                If no explicit size is set for instances of the function block, this is calculated 
                based on the number of fields which are defined in association with the function 
                block. This action also determines the offset location for peristence of each of 
                the function block fields which is important for the resolution of these variables
                within IEC 61131-3 language.

                This determination of function block size allocation and field offsets is only
                performed a single time, irrespective of the number of instances.
            */

            if((pFunction->Size = pFunction->Block->Size) == 0) 
                pFunction->Size = _function_size(pContext, pFunction->Block);
            break;

        default:
            nResult = EINVAL;
            break;
    }
    va_end(sArg);
    if(nResult != 0)
        goto error;

    uBytes = ((Context->Count + 1) * sizeof(FUNCTION_REGISTER *));
    if((Context->Function = realloc(Context->Function, uBytes)) == NULL) {
        log_critical("Failed to allocated memory: %s", strerror(errno));
        nResult = errno;
        goto error;
    }
    Context->Function[Context->Count++] = pFunction;
    qsort(Context->Function, Context->Count, sizeof(FUNCTION_REGISTER *), _function_compare);

    return 0;

error:
    _function_destroy(pFunction);
    return nResult;
}


void 
function_destroy(void *Arg) {
    FUNCTIONS *pFunctions;
    FUNCTION_REGISTER *pFunction;
    int nIndex;

    if((pFunctions = (FUNCTIONS *) Arg) == NULL)
        return;
    if(pFunctions->Count == 0)
        return;
    assert(pFunctions->Function != NULL);
    for(nIndex = 0; nIndex < pFunctions->Count; ++nIndex) {
        if((pFunction = pFunctions->Function[nIndex]) != NULL)
            _function_destroy(pFunction);
    }
    free(pFunctions->Function);
}


void
function_initialise(FUNCTIONS *Context) {
    ECHIDNA *pContext;

    pContext = container_of(Context, ECHIDNA, Functions);
    assert(pContext != NULL);
    Context->Function = NULL;
    Context->Count = 0;
    Context->Lock = 0;
    memset(Context->Signature, 0, sizeof(Context->Signature));

    function_register(Context, "dbg", TYPE_FUNCTION, _function_debug);
    function_register(Context, "_exit", TYPE_FUNCTION, _function_exit, pContext);
    standard_initialise(pContext);
}


FUNCTION_REGISTER * 
function_search(FUNCTIONS *Context, const char *Name) {
    FUNCTION_REGISTER **pFunction, *pIndex, sFunction;

    ( void ) memset(&sFunction, 0, sizeof(sFunction));
    sFunction.Name = Name;

    pIndex = &sFunction;
    pFunction = bsearch(&pIndex, Context->Function, Context->Count, sizeof(FUNCTION_REGISTER *), _function_compare);
    return (pFunction != NULL) ? *pFunction : NULL;
}


void
function_table_build(FUNCTIONS *Context) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    FUNCTION_REGISTER *pFunction;
    SHA256 sDigest;
    char *pPtr, sResult[32];
    size_t uField, uIndex;

    assert(Context != NULL);
    if((Context->Count <= 0) ||
            (Context->Lock > 0))
        return;

    for(uIndex = 0; uIndex < Context->Count; ++uIndex)
        Context->Function[uIndex]->Id = uIndex;
    ++Context->Lock;

    /*
        The following generates a SHA-256 hash based upon function names function 
        block field names and field types. This will be used to ensure compatibility 
        between byte code loaded from an object file and the virtual machine run-time.
    */

    sha256_initialise(&sDigest);
    for(uIndex = 0; uIndex < Context->Count; ++uIndex) {
        pFunction = Context->Function[uIndex];
        assert(pFunction != NULL);
        sha256_update(&sDigest, pFunction->Name, strlen(pFunction->Name) + 1);

        switch(pFunction->Type) {
            case TYPE_FUNCTION_BLOCK:
                pBlock = pFunction->Block;
                assert(pBlock != NULL);
                for(uField = 0; uField < pBlock->Count; ++uField) {
                    pField = &pBlock->Fields[uField];
                    sha256_update(&sDigest, pField->Name, strlen(pField->Name) + 1);
                    sha256_update(&sDigest, (char *) &pField->Type, sizeof(pField->Type));
                }
                break;

            default:
                break;
        }
    }

    pPtr = Context->Signature;
    sha256_final(&sDigest, sResult);
    for(uIndex = 0; uIndex < sizeof(sResult); ++uIndex) 
        pPtr += sprintf(pPtr, "%02x", sResult[uIndex] & 0xff);
}
