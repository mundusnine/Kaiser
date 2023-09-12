#include "ISfx.h"

#include "engine.h"
#include "raylib.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_SOUNDS 512
#define MAX_MUS 64

static UID num_snd = 0;
static Sound snds[MAX_SOUNDS] = {0};
static UID num_mus = 0;
static Music mus[MAX_MUS] = {0};
UID raylib_load_mus(const char* filepath){
    Music mu = LoadMusicStream(filepath);
    if(mu.ctxData != NULL){
        mus[num_mus] = mu;
        return num_mus++;
    }
    return BAD_UID;
}

void raylib_set_mus_pan(UID id, float pan){
    assert(id < num_mus);
    SetMusicPan(mus[id],pan);
}
void raylib_set_mus_pitch(UID id, float pitch){
    assert(id < num_mus);
    SetMusicPitch(mus[id],pitch);
}
void raylib_set_mus_vol(UID id, float volume){
    assert(id < num_mus);
    SetMusicVolume(mus[id],volume);
}

UID raylib_play_mus(UID id){
    assert(id < num_mus);
    PlayMusicStream(mus[id]);
}

UID raylib_load_snd(const char* filepath){
    Sound snd = LoadSound(filepath);
    if(snd.frameCount != 0){
        snds[num_snd] = snd;
        return num_snd++;
    }
    return BAD_UID;
}

void raylib_set_snd_pan(UID id, float pan){
    assert(id < num_snd);
    SetSoundPan(snds[id],pan);
}
void raylib_set_snd_pitch(UID id, float pitch){
    assert(id < num_snd);
    SetSoundPitch(snds[id],pitch);
}
void raylib_set_snd_vol(UID id, float volume){
    assert(id < num_snd);
    SetSoundVolume(snds[id],volume);
}
void stopSnd(UID id){
    assert(id < num_snd);
    StopSound(snds[id]);
}

UID raylib_play_snd(UID id){
    assert(id < num_snd);
    PlaySound(snds[id]);
}

void raylib_audio_update(void* data){
    for(int i=0; i < num_mus;++i){
        if(IsMusicStreamPlaying(mus[i])){
            UpdateMusicStream(mus[i]);
        } 
    }
}
static ISfx sfx = {0};
void create_audio_provider(void* engine){
    sfx.loadMus = raylib_load_mus;
    sfx.setMusPan = raylib_set_mus_pan;
    sfx.setMusPitch = raylib_set_mus_pitch;
    sfx.setMusVol = raylib_set_mus_vol;
    sfx.playMus = raylib_play_mus;

    sfx.loadSnd = raylib_load_snd;
    sfx.setSndPan = raylib_set_snd_pan;
    sfx.setSndPitch = raylib_set_snd_pitch;
    sfx.setSndVol = raylib_set_snd_vol;
    sfx.playSnd = raylib_play_snd;

    sfx.private_funcs[0] = raylib_audio_update;
    
    
    Engine* eng = (Engine*)engine;
    eng->sfx = &sfx;
}