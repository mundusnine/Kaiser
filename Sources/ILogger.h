#pragma once

#include <enginedefs.h>
#include <stdint.h>
typedef enum {
    L_INFO,
    L_WARNING,
    L_ERROR,
    L_DEBUG
} LogLevel;

typedef struct ILogger {
    void (*write)(int log_level,char* format,...);
    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
} ILogger;

void create_logger_provider(void* engine);