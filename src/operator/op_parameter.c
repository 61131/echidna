#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#ifndef _MSC_VER
#include <strings.h>
#else
#include "deps.h"
#endif
#include <errno.h>
#include <assert.h>

#include <bytecode.h>
#include <echidna.h>
#include <frame.h>
#include <ll.h>
#include <operator.h>
#include <parameter.h>
#include <runtime.h>
#include <symbol.h>
#include <value.h>

#include <log.h>


int 
operator_parameter(RUNTIME_CONTEXT *Context) {
    ECHIDNA *pContext;
    PARAMETER *pParameter;
    RUNTIME *pRun;
    FRAME *pFrame;
    SYMBOL *pSymbol;
    VALUE sValue;
    uint32_t uCount, uId, uIndex, uParameter;
    int nLength, nResult, nStyle;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);
    pContext = (ECHIDNA *) pRun->Parent;
    assert(pContext != NULL);
    pFrame = frame_current(Context);

    /*
        The parameter operator is an internal operator of the virtual machine run-time
        and is used to specify input and output parameters to program organisation units 
        written in IEC 61131-3 languages. The current value of each of these parameters
        must however be stashed in the event that the current function has been called
        recursively.
    */

    uCount = G_VALUE(pFrame->BC);
    for(uIndex = 0; uIndex < uCount; ++uIndex) {
        if((nResult = runtime_read(Context, sizeof(uId), (char *) &uId)) != 0)
            return nResult;

        if(uId >= pContext->Symbols.Count) {
            pFrame->ER = RT_ERR_INVALID_SYMBOL;
            Context->State = STATE_ERROR;
            return EINVAL;
        }
        pSymbol = pContext->Symbols.Symbol[uId];
        nLength = pSymbol->Value.Length;
        assert(nLength > 0);

        if((pFrame->Type & TYPE_INPUT) == 0)
            continue;

        nStyle = 0;
        uParameter = 0;
        ll_reset(&pFrame->Parameters);
        while((pParameter = ll_iterate(&pFrame->Parameters)) != NULL) {
            for(;;) {
                switch(nStyle) {
                    case 2:     //  Named parameters
                        assert(pParameter->Name != NULL);
                        if(strcasecmp(pParameter->Name, pSymbol->Name) == 0) {
                            memcpy(&pRun->Memory[pSymbol->Offset], (char *) &pParameter->Value.Value.Pointer, nLength);
                            nStyle = -1;
                        }
                        break;

                    case 1:     //  Ordered parameters
                        assert(pParameter->Name == NULL);
                        if(uParameter < pFrame->Parameter) 
                            break;
                        value_copy(&sValue, &pParameter->Value);
                        value_cast(&sValue, pSymbol->Value.Type);
                        memcpy(&pRun->Memory[pSymbol->Offset], (char *) &sValue.Value.Pointer, nLength);
                        ++pFrame->Parameter;

                        nStyle = -1;
                        break;

                    case 0:
                    default:
                        nStyle = (pParameter->Name != NULL) ? 2 : 1;
                        continue;
                }
                break;
            }
            if(nStyle < 0)
                break;
            ++uParameter;
        }
    }
    return 0;
}


