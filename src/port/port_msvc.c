#ifdef _MSC_VER
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "deps.h"

# define TOLOWER(Ch) tolower (Ch)

int strcasecmp(const char* s1, const char* s2)
{
  const unsigned char* p1 = (const unsigned char*)s1;
  const unsigned char* p2 = (const unsigned char*)s2;
  int result;

  if (p1 == p2)
    return 0;

  while ((result = TOLOWER(*p1) - TOLOWER(*p2++)) == 0)
    if (*p1++ == '\0')
      break;

  return result;
}


#include <time.h>

struct tm* gmtime_r(const time_t* timer, struct tm* buf)
{
  gmtime_s(buf, timer);
  return buf;
}

// Algorithm: http://howardhinnant.github.io/date_algorithms.html
static int days_from_epoch(int y, int m, int d)
{
  y -= m <= 2;
  int era = y / 400;
  int yoe = y - era * 400;                                   // [0, 399]
  int doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;  // [0, 365]
  int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;           // [0, 146096]
  return era * 146097 + doe - 719468;
}

// It  does not modify broken-down time
time_t timegm(struct tm const* t)
{
  int year = t->tm_year + 1900;
  int month = t->tm_mon;          // 0-11
  if (month > 11)
  {
    year += month / 12;
    month %= 12;
  }
  else if (month < 0)
  {
    int years_diff = (11 - month) / 12;
    year -= years_diff;
    month += 12 * years_diff;
  }
  int days_since_epoch = days_from_epoch(year, month + 1, t->tm_mday);

  return 60 * (60 * (24L * days_since_epoch + t->tm_hour) + t->tm_min) + t->tm_sec;
}




#if defined _WIN32 || defined __WIN32__ || defined __EMX__ || defined __DJGPP__
/* Win32, OS/2, DOS */
# define HAS_DEVICE(P) \
((((P)[0] >= 'A' && (P)[0] <= 'Z') || ((P)[0] >= 'a' && (P)[0] <= 'z')) \
&& (P)[1] == ':')
# define FILESYSTEM_PREFIX_LEN(P) (HAS_DEVICE (P) ? 2 : 0)
# define ISSLASH(C) ((C) == '/' || (C) == '\\')
#endif

#ifndef FILESYSTEM_PREFIX_LEN
# define FILESYSTEM_PREFIX_LEN(Filename) 0
#endif

#ifndef ISSLASH
# define ISSLASH(C) ((C) == '/')
#endif

char* basename(char const* name)
{
  char const* base = name += FILESYSTEM_PREFIX_LEN(name);
  int all_slashes = 1;
  char const* p;

  for (p = name; *p; p++)
  {
    if (ISSLASH(*p))
      base = p + 1;
    else
      all_slashes = 0;
  }

  /* If NAME is all slashes, arrange to return `/'. */
  if (*base == '\0' && ISSLASH(*name) && all_slashes)
    --base;

  /* Make sure the last byte is not a slash. */
  assert(all_slashes || !ISSLASH(*(p - 1)));

  return (char*)base;
}

#endif