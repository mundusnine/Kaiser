#include "scene.h"
#include "cJSON.h"
#include "raylib.h"
#include <stdio.h>

static FILE* curr_scene = NULL;
static cJSON* root = NULL;
static void scene_add_base(char* name){
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root,"scene_name",name);

    Mesh cube = GenMeshCube(1.0f,1.0f,1.0f);
    // cube.vertices
    // cube.vertexCount

}
int create_scene(const char* filename){
    char temp[260] = {0};
    snprintf(temp,260,"%s.rna",filename);
    FILE* new_scene = fopen(temp,"wb+");
    if(new_scene != NULL){
        if(curr_scene != NULL){
            fclose(curr_scene);
        }
        curr_scene = new_scene;
        scene_add_base(filename);
        return 1;
    }
    return 0;
}