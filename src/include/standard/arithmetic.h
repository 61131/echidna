#ifndef _STANDARD_ARITHMETIC_H
#define _STANDARD_ARITHMETIC_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_add(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_mul(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_div(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_mod(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_expt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_move(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_ARITHMETIC_H
