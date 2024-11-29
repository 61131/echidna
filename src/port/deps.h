#ifndef DEPS_H__
#define DEPS_H__

#include <time.h>

int strcasecmp(const char* s1, const char* s2);

struct tm* gmtime_r(const time_t* timer, struct tm* buf);

time_t timegm(struct tm const* t);

char* basename(char const* name);

#endif