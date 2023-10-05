#include "cJSON.h"
#include "scenedefs.h"
#include "scene_parsing.h"

Vector3 json_to_Vector3(cJSON* obj){
	Vector3 out = {0};
	cJSON* item_x = cJSON_GetObjectItem(obj,"x");
	out.x = (float)cJSON_GetNumberValue(item_x);
	cJSON* item_y = cJSON_GetObjectItem(obj,"y");
	out.y = (float)cJSON_GetNumberValue(item_y);
	cJSON* item_z = cJSON_GetObjectItem(obj,"z");
	out.z = (float)cJSON_GetNumberValue(item_z);
	return out;
}

cJSON* Vector3_to_json(Vector3 obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddNumberToObject(out,"x",obj.x);
	cJSON_AddNumberToObject(out,"y",obj.y);
	cJSON_AddNumberToObject(out,"z",obj.z);
	return out;
}

Vector4 json_to_Vector4(cJSON* obj){
	Vector4 out = {0};
	cJSON* item_x = cJSON_GetObjectItem(obj,"x");
	out.x = (float)cJSON_GetNumberValue(item_x);
	cJSON* item_y = cJSON_GetObjectItem(obj,"y");
	out.y = (float)cJSON_GetNumberValue(item_y);
	cJSON* item_z = cJSON_GetObjectItem(obj,"z");
	out.z = (float)cJSON_GetNumberValue(item_z);
	cJSON* item_w = cJSON_GetObjectItem(obj,"w");
	out.w = (float)cJSON_GetNumberValue(item_w);
	return out;
}

cJSON* Vector4_to_json(Vector4 obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddNumberToObject(out,"x",obj.x);
	cJSON_AddNumberToObject(out,"y",obj.y);
	cJSON_AddNumberToObject(out,"z",obj.z);
	cJSON_AddNumberToObject(out,"w",obj.w);
	return out;
}

Mesh json_to_Mesh(cJSON* obj){
	Mesh out = {0};
	cJSON* item_vertexCount = cJSON_GetObjectItem(obj,"vertexCount");
	out.vertexCount = (int)cJSON_GetNumberValue(item_vertexCount);
	cJSON* item_triangleCount = cJSON_GetObjectItem(obj,"triangleCount");
	out.triangleCount = (int)cJSON_GetNumberValue(item_triangleCount);
	cJSON* item_vertices = cJSON_GetObjectItem(obj,"vertices");
	memcpy(out.vertices,cJSON_GetNumberValue(item_vertices),sizeof(float) * out.vertexCount * 3);
	cJSON* item_texcoords = cJSON_GetObjectItem(obj,"texcoords");
	memcpy(out.texcoords,cJSON_GetNumberValue(item_texcoords),sizeof(float) * out.vertexCount * 2);
	cJSON* item_texcoords2 = cJSON_GetObjectItem(obj,"texcoords2");
	memcpy(out.texcoords2,cJSON_GetNumberValue(item_texcoords2),sizeof(float) * out.vertexCount * 2);
	cJSON* item_normals = cJSON_GetObjectItem(obj,"normals");
	memcpy(out.normals,cJSON_GetNumberValue(item_normals),sizeof(float) * out.vertexCount * 3);
	cJSON* item_tangents = cJSON_GetObjectItem(obj,"tangents");
	memcpy(out.tangents,cJSON_GetNumberValue(item_tangents),sizeof(float) * out.vertexCount * 4);
	cJSON* item_colors = cJSON_GetObjectItem(obj,"colors");
	cJSON* item_indices = cJSON_GetObjectItem(obj,"indices");
	cJSON* item_animVertices = cJSON_GetObjectItem(obj,"animVertices");
	memcpy(out.animVertices,cJSON_GetNumberValue(item_animVertices),sizeof(float) * out.vertexCount * 3);
	cJSON* item_animNormals = cJSON_GetObjectItem(obj,"animNormals");
	memcpy(out.animNormals,cJSON_GetNumberValue(item_animNormals),sizeof(float) * out.vertexCount * 3);
	cJSON* item_boneIds = cJSON_GetObjectItem(obj,"boneIds");
	cJSON* item_boneWeights = cJSON_GetObjectItem(obj,"boneWeights");
	memcpy(out.boneWeights,cJSON_GetNumberValue(item_boneWeights),sizeof(float) * out.vertexCount * 4);
	cJSON* item_vaoId = cJSON_GetObjectItem(obj,"vaoId");
	cJSON* item_vboId = cJSON_GetObjectItem(obj,"vboId");
	return out;
}

cJSON* Mesh_to_json(Mesh obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddNumberToObject(out,"vertexCount",obj.vertexCount);
	cJSON_AddNumberToObject(out,"triangleCount",obj.triangleCount);
	return out;
}

KEntity* json_to_KEntity(cJSON* obj){
	KEntity* out = NULL;
	cJSON* item_transform = cJSON_GetObjectItem(obj,"transform");
	cJSON* item_model = cJSON_GetObjectItem(obj,"model");
	cJSON* item_uuid = cJSON_GetObjectItem(obj,"uuid");
	strcpy(out->uuid,cJSON_GetStringValue(item_uuid));
	cJSON* item_name = cJSON_GetObjectItem(obj,"name");
	strcpy(out->name,cJSON_GetStringValue(item_name));
	return out;
}

cJSON* KEntity_to_json(KEntity* obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddStringToObject(out,"uuid",obj->uuid);
	cJSON_AddStringToObject(out,"name",obj->name);
	return out;
}

KScene* json_to_KScene(cJSON* obj){
	KScene* out = NULL;
	cJSON* item_num_entities = cJSON_GetObjectItem(obj,"num_entities");
	cJSON* item_entities = cJSON_GetObjectItem(obj,"entities");
	return out;
}

cJSON* KScene_to_json(KScene* obj){
	cJSON* out = cJSON_CreateObject();
	return out;
}

