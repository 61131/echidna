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

#include <log.h>


enum { 
    FIELD_IN = 0, 
    FIELD_PT,
    FIELD_Q,
    FIELD_ET,
    FIELD_INIT,
    FIELD_START,
};


static int _timers_tof(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

static int _timers_ton(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

static int _timers_tp(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);


int
_timers_tof(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[6];
    double dElapsed, dPT, dTime;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0)
        return nResult;

    for(dTime = echidna_time(Context);;) {
        dElapsed = 0.0;
        if(sFields[FIELD_IN].Value.B1) {
            value_assign(&sFields[FIELD_Q], TYPE_BOOL, 1);
            value_assign(&sFields[FIELD_START], TYPE_LREAL, dTime);
            value_assign(&sFields[FIELD_INIT], TYPE_BOOL, 1);
        }
        else if((!sFields[FIELD_IN].Value.B1) &&
                (sFields[FIELD_INIT].Value.B1)) {
            dElapsed = (dTime - sFields[FIELD_START].Value.Double);
            dPT = sFields[FIELD_PT].Value.Time / 1000.0;
            if(dElapsed >= dPT) {
                value_assign(&sFields[FIELD_Q], TYPE_BOOL, 0);
                value_assign(&sFields[FIELD_INIT], TYPE_BOOL, 0);
            }
            value_assign(&sFields[FIELD_ET], TYPE_TIME, dElapsed * 1000.0);
        }
        break;
    }

    return parameter_write_values(Context, Function, Instance, sFields);
}


int
_timers_ton(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[6];
    double dElapsed, dPT, dTime;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0)
        return nResult;

    for(dTime = echidna_time(Context);;) {
        if(sFields[FIELD_IN].Value.B1) {
            if(!sFields[FIELD_INIT].Value.B1) {
                value_assign(&sFields[FIELD_START], TYPE_LREAL, dTime);
                value_assign(&sFields[FIELD_INIT], TYPE_BOOL, 1);
            }
            dElapsed = (dTime - sFields[FIELD_START].Value.Double);
            dPT = sFields[FIELD_PT].Value.Time / 1000.0;
            if(dElapsed >= dPT) {
                value_assign(&sFields[FIELD_Q], TYPE_BOOL, 1);
                dElapsed = dPT;
            }
            value_assign(&sFields[FIELD_ET], TYPE_TIME, dElapsed * 1000.0);
        }
        else {
            value_assign(&sFields[FIELD_Q], TYPE_BOOL, 0);
            value_assign(&sFields[FIELD_INIT], TYPE_BOOL, 0);
        }

        break;
    }

    return parameter_write_values(Context, Function, Instance, sFields);
}


int
_timers_tp(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[6];
    double dElapsed, dPT, dTime;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0)
        return nResult;

    for(dTime = echidna_time(Context);;) {
        //  Initialise timer fields
        if((sFields[FIELD_IN].Value.B1) &&
                (!sFields[FIELD_INIT].Value.B1)) {
            value_assign(&sFields[FIELD_Q], TYPE_BOOL, 1);
            value_assign(&sFields[FIELD_START], TYPE_LREAL, dTime);
            value_assign(&sFields[FIELD_INIT], TYPE_BOOL, 1);
            break;
        }
        if(sFields[FIELD_INIT].Value.B1) {
            dElapsed = (dTime - sFields[FIELD_START].Value.Double);
            dPT = sFields[FIELD_PT].Value.Time / 1000.0;
            if(dElapsed >= dPT) {
                value_assign(&sFields[FIELD_Q], TYPE_BOOL, 0);
                if(!sFields[FIELD_IN].Value.B1)
                    value_assign(&sFields[FIELD_INIT], TYPE_BOOL, 0);
                dElapsed = 0.0;
            }
            value_assign(&sFields[FIELD_ET], TYPE_TIME, dElapsed * 1000.0);
        }

        break;
    }

    return parameter_write_values(Context, Function, Instance, sFields);
}


static FUNCTION_BLOCK_FIELD _Fields[] = {
    { "IN", TYPE_INPUT|TYPE_BOOL },
    { "PT", TYPE_INPUT|TYPE_TIME },
    { "Q", TYPE_OUTPUT|TYPE_BOOL },
    { "ET", TYPE_OUTPUT|TYPE_TIME },
    { "_INIT", TYPE_BOOL },
    { "_START", TYPE_LREAL },
};

static _FUNCTION_BLOCK _Functions[] = {
    { .Name = "tp", .Count = 6, .Fields = _Fields, .Execute = _timers_tp },
    { .Name = "ton", .Count = 6, .Fields = _Fields, .Execute = _timers_ton },
    { .Name = "tof", .Count = 6, .Fields = _Fields, .Execute = _timers_tof },

    { NULL }
};


int
standard_timers(ECHIDNA *Context) {
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

