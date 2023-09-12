#pragma once

#include "enginedefs.h"
#include "stdint.h"

typedef struct IWorld {
    UID (*createEntity)(Vector3 position,Vector3 scale,Vector3 rotation);
    int (*addComponent)(UID id,void* component);
    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
} IWorld;

void create_world_provider(void* engine);