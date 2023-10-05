#include "scene.h"

#include "cJSON.h"
#include "stb_ds.h"
#include "scenedefs.h"
#include "uuid4.h"

#include <stdio.h>
#include <assert.h>


static FILE* curr_scene = NULL;
static cJSON* root = NULL;
static KScene scene;
static void scene_add_entity(const char* name, Matrix transform, Model model){

    // Add to application memory...
    KEntity* ent = &scene.entities[scene.num_entities++];

    memcpy(&ent->transform,&transform,sizeof(Matrix));
    memcpy(&ent->model,&model,sizeof(model));
    
    assert(strlen(name) > MAX_NAME_SIZE && "@TODO: Add validation on UI creation of name");
    strcpy(ent->name,name);
    UUID4_STATE_T state;
    UUID4_T uuid;

    uuid4_seed(&state);
    uuid4_gen(&state, &uuid);

    if (!uuid4_to_s(uuid,ent->uuid, UUID4_STR_BUFFER_SIZE))
        assert(0 && "UUID generation failed, something is horribly wrong...");

    //Add to json data
    

}
static void scene_add_base(char* name){
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root,"scene_name",name);

    Mesh cube = GenMeshCube(1.0f,1.0f,1.0f);
    Model m = LoadModelFromMesh(cube);
    scene_add_entity("default",MatrixIdentity(),m);
}

int create_scene(char* filename){
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