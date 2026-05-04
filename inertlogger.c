#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct {
    int edebug;
    int ecolors;
    int etime;
    int eprefix;
    char cdebug[14];
    char cinfo[14];
    char cwarn[14];
    char cerror[14];
    char cfatal[14];
    char cstdout[14];
} PropertiesValue;

PropertiesValue Properties = {
    .edebug = 1,
    .ecolors = 1,
    .etime = 1,
    .eprefix = 1,
    .cdebug = "255, 0, 240",
    .cinfo = "0, 230, 0",
    .cwarn = "240, 190, 0",
    .cerror = "210, 0, 0",
    .cfatal = "255, 0, 0",
    .cstdout = ""
};

char strtime[12];
char strprefix[15];
char *strcolor;

void iconfig(PropertiesKey key, const char* value) {
    switch(key) {
    case ENABLE_DEBUG:
        Properties.edebug = atoi(value);
        break;
    case ENABLE_COLORS:
        Properties.ecolors = atoi(value);
        break;
    case ENABLE_TIME:
        Properties.etime = atoi(value);
        break;
    case ENABLE_PREFIX:
        Properties.eprefix = atoi(value);
        break;
    case SET_COLOR_DEBUG:
        strcpy(Properties.cdebug, value);
        break;
    case SET_COLOR_INFO:
        strcpy(Properties.cinfo, value);
        break;
    case SET_COLOR_WARN:
        strcpy(Properties.cwarn, value);
        break;
    case SET_COLOR_ERROR:
        strcpy(Properties.cerror, value);
        break;
    case SET_COLOR_FATAL_ERROR:
        strcpy(Properties.cfatal, value);
        break;
    }
}

char* cctrgb(const char* rgb_string) {
    if(rgb_string == NULL || rgb_string[0] == '\0') return "";
    
    int r, g, b;
    static char ansi_color[20];
    
    sscanf(rgb_string, "%d, %d, %d", &r, &g, &b);
    snprintf(ansi_color, sizeof(ansi_color), "\033[38;2;%d;%d;%dm", r, g, b);
    
    return ansi_color;
}

#ifdef _WIN32
#include <windows.h>

void set_console_color(const char* rgb_string) {
    if(rgb_string == NULL || rgb_string[0] == '\0' || strcmp(rgb_string, "-1") == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return;
    }
    
    int r, g, b;
    sscanf(rgb_string, "%d, %d, %d", &r, &g, &b);
    
    int color = 0;
    if(r > 128) color |= FOREGROUND_RED;
    if(g > 128) color |= FOREGROUND_GREEN;
    if(b > 128) color |= FOREGROUND_BLUE;
    if(r > 200 || g > 200 || b > 200) color |= FOREGROUND_INTENSITY;
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#endif

void ilog(Level lvl, const char* format, ...) {
    if(Properties.etime == 1) strftime(strtime, sizeof(strtime), "[%H:%M:%S] ", localtime(&(time_t){time(NULL)}));
    
    switch(lvl) {
    case DEBUG:
        if(Properties.edebug == 0) return;
        if(Properties.eprefix == 1) strcpy(strprefix, "[DEBUG] ");
        strcolor = Properties.cdebug;
        break;

    case INFO:
        if(Properties.eprefix == 1) strcpy(strprefix, "[INFO] ");
        strcolor = Properties.cinfo;
        break;

    case WARN:
        if(Properties.eprefix == 1) strcpy(strprefix, "[WARN] ");
        strcolor = Properties.cwarn;
        break;

    case ERROR:
        if(Properties.eprefix == 1) strcpy(strprefix, "[ERROR] ");
        strcolor = Properties.cerror;
        break;

    case FATAL_ERROR:
        if(Properties.eprefix == 1) strcpy(strprefix, "[FATAL ERROR] ");
        strcolor = Properties.cfatal;
        break;

    case STDOUT:
        strtime[0] = '\0';
        strprefix[0] = '\0';
        strcolor = Properties.cstdout;
        break;

    default:
        printf("[InertLogger] An error occurred while defining the prefix. Please change the call");
        break;
        
    }

    va_list args;
    va_start(args, format);
    if (Properties.ecolors == 0) strcolor = '\0';

    #ifdef _WIN32
        set_console_color(strcolor);
        printf("%s%s", strtime, strprefix);
        vprintf(format, args);
        set_console_color("-1");
    #else
        printf("%s%s%s", cctrgb(strcolor), strtime, strprefix);
        vprintf(format, args);
        printf("\033[0m");
    #endif

    printf("\n");
    va_end(args);
}