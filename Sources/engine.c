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
}private_funcs_e;

static Engine engine ={0};
static uint64_t tex_id = -1;
static uint64_t mdl_id = -1;
// Define the camera to look into our 3d world
static Camera camera = { 0 };
void engine_init(const char* window_name,int w, int h){

    //load service and open window
    service_provider_init(window_name,w,h);

    create_timer_provider(&engine);
    create_input_provider(&engine);
    create_graphics_provider(&engine);
    #ifndef NDEBUG
    size_t IInputSize = sizeof(IInput);
    unsigned char *bytePtr = (unsigned char *)engine.input;
    for (size_t i = 0; i < IInputSize; i+=sizeof(void*)) {
        void* data = bytePtr[i];
        if(data == NULL){
            int index = i == 0 ? 0: i /sizeof(void*);
            fprintf(stderr,"Field at index %d of IInput Provider is not implemented.\n",index);
        }
        assert(data != NULL);
    }
    #endif

    camera.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    tex_id = engine.gfx->loadImg("assets/icon.png");
    mdl_id = engine.gfx->loadMesh("assets/teapot.obj");
}

void engine_start(void){
    service_provider_start(engine_update);
}

void engine_update(void){
    engine.timer->private_funcs[Update](NULL);
    engine.input->private_funcs[Update](NULL);

    engine.gfx->begin(0);
    engine.gfx->clear(0x151515FF);
    engine.gfx->setColor(0xFFFFFFFF);
    int w,h;
    engine.gfx->getImgSize(tex_id,&w,&h);
    KRect rect = {.x=0,.y=0,.w=w,.h=h};
    KRect dst = {.x=0,.y=0,.w=w,.h=h};
    static float angle = 0.0f;
    if(angle < 360.0f){
        angle+= 100 * engine.timer->dt();
    }
    else {
        angle = 0.0f;
    }
    KFlip flip = {.x=0,.y=1};
    engine.gfx->drawImg(tex_id,rect,dst,angle,flip);
    engine.gfx->setColor(0xFF0000FF);
    engine.gfx->fillRect(100,100,100,100);
    UpdateCamera(&camera, CAMERA_ORBITAL);
    engine.gfx->begin3D(camera);
    engine.gfx->drawMesh(mdl_id);
    engine.gfx->end3D();
    engine.gfx->end(0);

    engine.timer->sleep_end_frame();

}

const Engine* engine_get(void){
    return &engine;
}