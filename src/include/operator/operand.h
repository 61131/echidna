#ifndef _OPERATOR_OPERAND_H
#define _OPERATOR_OPERAND_H


#include <frame.h>
#include <value.h>


int operand_invert(FRAME *Frame, VALUE *Value);

int operand_subrange(VALUE *Value, VALUE *Range);


#endif  //  _OPERATOR_OPERAND_H
