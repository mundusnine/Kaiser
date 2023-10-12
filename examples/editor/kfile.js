// const { spawn } = require('child_process');
// const fs = require('fs');
// const path = require('path');
// const raylibPath = path.resolve(__dirname +"/../../Libraries/raylib/src");

// function runChildProcess() {
//   return new Promise((resolve, reject) => {
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
//     ];
//     console.log(args);
//     const child = spawn(cmd, args);

//     let stdoutData = '';

//     child.stdout.on('data', (data) => {
//       stdoutData += data.toString();
//     });
//     //@TODO: Add back error checking when this is fixed: https://github.com/ziglang/zig/issues/17361
//     // child.stderr.on('data', (data) => {
//     //   // Handle any error or stderr output here
//     //   reject(new Error(data.toString()));
//     // });

//     child.on('close', (code) => {
//     //   if (code === 0) {
//         resolve(stdoutData);
//     //   } else {
//     //     reject(new Error(`Child process exited with code ${code}`));
//     //   }
//     });
//   });
// }

// function write(file,line, indent = 0) {
//     let tabs = '';
//     for (let i = 0; i < indent; ++i) {
//         tabs += '\t';
//     }
//     return file += tabs + line + '\n';
// }

// function baseTypeToCJSON(type,toJSON=true,isArray=false){
//     switch(type){
//         case "float":
//         case "int":
//         case "short":
//             if(isArray){
//                 return "cJSON_CreateNumber";
//             }
//             return toJSON ? "cJSON_AddNumberToObject" : "cJSON_GetNumberValue";
//         case "char":
//             return toJSON ? "cJSON_AddStringToObject" : "cJSON_GetStringValue";
//     }
// }
// const baseTypes = ["float","int","short","size_t","bool","char"]
// const countsByType = {
//     "Mesh" : {
//         "vertices" :"vertexCount * 3",
//         "texcoords" : "vertexCount * 2",
//         "texcoords2" : "vertexCount * 2",
//         "normals" : "vertexCount * 3",
//         "tangents" : "vertexCount * 4",
//         "colors" : "vertexCount * 4",
//         "indices" : "triangleCount * 3",
//         "animVertices" : "vertexCount * 3",
//         "animNormals" : "vertexCount * 3",
//         "boneIds" : "vertexCount * 4",
//         "boneWeights" : "vertexCount * 4",
//         "vboId" : "7/*MAX_MESH_VERTEX_BUFFERS*/"
//     },
//     "Model" : {
//         "meshMaterial" : "meshCount",
//         "meshes" : "meshCount",
//     },
// };
// const neededTypes = [
//     "Vector3",
//     "Vector4",
//     "Matrix",
//     "Mesh",
//     "Model",
//     "KEntity",
//     "KScene"
// ];
// try {
//     let hFilename = "scene_parsing.h"
//     let hFile = ""
//     let cFile = ""
//     hFile = write(hFile,`#pragma once\n`);
//     hFile = write(hFile,`struct cJSON;\n`);
//     cFile = write(cFile,`#include "cJSON.h"`);
//     cFile = write(cFile,`#include "scenedefs.h"`);
//     cFile = write(cFile,`#include "${hFilename}"\n`);
//     console.log(cFile);
//     const result = await runChildProcess();
//     const jsonData = JSON.parse(result);
//     const data = jsonData.inner;
//     const writeFields = (file,type,isToJson,isPointer,jsonArr) =>{
//         console.log(type);
//         for (let i = 0; i < jsonArr.length; i++){
//             const element = jsonArr[i];
//             if(element["kind"] === "FieldDecl"){
//                 let name = element["name"];
//                 let f_type = element["type"]["qualType"].split('[')[0];
//                 let isUnsigned = f_type.indexOf("unsigned") > -1;
//                 if(isUnsigned){
//                     f_type = f_type.replace("unsigned","");
//                 }
//                 let isArray = f_type.endsWith("*");
//                 if(isArray){
//                     f_type = f_type.split("*")[0];
//                 }
//                 f_type = f_type.trim();
//                 let accessNoName = (isPointer ? "->": ".");
//                 let access = accessNoName + name;
//                 let outType = (isUnsigned ? "unsigned ":"") + f_type;
//                 if(isToJson){
//                     if(baseTypes.includes(f_type)){
//                         let arrName = `${name}_Array`;
//                         if(!isArray){
//                             file = write(file,`${baseTypeToCJSON(f_type)}(out,\"${name}\",obj${access});`,1);
//                         }
//                         else if(isArray){
//                             let isNum = /^\d$/.test(countsByType[type][name].at(0));
//                             let call = isNum ? countsByType[type][name] : `obj${accessNoName}${countsByType[type][name]}`;
//                             file = write(file,`cJSON* ${arrName} = cJSON_CreateArray();`,1);
//                             file = write(file,`for(int i =0; i < sizeof(${outType}) *${call} ; ++i){`,1);
//                             file = write(file,`cJSON_AddItemToArray(${arrName},${baseTypeToCJSON(f_type,false,isArray)}(obj${access}[i]));`,2);
//                             file = write(file,`}`,1);
//                             file = write(file,`cJSON_AddArrayToObject(out,${arrName});`,1);
//                         }
//                     }
//                     else {
//                         if(isArray){
//                             let isNum = /^\d$/.test(countsByType[type][name].at(0));
//                             let call = isNum ? countsByType[type][name] : `obj${accessNoName}${countsByType[type][name]}`;
//                             file = write(file,`cJSON* ${arrName} = cJSON_CreateArray();`,1);
//                             file = write(file,`for(int i =0; i < sizeof(${outType}) *${call} ; ++i){`,1);
//                             file = write(file,`cJSON_AddItemToArray(${arrName},${baseTypeToCJSON(f_type,false,isArray)}(obj${access}[i]));`,2);
//                             file = write(file,`}`,1);
//                             file = write(file,`cJSON_AddArrayToObject(out,${arrName});`,1);
//                         }
//                         else{
//                             file = write(file,`cJSON_AddObjectToObject(out,${f_type}_to_json(obj${access}));`,1)
//                         }
//                     }
//                 }
//                 else {
//                     let itemName = `item_${name}`;
//                     file = write(file,`cJSON* ${itemName} = cJSON_GetObjectItem(obj,"${name}");`,1);
//                     if(baseTypes.includes(f_type)){
//                         if(f_type === "char" && !isArray && !isUnsigned){
//                             file = write(file,`strcpy(out${access},${baseTypeToCJSON(f_type,false)}(${itemName}));`,1);
//                         }
//                         else if(isArray){
//                             let isNum = /^\d$/.test(countsByType[type][name].at(0));
//                             console.log(countsByType[type][name].at(0),isNum);
//                             let call = isNum ? countsByType[type][name] : `out${accessNoName}${countsByType[type][name]}`;
//                             file = write(file,
//                                 `memcpy(out${access},${baseTypeToCJSON(f_type,false)}(${itemName}),sizeof(${outType}) * ${call});`,
//                             1);
//                         }
//                         else{
//                             file = write(file,`out${access} = (${outType})${baseTypeToCJSON(f_type,false)}(${itemName});`,1);
//                         }
//                     }
//                 }
//             }
//         }
//         return file;
//     };
//     for (let i = 0; i < data.length; i++) {
//         const element = data[i];
//         let name = element["name"];
//         if(element["kind"] === "RecordDecl" && neededTypes.includes(name)){
//             let isPointer = name === "KScene" || name === "KEntity";
//             hFile = write(hFile,`struct ${name};`);
//             let toNativeFunc = `${name + (isPointer ? '*' : '')} json_to_${name}(cJSON* obj)`;
//             let toJsonFunc = `cJSON* ${name}_to_json(${name + (isPointer ? '*' : '')} obj)`
//             hFile = write(hFile,`${toNativeFunc};`);
//             hFile = write(hFile,`${toJsonFunc};`);

//             cFile = write(cFile,`${toNativeFunc}{`);
//             cFile = write(cFile,`${name + (isPointer ? '*' : '')} out = ${isPointer ? "NULL;":"{0};"}`,1);
//             if(element.inner){
//                 cFile = writeFields(cFile,name,false,isPointer,element.inner);
//             }
//             cFile = write(cFile,`return out;`,1);
//             cFile = write(cFile,`}\n`);
//             cFile = write(cFile,`${toJsonFunc}{`);
//             cFile = write(cFile,`cJSON* out = cJSON_CreateObject();`,1);
//             if(element.inner){
//                 cFile = writeFields(cFile,name,true,isPointer,element.inner);
//             }
//             cFile = write(cFile,`return out;`,1);
//             cFile = write(cFile,`}\n`);

//             hFile = write(hFile,`\n`);

//         }
//     }
//     fs.writeFileSync(__dirname+"/Sources/"+hFilename,hFile);
//     fs.writeFileSync(__dirname+"/Sources/"+hFilename.replace(".h",".c"),cFile);
//     process.abort();
// } catch (error) {
//     console.error('Error:', error);
// }
// process.abort();

let project = new Project('Kolosseum');

const isDebug = process.argv.indexOf("--debug") > -1 ? "Debug" : "Release";
await project.addProject("../..",
    { service_provider:"raylib",options: ["3D",isDebug]}
);

project.addIncludeDir("Libraries/cJSON");
project.addIncludeDir("Libraries/uuid4/src");
project.addIncludeDir("Sources");

project.addFiles(
    'Sources/**',
    'Libraries/cJSON/**',
    'Libraries/uuid4/src/**'
);

project.setDebugDir('Deployment');

resolve(project);