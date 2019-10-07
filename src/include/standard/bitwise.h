#ifndef _STANDARD_BITWISE_H
#define _STANDARD_BITWISE_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_and(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_or(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_xor(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_BITWISE_H
