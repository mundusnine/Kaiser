#include "ILevelLoader.h"
#include "engine.h"
#include "cLDtk.h"
#include <assert.h>

typedef struct levels Level;
typedef struct layerInstances Layer;

void ldtk_init_worlds(const char* filepath,const char* dir){
    assert(dir != NULL && "LDTK Level loader only expects a filepath, no directory.");

    loadJSONFile("{\"jsonVersion\":\"\"}",(char*)filepath);
    importMapData();
}
void ldtk_get_levels(char** names, int* amount){
    getLevelNames(names,amount);
}

static Level* loaded_lvl = NULL;
static Layer* layers[64] = {0};
static Layer* curr_entities = NULL;
int layers_len = 64;
void ldtk_load_level(char* name){
    loaded_lvl = getLevel(name);
    getLayers(loaded_lvl->uid,layers,&layers_len);
    for(int i = layers_len-1; i >= 0; --i){
		if(strcmp(layers[i]->type,"Entities")==0){
			curr_entities = layers[i];
			break;
		}
	}
}

void ldtk_get_entities(char** names, int* amount){
    if(names == NULL && curr_entities != NULL){
        *amount = curr_entities->numEntityInstancesDataPtr;
        
    }
    else {
        const Engine* eng = engine_get();
    }
    return;
}

static ILevelLoader loader = {0};
void create_levelLoader_provider(void* engine){
    loader.initWorlds = ldtk_init_worlds;
    loader.getLevels = ldtk_get_levels;
    loader.loadLevel = ldtk_load_level;

    loader.getEntities = ldtk_get_entities;

    Engine* eng = (Engine*)engine;
    eng->loader = &loader;

}