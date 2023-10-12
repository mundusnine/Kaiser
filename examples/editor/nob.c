

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
    if(left[i] != '\0')
        return 0;
    return 1;
}

int needs_include(char* struct_name){
    static const char* includes[] = {
        "Vector3",
        "Vector4",
        "Matrix",
        "Mesh",
        "Model",
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
    int is_unsigned;
    int is_array;
} FType;

FType build_ftype(const char* type_str){

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
        }
    }
}
int main( int argc, char** argv){
    Config config = {0};
    config.target = TARGET_ZIG;
    if (!generate_code(config)) return 1;
    Nob_String_Builder h_sb = {0};
    Nob_String_Builder c_sb = {0};
    nob_read_entire_file("./generated_includes/ast_output.json",&h_sb);
    nob_sb_append_null(&h_sb);
    cJSON* root = cJSON_Parse(h_sb.items);

    h_sb.count = 0;//Use for .h
    c_sb.count = 0;//Use for .c

    const char* hFilename = "scene_parsing.h";

    nob_sb_append_cstr(&h_sb,"#pragma once\n");
    nob_sb_append_cstr(&h_sb,"struct cJSON;\n");
    nob_sb_append_cstr(&c_sb,"#include \"cJSON.h\"\n");
    nob_sb_append_cstr(&c_sb,"#include \"scenedefs.h\"\n");
    nob_sb_append_multi(&c_sb,"#include \"",hFilename,"\"\n");

    cJSON* arr = cJSON_GetObjectItem(root,"inner");
    if(cJSON_IsArray(arr)){
        int len = cJSON_GetArraySize(arr);
        for(int i =0; i < len; ++i){
            cJSON* obj = cJSON_GetArrayItem(arr,i);
            cJSON* kind = cJSON_GetObjectItem(obj,"kind");
            cJSON* name_obj = cJSON_GetObjectItem(obj,"name");
            char* str = cJSON_GetStringValue(kind);
            const char* name = cJSON_GetStringValue(name_obj);
            if(nob_cstr_match(str,"RecordDecl") && name_obj && needs_include(name)){
                int isPointer = nob_cstr_match(name,"KScene") || nob_cstr_match(name,"KEntity");
                nob_sb_append_multi(&h_sb,"struct ",name,";\n");
                char line[256] = {0};
                int n = snprintf(line,256,"%s%s json_to_%s(cJSON* obj)",name,isPointer ? "*":"",name);
                nob_sb_append_buf(&h_sb,line,n);
                nob_sb_append_cstr(&h_sb,";\n");
                
                nob_sb_append_buf(&c_sb,line,n);
                nob_sb_append_multi(&c_sb,"\t",name,isPointer ? "*":""," out = ",isPointer ? "NULL":"{0}",";\n");
                cJSON* fields_arr = cJSON_GetObjectItem(obj,"inner");
                assert(fields_arr && "Should not be NULL");
                if(fields_arr){
                    write_fields_native(&c_sb,name,isPointer,fields_arr);
                }
                //add C content

                // memset(line,0,n);
                // int n = snprintf(line,256,"cJSON* %s_to_json(%s%s obj);\n",name,name,isPointer ? "*":"");
                // nob_sb_append_buf(&h_sb,line,n);
                printf(name);
                printf("\n");
            }
        }
    }

}