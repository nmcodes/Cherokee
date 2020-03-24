/*
** main.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdarg.h>

#define LOG_VERSION "0.1.0"

typedef void (*log_LockFn)(void *udata, int lock);

enum  { SFTWR_LOG_TRACE, SFTWR_LOG_DEBUG, SFTWR_LOG_INFO, SFTWR_LOG_WARN, SFTWR_LOG_ERROR, SFTWR_LOG_FATAL };

#define log_trace(...) log_log(SFTWR_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(SFTWR_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(SFTWR_LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(SFTWR_LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(SFTWR_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(SFTWR_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_set_udata(void *udata);
void log_set_lock(log_LockFn fn);
void log_set_fp(FILE *fp);
void log_set_level(int level);
void log_set_quiet(int enable);

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif
