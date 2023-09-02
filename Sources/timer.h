#pragma once


static double timer_fdt = 0.016f;
static float timer_delta = 0.0f;
static double timer_lastTime = 0.0;
static double timer_accumulator = 0.0;

/**
 * Set Timer fixed delta rate. Defaults to 60 FPS if not set.
**/
void set_timer_fixed_rate(int FPS);
static void timer_update();