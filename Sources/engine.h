#pragma once

#include "ITimer.h"
#include "IInput.h"
#include "IGfx.h"
#include "ISfx.h"
#include "IWorld.h"
#include "ILevelLoader.h"

typedef struct Engine {
    const ITimer* timer;
    const IInput* input;
    const IGfx* gfx;
    const ISfx* sfx;
    const IWorld* world;
    const ILevelLoader* loader;
} Engine;


/*
* This needs to be implemented by your game.
* It should call engine_init and then engine_start.
*/
void init_gameplay(void);


void engine_init(const char* window_name,int w, int h);
void engine_update(void);
void engine_start(void);

const Engine* engine_get(void);