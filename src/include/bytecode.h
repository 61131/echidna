#ifndef _BYTECODE_H
#define _BYTECODE_H


#include <stdlib.h>

#include <block.h>
#include <echidna.h>
#include <macros.h>
#include <value.h>

#include <bytecode/generate.h>
#include <bytecode/label.h>
#include <bytecode/stack.h>


#define VALUE_MASK              (0x0000ffff)
#define VALUE_SHIFT             (0)
#define MODIFIER_MASK           (0x00ff0000)
#define MODIFIER_SHIFT          (16)
#define OP_MASK                 (0xff000000)
#define OP_SHIFT                (24)

#define G_VALUE(x)              (((x) & VALUE_MASK) >> VALUE_SHIFT)
#define G_MODIFIER(x)           (((x) & MODIFIER_MASK) >> MODIFIER_SHIFT)
#define G_OP(x)                 (((x) & OP_MASK) >> OP_SHIFT)
#define S_VALUE(x)              (((x) << VALUE_SHIFT) & VALUE_MASK)
#define S_MODIFIER(x)           (((x) << MODIFIER_SHIFT) & MODIFIER_MASK)
#define S_OP(x)                 (((x) << OP_SHIFT) & OP_MASK)

#define S_BYTECODE(op, mod)     (S_OP((op)) | S_MODIFIER((mod)))

/*
    The following enumeration contains the operators supported by the virtual 
    machine runtime.
*/

typedef enum _BYTECODE_OP {

    OP_NONE                     = _B(000000),   /* 0 */
    OP_NOP                      = _B(000001),   /* 1 */
    OP_LD                       = _B(000010),   /* 2 */    
    OP_ST                       = _B(000011),   /* 3 */
    OP_S                        = _B(000100),   /* 4 */
    OP_R                        = _B(000101),   /* 5 */
    OP_S1                       = _B(000110),   /* 6 */
    OP_R1                       = _B(000111),   /* 7 */
    OP_CLK                      = _B(001000),   /* 8 */
    OP_CU                       = _B(001001),   /* 9 */
    OP_CD                       = _B(001010),   /* 10 */
    OP_IN                       = _B(001011),   /* 11 */
    OP_PT                       = _B(001100),   /* 12 */
    OP_PV                       = _B(001101),   /* 13 */
    OP_AND                      = _B(001110),   /* 14 */
    OP_OR                       = _B(001111),   /* 15 */
    OP_XOR                      = _B(010000),   /* 16 */
    OP_NOT                      = _B(010001),   /* 17 */
    OP_ADD                      = _B(010010),   /* 18 */
    OP_SUB                      = _B(010011),   /* 19 */
    OP_MUL                      = _B(010100),   /* 20 */
    OP_DIV                      = _B(010101),   /* 21 */
    OP_MOD                      = _B(010110),   /* 22 */
    OP_GT                       = _B(010111),   /* 23 */
    OP_GE                       = _B(011000),   /* 24 */
    OP_EQ                       = _B(011001),   /* 25 */
    OP_NE                       = _B(011010),   /* 26 */
    OP_LE                       = _B(011011),   /* 27 */
    OP_LT                       = _B(011100),   /* 28 */
    OP_JMP                      = _B(011101),   /* 29 */
    OP_CAL                      = _B(011110),   /* 30 */
    OP_RET                      = _B(011111),   /* 31 */
    OP_PARENTHESIS              = _B(100000),   /* 32 */
    OP_PARAMETER                = _B(100001),   /* 33 */
}
BYTECODE_OP;

typedef enum _BYTECODE_MODIFIER {

    MODIFIER_NONE               = _B(000),      /* 0 */
    MODIFIER_C                  = _B(001),      /* 1 */
    MODIFIER_N                  = _B(010),      /* 2 */
    MODIFIER_PARENTHESIS        = _B(100),      /* 4 */
}
BYTECODE_MODIFIER;

typedef enum _BYTECODE_BYTECODE {

    BYTECODE_NOP                = S_BYTECODE(OP_NOP, MODIFIER_NONE),
    BYTECODE_LD                 = S_BYTECODE(OP_LD, MODIFIER_NONE),
    BYTECODE_LDN                = S_BYTECODE(OP_LD, MODIFIER_N),
    BYTECODE_ST                 = S_BYTECODE(OP_ST, MODIFIER_NONE),
    BYTECODE_STN                = S_BYTECODE(OP_ST, MODIFIER_N),
    BYTECODE_S                  = S_BYTECODE(OP_S, MODIFIER_NONE),
    BYTECODE_R                  = S_BYTECODE(OP_R, MODIFIER_NONE),
    BYTECODE_S1                 = S_BYTECODE(OP_S1, MODIFIER_NONE),
    BYTECODE_R1                 = S_BYTECODE(OP_R1, MODIFIER_NONE),
    BYTECODE_CLK                = S_BYTECODE(OP_CLK, MODIFIER_NONE),
    BYTECODE_CD                 = S_BYTECODE(OP_CD, MODIFIER_NONE),
    BYTECODE_CU                 = S_BYTECODE(OP_CU, MODIFIER_NONE),
    BYTECODE_IN                 = S_BYTECODE(OP_IN, MODIFIER_NONE),
    BYTECODE_PT                 = S_BYTECODE(OP_PT, MODIFIER_NONE),
    BYTECODE_PV                 = S_BYTECODE(OP_PV, MODIFIER_NONE),
    BYTECODE_AND                = S_BYTECODE(OP_AND, MODIFIER_NONE),
    BYTECODE_AND_P              = S_BYTECODE(OP_AND, MODIFIER_PARENTHESIS),
    BYTECODE_ANDN               = S_BYTECODE(OP_AND, MODIFIER_N),
    BYTECODE_ANDN_P             = S_BYTECODE(OP_AND, MODIFIER_N | MODIFIER_PARENTHESIS),
    BYTECODE_OR                 = S_BYTECODE(OP_OR, MODIFIER_NONE),
    BYTECODE_OR_P               = S_BYTECODE(OP_OR, MODIFIER_PARENTHESIS),
    BYTECODE_ORN                = S_BYTECODE(OP_OR, MODIFIER_N),
    BYTECODE_ORN_P              = S_BYTECODE(OP_OR, MODIFIER_N | MODIFIER_PARENTHESIS),
    BYTECODE_XOR                = S_BYTECODE(OP_XOR, MODIFIER_NONE),
    BYTECODE_XOR_P              = S_BYTECODE(OP_XOR, MODIFIER_PARENTHESIS),
    BYTECODE_XORN               = S_BYTECODE(OP_XOR, MODIFIER_N),
    BYTECODE_XORN_P             = S_BYTECODE(OP_XOR, MODIFIER_N | MODIFIER_PARENTHESIS),
    BYTECODE_NOT                = S_BYTECODE(OP_NOT, MODIFIER_NONE),
    BYTECODE_ADD                = S_BYTECODE(OP_ADD, MODIFIER_NONE),
    BYTECODE_ADD_P              = S_BYTECODE(OP_ADD, MODIFIER_PARENTHESIS),
    BYTECODE_SUB                = S_BYTECODE(OP_SUB, MODIFIER_NONE),
    BYTECODE_SUB_P              = S_BYTECODE(OP_SUB, MODIFIER_PARENTHESIS),
    BYTECODE_MUL                = S_BYTECODE(OP_MUL, MODIFIER_NONE),
    BYTECODE_MUL_P              = S_BYTECODE(OP_MUL, MODIFIER_PARENTHESIS),
    BYTECODE_DIV                = S_BYTECODE(OP_DIV, MODIFIER_NONE),
    BYTECODE_DIV_P              = S_BYTECODE(OP_DIV, MODIFIER_PARENTHESIS),
    BYTECODE_MOD                = S_BYTECODE(OP_MOD, MODIFIER_NONE),
    BYTECODE_MOD_P              = S_BYTECODE(OP_MOD, MODIFIER_PARENTHESIS),
    BYTECODE_GT                 = S_BYTECODE(OP_GT, MODIFIER_NONE),
    BYTECODE_GT_P               = S_BYTECODE(OP_GT, MODIFIER_PARENTHESIS),
    BYTECODE_GE                 = S_BYTECODE(OP_GE, MODIFIER_NONE),
    BYTECODE_GE_P               = S_BYTECODE(OP_GE, MODIFIER_PARENTHESIS),
    BYTECODE_EQ                 = S_BYTECODE(OP_EQ, MODIFIER_NONE),
    BYTECODE_EQ_P               = S_BYTECODE(OP_EQ, MODIFIER_PARENTHESIS),
    BYTECODE_NE                 = S_BYTECODE(OP_NE, MODIFIER_NONE),
    BYTECODE_NE_P               = S_BYTECODE(OP_NE, MODIFIER_PARENTHESIS),
    BYTECODE_LE                 = S_BYTECODE(OP_LE, MODIFIER_NONE),
    BYTECODE_LE_P               = S_BYTECODE(OP_LE, MODIFIER_PARENTHESIS),
    BYTECODE_LT                 = S_BYTECODE(OP_LT, MODIFIER_NONE),
    BYTECODE_LT_P               = S_BYTECODE(OP_LT, MODIFIER_PARENTHESIS),
    BYTECODE_CAL                = S_BYTECODE(OP_CAL, MODIFIER_NONE),
    BYTECODE_CALC               = S_BYTECODE(OP_CAL, MODIFIER_C),
    BYTECODE_CALCN              = S_BYTECODE(OP_CAL, MODIFIER_C | MODIFIER_N),
    BYTECODE_JMP                = S_BYTECODE(OP_JMP, MODIFIER_NONE),
    BYTECODE_JMPC               = S_BYTECODE(OP_JMP, MODIFIER_C),
    BYTECODE_JMPCN              = S_BYTECODE(OP_JMP, MODIFIER_C | MODIFIER_N),
    BYTECODE_RET                = S_BYTECODE(OP_RET, MODIFIER_NONE),
    BYTECODE_RETC               = S_BYTECODE(OP_RET, MODIFIER_C),
    BYTECODE_RETCN              = S_BYTECODE(OP_RET, MODIFIER_C | MODIFIER_N),
    BYTECODE_PARENTHESIS        = S_BYTECODE(OP_PARENTHESIS, MODIFIER_NONE),
    BYTECODE_PARAMETER          = S_BYTECODE(OP_PARAMETER, MODIFIER_NONE),

    BYTECODE_MASK               = (OP_MASK | MODIFIER_MASK),
}
BYTECODE_BYTECODE;


typedef VALUE_TYPE BYTECODE_VALUE;

typedef uint32_t BYTECODE;


int bytecode_configuration(ECHIDNA *Context);

const char * bytecode_typetostr(BYTECODE BC);

int bytecode_write(ECHIDNA *Context, BLOCK *Block, size_t Length, char *Data);


#endif  /* _BYTECODE_H */

