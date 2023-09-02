#pragma once

#include "IInput.h"

typedef struct Engine {
    const IInput* input;
} Engine;


void engine_init(const char* window_name,int w, int h);
void engine_update(void);
void engine_start(void);