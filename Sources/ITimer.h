#pragma once

#include <enginedefs.h>
#include <stdint.h>

typedef struct ITimer {
    float (*dt)(void);
    void (*sleep_end_frame)(void);
    void (*set_max_fps)(int fps);
    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
} ITimer;

void create_timer_provider(void* engine);