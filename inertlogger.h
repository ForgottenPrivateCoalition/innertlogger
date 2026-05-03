#ifndef INERTLOGGER_H
#define INERTLOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL_ERROR
} Level;

void ilog(Level lvl, int db, const char* format, ...);

#endif