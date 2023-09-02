#include "engine.h"
#include "IInput.h"
#include "raylib.h"
static IInput input = {0};
static int key_convert[] ={
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
};
int raylib_is_key_down(int key){
    return IsKeyDown(key_convert[key]);
}
void create_input_provider(void* engine){
    Engine* eng = (Engine*)engine;
    input.isKeyDown = raylib_is_key_down;
    eng->input = &input;
}