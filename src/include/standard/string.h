#ifndef _STANDARD_STRING_H
#define _STANDARD_STRING_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_concat(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_delete(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_find(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_insert(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_left(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_len(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_mid(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_replace(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_right(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_STRING_H
