#include "ITimer.h"
#include "engine.h"
#include "raylib.h"

static double end;
static double start;
static float dt;
static double target_fps = 1.0/60;
void raylib_timer_update(void* data){
    start = GetTime();
    dt = start - end;
}
float raylib_dt(void){
    return dt;
}

void raylib_set_max_fps(int fps){
    target_fps = 1.0/fps;
}

void raylib_sleep_end_frame(void){
    double sleep_time = GetTime() - start + target_fps;
    if(sleep_time >0){
        WaitTime(sleep_time);
    }
    end = start;
}
static ITimer timer = {0};
void create_timer_provider(void* engine){
    end = GetTime();

    timer.dt = raylib_dt;
    timer.sleep_end_frame = raylib_sleep_end_frame;
    timer.set_max_fps = raylib_set_max_fps;
    timer.private_funcs[0] = raylib_timer_update;

    Engine* eng = (Engine*)engine;
    eng->timer = &timer;
}