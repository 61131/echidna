#ifndef _OPERATOR_COMPARISON_H
#define _OPERATOR_COMPARISON_H


#include <frame.h>
#include <value.h>


int operator_eq(FRAME *Frame, VALUE *Value);

int operator_ge(FRAME *Frame, VALUE *Value);

int operator_gt(FRAME *Frame, VALUE *Value);

int operator_le(FRAME *Frame, VALUE *Value);

int operator_lt(FRAME *Frame, VALUE *Value);

int operator_ne(FRAME *Frame, VALUE *Value);


#endif  //  _OPERATOR_COMPARISON_H
