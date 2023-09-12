#pragma once

#include <enginedefs.h>
#include <stdint.h>

typedef struct ISfx {
    
    UID (*loadMus)(const char* filepath);
    void(*setMusPan)(UID id, float pan);
    void(*setMusPitch)(UID id, float pitch);
    void(*setMusVol)(UID id, float volume);
    void(*playMus)(UID id);

    UID (*loadSnd)(const char* filepath);
    void(*setSndPan)(UID id, float pan);
    void(*setSndPitch)(UID id, float pitch);
    void(*setSndVol)(UID id, float volume);
    void(*stopSnd)(UID id);
    void(*playSnd)(UID id);

    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
}ISfx;

void create_audio_provider(void* engine);