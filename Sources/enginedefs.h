#pragma once

#ifndef RAYLIB_PROVIDER
#include "rcamera.h"
#include "raymath.h"
#else
#include "raylib.h"
#endif

typedef struct KRect{
    float x;
    float y;
    float w;
    float h;
} KRect;

typedef struct KFlip{
    int x;
    int y;
} KFlip; 

#define MAX_IMAGES 512
#define MAX_PRIVATE_FUNCS 1