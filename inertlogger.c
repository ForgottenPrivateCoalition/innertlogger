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

char time_str[9];

void utime(){
    time_t now;
    struct tm *timeinfo;
    
    time(&now);
    timeinfo = localtime(&now);
    strftime(time_str, 9, "%H:%M:%S", timeinfo);
}

void ilog(Level lvl, int db, const char* format, ...) {
    utime();
    
    va_list args;
    va_start(args, format);
    
    switch(lvl) {
        case DEBUG:
            if(db != 0) {
                printf("[%s] [DEBUG] ", time_str);
                vprintf(format, args);
            }
            break;
        
        case INFO:
            printf("[%s] [INFO] ", time_str);
            vprintf(format, args);
            printf("\n");
            break;
        
        case WARN:
            printf("[%s] [WARN] ", time_str);
            vprintf(format, args);
            printf("\n");
            break;
        
        case ERROR:
            printf("[%s] [ERROR] ", time_str);
            vprintf(format, args);
            printf("\n");
            break;
        
        case FATAL_ERROR:
            printf("[%s] [FATAL] ", time_str);
            vprintf(format, args);
            printf("\n");
            break;
        
        default:
            printf("[WARN] InnerLogger can't write message! Please change log level.\n");
            break;
    }
    
    va_end(args);
}