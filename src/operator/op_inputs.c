#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifndef _MSC_VER
#include <strings.h>
#endif
#include <assert.h>

#include <bytecode.h>
#include <frame.h>
#include <operator.h>
#include <runtime.h>
#include <symbol.h>
#include <value.h>

#include <log.h>
#include <json.h>


static RT_FUNCTION * _operator_inputs_call(RUNTIME_CONTEXT *Context, SYMBOL *Symbol);

static int _operator_inputs_index(const char *Name);


static RT_FUNCTION *
_operator_inputs_call(RUNTIME_CONTEXT *Context, SYMBOL *Symbol) {
    ECHIDNA *pContext;
    FRAME *pFrame;
    _FUNCTION_BLOCK *pBlock;
    FUNCTION_BLOCK_FIELD *pField;
    FUNCTION_REGISTER *pFunction;
    RUNTIME *pRun;
    RT_FUNCTION *pInstance;
    RUNTIME_PARAMETER *pParameter;
    SYMBOL *pSymbol;
    char sName[SYMBOL_NAME_MAX];
    size_t uIndex;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);
    pFrame = frame_current(Context);

    /*
        Validate that the function block variable operand to the inputs operator 
        represents an instance of a standard function block.
    */

    assert(Symbol != NULL);
    assert(Symbol->Value.Type == TYPE_FUNCTION_BLOCK);
    if((strcasecmp((char *) Symbol->Value.Meta, "ctd") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "ctu") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "ctud") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "f_trig") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "ftrig") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "r_trig") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "rs") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "rtrig") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "sr") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "tof") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "ton") != 0) &&
            (strcasecmp((char *) Symbol->Value.Meta, "tp") != 0)) {
        pFrame->ER = RT_ERR_INVALID_FUNCTION;
        return NULL;
    }

    if((pInstance = runtime_call_instance(Context)) == NULL) {
        pFrame->ER = RT_ERR_INTERNAL_ALLOCATION;
        return NULL;
    }
    if(pInstance->Id >= 0)
        return pInstance;

    pFunction = Symbol->Function;
    assert(pFunction != NULL);
    assert(pFunction->Type == TYPE_FUNCTION_BLOCK);
    pBlock = pFunction->Block;
    assert(pBlock != NULL);

    /*
        The following code populates the remaining fields within the RT_FUNCTION 
        data structure associated with the current function block execution. As the 
        input parameters to this function block execution are taken from frame registers 
        rather than parameters which are encoded within bytecode, the list of fields 
        is taken from the function block registration.
    */

    for(uIndex = 0; uIndex < pBlock->Count; ++uIndex) {
        pField = &pBlock->Fields[uIndex];
        if((pField->Type & TYPE_IN_OUT) == 0)
            continue;

        snprintf(sName, sizeof(sName), "%s.%s", Symbol->Name, pField->Name);
        if((pSymbol = symbol_search(pContext, Symbol->Configuration,
                Symbol->Resource,
                Symbol->POU,
                sName)) == NULL)
            return NULL;

        if((pParameter = runtime_parameter_new()) == NULL) {
            pFrame->ER = RT_ERR_INTERNAL_ALLOCATION;
            return NULL;
        }
        pParameter->Id = pSymbol->Id;
        pParameter->Internal = _operator_inputs_index(pField->Name);
        pParameter->Type = pField->Type;
        value_cast(&pParameter->Value, pParameter->Type);
        pParameter->Parameter.Name = strdup(pField->Name);
        value_copy(&pParameter->Parameter.Value, &pParameter->Value);

        if((ll_insert(&pInstance->Parameters, pParameter) != 0) ||
                (ll_insert(&pInstance->List, &pParameter->Parameter) != 0)) {
            pFrame->ER = RT_ERR_INTERNAL_ALLOCATION;
            return NULL;
        }
    }

    pInstance->Id = Symbol->Id;
    return pInstance;
}


static int 
_operator_inputs_index(const char *Name) {
    if(strcasecmp(Name, "cd") == 0)
        return FRAME_CD;
    if(strcasecmp(Name, "clk") == 0)
        return FRAME_CLK;
    if(strcasecmp(Name, "cu") == 0)
        return FRAME_CU;
    if(strcasecmp(Name, "in") == 0)
        return FRAME_IN;
    if(strcasecmp(Name, "pt") == 0)
        return FRAME_PT;
    if(strcasecmp(Name, "pv") == 0)
        return FRAME_PV;
    if(strcasecmp(Name, "r") == 0)
        return FRAME_R;
    if(strcasecmp(Name, "r1") == 0)
        return FRAME_R1;
    if(strcasecmp(Name, "s") == 0)
        return FRAME_S;
    if(strcasecmp(Name, "s1") == 0)
        return FRAME_S1;
    return -1;
}


int
operator_inputs(RUNTIME_CONTEXT *Context, SYMBOL *Symbol, VALUE *Value) {
    FRAME *pFrame;
    LL_ITER sIter;
    RT_FUNCTION *pInstance;
    RUNTIME_PARAMETER *pParameter;
    uint32_t uBC, uType;
    int nIndex;

    pFrame = frame_current(Context);

    nIndex = -1;
    uBC = pFrame->BC & BYTECODE_MASK;
    switch(uBC) {
        case BYTECODE_CD:       nIndex = FRAME_CD; break;
        case BYTECODE_CLK:      nIndex = FRAME_CLK; break;
        case BYTECODE_CU:       nIndex = FRAME_CU; break;
        case BYTECODE_IN:       nIndex = FRAME_IN; break;
        case BYTECODE_PT:       nIndex = FRAME_PT; break;
        case BYTECODE_PV:       nIndex = FRAME_PV; break;
        case BYTECODE_R:        nIndex = FRAME_R; break;
        case BYTECODE_R1:       nIndex = FRAME_R1; break;
        case BYTECODE_S:        nIndex = FRAME_S; break;
        case BYTECODE_S1:       nIndex = FRAME_S1; break;
        default:
            return RT_ERR_INVALID_BYTECODE;
    }

    /*
        Note that the S and R operators can be used either to set/reset the operand, 
        where this is a boolean variable, or manipulate parameters passed to standard 
        function blocks as per Table 54 - Standard function block input operators for 
        IL language. The determination as to whether the initial form of this operator 
        is to be employed is based on: i) the current result of execution frame being 
        of type boolean, and ii) the operand to the R/S operator being a boolean 
        variable.
    */

    for(;;) {
        if((uBC != BYTECODE_R) &&
                (uBC != BYTECODE_S))
            break;
        if((Symbol == NULL) ||
                (Symbol->Value.Type != TYPE_BOOL))
            break;
        if(pFrame->CR.Type != TYPE_BOOL)
            break;

        return operator_boolean(Context, Symbol);
    }

    //  Simple assignment of input parameters

    switch(uBC) {
        case BYTECODE_CD:
        case BYTECODE_CLK:
        case BYTECODE_CU:
        case BYTECODE_IN:
        case BYTECODE_R:
        case BYTECODE_R1:
        case BYTECODE_S:
        case BYTECODE_S1:
            if((pFrame->Type & ~ANY_INTERNAL) != TYPE_BOOL)
                break;
            value_copy(&pFrame->Inputs[nIndex], Value);
            return 0;

        case BYTECODE_PT:
            if((pFrame->Type & ~ANY_INTERNAL) != TYPE_TIME)
                break;
            value_copy(&pFrame->Inputs[FRAME_PT], Value);
            return 0;

        case BYTECODE_PV:
            uType = (pFrame->Type & ~ANY_INTERNAL);
            if((uType & ANY_INT) != uType)
                break;
            value_copy(&pFrame->Inputs[FRAME_PV], Value);
            return 0;
    }

    /*
        If execution reaches this point, the operand should be a variable of the 
        function block to be executed. The following code leverages some of that
        employed in association with the call operator, but needs to be distinct as
        no function block call parameters will be encoded within the bytecode.
    */

    if((pFrame->Type & ~TYPE_VARIABLE) != TYPE_FUNCTION_BLOCK)
        return RT_ERR_OPERAND_TYPE;
    value_copy(&pFrame->Inputs[nIndex], &pFrame->CR);

    if((pInstance = _operator_inputs_call(Context, Symbol)) == NULL)
        return RT_ERR_INTERNAL;
    assert(pInstance->Id == Symbol->Id);
    for(pParameter = ll_iterate_first(&sIter, &pInstance->Parameters);
            pParameter;
            pParameter = ll_iterate_next(&sIter)) {
        assert((pParameter->Type & TYPE_INPUT) != 0);
        assert(pParameter->Internal >= 0);
        value_copy(&pParameter->Value, &pFrame->Inputs[pParameter->Internal]);
    }

    return operator_call(Context);
}


