#include "scene.h"

#include "timer.h"

void scene_update() {
    timer_update();
    // call update funcs
    if ( timer_accumulator >= timer_fdt )
    {
        //Update physics and call fixe updates on objects
        timer_accumulator = 0.0;
    }
    scene_render();
}

void scene_render() {
    //Add render code.
}