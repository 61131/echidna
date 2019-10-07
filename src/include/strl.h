#ifndef _STRL_H
#define _STRL_H


#include <sys/types.h>


size_t strlcat(char *dst, const char *src, size_t dsize);

size_t strlcpy(char *dst, const char *src, size_t dsize);


#endif  //  _STRL_H
