#ifndef _STANDARD_BITSTRING_H
#define _STANDARD_BITSTRING_H


#include <echidna.h>
#include <ll.h>
#include <value.h>


int standard_rol(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_ror(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_shl(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);

int standard_shr(ECHIDNA *Context, const char *Name, LL *Parameters, VALUE *Result, void *User);


#endif  //  _STANDARD_BITSTRING_H
