#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#endif
#include <assert.h>

#include <echidna.h>
#include <function.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>


enum { 
    FIELD_CLK = 0, 
    FIELD_Q, 
    FIELD_M 
};

static int _standard_ftrig(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

static int _standard_rtrig(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);


int
_standard_ftrig(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[3];
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0)
        return nResult;

    /*
        Table 35 - Standard edge detection function blocks describes the operations 
        of the F_TRIG function block as:

            Q := NOT CLK AND NOT M;
            M := NOT CLK;
    */

    value_assign(&sFields[FIELD_Q], TYPE_BOOL, ~sFields[FIELD_CLK].Value.B1 & ~sFields[FIELD_M].Value.B1);
    value_assign(&sFields[FIELD_M], TYPE_BOOL, ~sFields[FIELD_CLK].Value.B1);

    return parameter_write_values(Context, Function, Instance, sFields);
}


int
_standard_rtrig(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[3];
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0)
        return nResult;

    /*
        Table 35 - Standard edge detection function blocks describes the operations 
        of the R_TRIG function block as:

            Q := CLK AND NOT M;
            M := CLK;
    */

    value_assign(&sFields[FIELD_Q], TYPE_BOOL, sFields[FIELD_CLK].Value.B1 & ~sFields[FIELD_M].Value.B1);
    value_assign(&sFields[FIELD_M], TYPE_BOOL, sFields[FIELD_CLK].Value.B1);

    return parameter_write_values(Context, Function, Instance, sFields);
}


/*
    There are two means by which the Fields member of the FUNCTION_BLOCK array 
    can be initialised - The first, as employed below, is through the definition 
    of a separate data structure for these members and the passing of a reference 
    to this structure. The second is through the use of C99 compound literals. 
    While the latter provides a more succinct format for structure initialisation, 
    the former has been employed to reuse the field definition between function 
    block definitions.

        .Fields = (FUNCTION_BLOCK_FIELD[]){
            { "CLK", TYPE_INPUT|TYPE_BOOL, 0 },
            { "Q", TYPE_OUTPUT|TYPE_BOOL, 0 },
            { "M", TYPE_BOOL, 0 }
        }
*/

static FUNCTION_BLOCK_FIELD _Fields[] = {
    { "CLK", TYPE_INPUT|TYPE_BOOL },
    { "Q", TYPE_OUTPUT|TYPE_BOOL },
    { "M", TYPE_BOOL }
};

static _FUNCTION_BLOCK _Functions[] = {
    { .Name = "f_trig", .Count = 3, .Fields = _Fields, .Execute = _standard_ftrig },
    { .Name = "ftrig", .Count = 3, .Fields = _Fields, .Execute = _standard_ftrig },
    { .Name = "r_trig", .Count = 3, .Fields = _Fields, .Execute = _standard_rtrig },
    { .Name = "rtrig", .Count = 3, .Fields = _Fields, .Execute = _standard_rtrig },

    { NULL }
};


int
standard_edge(ECHIDNA *Context) {
    _FUNCTION_BLOCK *pFunction;
    size_t uIndex;
    int nResult;

    for(uIndex = 0;; ++uIndex) {
        pFunction = &_Functions[uIndex];
        if(!pFunction->Name)
            break;
        if((nResult = echidna_register(Context, pFunction->Name, TYPE_FUNCTION_BLOCK, pFunction)) != 0)
            return nResult;
    }
    return 0;
}

