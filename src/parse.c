/*
    The following definition is included so that the GNU version of the
    basename function is preferentially employed by glibc.
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>

#include <function.h>
#include <grammar.h>
#include <lexer.h>
#include <log.h>
#include <parse.h>
#include <strl.h>
#include <symbol.h>
#include <token.h>
#include <tree.h>


static int _parse_compare_identifier(void *A, void *B);

/* static */ int _parse_file(ECHIDNA *Context, FILE *File);

static char * _parse_scope_global(PARSE *Parse, char *Name);


static char _sPath[LINE_MAX];


static int
_parse_compare_identifier(void *A, void *B) {
    LEXER_TOKEN *pTokenA, *pTokenB;

    pTokenA = (LEXER_TOKEN *) A;
    assert(pTokenA != NULL);
    pTokenB = (LEXER_TOKEN *) B;
    assert(pTokenB != NULL);
    return strcasecmp(pTokenA->Text, pTokenB->Text);
}


/* static */ int
_parse_file(ECHIDNA *Context, FILE *File) {
    PARSE *pParse;
    int nIndex, nResult;

    pParse = &Context->Parse;
    token_list_initialise(&pParse->Parse);
    pParse->Configuration = NULL;
    pParse->Resource = NULL;
    pParse->POU = NULL;
    if(!pParse->File)
        pParse->File = "<input>";

    yydebug = (Context->Verbose > 2);
    yyin = File;
    for(nIndex = 1; nIndex >= 0; --nIndex) {
        pParse->Preparse = nIndex;
        if((nResult = yyparse(Context)) != 0)
            break;
        yyrestart(yyin);
        fseek(yyin, 0, SEEK_SET);

        if(pParse->Preparse) {
            token_destroy(&pParse->Parse);
            token_list_initialise(&pParse->Parse);
        }
    }
    yylex_destroy();

    token_list_merge(&pParse->Tokens, &pParse->Parse);
    token_destroy(&pParse->Parse);

    return nResult;
}


static char *
_parse_scope_global(PARSE *Parse, char *Name) {
    _sPath[0] = '\0';
    if(Parse->Configuration)
        snprintf(_sPath, sizeof(_sPath), "%s.", Parse->Configuration->Name);
    strlcat(_sPath, Name, sizeof(_sPath));
    return _sPath;
}


void 
parse_destroy(PARSE *Parse) {
    tree_destroy(&Parse->Identifiers, lexer_destroy);
    token_destroy(&Parse->Tokens);
}


int 
parse_file(ECHIDNA *Context, char *Path) {
    PARSE *pParse;
    FILE *pFile;
    int nResult;

    pParse = &Context->Parse;
    pParse->File = basename(Path);
    if((pFile = fopen(Path, "r")) == NULL) {
        log_error("%s: %s", pParse->File, strerror(errno));
        return -errno;
    }
    nResult = _parse_file(Context, pFile);
    fclose(pFile);
    pParse->File = NULL;

    return nResult;
}


int 
parse_initialise(ECHIDNA *Context, PARSE *Parse) {
    FUNCTION_REGISTER *pFunction;
    LEXER_TOKEN *pToken;
    uint32_t uType;
    size_t uIndex;

    assert(Context != NULL);
    assert(Parse != NULL);

    token_list_initialise(&Parse->Tokens);
    tree_initialise(&Parse->Identifiers, _parse_compare_identifier);

    for(uIndex = 0; uIndex < Context->Functions.Count; ++uIndex) {
        pFunction = Context->Functions.Function[uIndex];
        uType = (pFunction->Type == TYPE_FUNCTION) ? _function_name : _function_block_type_name;
        if((pToken = lexer_new(uType, pFunction->Name)) == NULL)
            return -1;
        if( tree_insert(&Parse->Identifiers, pToken) != 0) {
            lexer_destroy(pToken);
            return -1;
        }
    }

    Parse->File = NULL;
    Parse->Preparse = 0;
    Parse->Type = TYPE_NONE;

    return 0;
}


int
parse_register(PARSE *Parse, int Id, char *Name) {
    LEXER_TOKEN *pToken;
    char *pPath;
    int nResult;

    pPath = parse_scope(Parse, Name);
    if((pToken = lexer_new(Id, pPath)) == NULL)
        return -errno;
    if((nResult = tree_insert(&Parse->Identifiers, pToken)) != 0) {
        lexer_destroy(pToken);
        return nResult;
    }

    if(strcmp(pPath, Name) == 0)
        return 0;
    if((pToken = lexer_new( Id, Name)) == NULL)
        return -errno;
    if((nResult = tree_insert(&Parse->Identifiers, pToken)) != 0)
        lexer_destroy(pToken);

    return nResult;
}


int
parse_register_scope(PARSE *Parse, int Id, char *Name) {
    LEXER_TOKEN *pToken;
    char *pPath;
    int nResult;

    pPath = parse_scope(Parse, Name);
    if((pToken = lexer_new(Id, pPath)) == NULL)
        return -errno;
    if((nResult = tree_insert(&Parse->Identifiers, pToken)) != 0) 
        lexer_destroy(pToken);

    return nResult;
}


void
parse_reset(ECHIDNA *Context, PARSE *Parse) {
    parse_destroy(Parse);
    parse_initialise(Context, Parse);
}


char * 
parse_scope(PARSE *Parse, char *Name) {
    TOKEN *pToken[] = {
        Parse->Configuration,
        Parse->Resource,
        Parse->POU,
    };
    int nIndex;

    _sPath[0] = '\0';
    for(nIndex = 0; nIndex < 3; ++nIndex) {
        if(!pToken[nIndex])
            break;
        if(strlen(_sPath))
            strlcat(_sPath, ".", sizeof(_sPath));
        strlcat(_sPath, pToken[nIndex]->Name, sizeof(_sPath));
    }
    if(strlen(_sPath))
        strlcat(_sPath, ".", sizeof(_sPath));
    strlcat(_sPath, Name, sizeof(_sPath));

    return _sPath;
}


LEXER_TOKEN *
parse_search(PARSE *Parse, char *Name) {
    LEXER_TOKEN *pToken, sToken;
    int nIndex;

    memset(&sToken, 0, sizeof(sToken));
    for(nIndex = 0; nIndex < 3; ++nIndex) {
        switch(nIndex) {
            case 0:     sToken.Text = parse_scope(Parse, Name); break;
            case 1:     sToken.Text = _parse_scope_global(Parse, Name); break; 
            case 2:     sToken.Text = Name; break;
            default:
                assert(0);
        }
        if((pToken = tree_search(&Parse->Identifiers, &sToken)) != NULL) 
            return pToken;
    }

    return NULL;
}


