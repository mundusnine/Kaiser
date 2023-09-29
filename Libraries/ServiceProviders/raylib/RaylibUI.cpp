#include "IUi.h"
#include "engine.h"

#include "rlImGui.h"
#include "imgui.h"

#include <stdarg.h>

static int isBegin = 0;
void rl_begin(void){
    assert(!isBegin && "End before you begin");
    rlImGuiBegin();
    isBegin = 1;
}
void rl_end(void){
    assert(isBegin && "Begin before you end");
    rlImGuiEnd();
    isBegin = 0;
}
void rl_shutdown(void* data){
    rlImGuiShutdown();
}

void rl_window_set_pos(float x, float y){
    ImGui::SetNextWindowPos(ImVec2(x,y));
}
void rl_window_set_size(float w, float h){
    ImGui::SetNextWindowSize(ImVec2(w,h));
}
int rl_window_begin(const char* name,int* open,int flags){
    return (int)ImGui::Begin(name,(bool*)open,flags);
}

void rl_window_end(void){
    ImGui::End();
}

void rl_elem_set_pos(float x, float y){
    if(x >= 0){
        ImGui::SetCursorPosX(x);   
    }
    if(y >= 0){
        ImGui::SetCursorPosY(y);   
    }
}
void rl_elem_same_line(void){
    ImGui::SameLine();
}

#ifdef __cplusplus
extern "C"{
#endif
Texture2D* raylib_get_texture(UID image_id);
#ifdef __cplusplus
}
#endif

void rl_image(UID image_id,float w, float h){
    Texture* image = raylib_get_texture(image_id);
    float width = w > 0 ? w : float(image->width);
    float height = h > 0 ? h : float(image->height);

    ImGui::Image((ImTextureID)image, ImVec2(width, height));
}

void rl_text(char* fmt,float fontSize,...){
    fontSize = fontSize >0 ? fontSize : ImGui::GetFontSize(); 
    ImGui::SetWindowFontScale(fontSize/ImGui::GetFontSize());
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt,args);
    va_end(args);
    ImGui::SetWindowFontScale(1.0f);
}

int rl_table_begin(const char* id, int num_columns){
    return (int)ImGui::BeginTable(id,num_columns);
}

void rl_table_next_column(void){
    ImGui::TableNextColumn();
}

void rl_table_end(void){
    ImGui::EndTable();
}


int rl_button(const char* label,float w, float h){
    return (int)ImGui::Button(label,ImVec2(w,h));
}

static IUi ui = {0};
void create_ui_provider(void* engine){
    rlImGuiSetup(true);

    ui.begin = rl_begin;
    ui.end = rl_end;

    ui.window_begin = rl_window_begin;
    ui.window_end = rl_window_end;
    ui.window_set_pos = rl_window_set_pos;
    ui.window_set_size = rl_window_set_size;

    ui.table_begin = rl_table_begin;
    ui.table_end = rl_table_end;
    ui.table_next_column = rl_table_next_column;

    ui.elem_set_pos = rl_elem_set_pos;
    ui.elem_same_line = rl_elem_same_line;

    ui.image = rl_image;
    ui.text = rl_text;
    ui.button = rl_button;

    ui.private_funcs[2] = rl_shutdown;

    Engine* eng = (Engine*)engine;
    eng->ui = &ui;

}