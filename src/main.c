#include <stdio.h>
#include <string.h>

#include <echidna.h>


int
main(int Count, char **Arg) {
    ECHIDNA sContext;
    int nResult;

    /*
        In passing the command-line arguments to the echidna_initialise function, 
        all operations of library are initiated and executed based upon these 
        arguments. If these arguments are _not_ passed to this function, file 
        parsing, compilation and execution can be controlled programmatically 
        through the functions exposed in the echidna.h header file.
    */

    memset(&sContext, 0, sizeof(sContext));
    nResult = echidna_initialise(&sContext, Count, Arg);
    echidna_destroy(&sContext);
    return nResult;
}

