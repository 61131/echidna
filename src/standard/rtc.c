#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <sys/time.h>

#include <echidna.h>
#include <function.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>

/*
    The real-time clock function block is included in Annex F of the IEC 61131-3 
    version 2 standard, but is not referenced anywhere else in the standard. This 
    reference is removed entirely in the IEC 61131-3 version 3 standard. Nevertheless, 
    this function block has been implemented so as to provide the means for 
    implementation and testing of date and time variable types described in this 
    standard.
*/

enum { 
    FIELD_IN = 0, 
    FIELD_PDT,
    FIELD_Q,
    FIELD_CDT,
};


int
_standard_rtc(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[4];
    struct timeval sTime;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0)
        return nResult;

    if(sFields[FIELD_IN].Value.B1 & ~sFields[FIELD_Q].Value.B1) {
        //  Set RTC
    }
    value_assign(&sFields[FIELD_Q], TYPE_BOOL, sFields[FIELD_IN].Value.B1);

    gettimeofday(&sTime, NULL);

    return parameter_write_values(Context, Function, Instance, sFields);
}


static _FUNCTION_BLOCK _Function = {

    .Name = "rtc",
    .Count = 4,
    .Fields = (FUNCTION_BLOCK_FIELD[]){
        { "IN", TYPE_INPUT|TYPE_BOOL },
        { "PDT", TYPE_INPUT|TYPE_DT },
        { "Q", TYPE_OUTPUT|TYPE_BOOL },
        { "CDT", TYPE_OUTPUT|TYPE_DT },
    },
    .Execute = _standard_rtc,
};


int
standard_rtc(ECHIDNA *Context) {
    return echidna_register(Context, "rtc", TYPE_FUNCTION_BLOCK, &_Function);
}

