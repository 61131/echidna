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
#include <runtime/error.h>
#include <value.h>


enum {
    FIELD_R1,
    FIELD_S,
    FIELD_Q,

    FIELD_S1 = FIELD_R1,
    FIELD_R = FIELD_S
};

static int _standard_rs(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

static int _standard_sr(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);


int
_standard_rs(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sValue[3];
    uint8_t uResult;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sValue)) != 0)
        return nResult;

    /*
        Table 34 - Standard bistable function blocks describes the operations of the
        RS function block.
    */

    uResult = (~sValue[FIELD_R1].Value.B1 & (sValue[FIELD_S].Value.B1 | sValue[FIELD_Q].Value.B1));
    value_assign(&sValue[FIELD_Q], TYPE_BOOL, (uResult > 0));

    return parameter_write_values(Context, Function, Instance, sValue);
}


int
_standard_sr(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sValue[3];
    uint8_t uResult;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sValue)) != 0)
        return nResult;

    /*
        Table 34 - Standard bistable function blocks describes the operations of the
        SR function block.
    */

    uResult = (sValue[FIELD_S1].Value.B1 | (~sValue[FIELD_R].Value.B1 & sValue[FIELD_Q].Value.B1));
    value_assign(&sValue[FIELD_Q], TYPE_BOOL, (uResult > 0));

    return parameter_write_values(Context, Function, Instance, sValue);
}


static _FUNCTION_BLOCK _Functions[] = {
    { .Name = "sr", 
            .Count = 3, 
            .Fields = (FUNCTION_BLOCK_FIELD[]){
                { "S1", TYPE_INPUT|TYPE_BOOL },
                { "R", TYPE_INPUT|TYPE_BOOL },
                { "Q", TYPE_OUTPUT|TYPE_BOOL },
            },
            .Execute = _standard_sr },
    { .Name = "rs",
            .Count = 3,
            .Fields = (FUNCTION_BLOCK_FIELD[]){
                { "R1", TYPE_INPUT|TYPE_BOOL },
                { "S", TYPE_INPUT|TYPE_BOOL },
                { "Q", TYPE_OUTPUT|TYPE_BOOL },
            },
            .Execute = _standard_rs },

    { NULL }
};


int
standard_bistable(ECHIDNA *Context) {
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

