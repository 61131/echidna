#include <stdio.h>
#include <errno.h>

#include <block.h>
#include <bytecode.h>
#include <echidna.h>


const char *
bytecode_typetostr(BYTECODE BC) {
    switch(BC & BYTECODE_MASK) {
        case BYTECODE_NOP:      return "NOP";
        case BYTECODE_LD:       return "LD";
        case BYTECODE_LDN:      return "LDN";
        case BYTECODE_ST:       return "ST";
        case BYTECODE_STN:      return "STN";
        case BYTECODE_S:        return "S";
        case BYTECODE_R:        return "R";
        case BYTECODE_S1:       return "S1";
        case BYTECODE_R1:       return "R1";
        case BYTECODE_CLK:      return "CLK";
        case BYTECODE_CD:       return "CD";
        case BYTECODE_CU:       return "CU";
        case BYTECODE_IN:       return "IN";
        case BYTECODE_PT:       return "PT";
        case BYTECODE_PV:       return "PV";
        case BYTECODE_AND:      return "AND";
        case BYTECODE_AND_P:    return "ANDP";
        case BYTECODE_ANDN:     return "ANDN";
        case BYTECODE_ANDN_P:   return "ANDNP";
        case BYTECODE_OR:       return "OR";
        case BYTECODE_OR_P:     return "ORP";
        case BYTECODE_ORN:      return "ORN";
        case BYTECODE_ORN_P:    return "ORNP";
        case BYTECODE_XOR:      return "XOR";
        case BYTECODE_XOR_P:    return "XOR_P";
        case BYTECODE_XORN:     return "XORN";
        case BYTECODE_XORN_P:   return "XORNP";
        case BYTECODE_NOT:      return "NOT";
        case BYTECODE_ADD:      return "ADD";
        case BYTECODE_ADD_P:    return "ADDP";
        case BYTECODE_SUB:      return "SUB";
        case BYTECODE_SUB_P:    return "SUBP";
        case BYTECODE_MUL:      return "MUL";
        case BYTECODE_MUL_P:    return "MULP";
        case BYTECODE_DIV:      return "DIV";
        case BYTECODE_DIV_P:    return "DIVP";
        case BYTECODE_MOD:      return "MOD";
        case BYTECODE_MOD_P:    return "MODP";
        case BYTECODE_GT:       return "GT";
        case BYTECODE_GT_P:     return "GTP";
        case BYTECODE_GE:       return "GE";
        case BYTECODE_GE_P:     return "GEP";
        case BYTECODE_EQ:       return "EQ";
        case BYTECODE_EQ_P:     return "EQP";
        case BYTECODE_NE:       return "NE";
        case BYTECODE_NE_P:     return "NEP";
        case BYTECODE_LE:       return "LE";
        case BYTECODE_LE_P:     return "LEP";
        case BYTECODE_LT:       return "LT";
        case BYTECODE_LT_P:     return "LTP";
        case BYTECODE_CAL:      return "CAL";
        case BYTECODE_CALC:     return "CALC";
        case BYTECODE_CALCN:    return "CALCN";
        case BYTECODE_JMP:      return "JMP";
        case BYTECODE_JMPC:     return "JMPC";
        case BYTECODE_JMPCN:    return "JMPCN";
        case BYTECODE_RET:      return "RET";
        case BYTECODE_RETC:     return "RETC";
        case BYTECODE_RETCN:    return "RETCN";
        case BYTECODE_PARENTHESIS:      return "PAREN";
        case BYTECODE_PARAMETER:        return "PARAM";
        default:
            return "ERROR";
    }
}


int
bytecode_write(ECHIDNA *Context, BLOCK *Block, size_t Length, char *Data) {
    size_t uCount;
    uint8_t uByte;
    int nResult;

    if((nResult = block_append(Block, Length, Data)) != (int) Length)
        return nResult;
    if((Length % Context->Align) != 0) {
        uByte = 0;
        uCount = (Context->Align - (Length % Context->Align));
        for(; uCount > 0; --uCount) {
            if((nResult = block_append(Block, 1, ( char * ) &uByte)) != 1)
                return nResult;
        }
    }
    return 0;
}

