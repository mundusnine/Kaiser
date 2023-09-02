#include "script.h"
#include <stddef.h>
#include <stdlib.h>
// #include <kinc/log.h>
// #include <kinc/system.h>

Script* create_script(int32_t updates_count, int32_t renders_count){

    Script* s = malloc(sizeof(Script));
    
    s->object = NULL;

    s->updates = malloc(updates_count * sizeof(UPDATE_FUNC));
    s->fixed_updates = malloc(updates_count * sizeof(UPDATE_FUNC));
    s->renders = malloc(renders_count * sizeof(RENDER_FUNC));

    s->updates_count = updates_count;
    s->renders_count = renders_count;

    s->updates_used = 0;
    s->renders_used = 0;
    return s;
}

void notifyOnUpdate(Script* script,UPDATE_FUNC value){
    if(script->updates_used < script->updates_count){
        script->updates[script->updates_used] = value;
        script->updates_used += 1;
    }
    #ifdef DEBUG_KAISER
    else{
        kinc_log(KINC_LOG_LEVEL_ERROR,"Exceeded the count. Create the script %s with a bigger update count on Start.",script->name);
    }
    #endif
}

void notifyOnFixedUpdate(Script* script,UPDATE_FUNC value){
    if(script->fixed_updates_used < script->fixed_updates_count){
        script->fixed_updates[script->fixed_updates_used] = value;
        script->fixed_updates_used += 1;
    }
    #ifdef DEBUG_KAISER
    else{
        kinc_log(KINC_LOG_LEVEL_ERROR,"Exceeded the count. Create the script %s with a bigger update count on Start.",script->name);
    }
    #endif
}

void notifyOnRender(Script* script,RENDER_FUNC value){
    if(script->renders_used < script->renders_count){
        script->renders[script->renders_used] = value;
        script->renders_used += 1;
    }
    #ifdef DEBUG_KAISER
    else{
        kinc_log(KINC_LOG_LEVEL_ERROR,"Exceeded the count. Create the script %s with a bigger render count on Start.",script->name);
    }
    #endif
}

void removeOnUpdate(Script* script,UPDATE_FUNC value){
    for(int i = 0; i < script->updates_used;i++){
        if(script->updates[i] == value){
            for(int y = 0; y +1 < script->updates_used - i; y++){
                script->updates[i+y] =  script->updates[i+y+1];
            }
            script->updates_used -= 1;
            break;
        }
    }
}

void removeOnFixedUpdate(Script* script,UPDATE_FUNC value){
    for(int i = 0; i < script->fixed_updates_used;i++){
        if(script->fixed_updates[i] == value){
            for(int y = 0; y +1 < script->fixed_updates_used - i; y++){
                script->fixed_updates[i+y] =  script->fixed_updates[i+y+1];
            }
            script->fixed_updates_used -= 1;
            break;
        }
    }
}

void removeOnRender(Script* script,RENDER_FUNC value){
    for(int i = 0; i < script->renders_used;i++){
        if(script->renders[i] == value){
            for(int y = 0; y +1 < script->renders_used - i; y++){
                script->renders[i+y] =  script->renders[i+y+1];
            }
            script->renders_used -= 1;
            break;
        }
    }
}