#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>

extern "C" {
    
#ifdef LOGGING

#define DEBUG_PRINT(...) fprintf(logfile, __VA_ARGS__)
#define ENTER() DEBUG_PRINT("%s:%d Entering %s\n", __FILE__, __LINE__, __func__)
#define EXIT() DEBUG_PRINT("%s:%d Exiting %s\n", __FILE__, __LINE__, __func__)
#define LOG(...) DEBUG_PRINT(__VA_ARGS__)

extern FILE* logfile;

static void openlogfile() {
    logfile = fopen("log/log.txt", "w");
    setvbuf(logfile, NULL, _IONBF, 0);
}

#else
#define DEBUG_PRINT(...) 
#define ENTER() 
#define EXIT() 
#define LOG(...) 
static void openlogfile() {}
#endif

}

#endif /* __LOGGER_H__ */
