#pragma once

#include "enginedefs.h"
#include "stdint.h"

typedef struct ILevelLoader {
    void (*initWorlds)(const char* filepath,const char* dir);
    /*
    * names is an array of char*, the array can contain NULL
    * amount will contain the amount of levels. The initial value of amount should be the max length of teh array.
    */
    void (*getLevels)(char** names, int* amount);
    void (*loadLevel)(char* name);
    void (*getEntities)(char** names, int* amount);
    UID  (*load_entity)(char* name);
} ILevelLoader;

void create_levelLoader_provider(void* engine);