#ifndef _STANDARD_COMPARISON_H
#define _STANDARD_COMPARISON_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_eq(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_ge(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_gt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_le(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_lt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_ne(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_COMPARISON_H
