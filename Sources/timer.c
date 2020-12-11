#include "timer.h"

#include <kinc/system.h>

void set_timer_fixed_rate(int FPS){
    timer_fdt = 1.0 / FPS;
}

void timer_update(){
    double time = kinc_time();
    double frameTime = time - timer_lastTime;
    timer_delta = (float)frameTime;
    timer_lastTime = time;

    timer_accumulator += frameTime;
}