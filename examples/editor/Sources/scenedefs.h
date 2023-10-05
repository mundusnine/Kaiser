#pragma once

#include <stdint.h>
#include "raylib.h"
#include "raymath.h"

#define UUID_STR_BUFFER_SIZE (int)sizeof("xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx")

#define MAX_NAME_SIZE 32
#define MAX_ENTITIES UINT16_MAX
#define MAX_RENDERING_INSTANCES 64

typedef struct KEntity{
    Matrix transform;
    Model model;
    char uuid[UUID_STR_BUFFER_SIZE];
    char name[MAX_NAME_SIZE];
} KEntity;

typedef struct KScene {
    uint16_t num_entities;
    KEntity entities[MAX_ENTITIES];
} KScene;