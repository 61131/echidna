#define _DEFAULT_SOURCE         //  Required for vsyslog since glibc 2.19

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <syslog.h>

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
        if(/* isatty(fileno(pFile)) */ 1) {
            fprintf(pFile, "%s: ", _Level[Priority]);
            vfprintf(pFile, Format, sArg);
            fprintf(pFile, "\n");
            fflush(pFile);
        }
        else
            vsyslog(Priority, Format, sArg);

        va_end(sArg);
    }
    if(Priority == LOG_EMERG) 
        exit(1);
}
