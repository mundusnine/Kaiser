#include "engine.h"
#include "IUi.h"
#include "rlImGui.h"
#include "imgui.h"

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

    ui.elem_set_pos = rl_elem_set_pos;
    ui.button = rl_button;

    ui.private_funcs[2] = rl_shutdown;

    Engine* eng = (Engine*)engine;
    eng->ui = &ui;

}