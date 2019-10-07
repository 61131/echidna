#ifndef _STANDARD_TYPE_H
#define _STANDARD_TYPE_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_bcd(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_trunc(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_type(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_TYPE_H
