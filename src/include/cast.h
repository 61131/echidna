#ifndef _CAST_H
#define _CAST_H


#include <value.h>


int cast_lreal(VALUE *Value);

int cast_real(VALUE *Value);

int cast_lint(VALUE *Value);

int cast_dint(VALUE *Value);

int cast_int(VALUE *Value);

int cast_sint(VALUE *Value);

int cast_ulint(VALUE *Value);

int cast_udint(VALUE *Value);

int cast_uint(VALUE *Value);

int cast_usint(VALUE *Value);

int cast_time(VALUE *Value);

int cast_lword(VALUE *Value);

int cast_dword(VALUE *Value);

int cast_word(VALUE *Value);

int cast_byte(VALUE *Value);

int cast_bool(VALUE *Value);

int cast_string(VALUE *Value);

int cast_wstring(VALUE *Value);

int cast_date(VALUE *Value);

int cast_dt(VALUE *Value);

int cast_tod(VALUE *Value);


#endif  /* _CAST_H */
