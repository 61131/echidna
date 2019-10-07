#ifndef _FILE_H
#define _FILE_H


#include <echidna.h>


int file_read(ECHIDNA *Context, char *Path);

int file_write(ECHIDNA *Context, char *Path);


#endif  /* _FILE_H */
