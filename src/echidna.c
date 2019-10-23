/*
    The following definition is included so that the GNU version of the 
    basename function is preferentially employed by glibc.
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <block.h>
#include <bytecode.h>
#include <config.h>
#include <echidna.h>
#include <file.h>
#include <function.h>
#include <hardware.h>
#include <log.h>
#include <strl.h>
#include <symbol.h>
#include <unit.h>

#include <json.h>


#define IS_DIR_SEPARATOR( c )   ( ( (c) == '/' ) || ( (c) == '\\' ) )


static int _echidna_arguments(ECHIDNA *Context, int Count, char **Arg);

static int _echidna_daemon(ECHIDNA *Context);

static void _echidna_destroy_configuration(void *Arg);

static int _echidna_open_directory(ECHIDNA *Context, char *Path);

static int _echidna_open_file(ECHIDNA *Context, char *Path);

static int _echidna_runtime(ECHIDNA *Context);


static int 
_echidna_arguments(ECHIDNA *Context, int Count, char **Arg) {
    int nIndex, nOpt, nResult;

    Context->Name = Arg[0] + strlen(Arg[0]);
    while((Context->Name != Arg[0]) &&
            (!IS_DIR_SEPARATOR(Context->Name[-1])))
        --Context->Name;

    opterr = 0;
    while((nOpt = getopt(Count, Arg, "Vdho:rv")) != -1) {
        switch(nOpt) {
            case 'd':
                Context->Option |= OPTION_DAEMON;
                break;

            case 'o':
                Context->Output = optarg;
                break;

            case 'r':
                Context->Option |= OPTION_RUN;
                break;

            case 'v':
                ++Context->Verbose;
                break;

            case 'V':
                fprintf(stdout, "%s version %s (%s)\n", Context->Name, _STR(GIT_VERSION), _STR(TIMESTAMP));
                if(0) {
            case 'h':
            default:
                    fprintf(stdout, "Usage: %s -o <output> -d -r file...\n", Context->Name);
                }
                fflush(stdout);
                echidna_destroy(Context);
                exit(0);
                /* break; */
        }
    }

    nResult = 0;

    if(optind >= Count) {
        log_error("No input files");
        echidna_destroy(Context);
        exit(1);
    }

    for(;;) {
        for(nIndex = optind; nIndex < Count; ++nIndex) {
            if((nResult = echidna_open(Context, Arg[nIndex])) != 0)
                return nResult;
        }

        function_table_build(&Context->Functions);
        
        if((Context->Option & OPTION_COMPILE) != 0) {
            if((nResult = echidna_compile(Context)) != 0) 
                break;
        }

        if(!Context->Output)
            Context->Option |= OPTION_RUN;
        if((Context->Option & OPTION_RUN) != 0) 
            nResult = echidna_run(Context);

        break;
    }

    return nResult;
}


static int
_echidna_daemon(ECHIDNA *Context) {
    int nFd, nIndex;

    if((Context->Option & OPTION_DAEMON) == 0)
        return 0;

    switch(fork()) {
        case 0:     break;
        case -1:    return -1;
        default:
            _exit(0);
    }
    if(setsid() < 0)
        return -1;
    switch(fork()) {
        case 0:     break;
        case -1:
        default:
            _exit(0);
    }
    umask(0);
    chdir("/");

    nFd = sysconf(_SC_OPEN_MAX);
    for(nIndex = 0; nIndex < nFd; ++nIndex)
        close(nIndex);

    nFd = open("/dev/null", O_RDWR);
    assert(nFd == STDIN_FILENO);
    if((dup2(nFd, STDOUT_FILENO) != STDOUT_FILENO) ||
            (dup2(nFd, STDERR_FILENO) != STDERR_FILENO))
        _exit(1);

    return 0;
}


static void
_echidna_destroy_configuration(void *Arg) {
    CONFIG *pConfig;

    if((pConfig = (CONFIG *) Arg) != NULL)
        config_destroy(pConfig);
}


static int
_echidna_open_directory(ECHIDNA *Context, char *Path) {
    struct dirent **pEntry;
    struct stat sInfo;
    char sPath[PATH_MAX];
    int nCount, nIndex, nResult;

    if((nCount = scandir(Path, &pEntry, NULL, alphasort)) < 0)
        return errno;

    for(nIndex = 0, nResult = 0; nIndex < nCount; ++nIndex) {
        if(nResult == 0) {
            strlcpy(sPath, Path, sizeof(sPath));
            if(sPath[strlen(sPath) - 1] != '/')
                strlcat(sPath, "/", sizeof(sPath));
            strlcat(sPath, pEntry[nIndex]->d_name, sizeof(sPath));
            if((stat(sPath, &sInfo) == 0) &&
                    ((sInfo.st_mode & S_IFMT) == S_IFREG)) {
                nResult = _echidna_open_file(Context, sPath);
            }
        }
        free(pEntry[nIndex]);
    }
    free(pEntry);

    return nResult;
}


static int
_echidna_open_file(ECHIDNA *Context, char *Path) {
    char *pChar, *pFile;
    int nResult;

    /*
        The following only permits a single compiled hexadecimal file to be loaded at 
        a time. This is because of the fixed nature of the information contained within 
        these files, such as references to symbol and function identifiers, which would 
        be in conflict if multiple files were opened. The immediate remediation of this 
        situation from a practical perspective is to compile multiple source files into 
        a single hexadecimal file for execution, but longer term consideration may need 
        to be given to how to permit discrete POU downloads to a running controller, an
        action which would need to support symbol and function identifier renumbering.
    */

    assert(Path != NULL);
    assert(Context != NULL); 
    if((Context->Option & OPTION_NOFILE) != 0)
        return 0;

    pFile = basename(Path);
    assert(pFile != NULL);
    if((pChar = strrchr(pFile, '.')) == NULL) {
        if((nResult = parse_file(Context, Path)) == 0)
            Context->Option |= OPTION_COMPILE;
    }
    ++pChar;

    nResult = EINVAL;
    if((strcasecmp(pChar, "txt") == 0) ||
            (strcasecmp(pChar, "il") == 0) ||
            (strcasecmp(pChar, "st") == 0)) {
        if((nResult = parse_file(Context, Path)) == 0)
            Context->Option |= OPTION_COMPILE;
    }
    else if(strcasecmp(pChar, "hex") == 0) {
        if((nResult = file_read(Context, Path)) == 0)
            Context->Option |= OPTION_NOFILE;
    }
    else 
        log_error("Unsupported file type: %s", pFile);

    return nResult;
}


static int 
_echidna_runtime(ECHIDNA *Context) {
    RUNTIME *pRun;
    SYMBOL *pSymbol;
    TREE_ITER sIter;
    UNIT *pPOU;
    size_t uBytes;
    int nResult;

    /*
        The following allocates memory for the virtual machine run-time and associated 
        symbol table storage. In addition to this, a list of symbols associated with 
        each POU is created for ease of reference in run-time operations.
    */

    if(Context->VM != NULL)
        return 0;
    if((pRun = runtime_new(Context)) == NULL)
        return errno;
    if((uBytes = symbol_table_size(Context)) > 0) {
        if((pRun->Memory = (char *) calloc(uBytes, sizeof(uint8_t))) == NULL) {
            runtime_destroy(pRun);
            return errno;
        }
    }
    Context->VM = pRun;

    for(pPOU = tree_iterate_first(&sIter, &Context->POU);
            pPOU != NULL;
            pPOU = tree_iterate_next(&sIter)) {
        uBytes = 0;
        symbol_table_reset(Context);
        while((pSymbol = symbol_table_iterate(Context, pPOU->Config, pPOU->Resource, pPOU->POU)) != NULL) {
            if((nResult = ll_insert(&pPOU->Symbols, pSymbol)) != 0)
                return nResult;
            assert(pSymbol->Value.Length >= 0);
            uBytes += pSymbol->Value.Length;
            if((uBytes % Context->Align) != 0)
                uBytes += (Context->Align - (uBytes % Context->Align));
        }
        pPOU->Size = uBytes;
    }

    return 0;
}


int
_echidna_initialise(size_t Arg, ECHIDNA *Context, ...) {
    va_list sArg;
    char **pArg;
    int nArg, nResult;

    Context->Name = "echidna";
    Context->Align = sizeof(int);
    Context->Option = OPTION_NONE;
    Context->Output = NULL;
    Context->Verbose = 0;
    Context->Symbols.Symbol = NULL;
    Context->Symbols.Count = 0;

    ll_initialise(&Context->Config);
    tree_initialise(&Context->POU, block_compare);
    function_initialise(&Context->Functions);
    parse_initialise(Context, &Context->Parse);
#if defined(HARDWARE_PIFACE)
    if((nResult = hardware_initialise(Context)) != 0)
        return nResult;
#endif

    nResult = 0;
    if(Arg > 2) {
        va_start(sArg, Context);
        if((nArg = va_arg(sArg, int)) > 0) {
            pArg = va_arg(sArg, char **);
            nResult = _echidna_arguments(Context, nArg, pArg);
        }
        va_end(sArg);
    }

    return nResult;
}


int
_echidna_register(size_t Arg, ECHIDNA *Context, const char *Name, VALUE_TYPE Type, ...) {
    _FUNCTION sFunction;
    _FUNCTION_BLOCK *pBlock;
    va_list sArg;
    void *pContext;
    int nResult;

    /*
        This function is intended to provide a thin-veneer over the function_register 
        function allowing this to be referenced in a consistent manner to other library 
        functions. This may change however depending upon implementation requirements.
    */

    assert(Context != NULL);
    assert(Name != NULL);

    nResult = 0;
    pBlock = pContext = NULL;
    va_start(sArg, Type);
    switch(Type) {
        case TYPE_FUNCTION:
            sFunction = va_arg(sArg, _FUNCTION);
            if(Arg > 4)
                pContext = va_arg(sArg, void *);
            nResult = function_register(&Context->Functions, Name, Type, sFunction, pContext);
            break;

        case TYPE_FUNCTION_BLOCK:
            if(Arg > 3)
                pBlock = va_arg(sArg, _FUNCTION_BLOCK *);
            if(Arg > 4) 
                pContext = va_arg(sArg, void *);
            nResult = function_register(&Context->Functions, Name, Type, pBlock, pContext);
            break;

        default:
            nResult = EINVAL;
            break;
    }
    va_end(sArg);

    return nResult;
}


int
echidna_compile(ECHIDNA *Context) {
    int nResult;

    if((Context->Option & OPTION_COMPILE) == 0)
        return 0;
    //  TODO: Resolve function/symbol table build from bytecode without compile
    symbol_table_build(Context);

    for(;;) {
//json_token_dump((TOKEN *) &Context->Parse.Tokens);
        if((nResult = bytecode_generate(Context)) != 0) {
            log_error("Failed to generate bytecode");
            break;
        }
        if((nResult = config_generate(Context)) != 0) {
            log_error("Failed to generate configuration");
            break;
        }

        if(Context->Output != NULL)
            nResult = file_write(Context, Context->Output);

        break;
    }

    parse_destroy(&Context->Parse);
    return nResult;
}


void
echidna_destroy(ECHIDNA *Context) {
    assert(Context != NULL);
    symbol_table_destroy(Context);
    runtime_destroy(Context->VM);
    parse_destroy(&Context->Parse);
    tree_destroy(&Context->POU, unit_destroy);
    ll_destroy(&Context->Config, _echidna_destroy_configuration);
    function_destroy(&Context->Functions);
}


int 
echidna_open(ECHIDNA *Context, char *Path) {
    struct stat sInfo;
    int nResult;

    if(Path == NULL)
        return EINVAL;
    if(stat(Path, &sInfo) < 0) {
        log_error("%s: %s", basename(Path), strerror(errno));
        return errno;
    }
    nResult = EINVAL;
    if(S_ISDIR(sInfo.st_mode))
        nResult = _echidna_open_directory(Context, Path);
    if(S_ISREG(sInfo.st_mode))
        nResult = _echidna_open_file(Context, Path);

    return nResult;
}


int
echidna_run(ECHIDNA *Context) {
    CONFIG *pConfig;
    LL_ITER sIter;
    int nResult;

    /*
        The following should support the execution of multiple configurations 
        concurrently, but this is presently outside the immediate development scope.
    */

    if((nResult = _echidna_daemon(Context)) != 0)
        return nResult;
    if((nResult = _echidna_runtime(Context)) != 0) 
        return nResult;

    log_notice("Running %s version %s (%s)", Context->Name, _STR(GIT_VERSION), _STR(TIMESTAMP));
    log_notice("Function signature: %.7s..%.7s", Context->Functions.Signature, Context->Functions.Signature + 57);

    if((pConfig = (CONFIG *) ll_iterate_first(&sIter, &Context->Config)) == NULL)
        return 0;
    if((nResult = runtime_start(Context->VM, pConfig)) != 0)
        return nResult;

    nResult = runtime_execute(Context->VM);

    return nResult;
}


double
echidna_time(ECHIDNA *Context) {
    assert(Context != NULL);
    return Context->Time;
}

