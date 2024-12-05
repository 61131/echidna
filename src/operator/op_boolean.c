#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <bytecode.h>
#include <frame.h>
#include <runtime.h>
#include <symbol.h>
#include <value.h>


int
operator_boolean(RUNTIME_CONTEXT *Context, SYMBOL *Symbol) {
    RUNTIME *pRun;
    FRAME *pFrame;
    VALUE sValue;

    assert(Context != NULL);
    pRun = (RUNTIME *) Context->Parent;
    assert(pRun != NULL);

    pFrame = frame_current(Context);
    value_copy(&sValue, &pFrame->CR);
    value_cast(&sValue, TYPE_BOOL);

    if(sValue.Value.B1) {
        assert(Symbol != NULL);
        value_assign(&sValue, TYPE_BOOL, (pFrame->BC == BYTECODE_S));
        memcpy(&pRun->Memory[Symbol->Offset], &sValue.Value.Pointer, sValue.Length);
    }

    return 0;
}


