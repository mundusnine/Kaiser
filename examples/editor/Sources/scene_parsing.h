#pragma once

struct cJSON;

struct Vector3;
Vector3 json_to_Vector3(cJSON* obj);
cJSON* Vector3_to_json(Vector3 obj);


struct Vector4;
Vector4 json_to_Vector4(cJSON* obj);
cJSON* Vector4_to_json(Vector4 obj);


struct Mesh;
Mesh json_to_Mesh(cJSON* obj);
cJSON* Mesh_to_json(Mesh obj);


struct KEntity;
KEntity* json_to_KEntity(cJSON* obj);
cJSON* KEntity_to_json(KEntity* obj);


struct KScene;
KScene* json_to_KScene(cJSON* obj);
cJSON* KScene_to_json(KScene* obj);


