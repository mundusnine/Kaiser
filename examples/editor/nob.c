

#define NOB_IMPLEMENTATION
#include "nob.h"
#include "cJSON.h"

typedef enum {
    TARGET_POSIX,
    TARGET_WIN64_MINGW,
    TARGET_WIN64_MSVC,
    TARGET_ZIG,
    COUNT_TARGETS
} Target;

static_assert(4 == COUNT_TARGETS, "Amount of targets have changed");
const char *target_names[] = {
    [TARGET_POSIX]       = "posix",
    [TARGET_WIN64_MINGW] = "win64-mingw",
    [TARGET_WIN64_MSVC]  = "win64-msvc",
    [TARGET_ZIG]  = "zig",
};

void log_available_targets(Nob_Log_Level level)
{
    nob_log(level, "Available targets:");
    for (size_t i = 0; i < COUNT_TARGETS; ++i) {
        nob_log(level, "    %s", target_names[i]);
    }
}

typedef struct {
    Target target;
    bool hotreload;
} Config;

bool generate_code(Config config)
{
    bool result = true;
    Nob_Cmd cmd = {0};
    Nob_Procs procs = {0};

    if (!nob_mkdir_if_not_exists("./generated_includes")) {
        nob_return_defer(false);
    }

    switch (config.target) {
        case TARGET_ZIG:{
            cmd.count = 0;
            //     const cmd = "zig"
//     const args = [
//         "cc",
//         "-Xclang",
//         "-ast-dump=json",
//         "-fsyntax-only",
//         "-fno-sanitize=undefined",
//         "-fno-omit-frame-pointer",
//         `-I${raylibPath}`,
//         __dirname+"/Sources/scenedefs.h"
            nob_cmd_append(&cmd, "zig","cc");
            nob_cmd_append(&cmd, "-Xclang");
            nob_cmd_append(&cmd, "-ast-dump=json", "-fsyntax-only", "-fno-sanitize=undefined","-fno-omit-frame-pointer");
            nob_cmd_append(&cmd, "-I../../Libraries/raylib/src");
            nob_cmd_append(&cmd,
                "./Sources/scenedefs.h",
            );
            nob_cmd_append(&cmd,">","\"./generated_includes/ast_output.json\"");
            // Nob_String_Builder command = {0};
            // nob_cmd_render(cmd,&command);
            // nob_sb_append_null(&command);
            // printf("%s\n",command.items);
            nob_cmd_run_sync(cmd);
            // if (!) nob_return_defer(false);
        }break;
        default: NOB_ASSERT(0 && "unreachable");
    }
defer:
    nob_cmd_free(cmd);
    nob_da_free(procs);
    return result;
}

int nob_cstr_match(char* left, char* right){
    int i =0;
    while(left[i] != '\0' && right[i] != '\0'){
        if(left[i] != right[i]){
            return 0;
        }
        ++i;
    }
    if(left[i] != '\0' || right[i] != '\0')
        return 0;
    return 1;
}

int needs_include(char* struct_name){
    static const char* includes[] = {
        "Vector3",
        "Vector4",
        "Matrix",
        "Transform",
        "Color",
        "Texture",
        "Shader",
        "MaterialMap",
        "Material",
        "Mesh",
        "Model",
        "BoneInfo",
        "KEntity",
        "KScene"
    };
    static const int size = sizeof(includes) / sizeof(includes[0]);
    for(int i =0; i < size; ++i){
        if(nob_cstr_match(struct_name,includes[i])){
            return 1;
        }
    }
    return 0;
}
typedef struct {
    char typename[32];
    int is_pointer;
    int is_unsigned;
    int is_array;
    int arr_len;
} FType;

FType build_ftype(const char* type_str){
    FType type = {0};
    char* curr = type_str;
    char* unsign = strstr(curr,"unsigned");
    type.is_unsigned = unsign != NULL; 
    curr = type.is_unsigned ? unsign + 9 : curr;
    char* ptr = strstr(curr,"*");
    char* arr_s = strstr(curr,"[");
    char* arr_e = strstr(curr,"]");

    type.is_pointer = ptr != NULL;
    char* end_type = ptr;
    type.is_array = ptr != NULL || arr_s != NULL;
    if(type.is_array && !ptr){
        int i =1;
        char num[64] ={0};
        while(arr_s[i] !=']'){
            num[i-1] = arr_s[i];
            ++i;
        }
        type.arr_len = atoi(num);
        end_type = arr_s;
    }
    
    int size = end_type != NULL ? end_type - curr : strlen(curr);
    int i =0;
    int y = 0;

    while(i < size){
        if(curr[i] != ' '){
            type.typename[y++] = curr[i];
        }
        ++i;
    }
    if(nob_cstr_match(type.typename,"KScene") || nob_cstr_match(type.typename,"KEntity")){
        type.is_pointer = 1;
    }
    return type;
}

char* baseTypeTocJSON(FType type,int toJSON){
    if(strcmp(type.typename,"float") == 0 || strcmp(type.typename,"int") == 0 || strcmp(type.typename,"short") == 0){
        if(toJSON && type.is_array){
            return "cJSON_CreateNumber";
        }
        return toJSON ? "cJSON_AddNumberToObject" : "cJSON_GetNumberValue";
    }
    if(strcmp(type.typename,"char") == 0 ){
        if(type.is_array && !type.is_unsigned){//This is a hack, we need to reevaluate this when we have more strings...
            return toJSON ? "cJSON_AddStringToObject" : "cJSON_GetStringValue";
        }
        return toJSON ? "cJSON_AddNumberToObject" : "cJSON_GetNumberValue";
    }
    return NULL;
}

char* countsByType(char* typeName,char* fieldName){
    #define GetCountByTypeName(name)                         \
    do {                                                     \
        size_t len = sizeof(name##Names)/sizeof(name##Names[0]); \
        for(int i =0; i < len;++i){                          \
            if(strcmp(fieldName,name##Names[i]) == 0){         \
                return name##Counts[i];                        \   
            }                                                \ 
        }                                                    \
    } while (0)                                              \

    static char* meshNames[] = {
        "vertices","texcoords","texcoords2","normals","tangents","colors",       
        "indices","animVertices","animNormals",  "boneIds","boneWeights",
        "vboId",        
    };
    static char* meshCounts[] = {
        "vertexCount * 3","vertexCount * 2","vertexCount * 2","vertexCount * 3","vertexCount * 4","vertexCount * 4",
        "triangleCount * 3","vertexCount * 3","vertexCount * 3","vertexCount * 4","vertexCount * 4",
        "7/*MAX_MESH_VERTEX_BUFFERS*/"
    };
    static char* modelNames[] = {
        "meshMaterial","meshes","materials","bones"
    };
    static char* modelCounts[] = {
        "meshCount","meshCount","materialCount","boneCount"
    };
    static char* shaderNames[] = {
        "locs"
    };
    static char* shaderCounts[] = {
        "32/*RL_MAX_SHADER_LOCATIONS*/"
    };
    static char* ksceneNames[] = {
        "entities"
    };
    static char* ksceneCounts[] = {
        "num_entities"
    };
    if(strcmp(typeName,"Mesh") == 0){
        GetCountByTypeName(mesh);
    }
    else if(strcmp(typeName,"Model") == 0){
        GetCountByTypeName(model);
    }
    else if(strcmp(typeName,"Shader") == 0){
        GetCountByTypeName(shader);
    }
    // else if(strcmp(typeName,"KScene") == 0){
    //     GetCountByTypeName(kscene);
    // }
    return NULL;

}
void write_fields_native(Nob_String_Builder* sb,char* type_name,int isPointer, cJSON* fields_arr){
    int len = cJSON_GetArraySize(fields_arr);
    for(int i =0; i < len; ++i){
        cJSON* obj = cJSON_GetArrayItem(fields_arr,i);
        cJSON* kind = cJSON_GetObjectItem(obj,"kind");
        cJSON* name_obj = cJSON_GetObjectItem(obj,"name");
        char* str = cJSON_GetStringValue(kind);
        const char* name = cJSON_GetStringValue(name_obj);
        if(nob_cstr_match(str,"FieldDecl")){
            char* type_str = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(obj,"type"),"qualType"));
            FType type = build_ftype(type_str);

            char* t_access = isPointer ? "->" : ".";
            char itemName[96] = {0};
            snprintf(itemName,96,"item_%s",name);

            nob_sb_append_cstr(sb,nob_temp_sprintf("\tcJSON* %s = cJSON_GetObjectItem(obj,\"%s\");\n",itemName,name));

            char* size_mul = countsByType(type_name,name);
            char* end_typename = nob_cstr_match(type.typename,"Quaternion") ? "Vector4" : nob_cstr_match(type.typename,"Texture2D") ? "Texture" : type.typename;
            char type_get[64] ={0};
            char* ttype_get = baseTypeTocJSON(type,0);
            if(!ttype_get){
                snprintf(type_get,64,"json_to_%s",end_typename);
            }
            else{
                snprintf(type_get,64,"%s",ttype_get);
            }
            if(strcmp(type.typename,"char") == 0 && type.is_array && !type.is_unsigned){
                nob_sb_append_cstr(sb,nob_temp_sprintf("\tstrcpy(out%s%s,%s(%s));\n",t_access,name,baseTypeTocJSON(type,0),itemName));
            }
            else if(type.is_array && size_mul){
                char* unsigned_c = type.is_unsigned ? "unsigned " : "";
                char outType[64] = {0};
                snprintf(outType,64,"out%s%s",t_access,size_mul);
                if(isdigit(size_mul[0])){
                    snprintf(outType,64,"%s",size_mul);
                }
                if(type.is_pointer){
                    nob_sb_append_cstr(sb,nob_temp_sprintf("\tout%s%s = allocate(sizeof(%s%s) * (%s));\n",
                        t_access,
                        name,
                        unsigned_c,
                        end_typename,
                        outType
                    ));
                }
                nob_sb_append_cstr(sb,nob_temp_sprintf(
                    "\tfor(int i =0; i < cJSON_GetArraySize(%s);++i){\n"
                    "\t\tcJSON* obj = cJSON_GetArrayItem(%s,i);\n"
                    "\t\tout%s%s[i] = %s(obj);\n"
                    "\t}\n",
                    itemName,
                    itemName,
                    t_access,
                    name,
                    type_get
                ));
            }
            else if(type.is_array && type.arr_len > 0){//static array
                char assign_line[128] = {0};
                if(!type.is_pointer){
                    snprintf(assign_line,128,"\t\tout%s%s[i] = %s(obj);\n",t_access,name,type_get);
                }
                else {
                    snprintf(assign_line,128,"\t\tmemcpy(&out%s%s[i],%s(obj),sizeof(%s));\n",t_access,name,type_get,type.typename);
                }
                nob_sb_append_cstr(sb,nob_temp_sprintf(
                    "\tfor(int i =0; i < %d;++i){\n"
                    "\t\tcJSON* obj = cJSON_GetArrayItem(%s,i);\n"
                    "%s"
                    "\t}\n",
                    type.arr_len,
                    itemName,
                    assign_line
                ));
            }
            else{
                // file = write(file,`out${access} = (${outType})${baseTypeToCJSON(f_type,false)}(${itemName});`,1);
                if(type.is_pointer){
                    nob_sb_append_cstr(sb,nob_temp_sprintf("\t%s temp_%s = %s(%s);\n",
                        end_typename,
                        name,
                        type_get,
                        itemName
                    ));
                    nob_sb_append_cstr(sb,nob_temp_sprintf("\tout%s%s = allocate(sizeof(%s));\n",
                        t_access,
                        name,
                        end_typename
                    ));
                    nob_sb_append_cstr(sb,nob_temp_sprintf("\tmemcpy(out%s%s,&temp_%s,sizeof(%s));\n",
                        t_access,
                        name,
                        name,
                        end_typename
                    ));
                }
                else {
                    // char* ttype_get = baseTypeTocJSON(type,0);
                    nob_sb_append_cstr(sb,nob_temp_sprintf("\tout%s%s = %s(%s);\n",
                        t_access,
                        name,
                        type_get,
                        itemName
                    ));
                }
            }
            nob_sb_append_cstr(sb,"\n");
        }
    }
}
const char* base_path = "./generated_includes";
int main( int argc, char** argv){
    Config config = {0};
    config.target = TARGET_ZIG;
    if (!generate_code(config)) return 1;
    Nob_String_Builder h_sb = {0};
    Nob_String_Builder c_sb = {0};
    nob_read_entire_file("./generated_includes/ast_output.json",&h_sb);
    nob_sb_append_null(&h_sb);
    cJSON* root = cJSON_Parse(h_sb.items);

    memset(h_sb.items,0,h_sb.count);
    h_sb.count = 0;//Use for .h
    c_sb.count = 0;//Use for .c

    const char* hFilename = "scene_parsing";

    nob_sb_append_cstr(&h_sb,"#pragma once\n");
    nob_sb_append_cstr(&h_sb,"struct cJSON;\n");
    nob_sb_append_cstr(&c_sb,"#include \"cJSON.h\"\n");
    nob_sb_append_cstr(&c_sb,"#include \"stdlib.h\"\n");
    nob_sb_append_cstr(&c_sb,"#include \"scenedefs.h\"\n");
    nob_sb_append_cstr(&c_sb,nob_temp_sprintf("#include \"%s.h\"\n\n",hFilename));

    cJSON* arr = cJSON_GetObjectItem(root,"inner");
    if(cJSON_IsArray(arr)){
        int len = cJSON_GetArraySize(arr);
        for(int i =0; i < len; ++i){
            cJSON* obj = cJSON_GetArrayItem(arr,i);
            cJSON* kind = cJSON_GetObjectItem(obj,"kind");
            cJSON* name_obj = cJSON_GetObjectItem(obj,"name");
            char* str = cJSON_GetStringValue(kind);
            char* name = cJSON_GetStringValue(name_obj);
            if(nob_cstr_match(str,"RecordDecl") && name_obj && needs_include(name)){
                int isPointer = nob_cstr_match(name,"KScene") || nob_cstr_match(name,"KEntity");
                nob_sb_append_cstr(&h_sb,nob_temp_sprintf("struct %s;\n",name));
                char line[256] = {0};
                int n = snprintf(line,256,"%s%s json_to_%s(cJSON* obj)",name,isPointer ? "*":"",name);
                nob_sb_append_buf(&h_sb,line,n);
                nob_sb_append_cstr(&h_sb,";\n");
                
                nob_sb_append_buf(&c_sb,line,n);
                nob_sb_append_cstr(&c_sb,nob_temp_sprintf("{\n\t%s%s out = %s;\n",name,isPointer ? "*":"",isPointer ? "NULL":"{0}"));
                cJSON* fields_arr = cJSON_GetObjectItem(obj,"inner");
                assert(fields_arr && "Should not be NULL");
                if(fields_arr){
                    write_fields_native(&c_sb,name,isPointer,fields_arr);
                }
                nob_sb_append_cstr(&c_sb,"}\n");

                //add C content

                // memset(line,0,n);
                // int n = snprintf(line,256,"cJSON* %s_to_json(%s%s obj);\n",name,name,isPointer ? "*":"");
                // nob_sb_append_buf(&h_sb,line,n);
                printf(name);
                printf("\n");
            }
        }
    }
    //Reevaluate if we need this... behavior seems unstable when using it so we remove for now. 
    // nob_sb_append_null(&h_sb);
    // nob_sb_append_null(&c_sb);
    char path_name[128] = {0};
    int n = snprintf(path_name,128,"%s/%s.h",base_path,hFilename);
    nob_write_entire_file(path_name,h_sb.items,h_sb.count);
    path_name[n-1] = 'c';
    nob_write_entire_file(path_name,c_sb.items,c_sb.count* sizeof(char));   

}