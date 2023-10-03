#pragma once

#ifndef RAYLIB_PROVIDER
#include "rcamera.h"
#include "raymath.h"
#else
#include "raylib.h"
#endif
#include <stdlib.h>
#include <stdint.h>

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

//@TODO: Have a way to generate components type and entity fields
// based on data definitions, Maybe ?
typedef enum Component_e{
    Renderable,
    Updateable,
    Both = (Renderable+1) | (Updateable+1) // 3
} Component_e;

typedef enum Asset{
    Texture_e,
    Font_e,
    Model_e,
    NUM_ASSETS_TYPES
} Asset;

typedef struct Component Component;
typedef struct Entity Entity;

#define MAX_COMPONENTS 16
#define MAX_IMAGES 512
#define MAX_ENTITIES 512 // @TODO: We will make the entity amount dynamic
#define MAX_PRIVATE_FUNCS 3

#define UID uint16_t
#define BAD_UID UINT16_MAX

struct Component{
    Component_e type;
    void (*funcs[2])(Entity* ent);
};
struct Entity {
    uint8_t active;
    Matrix transform;
    Component* components[MAX_COMPONENTS];
    UID assets[NUM_ASSETS_TYPES];
    UID id;
};