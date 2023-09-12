#include "IWorld.h"

#include <assert.h>
#include <string.h>

#include "engine.h"
#include "enginedefs.h"

#include "raymath.h"

static UID num_entities = 0;
static Entity entities[MAX_ENTITIES] = {0};
UID world_create_entity(Vector3 position,Vector3 scale,Vector3 rotation){
    Entity* ent = &entities[num_entities];
    memset(ent,0,sizeof(Entity));
    memset(ent->components,0,sizeof(Component) * MAX_COMPONENTS);
    ent->transform = MatrixTranslate(position.x,position.y,position.z);
    ent->transform = MatrixMultiply(ent->transform,MatrixScale(scale.x,scale.y,scale.z));
    ent->transform = MatrixMultiply(ent->transform,MatrixRotateXYZ(rotation)); 
    ent->id = num_entities;
    return num_entities++;
}
int world_add_component(UID id,void* component){
    Entity* ent = &entities[id];
    int i = 0;
    for(; i < MAX_COMPONENTS;++i){
        if(ent->components[i] == NULL){
            ent->components[i] = component;
            return i;
        }
    }
    assert(i< MAX_COMPONENTS);
    return -1;//Failed to add component
}
void world_update(void* data){
    Component* comp;
    for(int i =0; i < num_entities;++i){
        Entity* ent = &entities[i];
        for(int y = 0; y < MAX_COMPONENTS && ent->components[y] != NULL;++y){
            comp = ent->components[y];
            if(comp->type == Updateable || comp->type == Both){
                comp->funcs[Updateable](ent);
            }
        }
    }
}
void world_render(void* data){
    Engine* eng = engine_get();
    eng->gfx->begin(0);
    eng->gfx->clear(0x151515FF);
    Component* comp;
    for(int i =0; i < num_entities;++i){
        Entity* ent = &entities[i];
        for(int y = 0; y < MAX_COMPONENTS && ent->components[y] != NULL;++y){
            comp = ent->components[y];
            if(comp->type == Renderable || comp->type == Both){
                comp->funcs[Renderable](ent);
            }

        }
    }
    eng->gfx->end(0);
}
static IWorld world = {0};
void create_world_provider(void* engine){
    world.createEntity = world_create_entity;
    world.addComponent = world_add_component;

    world.private_funcs[0] = world_update;
    world.private_funcs[1] = world_render;

    Engine* eng = (Engine*)engine;
    eng->world = &world;
}

