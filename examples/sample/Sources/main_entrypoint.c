#include "engine.h"
#include <stdlib.h>

void init_gameplay(void){
    engine_init("TestGame",1024,768);
    const Engine* eng = engine_get();
    eng->loader->initWorlds(NULL,NULL);
    engine_start();
}