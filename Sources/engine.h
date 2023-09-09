#pragma once

#include "ITimer.h"
#include "IInput.h"
#include "IGfx.h"

typedef struct Engine {
    const ITimer* timer;
    const IInput* input;
    const IGfx* gfx;
} Engine;


void engine_init(const char* window_name,int w, int h);
void engine_update(void);
void engine_start(void);

const Engine* engine_get(void);