#include "engine.h"
#include "service_provider.h"
#include <stddef.h>
#ifndef NDEBUG
#include <stdio.h>
#include <assert.h>
#endif

#ifndef RAYLIB_PROVIDER
#define RCAMERA_IMPLEMENTATION
#define RCAMERA_STANDALONE
#include "rcamera.h"// Includes raymath definitions
#endif


typedef enum{
    Update,
    Render
}private_funcs_e;

static Engine engine ={0};
// Define the camera to look into our 3d world
static Camera camera = { 0 };
void engine_init(const char* window_name,int w, int h){

    //load service and open window
    service_provider_init(window_name,w,h);
    
    create_timer_provider(&engine);
    create_input_provider(&engine);
    create_world_provider(&engine);
    create_graphics_provider(&engine);
    create_audio_provider(&engine);
    create_levelLoader_provider(&engine);
    // #ifndef NDEBUG
    // size_t IInputSize = sizeof(IInput);
    // unsigned char *bytePtr = (unsigned char *)engine.input;
    // for (size_t i = 0; i < IInputSize; i+=sizeof(void*)) {
    //     void* data = bytePtr[i];
    //     if(data == NULL){
    //         int index = i == 0 ? 0: i /sizeof(void*);
    //         fprintf(stderr,"Field at index %d of IInput Provider is not implemented.\n",index);
    //     }
    //     assert(data != NULL);
    // }
    // #endif
}

void engine_start(void){
    service_provider_start(engine_update);
}

void engine_update(void){
    engine.timer->private_funcs[Update](NULL);
    engine.input->private_funcs[Update](NULL);

    engine.sfx->private_funcs[Update](NULL);
    engine.world->private_funcs[Update](NULL);
    engine.world->private_funcs[Render](NULL);

    engine.timer->sleep_end_frame();

}

const Engine* engine_get(void){
    return &engine;
}