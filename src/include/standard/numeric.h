#ifndef _STANDARD_NUMERIC_H
#define _STANDARD_NUMERIC_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_abs(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_acos(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_asin(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_atan(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_cos(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_exp(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_ln(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_log(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sin(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sqrt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_tan(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_NUMERIC_H
