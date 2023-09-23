#include "ILogger.h"

#include"engine.h"
#include "raylib.h"

#include <stdio.h>
#include <stdarg.h>

#ifdef NDEBUG
static FILE* logs = NULL;
#endif
void raylib_write(int log_level,char* format,...){
    va_list args;
    va_start(args, format);
#ifdef _DEBUG
    TraceLog(log_level,format,args);
#elif defined(NDEBUG)
    vfprintf(logs,format,args);
#endif
    va_end(args);
}

void raylib_logger_shutdown(void* data){
#ifdef NDEBUG
    fclose(logs);
#else
    TraceLog(LOG_INFO,"LOGGER: Shutting down logger");
#endif
}

static ILogger log = {0};
void create_logger_provider(void* engine){
    //@TODO: close file at some point...
    #ifdef NDEBUG
    logs = fopen("logs.txt","w+");
    #endif
    log.write = raylib_write;

    log.private_funcs[2] = raylib_logger_shutdown;

    Engine* eng = (Engine*)engine;
    eng->log = &log;
}