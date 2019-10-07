#ifndef _OPERATOR_ARITHMETIC_H
#define _OPERATOR_ARITHMETIC_H


#include <frame.h>
#include <value.h>


int operator_add(FRAME *Frame, VALUE *Value);

int operator_div(FRAME *Frame, VALUE *Value);

int operator_mod(FRAME *Frame, VALUE *Value);

int operator_mul(FRAME *Frame, VALUE *Value);

int operator_sub(FRAME *Frame, VALUE *Value);


#endif  //  _OPERATOR_ARITHMETIC_H
