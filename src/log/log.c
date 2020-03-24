/*
** main.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/file.h>

#include "log.h"

static struct {
    void *udata;
    log_LockFn lock;
    FILE *fp;
    int level;
    int quiet;
} L;


static const char *level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};


static void lock(void)   {
    if (L.lock) {
        L.lock(L.udata, 1);
    }
}


static void unlock(void) {
    if (L.lock) {
        L.lock(L.udata, 0);
    }
}


void log_set_udata(void *udata) {
    L.udata = udata;
}


void log_set_lock(log_LockFn fn) {
    L.lock = fn;
}


void log_set_fp(FILE *fp) {
    L.fp = fp;
}


void log_set_level(int level) {
    L.level = level;
}


void log_set_quiet(int enable) {
    L.quiet = enable ? 1 : 0;
}


void log_log(int level, const char *file, int line, const char *fmt, ...) {
    if (level < L.level) {
        return;
    }

    /* Acquire lock */
    lock();

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    /* Log to stderr */
    if (!L.quiet) {
        va_list args;
        char buf[16];
        char buf2[1024];
        char buf3[1024];
        char logbuf[2080];

        buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
        sprintf(
            buf2,
            "[%d] %s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
            (int) getpid(), buf, level_colors[level], level_names[level], file, line
        );

        va_start(args, fmt);
        vsprintf(buf3, fmt, args);
        va_end(args);

        memset(logbuf, '\0', 2080);
        strcat(logbuf, buf2);
        strcat(logbuf, buf3);
        strcat(logbuf, "\n");

        int lock_failed = flock(fileno(stderr), LOCK_EX);
        if (!lock_failed) {
            fwrite(logbuf, sizeof(char), strlen(logbuf), stderr);
            fflush(stderr);
            flock(fileno(stderr), LOCK_UN);
        }
    }

    /* Log to file */
    if (L.fp) {
        va_list args;
        char buf[32];
        char buf2[1024];
        char buf3[1024];
        char logbuf[2080];

        buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';

        sprintf(buf2, "%s %-5s %s:%d: ", buf, level_names[level], file, line);
        va_start(args, fmt);
        vsprintf(buf3, fmt, args);
        va_end(args);

        memset(logbuf, '\0', 2080);
        strcat(logbuf, buf2);
        strcat(logbuf, buf3);
        strcat(logbuf, "\n");

        int lock_failed = flock(fileno(L.fp), LOCK_EX);
        if (!lock_failed) {
            fwrite(logbuf, sizeof(char), strlen(logbuf), L.fp);
            fflush(L.fp);
            flock(fileno(L.fp), LOCK_UN);
        }
    }

    /* Release lock */
    unlock();
}
