#include <assert.h>

#include <bytecode.h>
#include <frame.h>
#include <value.h>


int
operator_jump(FRAME *Frame, VALUE *Value) {
    uint8_t uValue;

    switch(Frame->BC & BYTECODE_MASK) {
        case BYTECODE_JMPC:
        case BYTECODE_JMPCN:

            /*
                The modifier "C" indicates that the associated instruction shall be performed  
                only if the value of the currently evaluated result is Boolean 1 (or Boolean 0 
                if the operator is combined with the "N" modifier).
            */

            uValue = ((Frame->BC & BYTECODE_MASK) == BYTECODE_JMPC);
            uValue &= 1;
            if((Frame->CR.Type == TYPE_BOOL) &&
                    (Frame->CR.Value.B1 == uValue)) {
        case BYTECODE_JMP: 
                assert(Value->Type == TYPE_LABEL);
                Frame->PC = Value->Value.U32;
            }
            break;

        default:
            break;
    }
    return 0;
}


