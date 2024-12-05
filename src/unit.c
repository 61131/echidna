#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <block.h>
#include <echidna.h>
#include <ll.h>
#include <log.h>
#include <unit.h>


void
_unit_initialise(size_t Arg, UNIT *POU, ...) {
    va_list sArg;
    char *pName, *pParam;

    block_initialise(&POU->Block);
    ll_initialise(&POU->Symbols);
    POU->Config = POU->Resource = POU->POU = NULL;
    POU->Size = 0;
    POU->Alloc = 0;

    if(Arg < 2)
        return;

    va_start(sArg, POU);
    switch(Arg) {
        case 4:
            if((pParam = va_arg(sArg, char *)) != NULL)
                POU->Config = strdup(pParam);
            /* break; */
        case 3:
            if((pParam = va_arg(sArg, char *)) != NULL)
                POU->Resource = strdup(pParam);
            /* break; */
        case 2:
            if((pParam = va_arg(sArg, char *)) != NULL)
                POU->POU = strdup(pParam);
            break;

        default:
            break;
    }
    va_end(sArg);

    if(POU->POU != NULL) {
        if((pName = symbol_build_path(POU->Config, POU->Resource, POU->POU)) != NULL)
            block_name(&POU->Block, pName);
    }
}


int
unit_compare(void *A, void *B) {
    return block_compare(A, B);
}


UNIT *
unit_create(char *Config, char *Resource, char *Name) {
    UNIT *pPOU;

    pPOU = unit_new();
    if (pPOU != NULL)
    {
      unit_initialise(pPOU, Config, Resource, Name);
      pPOU->Alloc = 1;
    }
    return pPOU;
}


void
unit_destroy(void *Arg) {
    BLOCK *pBlock;
    UNIT *pPOU;

    if((pPOU = (UNIT *) Arg) == NULL)
        return;

    ll_destroy(&pPOU->Symbols, NULL);
    if(pPOU->Config)
        free(pPOU->Config);
    if(pPOU->Resource)
        free(pPOU->Resource);
    if(pPOU->POU)
        free(pPOU->POU);
    pBlock = &pPOU->Block;
    if(pBlock->Name)
        free(pBlock->Name);
    block_destroy(pBlock);

    if(pPOU->Alloc)
        free(pPOU);
}


UNIT *
unit_new(void) {
    UNIT *pPOU;

    errno = 0;
    if((pPOU = (UNIT *) calloc(1, sizeof(UNIT))) == NULL) {
        log_critical("Failed to allocate memory: %s", strerror(errno));
        return NULL;
    }
    unit_initialise(pPOU);
    pPOU->Alloc = 1;
    return pPOU;
}


