#include "ILevelLoader.h"

#include "engine.h"
#include "scene.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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
UID logo_id = -1;
void renderMainMenu(Entity* self){
    const Engine* engine = engine_get();
    IUi* ui = engine->ui;
    IGfx* gfx = engine->gfx;


    ui->begin();
    static int open = 1;
    ui->window_set_pos(0,0);
    int w,h;
    gfx->getWindowSize(&w,&h);
    ui->window_set_size(w,h);
    const char* scene_creation_popup = "Create Scene";
    if(ui->window_begin("MainMenu",&open,KUiWindowFlags_NoMove | KUiWindowFlags_NoCollapse | KUiWindowFlags_NoResize | KUiWindowFlags_NoTitleBar)){

        if(ui->table_begin("split",2)){
            ui->table_next_column();
            static Vector2 item_pos = {0};
            static Vector2 r_table_pos = {0};
            float img_w = 100;
            float x = r_table_pos.x* 0.5f - item_pos.x*0.5f;
            ui->elem_set_pos(x,-1);
            ui->image(logo_id,100,100);
            ui->elem_set_pos(x,-1);
            item_pos = ui->text("Kolosseum",48);
            ui->elem_set_pos(x,-1);
            ui->text("Version %d.%d",0,0,1);

            float elem_w = w* 0.25f;
            // ui->elem_set_pos((w- elem_w)*0.5f,-1);
            // ui->elem_set_pos((w * 0.5f - elem_w)*0.5f,-1);
            if(ui->button("New Scene",elem_w,0)){
                ui->popup_open(scene_creation_popup);
            }
            if(ui->popup_begin(scene_creation_popup,0)){
                static char buff[256] ={0};
                char temp[256] = {0};
                if(ui->text_input("Scene name",buff,256)){
                    strcpy(buff,temp);
                }
                if(ui->button("Create",0,0)){
                    create_scene(buff);
                    self->active = 0;
                    //@TODO: Scene creation logic
                }
                ui->elem_same_line();
                if(ui->button("Cancel",0,0)){
                    ui->popup_close();
                }
                ui->popup_end();
            }
            ui->elem_same_line();
            if(ui->button("Browse",elem_w,0)){
                
            }

            ui->table_next_column();
            r_table_pos = ui->elem_get_pos();
            ui->text("Recently Opened Scenes",0);
            ui->table_end();

        }
        ui->window_end();
    }
    ui->end();
}
void create_mainmenu_entity(void){
    const Engine* engine = engine_get();
    logo_id = engine->gfx->loadImg("assets/kolosseum.png");
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