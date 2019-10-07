#ifndef _LOG_H
#define _LOG_H


/* Re-use log levels from syslog.h */

#include <syslog.h>


#define LOG_NONE                (-1)

#define log_emerg(...)          log_message(LOG_EMERG, __VA_ARGS__)
#define log_alert(...)          log_message(LOG_ALERT, __VA_ARGS__)
#define log_critical(...)       log_message(LOG_CRIT, __VA_ARGS__)
#define log_crit(...)           log_message(LOG_CRIT, __VA_ARGS__)
#define log_err(...)            log_message(LOG_ERR, __VA_ARGS__)
#define log_error(...)          log_message(LOG_ERR, __VA_ARGS__)
#define log_warning(...)        log_message(LOG_WARNING, __VA_ARGS__)
#define log_warn(...)           log_message(LOG_WARNING, __VA_ARGS__)
#define log_notice(...)         log_message(LOG_NOTICE, __VA_ARGS__)
#define log_info(...)           log_message(LOG_INFO, __VA_ARGS__)
#define log_debug(...)          log_message(LOG_DEBUG, __VA_ARGS__)


void log_message(int Priority, const char *Format, ...);

extern int log_level;


#endif
