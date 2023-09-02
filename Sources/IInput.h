#pragma once

#include "enginedefs.h"

typedef enum keys {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
} keys_e;

typedef struct IInput {
    int (*isKeyDown)(int key);
    int (*isButtonDown)(int button );
    void (*getMousePosition)(int* x, int* y);
    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
} IInput;

void create_input_provider(void* engine);