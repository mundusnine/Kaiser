#pragma once
/*
* Call init functions of the provider and open a window
*/
void service_provider_init(const char* title,int w,int h);

void service_provider_start(void (*update)(void));