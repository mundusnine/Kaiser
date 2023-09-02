#pragma once


#include "script.h"

typedef struct {
    // kinc_matrix4x4_t transform[3];
    // Script* scripts;
    int32_t num_scripts;
} Object;

Object* create_object(int32_t number_of_scripts);

// void addScript(Script* script);