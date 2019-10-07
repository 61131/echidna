#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <float.h>

#include <block.h>
#include <config.h>
#include <echidna.h>
#include <grammar.h>
#include <log.h>
#include <protobuf.h>
#include <strl.h>
#include <symbol.h>
#include <unit.h>

#include <json.h>


#define config_program(...)     _config_program(_NARG(__VA_ARGS__), __VA_ARGS__)


static CONFIG * _config_add_config(ECHIDNA *Context, TOKEN *Token);

static CONFIG * _config_add_program(CONFIG *Resource, TOKEN *Token);

static CONFIG * _config_add_resource(CONFIG *Config, TOKEN *Token);

static CONFIG * _config_add_task(CONFIG *Resource, TOKEN *Token);

static void _config_destroy_block(void *Arg);

static void _config_destroy_callback(void *Arg);

static int _config_generate(ECHIDNA *Context);

static int _config_populate_program(ECHIDNA *Context, PROTOBUF_RESOURCE *File, CONFIG *Resource);

static int _config_populate_resource(ECHIDNA *Context, PROTOBUF_CONFIG *File, CONFIG *Config);

static int _config_populate_task(ECHIDNA *Context, PROTOBUF_RESOURCE *File, CONFIG *Resource);

static UNIT * _config_program(size_t Arg, ECHIDNA *Context, ...);


static CONFIG * 
_config_add_config(ECHIDNA *Context, TOKEN *Token) {
    CONFIG *pConfig;
    int nResult;

    if((pConfig = config_new(TYPE_CONFIG, Token->Name)) == NULL)
        return NULL;
    pConfig->Parent = Context;
    if((nResult = ll_insert(&Context->Config, pConfig)) != 0) {
        config_destroy(pConfig);
        pConfig = NULL;
        errno = nResult;
    }
    return pConfig;
}


static CONFIG * 
_config_add_program(CONFIG *Resource, TOKEN *Token) {
    CONFIG *pConfig, *pProgram;
    ECHIDNA *pContext;
    TOKEN *pTask;
    TOKEN_LIST *pList;
    UNIT *pPOU;
    int nResult;

    /*
        The PROGRAM token within the parse tree is a TOKEN_LIST with list elements 
        being tokens specifying program configuration. One such token is TASK which 
        identifies the name of the task with which the program is associated. Note 
        that programs can be defined without task associations which are instead 
        only executed upon resource start.
    */

    pList = (TOKEN_LIST *) Token;
    assert(pList != NULL);

    pTask = NULL;
    token_list_reset(pList);
    while((Token = token_list_iterate(pList)) != NULL) {
        switch(Token->Id) {
            case TASK:  pTask = Token;
            default:
                break;
        }
    }

    assert(Resource != NULL);
    pConfig = (CONFIG *) Resource->Parent;
    assert(pConfig != NULL);
    pContext = (ECHIDNA *) pConfig->Parent;
    assert(pContext != NULL);

    for(Token = (TOKEN *) pList;;) {
        if((pProgram = config_new(TYPE_PROGRAM, Token->Name)) == NULL)
            break;
        pProgram->Parent = Resource;
        pProgram->Task = (pTask != NULL) ? strdup(pTask->Name) : NULL;

        if((pPOU = config_program(pContext, 
                pConfig->Name, 
                Resource->Name, 
                pProgram->Name)) == NULL)
            goto error;

        if((nResult = ll_insert(&Resource->List, pProgram)) != 0)
            goto error;
        if((nResult = ll_insert(&pProgram->List, pPOU)) != 0)
            goto error;

        break;
    }
    return pProgram;

error:
    config_destroy(pProgram);
    return NULL;
}


static CONFIG * 
_config_add_resource(CONFIG *Config, TOKEN *Token) {
    CONFIG *pResource;
    int nResult;

    for(;;) {
        if((pResource = config_new(TYPE_RESOURCE, Token->Name)) == NULL)
            break;
        pResource->Parent = Config;        
        if((nResult = ll_insert(&Config->List, pResource)) != 0) {
            config_destroy(pResource);
            pResource = NULL;
            errno = nResult;
        }
        break;
    }
    return pResource;
}


static CONFIG * 
_config_add_task(CONFIG *Resource, TOKEN *Token) {
    CONFIG *pConfig;
    ECHIDNA *pContext;
    SYMBOL *pSymbol;
    TOKEN *pToken;
    TOKEN_LIST *pList;
    char *pName, *pParam;
    char sName[LINE_MAX];
    int nResult;

    pList = (TOKEN_LIST *) Token;
    assert(Resource != NULL);
    pConfig = (CONFIG *) Resource->Parent;
    assert(pConfig != NULL);
    pContext = (ECHIDNA *) pConfig->Parent;
    assert(pContext != NULL);
    pName = pConfig->Name;

    for(;;) {
        if((pConfig = config_new(TYPE_TASK, Token->Name)) == NULL)
            break;
        pConfig->Parent = Resource;

        pList = (TOKEN_LIST *) Token;
        token_list_reset(pList);
        while((pToken = token_list_iterate(pList)) != NULL) {
            switch(pToken->Id) {
                case PRIORITY:
                    pConfig->Priority = pToken->Value.Value.S64;
                    break;

                case INTERVAL:  pParam = "INTERVAL"; if(0) {
                case SINGLE:    pParam = "SINGLE"; }
                    if(!pToken->Name) {
                        snprintf(sName, sizeof(sName), "%s:%s:%s",
                                Resource->Name,
                                pList->Token.Name,
                                pParam);
                    }
                    else 
                        strcpy(sName, pToken->Name);

                    if((pSymbol = symbol_search(pContext, pName, Resource->Name, pList->Token.Name, sName)) == NULL) 
                        goto error;

                    switch(pToken->Id) {
                        case INTERVAL:  pConfig->Interval = pSymbol; break;
                        case SINGLE:    pConfig->Single = pSymbol; break;
                        default:
                            assert(0);
                    }
                    ++pSymbol->Ref;
                    break;

                default:
                    break;
            }
        }

        if((nResult = ll_insert(&Resource->List, pConfig)) != 0) {
            errno = nResult;
            goto error;
        }
        break;
    }
    return pConfig;

error:
    config_destroy(pConfig);
    return NULL;
}


static void 
_config_destroy_block(void *Arg) {
    BLOCK *pBlock;

    if((pBlock = (BLOCK *) Arg) == NULL) 
        return;
    free(pBlock->Name);
    block_destroy(pBlock);
}

/*
    This function is required in order to allow cascading deletion of CONFIG data 
    structures within a configuration tree. The underlying config_destroy function 
    cannot be used directly as this is merely a macro for the _config_destroy 
    function which does not fit the void( * )( void * ) prototype required for the 
    destroy function argument.
*/

static void
_config_destroy_callback(void *Arg) {
    config_destroy(Arg);
}


static int
_config_generate(ECHIDNA *Context) {
    BLOCK *pBlock, sBlock;
    CONFIG *pConfig, *pElement, *pResource, *pTask;
    LL *pStack[3];
    TREE sTasks;
    char *pName, *pPath;
    int nId[2] = {
            TYPE_TASK,
            TYPE_PROGRAM,
    };
    int nIteration, nResult, nStack;

    /*
        The role of this function is to link task and program items within 
        configuration definitions such that when tasks are executed, there is a 
        ready reference to associated programs. This is a required operation in 
        order for the generated configuration to be usable.
    */

    block_initialise( &sBlock );
    tree_initialise( &sTasks, block_compare );
    pStack[0] = &Context->Config;

    nResult = 0;
    for( nIteration = 0; nIteration < 2; ++nIteration ) {
        ll_reset( pStack[0] );
        for( nStack = 0; nStack >= 0; --nStack ) {
            while( ( pElement = ( CONFIG * ) ll_iterate( pStack[ nStack ] ) ) != NULL ) {
                switch( pElement->Type ) {
                    case TYPE_CONFIG:
                    case TYPE_RESOURCE:
                        pStack[ ++nStack ] = &pElement->List;
                        ll_reset( pStack[ nStack ] );
                        continue;

                    default:
                        break;
                }
                if( pElement->Type != nId[ nIteration ] )
                    continue;

                pResource = pElement->Parent;
                pConfig = pResource->Parent;

                if( ( pName = ( pElement->Type == TYPE_TASK ) ? 
                            pElement->Name : 
                            pElement->Task ) == NULL )
                    continue;
                
                if( ( pPath = symbol_build_path( pConfig->Name, pResource->Name, pName ) ) == NULL ) {
                    nResult = -errno;
                    goto error;
                }

                switch( pElement->Type ) {
                    case TYPE_TASK:
                        if( ( pBlock = block_new() ) == NULL ) {
                            nResult = -errno;
                            goto error;
                        }
                        block_name( pBlock, pPath );
                        block_pointer( pBlock, pElement );
                        if( ( nResult = tree_insert( &sTasks, pBlock ) ) != 0 ) {
                            _config_destroy_block( pBlock );
                            nResult = -errno;
                            goto error;
                        }
                        break;

                    case TYPE_PROGRAM:
                        block_name( &sBlock, pPath );
                        if( ( pBlock = tree_search( &sTasks, &sBlock ) ) == NULL ) {
                            //  This should _never_ occur!
                            free( pPath );
                            nResult = -EFAULT;
                            goto error;
                        }
                        free( pPath );

                        pTask = ( CONFIG * ) block_pointer( pBlock );
                        if( ( nResult = ll_insert( &pTask->List, pElement ) ) != 0 )
                            goto error;

                        break;

                    default:
                        break;
                }
            }
        }
    }

error:
    tree_destroy( &sTasks, _config_destroy_block );
    return nResult;
}


static int 
_config_populate_program(ECHIDNA *Context, PROTOBUF_RESOURCE *File, CONFIG *Resource) {
    CONFIG *pConfig, *pProgram;
    PROTOBUF_PROGRAM *pFile;
    UNIT *pPOU;
    size_t uIndex;
    int nResult;

    assert(Resource != NULL);
    pConfig = (CONFIG *) Resource->Parent;

    assert(File != NULL);
    for(uIndex = 0; uIndex < File->Programs; ++uIndex) {
        pFile = File->Program[uIndex];
        assert(pFile->Name != NULL);
        if((pProgram = config_new(TYPE_PROGRAM, pFile->Name)) == NULL)
            return errno;
        pProgram->Parent = Resource;
        if(pFile->Task != NULL) {
            if((pProgram->Task = strdup(pFile->Task)) == NULL)
                goto error;
        }
        if((pPOU = config_program(Context,
                pConfig->Name,
                Resource->Name,
                pProgram->Name)) == NULL) {
            nResult = errno;
            goto error;
        }

        if((nResult = ll_insert(&pProgram->List, pPOU)) != 0)
            goto error;
        if((nResult = ll_insert(&Resource->List, pProgram)) != 0)
            goto error;
    }

    return 0;

error:
    config_destroy(pProgram);
    return nResult;
}


static int 
_config_populate_resource(ECHIDNA *Context, PROTOBUF_CONFIG *File, CONFIG *Config) {
    CONFIG *pResource;
    PROTOBUF_RESOURCE *pFile;
    size_t uIndex;
    int nResult;

    assert(File != NULL);
    for(uIndex = 0; uIndex < File->Resources; ++uIndex) {
        pFile = File->Resource[uIndex];
        assert(pFile->Name != NULL);
        if((pResource = config_new(TYPE_RESOURCE, pFile->Name)) == NULL) 
            return errno;
        pResource->Parent = Config;
        if((nResult = _config_populate_program(Context, pFile, pResource)) != 0)
            goto error;
        if((nResult = _config_populate_task(Context, pFile, pResource)) != 0) 
            goto error;
        if((nResult = ll_insert(&Config->List, pResource)) != 0)
            goto error;
    }

    return 0;

error:
    config_destroy(pResource);
    return nResult;
}


static int
_config_populate_task(ECHIDNA *Context, PROTOBUF_RESOURCE *File, CONFIG *Resource) {
    CONFIG *pTask;
    PROTOBUF_TASK *pFile;
    SYMBOL *pSymbol;
    SYMBOLS *pSymbols;
    size_t uIndex;
    int nResult;

    assert(File != NULL);
    for(uIndex = 0; uIndex < File->Tasks; ++uIndex) {
        pFile = File->Task[uIndex];
        assert(pFile->Name != NULL);
        if((pTask = config_new(TYPE_TASK, pFile->Name)) == NULL)
            return errno;
        pTask->Parent = Resource;
        pTask->Priority = pFile->Priority;
        pSymbols = &Context->Symbols;
        if(pFile->IncludeSingle) {
            assert(pFile->Single < Context->Symbols.Count);
            pSymbol = pSymbols->Symbol[pFile->Single];
            assert(pSymbol->Value.Type == TYPE_BOOL);
            pTask->Single = pSymbol;
        }
        if(pFile->IncludeInterval) {
            assert(pFile->Interval < Context->Symbols.Count);
            pSymbol = pSymbols->Symbol[pFile->Interval];
            assert(pSymbol->Value.Type == TYPE_TIME);
            pTask->Interval = pSymbol;
        }
        if((nResult = ll_insert(&Resource->List, pTask)) != 0)
            goto error;
    }

    return 0;

error:
    config_destroy(pTask);
    return nResult;
}


UNIT * 
_config_program(size_t Arg, ECHIDNA *Context, ...) {
    BLOCK sBlock;
    UNIT *pPOU;
    va_list sArg;
    char sPath[LINE_MAX];
    char *pValue;

    sPath[0] = '\0';
    va_start(sArg, Context);
    for(; Arg > 1; --Arg) {
        if((pValue = va_arg(sArg, char *)) == NULL)
            continue;
        if(strlen(sPath) > 0)
            strlcat(sPath, ".", sizeof(sPath));
        strlcat(sPath, pValue, sizeof(sPath));
    }
    va_end(sArg);

    block_initialise(&sBlock, sPath);
    pPOU = tree_search(&Context->POU, &sBlock);
    block_destroy(&sBlock);
    return pPOU;
}


void
_config_destroy(size_t Arg, ...) {
    CONFIG *pConfig;
    va_list sArg;

    va_start(sArg, Arg);
    for(; Arg > 0; --Arg) {
        if((pConfig = va_arg(sArg, CONFIG *)) == NULL)
            continue;
        switch(pConfig->Type) {
            case TYPE_CONFIG:
            case TYPE_RESOURCE:
                ll_destroy(&pConfig->List, _config_destroy_callback);
                break;

            case TYPE_TASK:
            case TYPE_PROGRAM:
                ll_destroy(&pConfig->List, NULL);
                break;

            default:
                continue;
        }
        free(pConfig->Task);
        free(pConfig->Name);

        if(pConfig->Alloc)
            free(pConfig);
    }
    va_end(sArg);
}


void
_config_initialise( size_t uArg, CONFIG *pConfig, ... ) {
    CONFIG_TYPE uType;
    char *pName;
    va_list sArg;

    pConfig->Type = /* TYPE_NONE */ 0;
    pConfig->Name = pConfig->Task = NULL;
    pConfig->Interval = pConfig->Single = NULL;
    pConfig->Priority = -1;
    pConfig->Context = NULL;
    ll_initialise( &pConfig->List );
    pConfig->Alloc = 0;

    if( uArg > 1 ) {
        va_start( sArg, pConfig );
        uType = ( CONFIG_TYPE ) va_arg( sArg, CONFIG_TYPE );
        switch( uType ) {
            case TYPE_TASK:
            case TYPE_CONFIG:
            case TYPE_RESOURCE:
            case TYPE_PROGRAM:
                pConfig->Type = uType;
                break;

            default:
                assert(0);
        }
        if( uArg > 2 ) {
            if( ( pName = ( char * ) va_arg( sArg, char * ) ) != NULL )
                pConfig->Name = strdup( pName );
        }
        va_end( sArg );
    }
}


CONFIG *
_config_new( size_t uArg, CONFIG_TYPE uType, ... ) {
    CONFIG *pConfig;
    char *pName;
    va_list sArg;

    if( ( pConfig = ( CONFIG * ) calloc( 1, sizeof( CONFIG ) ) ) == NULL ) 
        return NULL;
    config_initialise( pConfig, uType );
    pConfig->Alloc = 1;

    if( uArg > 1 ) {
        va_start( sArg, uType );
        if( ( pName = ( char * ) va_arg( sArg, char * ) ) != NULL )
            pConfig->Name = strdup( pName );
        va_end( sArg );
    }

    return pConfig;
}


int 
config_generate(ECHIDNA *Context) {
    CONFIG *pConfig, *pResource;
    TOKEN_LIST *pTokens[3];
    TOKEN *pToken;
    int nId[3] = {
            CONFIGURATION,
            RESOURCE,
            0,
    };
    int nSize, nStack;

    /*
        This function will generate a data structure tree representative of the 
        configurations, resources, tasks and programs defined within the parsed 
        source files. While these have been validated within the scope of parsing 
        that valid names have been used for task and program associations, the 
        linking of these within this data structure tree still requires multiple 
        passes to remove dependency on the order of element creation.
    */

    pConfig = pResource = NULL;

    nSize = (sizeof(nId) / sizeof(nId[0]));
    pTokens[0] = &Context->Parse.Tokens;
    token_list_reset(pTokens[0]);
    for(nStack = 0; nStack >= 0; --nStack) {
        while((pToken = token_list_iterate(pTokens[nStack])) != NULL) {
            if(nId[nStack] == 0) {
                switch(pToken->Id) {
                    case PROGRAM:
                    case TASK:
                        break;

                    default:
                        continue;
                }
            }
            else if(pToken->Id != nId[nStack])
                continue;

            switch(pToken->Id) {
                case CONFIGURATION:
                    if((pConfig = _config_add_config(Context, pToken)) == NULL)
                        return -errno;
                    break;

                case RESOURCE:
                    if((pResource = _config_add_resource(pConfig, pToken)) == NULL) 
                        return -errno;
                    break;

                case TASK:
                    if(_config_add_task(pResource, pToken) == NULL) 
                        return -errno;
                    break;

                case PROGRAM:
                    if(_config_add_program(pResource, pToken) == NULL) 
                        return -errno;
                    break;

                default:
                    break;
            }

            if(nStack < (nSize - 1)) {
                pTokens[++nStack] = (TOKEN_LIST *) pToken;
                token_list_reset(pTokens[nStack++]);
                break;
            }
        }
    }

    return _config_generate(Context);
}


int
config_populate(ECHIDNA *Context, PROTOBUF_FILE *File) {
    CONFIG *pConfig;
    PROTOBUF_CONFIG *pFile;
    size_t uIndex;
    int nResult;

    assert(File != NULL);
    for(uIndex = 0; uIndex < File->Configs; ++uIndex) {
        pFile = File->Config[uIndex];
        assert(pFile->Name != NULL);
        if((pConfig = config_new(TYPE_CONFIG, pFile->Name)) == NULL) 
            return errno;
        pConfig->Parent = Context;
        if((nResult = _config_populate_resource(Context, pFile, pConfig)) != 0) 
            goto error;
        if((nResult = ll_insert(&Context->Config, pConfig)) != 0)
            goto error;
    }

    return _config_generate(Context);

error:
    config_destroy(pConfig);
    return nResult;
}


const char *
config_typetostr(CONFIG_TYPE Type) {
    switch(Type) {
        case TYPE_CONFIG:       return "config";
        case TYPE_RESOURCE:     return "resource";
        case TYPE_TASK:         return "task";
        case TYPE_PROGRAM:      return "program";
        default:
            return "(error)";
    }
}

