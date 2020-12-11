#pragma once

#include <kinc/math/matrix.h>

#include "script.h"

typedef struct {
    kinc_matrix4x4_t transform[3];
    Script* scripts;
    int32_t num_scripts;
} Object;

KINC_FUNC Object* create_object(int32_t number_of_scripts);

KINC_FUNC void addScript(Script* script);