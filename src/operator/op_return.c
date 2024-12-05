#include <bytecode.h>
#include <frame.h>


void
operator_return(FRAME *Frame) {
    uint8_t uValue;

    switch(Frame->BC & BYTECODE_MASK) {
        case BYTECODE_RETC:
        case BYTECODE_RETCN:

            /*
                The modifier "C" indicates that the associated instruction shall be performed  
                only if the value of the currently evaluated result is Boolean 1 (or Boolean 0 
                if the operator is combined with the "N" modifier).
            */

            uValue = ((Frame->BC & BYTECODE_MASK) == BYTECODE_RETC);
            uValue &= 1;
            if((Frame->CR.Type == TYPE_BOOL) &&
                    (Frame->CR.Value.B1 == uValue)) {
        case BYTECODE_RET: 
                Frame->PC = (uint32_t) -1;
            }
            break;

        default:
            break;
    }
}


