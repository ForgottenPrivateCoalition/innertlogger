#ifndef INERTLOGGER_H
#define INERTLOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL_ERROR,
    STDOUT
} Level;

typedef enum {
    ENABLE_DEBUG,
    ENABLE_COLORS,
    SET_COLOR_DEBUG,
    SET_COLOR_INFO,
    SET_COLOR_WARN,
    SET_COLOR_ERROR,
    SET_COLOR_FATAL_ERROR,
    ENABLE_TIME,
    ENABLE_PREFIX
} PropertiesKey;

void iconfig(PropertiesKey key, const char* value);
void ilog(Level lvl, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif // INERTLOGGER_H