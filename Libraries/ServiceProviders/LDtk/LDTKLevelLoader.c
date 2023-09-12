#include "ILevelLoader.h"
#include "engine.h"
#include "cLDtk.h"
#include <assert.h>

void ldtk_init_worlds(const char* filepath,const char* dir){
    assert(dir != NULL && "LDTK Level loader only expects a filepath, no directory.");

    loadJSONFile("{\"jsonVersion\":\"\"}",(char*)filepath);
    importMapData();
}
void ldtk_get_levels(char** names, int* amount){
    getLevelNames(names,amount);
}
void ldtk_load_level(char* name){
    const Engine* eng = engine_get();
    
}
static ILevelLoader loader = {0};
void create_levelLoader_provider(void* engine){
    loader.initWorlds = ldtk_init_worlds;
    loader.getLevels = ldtk_get_levels;
    loader.loadLevel = ldtk_load_level;

    Engine* eng = (Engine*)engine;
    eng->loader = &loader;

}