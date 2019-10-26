#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#include <echidna.h>
#include <function.h>
#include <ll.h>
#include <parameter.h>
#include <runtime.h>
#include <value.h>

#include <log.h>

enum { 
    CTU_CU = 0, 
    CTU_R, 
    CTU_PV, 
    CTU_Q, 
    CTU_CV 
};

enum { 
    CTD_CD = 0, 
    CTD_LD, 
    CTD_PV,
    CTD_Q, 
    CTD_CV 
};

enum {
    CTUD_CU = 0,
    CTUD_CD,
    CTUD_R,
    CTUD_LD,
    CTUD_PV,
    CTUD_QU,
    CTUD_QD,
    CTUD_CV
};


static int _standard_ctd(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);

static int _standard_ctu(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User);


int
_standard_ctd(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[5], sType;
    char *pPtr;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0) 
        return nResult;
  
    /*
        Table 36 - Standard counter function blocks describes the operations of the
        down-counter function blocks as:

            IF LD THEN CV := PV;
            ELSIF CD AND (CV > PVmin)
                THEN CV := CV-1;
            END_IF;
            Q := (CV <= 0);

        The following code also includes the ability to qualify the LD data type based 
        upon the registered function name and provide typed-versions of the down-counter 
        function block.
    */

    if((pPtr = strchr(Function->Name, '_')) != NULL) {
        value_strtotype(&sType, ++pPtr);
        if(sFields[CTD_PV].Type != sType.Type) 
            return ERROR_PARAMETER_TYPE;
    }

    value_cast(&sFields[CTD_CV], sFields[CTD_PV].Type);

    if(sFields[CTD_LD].Value.B1)
        value_copy(&sFields[CTD_CV], &sFields[CTD_PV]);
    else {
        switch(sFields[CTD_PV].Type) {
            case TYPE_LINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.S64 > sFields[CTD_PV].Minimum.S64)
                        --sFields[CTD_CV].Value.S64;
                }  
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.S64 <= 0));
                break;

            case TYPE_DINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.S32 > sFields[CTD_PV].Minimum.S32)
                        --sFields[CTD_CV].Value.S32;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.S32 <= 0));
                break;

            case TYPE_INT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.S16 > sFields[CTD_PV].Minimum.S16)
                        --sFields[CTD_CV].Value.S16;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.S16 <= 0));
                break;

            case TYPE_SINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.S8 > sFields[CTD_PV].Minimum.S8)
                        --sFields[CTD_CV].Value.S8;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.S8 <= 0));
                break;

            case TYPE_ULINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.U64 > sFields[CTD_PV].Minimum.U64)
                        --sFields[CTD_CV].Value.U64;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.U64 <= 0));
                break;

            case TYPE_UDINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.U32 > sFields[CTD_PV].Minimum.U32)
                        --sFields[CTD_CV].Value.U32;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.U32 <= 0));
                break;

            case TYPE_UINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.U16 > sFields[CTD_PV].Minimum.U16)
                        --sFields[CTD_CV].Value.U16;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.U16 <= 0));
                break;

            case TYPE_USINT:
                if(sFields[CTD_CD].Value.B1) {
                    if(sFields[CTD_CV].Value.U8 > sFields[CTD_PV].Minimum.U8)
                        --sFields[CTD_CV].Value.U8;
                }
                value_assign(&sFields[CTD_Q], TYPE_BOOL, (sFields[CTD_CV].Value.U8 <= 0));
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    return parameter_write_values(Context, Function, Instance, sFields);
}


int
_standard_ctu(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[5], sType;
    char *pPtr;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0) 
        return nResult;

    /*
        Table 36 - Standard counter function blocks describes the operations of the
        up-counter function blocks as:

            IF R THEN CV := 0;
            ELSIF CU AND (CV < PVmax)
                THEN CV := CV+1;
            END_IF;
            Q := (CV >= PV);

        The following code also includes the ability to qualify the PV data type based 
        upon the registered function name and provide typed-versions of the up-counter 
        function block.
    */

    if((pPtr = strchr(Function->Name, '_')) != NULL) {
        value_strtotype(&sType, ++pPtr);
        if(sFields[CTU_PV].Type != sType.Type) 
            return ERROR_PARAMETER_TYPE;
    }
    value_cast(&sFields[CTU_CV], sFields[CTU_PV].Type);

    if(sFields[CTU_R].Value.B1) 
        value_assign(&sFields[CTU_CV], sFields[CTU_CV].Type, 0);

    switch(sFields[CTU_PV].Type) {
        case TYPE_LINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.S64 < sFields[CTU_PV].Maximum.S64)) {

                ++sFields[CTU_CV].Value.S64;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.S64 >= sFields[CTU_PV].Value.S64));
            break;

        case TYPE_DINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.S32 < sFields[CTU_PV].Maximum.S32)) {

                ++sFields[CTU_CV].Value.S32;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.S32 >= sFields[CTU_PV].Value.S32));
            break;

        case TYPE_INT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.S16 < sFields[CTU_PV].Maximum.S16)) {

                ++sFields[CTU_CV].Value.S16;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.S16 >= sFields[CTU_PV].Value.S16));
            break;

        case TYPE_SINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.S8 < sFields[CTU_PV].Maximum.S8)) {

                ++sFields[CTU_CV].Value.S8;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.S8 >= sFields[CTU_PV].Value.S8));
            break;

        case TYPE_ULINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.U64 < sFields[CTU_PV].Maximum.U64)) {

                ++sFields[CTU_CV].Value.U64;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.U64 >= sFields[CTU_PV].Value.U64));
            break;

        case TYPE_UDINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.U32 < sFields[CTU_PV].Maximum.U32)) {

                ++sFields[CTU_CV].Value.U32;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.U32 >= sFields[CTU_PV].Value.U32));
            break;

        case TYPE_UINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.U16 < sFields[CTU_PV].Maximum.U16)) {

                ++sFields[CTU_CV].Value.U16;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.U16 >= sFields[CTU_PV].Value.U16));
            break;

        case TYPE_USINT:
            if((!sFields[CTU_R].Value.B1) &&
                    (sFields[CTU_CU].Value.B1) &&
                    (sFields[CTU_CV].Value.U8 < sFields[CTU_PV].Maximum.U8)) {

                ++sFields[CTU_CV].Value.U8;
            }
            value_assign(&sFields[CTU_Q], TYPE_BOOL, (sFields[CTU_CV].Value.U8 >= sFields[CTU_PV].Value.U8));
            break;

        default:
            break;
    }

    return parameter_write_values(Context, Function, Instance, sFields);
}


int
_standard_ctud(ECHIDNA *Context, _FUNCTION_BLOCK *Function, char *Instance, void *User) {
    VALUE sFields[8], sType;
    char *pPtr;
    int nResult;

    if((nResult = parameter_read_values(Context, Function, Instance, sFields)) != 0) 
        return nResult;

    /*
        Table 36 - Standard counter function blocks describes the operations of the
        up-down counter function blocks as:

            IF R THEN CV := 0;
            ELSIF LD THEN CV := PV;
            ELSE
                IF NOT (CU AND CD) THEN
                    IF CU AND (CV < PVmax)
                    THEN CV := CV+1;
                    ELSIF CD AND (CV > PVmin)
                    THEN CV := CV-1;
                    END_IF;
                END_IF
            END_IF;
            QU := (CV >= PV);
            QD := (CV <= 0);

        The following code also includes the ability to qualify the PV and LD data 
        type based upon the registered function name and provide typed-versions of 
        the up-down counter function block.
    */

    if((pPtr = strchr(Function->Name, '_')) != NULL) {
        value_strtotype(&sType, ++pPtr);
        if(sFields[CTUD_PV].Type != sType.Type) 
            return ERROR_PARAMETER_TYPE;
    }
    value_cast(&sFields[CTUD_CV], sFields[CTUD_PV].Type);

    if(sFields[CTUD_R].Value.B1)
        value_assign(&sFields[CTUD_CV], sFields[CTUD_CV].Type, 0);
    else if(sFields[CTUD_LD].Value.B1)
        value_copy(&sFields[CTUD_CV], &sFields[CTUD_PV]);
    else {
        switch(sFields[CTUD_CV].Type) {
            case TYPE_LINT:
                if((sFields[CTUD_CU].Value.B1 & sFields[CTUD_CD].Value.B1) != 0)
                    break;

                if((sFields[CTUD_CU].Value.B1) &&
                        (sFields[CTUD_CV].Value.S64 < sFields[CTUD_PV].Maximum.S64))
                    ++sFields[CTUD_CV].Value.S64;
                else if((sFields[CTUD_CD].Value.B1) &&
                        (sFields[CTUD_CV].Value.S64 > sFields[CTUD_PV].Minimum.S64))
                    --sFields[CTUD_CV].Value.S64;

                value_assign(&sFields[CTUD_QU], TYPE_BOOL, (sFields[CTUD_CV].Value.S64 >= sFields[CTUD_PV].Value.S64));
                value_assign(&sFields[CTUD_QD], TYPE_BOOL, (sFields[CTUD_CV].Value.S64 <= 0));
                break;

            case TYPE_DINT:
                if((sFields[CTUD_CU].Value.B1 & sFields[CTUD_CD].Value.B1) != 0)
                    break;

                if((sFields[CTUD_CU].Value.B1) &&
                        (sFields[CTUD_CV].Value.S32 < sFields[CTUD_PV].Maximum.S32))
                    ++sFields[CTUD_CV].Value.S32;
                else if((sFields[CTUD_CD].Value.B1) &&
                        (sFields[CTUD_CV].Value.S32 > sFields[CTUD_PV].Minimum.S32))
                    --sFields[CTUD_CV].Value.S32;

                value_assign(&sFields[CTUD_QU], TYPE_BOOL, (sFields[CTUD_CV].Value.S32 >= sFields[CTUD_PV].Value.S32));
                value_assign(&sFields[CTUD_QD], TYPE_BOOL, (sFields[CTUD_CV].Value.S32 <= 0));
                break;

            case TYPE_ULINT:
                if((sFields[CTUD_CU].Value.B1 & sFields[CTUD_CD].Value.B1) != 0)
                    break;

                if((sFields[CTUD_CU].Value.B1) &&
                        (sFields[CTUD_CV].Value.U64 < sFields[CTUD_PV].Maximum.U64))
                    ++sFields[CTUD_CV].Value.U64;
                else if((sFields[CTUD_CD].Value.B1) &&
                        (sFields[CTUD_CV].Value.U64 > sFields[CTUD_PV].Minimum.U64))
                    --sFields[CTUD_CV].Value.U64;

                value_assign(&sFields[CTUD_QU], TYPE_BOOL, (sFields[CTUD_CV].Value.U64 >= sFields[CTUD_PV].Value.U64));
                value_assign(&sFields[CTUD_QD], TYPE_BOOL, (sFields[CTUD_CV].Value.U64 <= 0));
                break;

            case TYPE_UDINT:
                if((sFields[CTUD_CU].Value.B1 & sFields[CTUD_CD].Value.B1) != 0)
                    break;

                if((sFields[CTUD_CU].Value.B1) &&
                        (sFields[CTUD_CV].Value.U32 < sFields[CTUD_PV].Maximum.U32))
                    ++sFields[CTUD_CV].Value.U32;
                else if((sFields[CTUD_CD].Value.B1) &&
                        (sFields[CTUD_CV].Value.U32 > sFields[CTUD_PV].Minimum.U32))
                    --sFields[CTUD_CV].Value.U32;

                value_assign(&sFields[CTUD_QU], TYPE_BOOL, (sFields[CTUD_CV].Value.U32 >= sFields[CTUD_PV].Value.U32));
                value_assign(&sFields[CTUD_QD], TYPE_BOOL, (sFields[CTUD_CV].Value.U32 <= 0));
                break;

            default:
                return ERROR_PARAMETER_TYPE;
        }
    }

    return parameter_write_values(Context, Function, Instance, sFields);
}


static FUNCTION_BLOCK_FIELD _ctd_fields[] = {
    { "CD", TYPE_INPUT|TYPE_BOOL },
    { "LD", TYPE_INPUT|TYPE_BOOL },
    { "PV", TYPE_INPUT|ANY_INT },
    { "Q", TYPE_OUTPUT|TYPE_BOOL },
    { "CV", TYPE_OUTPUT|ANY_INT }
};

static FUNCTION_BLOCK_FIELD _ctu_fields[] = {
    { "CU", TYPE_INPUT|TYPE_BOOL },
    { "R", TYPE_INPUT|TYPE_BOOL },
    { "PV", TYPE_INPUT|ANY_INT },
    { "Q", TYPE_OUTPUT|TYPE_BOOL },
    { "CV", TYPE_OUTPUT|ANY_INT }
};

static FUNCTION_BLOCK_FIELD _ctud_fields[] = {
    { "CU", TYPE_INPUT|TYPE_BOOL },
    { "CD", TYPE_INPUT|TYPE_BOOL },
    { "R", TYPE_INPUT|TYPE_BOOL },
    { "LD", TYPE_INPUT|TYPE_BOOL },
    { "PV", TYPE_INPUT|ANY_INT },
    { "QU", TYPE_OUTPUT|TYPE_BOOL },
    { "QD", TYPE_OUTPUT|TYPE_BOOL },
    { "CV", TYPE_OUTPUT|ANY_INT }
};

static _FUNCTION_BLOCK _Functions[] = {
    { .Name = "ctd", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_lint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_dint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_int", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_sint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_ulint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_udint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_uint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },
    { .Name = "ctd_usint", .Count = 5, .Fields = _ctd_fields, .Execute = _standard_ctd },

    { .Name = "ctu", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_lint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_dint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_int", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_sint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_ulint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_udint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_uint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },
    { .Name = "ctu_usint", .Count = 5, .Fields = _ctu_fields, .Execute = _standard_ctu },

    { .Name = "ctud", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_lint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_dint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_int", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_sint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_ulint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_udint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_uint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },
    { .Name = "ctud_usint", .Count = 8, .Fields = _ctud_fields, .Execute = _standard_ctud },

    { NULL }
};


int
standard_counters(ECHIDNA *Context) {
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

