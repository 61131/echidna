#ifndef _OPERATOR_LOGICAL_H
#define _OPERATOR_LOGICAL_H


#include <frame.h>
#include <value.h>


int operator_and(FRAME *Frame, VALUE *Value);

int operator_not(FRAME *Frame, VALUE *Value);

int operator_or(FRAME *Frame, VALUE *Value);

int operator_xor(FRAME *Frame, VALUE *Value);


#endif  //  _OPERATOR_LOGICAL_H
