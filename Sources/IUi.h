#pragma once
#include <enginedefs.h>

typedef struct IUi {
    void (*begin)(const char* name,int* open,int flags);
    int (*button)(const char* label);
    void (*end)(void);
    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
} IUi;

void create_ui_provider(void* engine);