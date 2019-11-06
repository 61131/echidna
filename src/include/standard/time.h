#ifndef _STANDARD_TIME_H
#define _STANDARD_TIME_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_add_dttime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_add_time(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_add_todtime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_divtime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_multime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub_datedate(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub_dtdt(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub_dttime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub_time(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub_todtime(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_sub_todtod(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_TIME_H
