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

void renderMainMenu(Entity* ent){
    const Engine* engine = engine_get();
    IUi* ui = engine->ui;
    IGfx* gfx = engine->gfx;
    gfx->begin(0);

    ui->begin();
    static int open = 1;
    ui->window_set_pos(0,0);
    int w,h;
    gfx->getWindowSize(&w,&h);
    ui->window_set_size(w,h);
    if(ui->window_begin("Test",&open,KUiWindowFlags_NoMove | KUiWindowFlags_NoCollapse | KUiWindowFlags_NoResize | KUiWindowFlags_NoTitleBar)){
        float elem_w = w* 0.5f;
        ui->elem_set_pos((w- elem_w)*0.5f,-1);
        if(ui->button("Press Me !",elem_w,0)){
            engine->log->write(LOG_INFO,"Button works !");
        }
        ui->elem_set_pos((w- elem_w)*0.5f,-1);
        if(ui->button("Quit",elem_w,0)){
            engine_stop();
        }
        ui->window_end();
    }
    ui->end();

    gfx->end(0);
}
void create_mainmenu_entity(void){
    const Engine* engine = engine_get();
    UID id = engine->world->createEntity(Vector3Zero(),Vector3One(),Vector3Zero());
    static Component main_menu = {0};
    main_menu.type = Renderable;
    main_menu.funcs[Renderable] = renderMainMenu;
    engine->world->addComponent(id,&main_menu);
}
void kolosseum_init_worlds(const char* filepath,const char* dir){
    const Engine* engine = engine_get();
    // create_camera_entity();
    create_mainmenu_entity();
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