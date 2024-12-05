#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#else
#include "deps.h"
#endif
#include <errno.h>
#include <limits.h>
#include <assert.h>

#include <echidna.h>
#include <grammar.h>
#include <log.h>
#include <runtime.h>
#include <strl.h>
#include <symbol.h>

#include <json.h>


static inline int _MIN(int A, int B) { if(A < B) { return A; } return B; }

static uint32_t _symbol_calculate_offset(ECHIDNA *Context);

static int _symbol_calculate_size(ECHIDNA *Context);

static int _symbol_compare_symbol(const void *A, const void *B);

static int _symbol_field_offset(ECHIDNA *Context, SYMBOL *Symbol);

static int _symbol_function_block(ECHIDNA *Context, SYMBOL *Symbol);

static int _symbol_initialise(SYMBOL *Symbol, char *Configuration, char *Resource, char *POU, char *Name);

static int _symbol_instantiate(ECHIDNA *Context, char *Configuration, char *Resource, char *POU, char *Name);

static int _symbol_instantiate_internal(ECHIDNA *Context);

static SYMBOL * _symbol_search(ECHIDNA *Context, char *Configuration, char *Resource, char *POU, char *Name); 

static size_t _symbol_size(ECHIDNA *Context, SYMBOL *Symbol);


static uint32_t
_symbol_calculate_offset(ECHIDNA *Context) {
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol;
    uint32_t uId, uLength, uNumber, uOffset;
    int nIndex;

    pSymbols = &Context->Symbols;
    uId = uOffset = 0;

    for(nIndex = 0; nIndex < pSymbols->Count; ++nIndex) {
        pSymbol = pSymbols->Symbol[nIndex];
        pSymbol->Id = uId++;

        /*
            If the name of the symbol includes a fullstop-separator, it is assumed that 
            this symbol is a field associated with a function block instance. The task of 
            calculating the offset for this symbol is then delegated to the _symbol_field_offset 
            function.
        */

        if(strchr(pSymbol->Name, '.') != NULL) {
            pSymbol->Offset = _symbol_field_offset(Context, pSymbol);
            continue;
        }
        else 
            pSymbol->Offset = uOffset;

        uNumber = 1;
        if((pSymbol->Value.Flags & FLAG_ARRAY) != 0)
            uNumber = pSymbol->Value.Index.Upper - pSymbol->Value.Index.Lower + 1;

        uLength = pSymbol->Value.Length;
        for(; uNumber > 0; --uNumber) {
            uOffset += uLength;
            if((uOffset % Context->Align) != 0) 
                uOffset += (Context->Align - (uOffset % Context->Align));
        }
    }

    pSymbols->Size = uOffset;
    return pSymbols->Size;
}


static int
_symbol_calculate_size(ECHIDNA *Context) {
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol = NULL;
    SYMBOL_STACK *pStack, sStack[SYMBOL_STACK_MAX];
    uint32_t uIndex, uSize;
    int nIndex, nStack;

    /*
        This function is intended to calculate the amount of memory which needs to be 
        reserved for each function block and program instance. For this operation, 
        the code iterates through all program, function and function block program
        organisation units building a list in which their respective sizes must be
        resolved in order to allow for calculation of the total size required for 
        each.
    */

    memset(&sStack, 0, sizeof(sStack));
    pSymbols = &Context->Symbols;
    nStack = 0;
    do {
        pStack = &sStack[nStack];
        for(; sStack[nStack].Index < pSymbols->Count; 
                ++sStack[nStack].Index) {

            uIndex = sStack[nStack].Index;
            pSymbol = pSymbols->Symbol[uIndex];

            if(pSymbol->Configuration || pSymbol->Resource)
                continue;
            if((pStack->POU) &&
                    (strcasecmp(pStack->POU, pSymbol->POU) != 0))
                continue;
            if((uSize = _symbol_size(Context, pSymbol)) > 0) {
                pStack->Size += uSize;
                continue;
            }

            /*
                This point is reached when a function block instance of unknown size is 
                encountered in the symbol table. Prior to pushing this onto the stack to 
                determine the corresponding symbol table size, a test for circular
                function references is performed.
            */

            for(nIndex = 1; nIndex < nStack; ++nIndex) {
                if(strcmp(sStack[nIndex].POU, pSymbol->POU) == 0) {
                    log_error("Circular reference in %s", pSymbol->POU);
                    return -1;
                }
            }
            if(++nStack >= SYMBOL_STACK_MAX) {
                log_critical("Symbol stack exhausted, aborting execution");
                return ENOMEM;
            }

            memset(&sStack[nStack], 0, sizeof(SYMBOL_STACK));
            sStack[nStack].POU = pSymbol->Value.Meta;
            sStack[nStack++].Symbol = pSymbol;
            break;
        }
        if((pSymbol == NULL) &&
                (pStack->POU != NULL)) {
            pStack->Symbol->Value.Length = pStack->Size;
        }
    }
    while(--nStack >= 0);

    return 0;
}


static int 
_symbol_compare_symbol(const void *A, const void *B) {
    SYMBOL *pSymbolA, *pSymbolB;

    pSymbolA = *(SYMBOL **) A;
    assert(pSymbolA != NULL);
    pSymbolB = *(SYMBOL **) B;
    assert(pSymbolB != NULL);
    return strcasecmp(pSymbolA->Path, pSymbolB->Path);
}


static int
_symbol_field_offset(ECHIDNA *Context, SYMBOL *Symbol) {
    FUNCTION_BLOCK_FIELD *pField;
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_REGISTER *pFunction;
    SYMBOL *pSymbol;
    char sName[SYMBOL_NAME_MAX];
    char *pPtr;
    size_t uIndex;

    assert(Context != NULL);
    assert(Symbol != NULL);
    assert(Symbol->Name != NULL);

    strcpy(sName, Symbol->Name);
    pPtr = strchr(sName, '.');
    assert(pPtr != NULL);
    *pPtr++ = '\0';

    if((pSymbol = _symbol_search(Context, Symbol->Configuration, 
            Symbol->Resource, 
            Symbol->POU, 
            sName)) == NULL)
        return 0;

    switch(pSymbol->Value.Type) {
        case TYPE_FUNCTION_BLOCK:
            pFunction = pSymbol->Function;
            assert(pFunction != NULL);
            pBlock = pFunction->Block;
            assert(pBlock != NULL);

            for(uIndex = 0; uIndex < pBlock->Count; ++uIndex) {
                pField = &pBlock->Fields[uIndex];
                assert(pField != NULL);
                if(strcasecmp(pPtr, pField->Name) == 0)
                    return pSymbol->Offset + pField->Offset;
            }
            break;

        default:
            assert(0);
    }

    return 0;
}


static int
_symbol_function_block(ECHIDNA *Context, SYMBOL *Symbol) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    FUNCTION_REGISTER *pFunction;
    RUNTIME *pRun;
    SYMBOL *pSymbol;
    char sName[SYMBOL_NAME_MAX];
    char *pInstance;
    size_t uIndex, uOffset;
    
    /*
        This function is intended to populate the header portion of the memory space 
        allocated for function blocks. This header portion contains either a field 
        symbol identifier (for input and output parameters to the function block) or 
        field value type identifier (for internal only parameters of the function
        block). This is primarily so that changes to symbol types within the function
        block code can be reflected in the calling IEC 61131-3 language code and to
        allow conversion of generic value types (such as ANY, ANY_NUM, etc) into 
        usable variable types within the function block and calling code.
    */

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->VM;
    assert(Symbol != NULL);
    pInstance = &pRun->Memory[Symbol->Offset];
    pFunction = Symbol->Function;
    assert(pFunction != NULL);
    pBlock = pFunction->Block;
    assert(pBlock != NULL);

    for(uIndex = 0; uIndex < pBlock->Count; ++uIndex) {
        pField = &pBlock->Fields[uIndex];
log_debug("%u: %s, %08x", uIndex, pField->Name, pField->Type);
        uOffset = sizeof(uint32_t) * uIndex;
        if((pField->Type & TYPE_IN_OUT) == 0) {

            /*
                Note that for symbols intended to be wholly internal to the function block, 
                the type of this variable is stored in the function block instance header 
                (rather than symbol identifier as performed for input and output variables). 
                This is because no symbols are instantiated for external reference of symbols 
                internal to the function block.
            */

            assert(sizeof(int32_t) == sizeof(VALUE_TYPE));
            memcpy(&pInstance[uOffset], &pField->Type, sizeof(VALUE_TYPE));
        }
        else {
            snprintf(sName, sizeof(sName), "%s.%s", Symbol->Name, pField->Name);
            if((pSymbol = symbol_search(Context, Symbol->Configuration,
                    Symbol->Resource,
                    Symbol->POU,
                    sName)) == NULL)
                continue;   //  This should never be the case

            memcpy(&pInstance[uOffset], &pSymbol->Id, sizeof(int32_t));
        }
    }
    return 0;
}


static int
_symbol_initialise(SYMBOL *Symbol, char *Configuration, char *Resource, char *POU, char *Name) {
    assert(Symbol != NULL);
    Symbol->Id = Symbol->Offset = -1;
    Symbol->Ref = 0;
    Symbol->Configuration = NULL;
    Symbol->Resource = NULL;
    Symbol->POU = NULL;
    Symbol->Name = NULL;
    Symbol->Function = Symbol->Context = NULL;
    value_initialise(&Symbol->Value);

    if((Symbol->Name = strdup(Name)) == NULL) 
        goto error;

    if(Configuration != NULL) {
        if((Symbol->Configuration = strdup(Configuration)) == NULL)
            goto error;
    }
    if(Resource != NULL) {
        if((Symbol->Resource = strdup(Resource)) == NULL)
            goto error;
    }
    if(POU != NULL) {
        if((Symbol->POU = strdup(POU)) == NULL)
            goto error;
    }

    if((Symbol->Path = symbol_build_path(Configuration, Resource, POU, Name)) == NULL)
        goto error;

    return 0;

error:
    log_critical("Failed to allocate memory: %s", strerror(errno));
    return errno;
}


static int
_symbol_instantiate(ECHIDNA *Context, char *Configuration, char *Resource, char *POU, char *Name) {
    LL sLL;
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol;
    uint32_t uIndex;
    int nResult;
    
    /*
        The following code creates an instance of a program organisation unit within 
        a configuration resource. This is performed by iterating through all symbols, 
        identifying those associated with the definition of given program 
        organisation unit (as opposed to those already associated with another 
        instance of the same program organisation unit) and creating list of these 
        for subsequent creation in the context of the specific configuration 
        resource.
    */

    ll_initialise(&sLL);
    nResult = 0;

    pSymbols = &Context->Symbols;
    for(uIndex = 0; uIndex < pSymbols->Count; ++uIndex) {
        pSymbol = pSymbols->Symbol[uIndex];
        if((pSymbol->Configuration != NULL) ||
                (pSymbol->Resource != NULL) ||
                (strcmp(pSymbol->POU, POU) != 0) ||
                (strchr(pSymbol->Name, '.') != NULL))
            continue;

        if((nResult = ll_insert(&sLL, pSymbol)) != 0) {
            ll_destroy(&sLL);
            return nResult;
        }
    }

    ll_reset(&sLL);
    while((pSymbol = ll_iterate(&sLL)) != NULL) {
        if((nResult = symbol_insert(Context,
                Configuration, 
                Resource, 
                Name, 
                pSymbol->Name, &pSymbol->Value)) != 0) 
            break;
    }

    ll_destroy(&sLL, NULL);
    return nResult;
}


static int 
_symbol_instantiate_internal(ECHIDNA *Context) {
    TOKEN_LIST *pStack[4];
    TOKEN *pToken;
    int nId[4] = {
            CONFIGURATION,
            RESOURCE,
            TASK,
            0,
    };
    char *pName, sName[LINE_MAX];
    int nResult, nSize, nStack;

    /*
        This function is intended to instantiate special (or hidden) values within 
        the symbol table that are used as the data source for single and interval 
        configuration parameters associated with task declarations. Where a variable 
        has already been defined as data source for these parameters, no action is 
        required.

            <Resource>:<Task>:INTERVAL
            <Resource>:<Task>:SINGLE
    */

    nSize = (sizeof(nId) / sizeof(nId[0]));
    pStack[0] = &Context->Parse.Tokens;
    token_list_reset(pStack[0]);
    for(nStack = 0; nStack >= 0; --nStack) {
        while((pToken = token_list_iterate(pStack[nStack])) != NULL) {
            if(nId[nStack] == 0) {
                switch(pToken->Id) {
                    case INTERVAL:  pName = "INTERVAL"; if(0) {
                    case SINGLE:    pName = "SINGLE"; }
                        if(pToken->Name != NULL)
                            continue;

                        snprintf(sName, sizeof(sName), "%s:%s:%s",
                                TOKEN_NAME(&pStack[2]->Token),
                                TOKEN_NAME(&pStack[3]->Token),
                                pName);
                        if((nResult = symbol_insert(Context,
                                TOKEN_NAME(&pStack[1]->Token),
                                NULL,
                                NULL,
                                sName, &pToken->Value)) != 0)
                            return nResult;
                        continue;

                    case PRIORITY:
                    default:
                        continue;
                }
            }
            else if(pToken->Id != nId[nStack])
                continue;

            if(nStack < (nSize - 1)) {
                /* assert(pToken->Type == TYPE_LIST); */
                pStack[++nStack] = (TOKEN_LIST *) pToken;
                token_list_reset(pStack[nStack]);
                continue;
            }
        }
    }

    return 0;
}


static SYMBOL * 
_symbol_search(ECHIDNA *Context, char *Configuration, char *Resource, char *POU, char *Name) {
    SYMBOLS *pSymbols;
    SYMBOL *pIndex, **pSymbol, sSymbol;

    pSymbols = &Context->Symbols;
    pSymbol = NULL;

    memset(&sSymbol, 0, sizeof(sSymbol));
    if((sSymbol.Path = symbol_build_path(Configuration, Resource, POU, Name)) == NULL)
        return NULL;
    pIndex = &sSymbol;
    pSymbol = bsearch(&pIndex, pSymbols->Symbol, pSymbols->Count, sizeof(SYMBOL *), _symbol_compare_symbol);
    free(sSymbol.Path);
    return (pSymbol != NULL) ? *pSymbol : NULL;
}


static size_t
_symbol_size(ECHIDNA *Context, SYMBOL *Symbol) {
    FUNCTION_REGISTER *pFunction;
    size_t uElements, uSize;

    assert(Context != NULL);
    assert(Symbol != NULL);

    uSize = 0;
    switch(Symbol->Value.Type) {
        case TYPE_FUNCTION_BLOCK:

            /*
                If the symbol represents an instance of a function block, the corresponding 
                size of memory block required for all variables should be returned. If the 
                function block is written in an IEC 61131-3 language however, this function 
                will return a size of zero - This will cause this function block to be added 
                to the stack of program organisation units that is iterated in order to 
                determine their respective size requirements.
            */

            if((pFunction = function_search(&Context->Functions, (const char *) Symbol->Value.Meta)) == NULL)
                return 0;
            Symbol->Value.Length = pFunction->Size;
            Symbol->Function = pFunction;
            /* break; */

        default:
            /* assert(value_typetosize(Symbol->Value.Type) == Symbol->Value.Length); */
            uSize = Symbol->Value.Length;
            break;
    }

    if(Symbol->Value.Flags & FLAG_ARRAY) {
        uElements = Symbol->Value.Index.Upper - Symbol->Value.Index.Lower + 1;
        if((uSize % Context->Align) != 0)
            uSize += (Context->Align - (uSize % Context->Align));
        uSize *= uElements;
    }
    return uSize;
}


char *
_symbol_build_path(size_t Arg, ...) {
    va_list sArg;
    char sPath[LINE_MAX];
    char *pValue;

    sPath[0] = '\0';
    va_start(sArg, Arg);
    for(; Arg > 0; --Arg) {
        if((pValue = va_arg(sArg, char *)) == NULL)
            continue;
        if(strlen(sPath) > 0)
            strlcat(sPath, ".", sizeof(sPath));
        strlcat(sPath, pValue, sizeof(sPath));
    }
    va_end(sArg);
    return strdup(sPath);
}


int
_symbol_split_path(size_t Arg, char *Path, ...) {
    va_list sArg;
    char sPath[LINE_MAX];
    char *pChar, **pValue[4];
    int nCount, nIndex;

    if((Path == NULL) ||
            (Arg < 2))
        return -EINVAL;

    memset(sPath, 0, sizeof(sPath));
    strcpy(sPath, Path);

    va_start(sArg, Path);
    for(nCount = 0; Arg > 1; --Arg)
        pValue[nCount++] = va_arg(sArg, char **);
    va_end(sArg);

    for(nIndex = 0; nIndex < nCount; ++nIndex)
        *pValue[nIndex] = NULL;

    while(nIndex >= 0) {
        if((pChar = strrchr(sPath, '.')) == NULL) {
            *pValue[--nIndex] = strdup(sPath);
            break;
        }
        *pValue[--nIndex] = strdup(pChar + 1);
        *pChar = '\0';
    }
    return 0;
}


int
_symbol_table_initialise(size_t Arg, ECHIDNA *Context, ...) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_REGISTER *pFunction;
    RUNTIME *pRun;
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol;
    va_list sArg;
    char *pValue, *pValues[3];
    size_t uCount, uIndex, uScope;
    int nResult;

    /*
        This function is intended to initialise the symbols associated with a 
        configuration, resource or program organisation unit to their initial values. 
        The determination as to the level of initialisation to perform is based upon 
        the number of arguments passed to this function. Note that all variables 
        associated with independent program organisation units (POUs), identifiable 
        by the lack of configuration parameter, are always initialised.
    */

    if((Arg < 2) || (Arg > 4))
        return -EINVAL;

    nResult = 0;
    uCount = (Arg - 1);
    va_start(sArg, Context);
    for(uIndex = 0; uIndex < uCount; ++uIndex) {
        if((pValues[uIndex] = va_arg(sArg, char *)) == NULL) {
            nResult = EINVAL;
            break;
        }
    }
    va_end(sArg);

    if(nResult != 0)
        return nResult;

    pRun = (RUNTIME *) Context->VM;
    pSymbols = &Context->Symbols;
    for(uIndex = 0; uIndex < pSymbols->Count; ++uIndex) {
        pSymbol = pSymbols->Symbol[uIndex];
        if(pSymbol->Configuration) {
            for(uScope = 0; uScope < uCount; ++uScope) {
                assert(pValues[uScope] != NULL);
                switch(uScope) {
                    case 0:     pValue = pSymbol->Configuration; break;
                    case 1:     pValue = pSymbol->Resource; break;
                    case 2:     pValue = pSymbol->POU; break;
                    default:
                        pValue = NULL;
                        break;
                }
                if(pValue == NULL)
                    break;
                if(strcasecmp(pValues[uScope], pValue) != 0)
                    break;
            }
            if(uScope < uCount)
                continue;
        }

        switch(pSymbol->Value.Type) {
            case TYPE_FUNCTION_BLOCK:
                pFunction = pSymbol->Function;
                assert(pFunction != NULL);
                pBlock = pFunction->Block;
                assert(pBlock != NULL);
log_debug("%s: pSymbol->Name %s, %s", __func__, pSymbol->Name, pSymbol->Path);
                _symbol_function_block(Context, pSymbol);

                if(pBlock->Initialise != NULL) 
                    pSymbol->Context = pBlock->Initialise(Context, pBlock, &pRun->Memory[pSymbol->Offset], pFunction->Context);
                else
                    pSymbol->Context = pFunction->Context;

                break;

            default:
                memcpy(&pRun->Memory[pSymbol->Offset], &pSymbol->Value.Value.Pointer, pSymbol->Value.Length);
                break;
        }
    }

    return 0;
}


/*
    This function is intended to permit iteration through symbols instantiated in 
    the symbol table, filtering for symbols specific to a given configuration, 
    resource and/or program organisation unit. This functionality is used in 
    association with program organisation unit and the stashing of current symbol 
    values on incrementing of the execution stack.
*/

SYMBOL *
_symbol_table_iterate(size_t Arg, ECHIDNA *Context, ...) {
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol;
    va_list sArg;
    char *pConfig, *pResource, *pPOU;

    assert(Context != NULL);
    pSymbols = (SYMBOLS *) &Context->Symbols;
    assert(pSymbols != NULL);

    if(pSymbols->Count == 0)
        return NULL;

    pConfig = pResource = pPOU = NULL;
    if(Arg > 1) {
        va_start(sArg, Context);
        pConfig = va_arg(sArg, char *);
        if(Arg > 2)
            pResource = va_arg(sArg, char *);
        if(Arg > 3)
            pPOU = va_arg(sArg, char *);
        va_end(sArg);
    }

    while(pSymbols->Index < pSymbols->Count) {
        pSymbol = pSymbols->Symbol[pSymbols->Index++];
        assert(pSymbol != NULL);

        /*
            The following ignore symbols which do not match the configuration, resource 
            and program organisation unit filter parameters passed to this function; are 
            representative of function block or structure members; and/or are without 
            reference in application bytecode.
        */

        if(pConfig != NULL) {
            if((pSymbol->Configuration == NULL) ||
                    (strcasecmp(pSymbol->Configuration, pConfig) != 0))
                continue;
        }
        if(pResource != NULL) {
            if((pSymbol->Resource == NULL) ||
                    (strcasecmp(pSymbol->Resource, pResource) != 0))
                continue;
        }
        if(pPOU != NULL) {
            if((pSymbol->POU == NULL) ||
                    (strcasecmp(pSymbol->POU, pPOU) != 0))
                continue;
        }

        if(strchr(pSymbol->Name, '.') != NULL)
            continue;
        if(pSymbol->Ref == 0)
            continue;

        return pSymbol;
    }
    return NULL;
}


void
symbol_destroy(ECHIDNA *Context, SYMBOL *Symbol) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_REGISTER *pFunction;
    RUNTIME *pRun;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->VM;
    assert(Symbol != NULL);

    if((pFunction = Symbol->Function) != NULL) {
        assert(pFunction->Type == TYPE_FUNCTION_BLOCK);
        pBlock = pFunction->Block;
        assert(pBlock != NULL);
        if(pBlock->Destroy != NULL)
            pBlock->Destroy(Context, &pRun->Memory[Symbol->Offset], Symbol->Context);
    }
    free(Symbol->Path);
    free(Symbol->POU);
    free(Symbol->Resource);
    free(Symbol->Configuration);
    free(Symbol->Name);
//    free(Symbol);
}


int
symbol_insert(ECHIDNA *Context, char *Config, char *Resource, char *POU, char *Name, VALUE *Value) {
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    SYMBOLS *pSymbols;
    SYMBOL *pSymbol;
    VALUE sValue;
    char sName[SYMBOL_NAME_MAX];
    size_t uIndex, uBytes;
    SYMBOL** pNew;

    assert(Context != NULL);
    assert(Name != NULL);

    if(_symbol_search(Context, Config, Resource, POU, Name) != NULL)
        return EEXIST;

    errno = 0;
    if((pSymbol = calloc(1, sizeof(SYMBOL))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return errno;
    }
    if(_symbol_initialise(pSymbol, Config, Resource, POU, Name) != 0)
        goto error;

    if(Value) {
        value_copy(&pSymbol->Value, Value);
        switch(pSymbol->Value.Type) {
            case TYPE_FUNCTION_BLOCK:

                /*
                    If the symbol is an instance of a function block, a pointer is stored to the 
                    function block type definition and a series of additional symbols are created 
                    within the same scope, representative of the public member fields of the 
                    function block instance.
                */

                pSymbol->Function = function_search(&Context->Functions, (const char *) pSymbol->Value.Meta);
                if(pSymbol->Function == NULL) {
                    errno = ENOENT;
                    goto error;
                }
                pBlock = pSymbol->Function->Block;
                assert(pBlock != NULL);

                for(uIndex = 0; uIndex < pBlock->Count; ++uIndex) {
                    pField = &pBlock->Fields[uIndex];
                    assert(pField != NULL);
                    if((pField->Type & TYPE_IN_OUT) == 0)
                        continue;

                    snprintf(sName, sizeof(sName), "%s.%s", Name, pField->Name);
                    value_initialise(&sValue);
                    value_assign(&sValue, (pField->Type & ~ANY_INTERNAL));

                    if(symbol_insert(Context, pSymbol->Configuration,
                            pSymbol->Resource,
                            pSymbol->POU,
                            sName, &sValue) != 0)
                        goto error;
                }
                break;

            default:
                break;
        }
    }

    pSymbols = &Context->Symbols;
    uBytes = ((pSymbols->Count + 1) * sizeof(SYMBOL *));

    errno = 0;
    pNew = realloc(pSymbols->Symbol, uBytes);
    if(pNew == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        goto error;
    }
    pSymbols->Symbol = pNew;
    pSymbols->Symbol[pSymbols->Count++] = pSymbol;
    qsort(pSymbols->Symbol, pSymbols->Count, sizeof(SYMBOL *), _symbol_compare_symbol);

    return 0;

error:
    symbol_destroy(Context, pSymbol);
    return errno;
}


SYMBOL * 
symbol_search(ECHIDNA *Context, char *Configuration, char *Resource, char *POU, char *Name) {
    SYMBOL *pSymbol, sSymbol;

    memset(&sSymbol, 0, sizeof(sSymbol));
    for(pSymbol = NULL;;) {
        if((pSymbol = _symbol_search(Context, Configuration, Resource, POU, Name)) != NULL)
            return pSymbol;

        /*
            The permitted loop-escape conditions are - a) the requested symbol has been 
            found, or b) the search performed was already performed at a configuration 
            level, indicated by either of the resource of program organisation unit 
            (POU) strings being undefined.
        */

        if((Resource == NULL) ||
                (POU == NULL))
            return NULL;
        Resource = NULL;
        POU = NULL;
    }
}


int 
symbol_table_build(ECHIDNA *Context) {
    TOKEN_LIST *pStack[3];
    TOKEN *pToken;
    int nId[3] = {
            CONFIGURATION,
            RESOURCE,
            PROGRAM,
    };
    int nResult, nSize, nStack;

    /*
        The following code iterates through the parsed token tree for program
        declarations within configuration declarations. This functionality could be
        implemented though nested loop iterations, recursive function calls or as
        performed in the code below, through stack-based loop iteration.
    */

    if(((nResult = _symbol_instantiate_internal(Context)) != 0) ||
            ((nResult = _symbol_calculate_size(Context)) != 0))
        return nResult;

    nSize = (sizeof(nId) / sizeof(nId[0]));
    pStack[0] = &Context->Parse.Tokens;
    token_list_reset(pStack[0]);
    for(nStack = 0; nStack >= 0; --nStack) {
        while((pToken = token_list_iterate(pStack[nStack])) != NULL) {
            if(pToken->Id != nId[nStack])
                continue;
            if(nStack < (nSize - 1)) {
                assert(pToken->Type == TYPE_LIST);
                pStack[++nStack] = (TOKEN_LIST *) pToken;
                token_list_reset(pStack[nStack++]);
                break;
            }
            /* assert( nStack == 2 ); */
            _symbol_instantiate(Context,
                    TOKEN_NAME(&pStack[1]->Token),
                    TOKEN_NAME(&pStack[2]->Token),
                    (char *) pToken->Value.Meta,
                    TOKEN_NAME(pToken));
        }
    }
    return _symbol_calculate_offset(Context);
}


void
symbol_table_destroy(ECHIDNA *Context) {
    size_t uIndex;

    assert(Context != NULL);
    if(!Context->Symbols.Symbol)
        return;
    assert(Context->Symbols.Count != 0);
    for(uIndex = 0; uIndex < Context->Symbols.Count; ++uIndex)
        symbol_destroy(Context, Context->Symbols.Symbol[uIndex]);
    free(Context->Symbols.Symbol);
}


void
symbol_table_reset(ECHIDNA *Context) {
    SYMBOLS *pSymbols;

    assert(Context != NULL);
    pSymbols = (SYMBOLS *) &Context->Symbols;
    pSymbols->Index = 0;
}


unsigned int
symbol_table_size(ECHIDNA *Context) {
    SYMBOLS *pSymbols;

    assert(Context != NULL);
    pSymbols = (SYMBOLS *) &Context->Symbols;
    if((pSymbols->Size == 0) &&
            (pSymbols->Count > 0))
        _symbol_calculate_offset(Context);
    return pSymbols->Size;
}



