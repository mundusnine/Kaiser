#include "raylib.h"
#include "IGfx.h"
#include "engine.h"
#include "enginedefs.h"

#include <assert.h>

void raylib_begin(int window){
    BeginDrawing();
}
void raylib_end(int window){
    EndDrawing();
}

void raylib_begin3D(Camera cam){
    BeginMode3D(cam);
}

void raylib_end3D(){
    EndMode3D();
}

void raylib_clear(unsigned color){
    ClearBackground(GetColor(color));
}

static unsigned lastColor = 0;
void raylib_set_color(unsigned color){
    lastColor = color;
}

void raylib_draw_rect(float x, float y, float w,float h,float strength){
    Rectangle rec = {.x=x,.y=y,.width=w,.height=h};
    DrawRectangleLinesEx(rec,strength,GetColor(lastColor));
}

void raylib_fill_rect(float x, float y, float w,float h){
    DrawRectangle(x,y,w,h,GetColor(lastColor));
}

void raylib_draw_line(float x1, float y1, float x2, float y2){
    DrawLine(x1,y1,x2,y2,GetColor(lastColor));
}

static UID num_images = 0;
static Texture2D images[MAX_IMAGES] = {0};
UID raylib_load_image(const char* filepath){
    assert(num_images+1 < MAX_IMAGES);
    images[num_images] =  LoadTexture(filepath);
    return num_images++;
}

void raylib_draw_image(UID id,KRect src, KRect dst,float angle,KFlip flip){
    assert(id < num_images);
    Rectangle s_rect = {.x=src.x,.y=src.y,.width=src.w,.height=src.h};
    Rectangle d_rect = {.x=dst.x,.y=dst.y,.width=dst.w,.height=dst.h};
    Vector2 origin = {0,0};
    DrawTexturePro(images[id],s_rect,d_rect,origin,angle,GetColor(lastColor));
}

void raylib_get_img_size(UID id,int* w,int* h){
    assert(id < num_images);
    *w = images[id].width;
    *h = images[id].height;
}

static UID num_meshes = 0;
static Model meshes[MAX_IMAGES] = {0};
UID raylib_load_mesh(const char* filepath){
    meshes[num_meshes] = LoadModel(filepath);
    return num_meshes++;
}

void raylib_draw_mesh(UID id){
    Vector3 pos = {0};
    DrawModel(meshes[id],pos,1.0f,WHITE);
}

void raylib_get_window_size(int* w, int* h){
    *w = GetScreenWidth();
    *h = GetScreenHeight();
}

static IGfx gfx = {0};
void create_graphics_provider(void* engine){
    
    num_images = 0;
    gfx.begin = raylib_begin;
    gfx.end = raylib_end;
    gfx.begin3D = raylib_begin3D;
    gfx.end3D = raylib_end3D;
    gfx.clear = raylib_clear;
    gfx.getWindowSize = raylib_get_window_size;
    gfx.setColor = raylib_set_color;
    gfx.drawRect = raylib_draw_rect;
    gfx.fillRect = raylib_fill_rect;
    gfx.drawLine = raylib_draw_line;
    gfx.loadImg = raylib_load_image;
    gfx.drawImg = raylib_draw_image;
    gfx.getImgSize = raylib_get_img_size;
    gfx.loadMesh = raylib_load_mesh;
    gfx.drawMesh = raylib_draw_mesh;

    Engine* eng = (Engine*)engine;
    eng->gfx = &gfx;
}