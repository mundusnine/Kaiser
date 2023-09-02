#pragma once

#include <stdint.h>

#include "object.h"

typedef void (*UPDATE_FUNC)(float);

typedef void (*RENDER_FUNC)(/*kinc_g4_pipeline_impl_t*/void*);

typedef struct {
    #ifdef DEBUG_KAISER
    char* name;
    #endif
    Object* object; 
    UPDATE_FUNC* updates;
    int32_t updates_count;
    int32_t updates_used;

    UPDATE_FUNC* fixed_updates;
    int32_t fixed_updates_count;
    int32_t fixed_updates_used;

    RENDER_FUNC* renders;
    int32_t renders_count;
    int32_t renders_used;
} Script;


#ifdef DEBUG_KAISER
/**
 * Creates a Script Object with the number of funcs specified.
**/
Script* create_script(int32_t updates_count, int32_t renders_count,const char *name);
#else

Script* create_script(int32_t updates_count, int32_t renders_count);
#endif

/**
 * Adds an update function to be called by the engine.
**/
void notifyOnUpdate(Script* script,UPDATE_FUNC value);

/**
 * Adds an update function to be called by the engine.
**/
void notifyOnFixedUpdate(Script* script,UPDATE_FUNC value);

/**
 * Adds a render function to be called by the 3D graphics engine.
**/
void notifyOnRender(Script* script,RENDER_FUNC value);


// void notifyOnRender2D(struct Script* script); @TODO: Add this when Rob made the g2 impl in kinc

/**
 * Removes the update function from the Script.
**/
void removeOnUpdate(Script* script,UPDATE_FUNC value);

/**
 * Removes the fixed update function from the Script.
**/
void removeOnUpdate(Script* script,UPDATE_FUNC value);

/**
 * Removes the render function from the Script.
**/
void removeOnRender(Script* script,RENDER_FUNC value);