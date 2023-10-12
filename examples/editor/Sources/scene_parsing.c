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

Matrix json_to_Matrix(cJSON* obj){
	Matrix out = {0};
	cJSON* item_m0 = cJSON_GetObjectItem(obj,"m0");
	out.m0 = (float)cJSON_GetNumberValue(item_m0);
	cJSON* item_m4 = cJSON_GetObjectItem(obj,"m4");
	out.m4 = (float)cJSON_GetNumberValue(item_m4);
	cJSON* item_m8 = cJSON_GetObjectItem(obj,"m8");
	out.m8 = (float)cJSON_GetNumberValue(item_m8);
	cJSON* item_m12 = cJSON_GetObjectItem(obj,"m12");
	out.m12 = (float)cJSON_GetNumberValue(item_m12);
	cJSON* item_m1 = cJSON_GetObjectItem(obj,"m1");
	out.m1 = (float)cJSON_GetNumberValue(item_m1);
	cJSON* item_m5 = cJSON_GetObjectItem(obj,"m5");
	out.m5 = (float)cJSON_GetNumberValue(item_m5);
	cJSON* item_m9 = cJSON_GetObjectItem(obj,"m9");
	out.m9 = (float)cJSON_GetNumberValue(item_m9);
	cJSON* item_m13 = cJSON_GetObjectItem(obj,"m13");
	out.m13 = (float)cJSON_GetNumberValue(item_m13);
	cJSON* item_m2 = cJSON_GetObjectItem(obj,"m2");
	out.m2 = (float)cJSON_GetNumberValue(item_m2);
	cJSON* item_m6 = cJSON_GetObjectItem(obj,"m6");
	out.m6 = (float)cJSON_GetNumberValue(item_m6);
	cJSON* item_m10 = cJSON_GetObjectItem(obj,"m10");
	out.m10 = (float)cJSON_GetNumberValue(item_m10);
	cJSON* item_m14 = cJSON_GetObjectItem(obj,"m14");
	out.m14 = (float)cJSON_GetNumberValue(item_m14);
	cJSON* item_m3 = cJSON_GetObjectItem(obj,"m3");
	out.m3 = (float)cJSON_GetNumberValue(item_m3);
	cJSON* item_m7 = cJSON_GetObjectItem(obj,"m7");
	out.m7 = (float)cJSON_GetNumberValue(item_m7);
	cJSON* item_m11 = cJSON_GetObjectItem(obj,"m11");
	out.m11 = (float)cJSON_GetNumberValue(item_m11);
	cJSON* item_m15 = cJSON_GetObjectItem(obj,"m15");
	out.m15 = (float)cJSON_GetNumberValue(item_m15);
	return out;
}

cJSON* Matrix_to_json(Matrix obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddNumberToObject(out,"m0",obj.m0);
	cJSON_AddNumberToObject(out,"m4",obj.m4);
	cJSON_AddNumberToObject(out,"m8",obj.m8);
	cJSON_AddNumberToObject(out,"m12",obj.m12);
	cJSON_AddNumberToObject(out,"m1",obj.m1);
	cJSON_AddNumberToObject(out,"m5",obj.m5);
	cJSON_AddNumberToObject(out,"m9",obj.m9);
	cJSON_AddNumberToObject(out,"m13",obj.m13);
	cJSON_AddNumberToObject(out,"m2",obj.m2);
	cJSON_AddNumberToObject(out,"m6",obj.m6);
	cJSON_AddNumberToObject(out,"m10",obj.m10);
	cJSON_AddNumberToObject(out,"m14",obj.m14);
	cJSON_AddNumberToObject(out,"m3",obj.m3);
	cJSON_AddNumberToObject(out,"m7",obj.m7);
	cJSON_AddNumberToObject(out,"m11",obj.m11);
	cJSON_AddNumberToObject(out,"m15",obj.m15);
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
	memcpy(out.colors,cJSON_GetStringValue(item_colors),sizeof(unsigned char) * out.vertexCount * 4);
	cJSON* item_indices = cJSON_GetObjectItem(obj,"indices");
	memcpy(out.indices,cJSON_GetNumberValue(item_indices),sizeof(unsigned short) * out.triangleCount * 3);
	cJSON* item_animVertices = cJSON_GetObjectItem(obj,"animVertices");
	memcpy(out.animVertices,cJSON_GetNumberValue(item_animVertices),sizeof(float) * out.vertexCount * 3);
	cJSON* item_animNormals = cJSON_GetObjectItem(obj,"animNormals");
	memcpy(out.animNormals,cJSON_GetNumberValue(item_animNormals),sizeof(float) * out.vertexCount * 3);
	cJSON* item_boneIds = cJSON_GetObjectItem(obj,"boneIds");
	memcpy(out.boneIds,cJSON_GetStringValue(item_boneIds),sizeof(unsigned char) * out.vertexCount * 4);
	cJSON* item_boneWeights = cJSON_GetObjectItem(obj,"boneWeights");
	memcpy(out.boneWeights,cJSON_GetNumberValue(item_boneWeights),sizeof(float) * out.vertexCount * 4);
	cJSON* item_vaoId = cJSON_GetObjectItem(obj,"vaoId");
	out.vaoId = (unsigned int)cJSON_GetNumberValue(item_vaoId);
	cJSON* item_vboId = cJSON_GetObjectItem(obj,"vboId");
	memcpy(out.vboId,cJSON_GetNumberValue(item_vboId),sizeof(unsigned int) * 7/*MAX_MESH_VERTEX_BUFFERS*/);
	return out;
}

cJSON* Mesh_to_json(Mesh obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddNumberToObject(out,"vertexCount",obj.vertexCount);
	cJSON_AddNumberToObject(out,"triangleCount",obj.triangleCount);
	cJSON* vertices_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 3 ; ++i){
		cJSON_AddItemToArray(vertices_Array,cJSON_CreateNumber(obj.vertices[i]));
	}
	cJSON_AddArrayToObject(out,vertices_Array);
	cJSON* texcoords_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 2 ; ++i){
		cJSON_AddItemToArray(texcoords_Array,cJSON_CreateNumber(obj.texcoords[i]));
	}
	cJSON_AddArrayToObject(out,texcoords_Array);
	cJSON* texcoords2_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 2 ; ++i){
		cJSON_AddItemToArray(texcoords2_Array,cJSON_CreateNumber(obj.texcoords2[i]));
	}
	cJSON_AddArrayToObject(out,texcoords2_Array);
	cJSON* normals_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 3 ; ++i){
		cJSON_AddItemToArray(normals_Array,cJSON_CreateNumber(obj.normals[i]));
	}
	cJSON_AddArrayToObject(out,normals_Array);
	cJSON* tangents_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 4 ; ++i){
		cJSON_AddItemToArray(tangents_Array,cJSON_CreateNumber(obj.tangents[i]));
	}
	cJSON_AddArrayToObject(out,tangents_Array);
	cJSON* colors_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(unsigned char) *obj.vertexCount * 4 ; ++i){
		cJSON_AddItemToArray(colors_Array,cJSON_GetStringValue(obj.colors[i]));
	}
	cJSON_AddArrayToObject(out,colors_Array);
	cJSON* indices_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(unsigned short) *obj.triangleCount * 3 ; ++i){
		cJSON_AddItemToArray(indices_Array,cJSON_CreateNumber(obj.indices[i]));
	}
	cJSON_AddArrayToObject(out,indices_Array);
	cJSON* animVertices_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 3 ; ++i){
		cJSON_AddItemToArray(animVertices_Array,cJSON_CreateNumber(obj.animVertices[i]));
	}
	cJSON_AddArrayToObject(out,animVertices_Array);
	cJSON* animNormals_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 3 ; ++i){
		cJSON_AddItemToArray(animNormals_Array,cJSON_CreateNumber(obj.animNormals[i]));
	}
	cJSON_AddArrayToObject(out,animNormals_Array);
	cJSON* boneIds_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(unsigned char) *obj.vertexCount * 4 ; ++i){
		cJSON_AddItemToArray(boneIds_Array,cJSON_GetStringValue(obj.boneIds[i]));
	}
	cJSON_AddArrayToObject(out,boneIds_Array);
	cJSON* boneWeights_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(float) *obj.vertexCount * 4 ; ++i){
		cJSON_AddItemToArray(boneWeights_Array,cJSON_CreateNumber(obj.boneWeights[i]));
	}
	cJSON_AddArrayToObject(out,boneWeights_Array);
	cJSON_AddNumberToObject(out,"vaoId",obj.vaoId);
	cJSON* vboId_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(unsigned int) *7/*MAX_MESH_VERTEX_BUFFERS*/ ; ++i){
		cJSON_AddItemToArray(vboId_Array,cJSON_CreateNumber(obj.vboId[i]));
	}
	cJSON_AddArrayToObject(out,vboId_Array);
	return out;
}

Model json_to_Model(cJSON* obj){
	Model out = {0};
	cJSON* item_transform = cJSON_GetObjectItem(obj,"transform");
	cJSON* item_meshCount = cJSON_GetObjectItem(obj,"meshCount");
	out.meshCount = (int)cJSON_GetNumberValue(item_meshCount);
	cJSON* item_materialCount = cJSON_GetObjectItem(obj,"materialCount");
	out.materialCount = (int)cJSON_GetNumberValue(item_materialCount);
	cJSON* item_meshes = cJSON_GetObjectItem(obj,"meshes");
	cJSON* item_materials = cJSON_GetObjectItem(obj,"materials");
	cJSON* item_meshMaterial = cJSON_GetObjectItem(obj,"meshMaterial");
	memcpy(out.meshMaterial,cJSON_GetNumberValue(item_meshMaterial),sizeof(int) * out.meshCount);
	cJSON* item_boneCount = cJSON_GetObjectItem(obj,"boneCount");
	out.boneCount = (int)cJSON_GetNumberValue(item_boneCount);
	cJSON* item_bones = cJSON_GetObjectItem(obj,"bones");
	cJSON* item_bindPose = cJSON_GetObjectItem(obj,"bindPose");
	return out;
}

cJSON* Model_to_json(Model obj){
	cJSON* out = cJSON_CreateObject();
	cJSON_AddObjectToObject(out,Matrix_to_json(obj.transform));
	cJSON_AddNumberToObject(out,"meshCount",obj.meshCount);
	cJSON_AddNumberToObject(out,"materialCount",obj.materialCount);
	cJSON_AddObjectToObject(out,Mesh_to_json(obj.meshes));
	cJSON_AddObjectToObject(out,Material_to_json(obj.materials));
	cJSON* meshMaterial_Array = cJSON_CreateArray();
	for(int i =0; i < sizeof(int) *obj.meshCount ; ++i){
		cJSON_AddItemToArray(meshMaterial_Array,cJSON_CreateNumber(obj.meshMaterial[i]));
	}
	cJSON_AddArrayToObject(out,meshMaterial_Array);
	cJSON_AddNumberToObject(out,"boneCount",obj.boneCount);
	cJSON_AddObjectToObject(out,BoneInfo_to_json(obj.bones));
	cJSON_AddObjectToObject(out,Transform_to_json(obj.bindPose));
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
	cJSON_AddObjectToObject(out,Matrix_to_json(obj->transform));
	cJSON_AddObjectToObject(out,Model_to_json(obj->model));
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
	cJSON_AddObjectToObject(out,uint16_t_to_json(obj->num_entities));
	cJSON_AddObjectToObject(out,KEntity_to_json(obj->entities));
	return out;
}

