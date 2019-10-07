#ifndef _STANDARD_SELECT_H
#define _STANDARD_SELECT_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_limit(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_max(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_min(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_mux(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sel(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_SELECT_H
