#include "ILevelLoader.h"

#include "engine.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static Camera cam = {0};
void update_cam_entity(Entity* ent){
    UpdateCamera(&cam,CAMERA_FIRST_PERSON);
}
void create_camera_entity(void){
    cam.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
    cam.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    cam.fovy = 45.0f;                                // Camera field-of-view Y
    cam.projection = CAMERA_PERSPECTIVE;           // Camera projection type
    const Engine* eng = engine_get();
    UID id = eng->world->createEntity(cam.position,Vector3One(),Vector3Zero());
    static Component cameraController = {0};
    cameraController.type = Updateable;
    cameraController.funcs[Updateable] = update_cam_entity;
    eng->world->addComponent(id,&cameraController);


}
static UID tex_id = -1;
static UID snd_id = -1;
void moveImage(Entity* ent){
    const Engine* engine = engine_get();

    if(ent->transform.m14 < 360.0f){
        ent->transform.m14+= 100 * engine->timer->dt();
    }
    else {
        ent->transform.m14 = 0.0f;
    }
    static float pitch = 1.0f;
    if(engine->input->isKeyDown(Key_A)){
        pitch -=0.1f;
        engine->sfx->setSndPitch(snd_id,pitch);
        engine->sfx->playSnd(snd_id);
    }
    if(engine->input->isKeyDown(Key_D)){
        pitch+=0.1f;
    }
}
void renderImage(Entity* ent){
    const Engine* engine = engine_get();
    int w,h;
    engine->gfx->setColor(0xFF0000FF);
    engine->gfx->fillRect(100,100,100,100);
    engine->gfx->getImgSize(tex_id,&w,&h);
    KRect rect = {.x=0,.y=0,.w=w,.h=h};
    KRect dst = {.x=0,.y=0,.w=w*ent->transform.m0,.h=h*ent->transform.m5};
    KFlip flip = {.x=0,.y=1};
    engine->gfx->setColor(0xFFFFFFFF);
    engine->gfx->drawImg(tex_id,rect,dst,ent->transform.m14,flip);
}
void create_image_entity(void){
    const Engine* engine = engine_get();
    tex_id = engine->gfx->loadImg("assets/icon.png");
    Vector3 scale = Vector3One();
    scale.x = scale.y = 0.5f;
    UID id = engine->world->createEntity(Vector3Zero(),scale,Vector3Zero());
    static Component imageMover = {0};
    imageMover.type = Both;
    imageMover.funcs[Updateable] = moveImage;
    imageMover.funcs[Renderable] = renderImage;
    engine->world->addComponent(id,&imageMover);
    snd_id = engine->sfx->loadSnd("assets/sound.wav");
}
static UID mdl_id = -1;
void renderModel(Entity* ent){
    const Engine* engine = engine_get();
    engine->gfx->begin3D(cam);
    engine->gfx->drawMesh(mdl_id);
    engine->gfx->end3D();
}
void create_model_entity(void){
    const Engine* engine = engine_get();
    mdl_id = engine->gfx->loadMesh("assets/teapot.obj");

    UID id = engine->world->createEntity(cam.position,Vector3One(),Vector3Zero());
    static Component modelController = {0};
    modelController.type = Renderable;
    modelController.funcs[Renderable] = renderModel;
    engine->world->addComponent(id,&modelController);
}
void kolosseum_init_worlds(const char* filepath,const char* dir){
    const Engine* engine = engine_get();
    create_camera_entity();
    create_image_entity();
    create_model_entity();
    engine->sfx->playMus(engine->sfx->loadMus("assets/country.mp3"));

}
static char* levels[] = {
    "MainMenu",
    "SceneEdit"
};
const uint64_t num_levels = sizeof(levels)/sizeof(char*);
void kolosseum_get_levels(char** names, int* amount){
    assert(*amount < num_levels);
    for(int i =0; i < num_levels;++i){
        names[i] = levels[i];
    }
    *amount = num_levels;
}
void kolosseum_load_level(char* name){
    const Engine* eng = engine_get();
    (void)eng;
    
}
static ILevelLoader loader = {0};
void create_levelLoader_provider(void* engine){
    loader.initWorlds = kolosseum_init_worlds;
    loader.getLevels = kolosseum_get_levels;
    loader.loadLevel = kolosseum_load_level;

    Engine* eng = (Engine*)engine;
    eng->loader = &loader;

}