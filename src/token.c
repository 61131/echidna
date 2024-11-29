#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#endif
#include <errno.h>
#include <assert.h>

#include <log.h>

#include <token.h>


typedef struct _TOKEN_UNIQUE {

    char * Name;

    size_t Count;
}
TOKEN_UNIQUE;


static void _token_destroy_callback(void *Token);


static void
_token_destroy_callback(void *Token) {
    token_destroy(Token);
}


TOKEN *
_token_cast(size_t Arg, TOKEN *Token, uint32_t Id, ...) {
    va_list sArg;

    if(!Token)
        return NULL;    
    Token->Id = Id;
    
    va_start(sArg, Id);
    if(Arg > 2)
        Token->Line = (uint32_t) va_arg(sArg, int);
    if(Arg > 3)
        Token->Column = (uint32_t) va_arg(sArg, int);
    va_end(sArg);

    return Token;
}


void
_token_destroy(size_t Arg, ...) {
    TOKEN *pToken;
    TOKEN_LIST *pList;
    va_list sArg;

    va_start(sArg, Arg);
    for(; Arg > 0; --Arg) {
        pToken = va_arg(sArg, TOKEN *);
        if(!pToken)
            continue;
        switch(pToken->Type) {
            case TYPE_LIST:
                pList = (TOKEN_LIST *) pToken;
                ll_destroy(&pList->List, _token_destroy_callback);
                /* break; */
            case TYPE_TOKEN:
                if(pToken->Name) 
                    free(pToken->Name);
                value_destroy(&pToken->Value, _token_destroy_callback);
                if(pToken->Alloc) 
                    free(pToken);
                break;

            default:
                break;
        }
    }
    va_end(sArg);
}


TOKEN_LIST *
_token_list_cast(size_t Arg, TOKEN_LIST *List, uint32_t Id, ...) {
    va_list sArg;
    uint32_t uColumn, uLine;

    assert(List != NULL);

    uLine = uColumn = 0;
    va_start(sArg, Id);
    if(Arg > 2)
        uLine = (uint32_t) va_arg(sArg, int);
    if(Arg > 3) 
        uColumn = (uint32_t) va_arg(sArg, int);
    va_end(sArg);

    switch(Arg) {
        case 2:
            return (TOKEN_LIST *) _token_cast(Arg, (TOKEN *) List, Id);
        case 3:
            return (TOKEN_LIST *) _token_cast(Arg, (TOKEN *) List, Id, uLine);
        case 4:
            return (TOKEN_LIST *) _token_cast(Arg, (TOKEN *) List, Id, uLine, uColumn);
        default:
            break;
    }
    return NULL;
}


int
_token_list_insert(size_t Arg, TOKEN_LIST *List, void *Item, ...) {
    va_list sArg;
    int nResult;

    assert(List != NULL);
    if((nResult = ll_insert(&List->List, Item)) != 0)
        return nResult;

    va_start(sArg, Item);
    while(Arg-- > 2) {
        Item = va_arg( sArg, void * );
        if((nResult = ll_insert(&List->List, Item)) != 0)
            break;
    }
    va_end(sArg);

    return nResult;
}


void
_token_list_merge(size_t Arg, TOKEN_LIST *List, ...) {
    TOKEN_LIST *pArg;
    va_list sArg;

    assert(List != NULL);
    va_start(sArg, List);
    while(Arg-- > 1) {
        pArg = va_arg(sArg, TOKEN_LIST *);
        ll_merge(&List->List, &pArg->List);
    }
    va_end(sArg);
}


TOKEN_LIST *
_token_list_new(size_t Arg, ...) {
    TOKEN_LIST *pList;
    va_list sArg;
    char *pStr;

    errno = 0;
    if((pList = calloc(1, sizeof(*pList))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }   
    token_list_initialise(pList);
    va_start(sArg, Arg);
    pList->Token.Id = (uint32_t) va_arg(sArg, int);
    if(Arg > 1)
        pList->Token.Line = (uint32_t) va_arg(sArg, int);
    if(Arg > 2)
        pList->Token.Column = (uint32_t) va_arg(sArg, int);
    if(Arg > 3) {
        pStr = va_arg(sArg, char *);
        pList->Token.Name = (pStr != NULL) ? strdup(pStr) : NULL;
    }
    if(Arg > 4) {
        pStr = va_arg(sArg, char *);
        pList->Token.Scope = (pStr != NULL) ? strdup(pStr) : NULL;
    }
    va_end(sArg);

    ++pList->Token.Alloc;
    return pList;
}


TOKEN *
_token_new(size_t Arg, ...) {
    TOKEN *pToken;
    va_list sArg;
    char *pStr;

    errno = 0;
    if((pToken = calloc(1, sizeof(*pToken))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    token_initialise(pToken);
    va_start(sArg, Arg);
    pToken->Id = (uint32_t) va_arg(sArg, int);
    if(Arg > 1)
        pToken->Line = (uint32_t) va_arg(sArg, int);
    if(Arg > 2)
        pToken->Column = (uint32_t) va_arg(sArg, int);
    if(Arg > 3) {
        pStr = va_arg(sArg, char*);
        pToken->Name = (pStr != NULL) ? strdup(pStr) : NULL;
    }
    if(Arg > 4) {
        pStr = va_arg(sArg, char*);
        pToken->Scope = (pStr != NULL) ? strdup(pStr) : NULL;
    }
    va_end(sArg);

    ++pToken->Alloc;
    return pToken;
}


void
token_initialise(TOKEN *Token) {
    if(!Token)
        return;
    value_initialise(&Token->Value);
    Token->Id = 0;
    Token->Line = 0;
    Token->Column = 0;
    Token->Name = NULL;
    Token->Scope = NULL;
    Token->Type = TYPE_TOKEN;
    Token->Alloc = 0;
}


TOKEN_LIST * 
token_list_convert(TOKEN *Token) {
    TOKEN_LIST *pList;

    errno = 0;
    if((pList = realloc(Token, sizeof(TOKEN_LIST))) == NULL) {
        log_critical("Failed to allcoate memory: %s", strerror(errno));
        return NULL;
    }
    ll_initialise(&pList->List);
    pList->Token.Type = TYPE_LIST;
    return pList;
}


void
token_list_initialise(TOKEN_LIST *List) {
    if(!List)
        return;
    token_initialise((TOKEN *) List);
    ll_initialise(&List->List);
    List->Token.Type = TYPE_LIST;
}


TOKEN *
token_list_iterate(TOKEN_LIST *List) {
    return (TOKEN *) ll_iterate(&List->List);
}


void
token_list_reset(TOKEN_LIST *List) {
    ll_reset(&List->List);
}


int
token_list_unique(TOKEN_LIST *List) {
    TOKEN *pToken;
    TOKEN_UNIQUE *sMap;
    size_t uCount, uIndex;
    int nResult;

    /*
        This function has been implemented to encapsulate the checking of a token list 
        for duplicates based on token name. The primary intended use-case for this C
        function is in association with validating parameters passed to IEC 61131-3 
        functions and allows for an additional validation step at the time of byte
        code compilation.
    */

    sMap = NULL;
    uCount = 0;

    ll_reset(&List->List);
    while((pToken = ll_iterate(&List->List)) != NULL) {
        assert(pToken->Name != NULL);
        nResult = ENOENT;
        for(uIndex = 0; uIndex < uCount; ++uIndex) {
            if(strcasecmp(sMap[uIndex].Name, pToken->Name) == 0) {
                ++sMap->Count;
                nResult = 0;
                break;
            }
        }
        if(nResult == 0)
            continue;

        if((sMap = realloc(sMap, (uCount + 1) * sizeof(TOKEN_UNIQUE))) == NULL) {
            nResult = -1;
            goto error;
        }
        sMap[uCount].Name = pToken->Name;
        sMap[uCount].Count = 1;
        ++uCount;
    }

    nResult = 0;
    for(uIndex = 0; uIndex < uCount; ++uIndex) {
        if(sMap[uIndex].Count == 1)
            ++nResult;
    }

error:
    if(sMap != NULL) 
        free(sMap);
    return nResult;
}

