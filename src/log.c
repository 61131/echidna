#define _DEFAULT_SOURCE         //  Required for vsyslog since glibc 2.19

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#ifndef _MSC_VER
#include <unistd.h>
#include <syslog.h>
#endif
#include <log.h>


static char * _Level[] = { "emerg", "alert", "crit", "error", "warn", "notice", "info", "debug" };

int log_level = LOG_DEBUG;


void
log_message(int Priority, const char *Format, ...) {
    FILE *pFile;
    va_list sArg;

    if(log_level == LOG_NONE)
        return;
    if(Priority <= log_level) {
        //pFile = (log_level <= LOG_ERR) ? stderr : stdout;
        pFile = stderr;
        va_start(sArg, Format);
#ifndef _MSC_VER
        if(/* isatty(fileno(pFile)) */ 1) {
#endif
            fprintf(pFile, "%s: ", _Level[Priority]);
            vfprintf(pFile, Format, sArg);
            fprintf(pFile, "\n");
            fflush(pFile);
#ifndef _MSC_VER
        }
        else
            vsyslog(Priority, Format, sArg);
#endif
        va_end(sArg);
    }
    if(Priority == LOG_EMERG) 
        exit(1);
}
