#pragma once

#include <enginedefs.h>
#include <stdint.h>

typedef struct IGfx {
    void (*begin)(int window);
    void (*end)(int window);
    void (*begin3D)(Camera cam);
    void (*end3D)(void);
    void (*clear)(unsigned color);
    void (*setColor)(unsigned color);
    void (*drawRect)(float x, float y, float w,float h,float strength);
    void (*fillRect)(float x, float y, float w,float h);
    void (*drawLine)(float x1, float y1, float x2, float y2);
    
    uint64_t (*loadImg)(const char* filepath);
    void (*drawImg)(uint64_t id,KRect src, KRect dst,float angle,KFlip flip);
    void (*getImgSize)(uint64_t id,int* w,int* h);

    uint64_t (*loadMesh)(const char* filepath);
    void (*drawMesh)(uint64_t id);
} IGfx;

void create_graphics_provider(void* engine);