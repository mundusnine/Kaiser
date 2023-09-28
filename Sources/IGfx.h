#pragma once

#include <enginedefs.h>
#include <stdint.h>

typedef struct IGfx {
    void (*begin)(int window);
    void (*end)(int window);
    void (*begin3D)(Camera cam);
    void (*end3D)(void);
    void (*clear)(unsigned color);
    void (*getWindowSize)(int* w,int* h);

    void (*setColor)(unsigned color);
    void (*drawRect)(float x, float y, float w,float h,float strength);
    void (*fillRect)(float x, float y, float w,float h);
    void (*drawLine)(float x1, float y1, float x2, float y2);
    
    UID (*loadImg)(const char* filepath);
    void (*drawImg)(UID id,KRect src, KRect dst,float angle,KFlip flip);
    void (*getImgSize)(UID id,int* w,int* h);

    UID (*loadMesh)(const char* filepath);
    void (*drawMesh)(UID id);
} IGfx;

#ifdef __cplusplus
extern "C"{
#endif

void create_graphics_provider(void* engine);

#ifdef __cplusplus
}
#endif