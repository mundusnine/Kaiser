#include "service_provider.h"

#include "raylib.h"

void service_provider_init(const char* title,int w,int h){
    InitWindow(w,h,title);
}
void service_provider_start(void (*update)(void)){

    while (!WindowShouldClose()){
        update();
    }
    CloseWindow();
}