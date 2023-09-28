#include "service_provider.h"

#include "raylib.h"

void service_provider_init(const char* title,int w,int h){
    InitAudioDevice();
    InitWindow(w,h,title);
}
static bool shouldStop = false;
void service_provider_start(void (*update)(void)){

    while (!WindowShouldClose() && !shouldStop){
        update();
    }
    
    CloseWindow();
    CloseAudioDevice();

}

void service_provider_stop(void){
    shouldStop = true;
}