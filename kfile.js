let project = new Project('Kaiser');

const serviceCommand = "--tolang";
let index = process.argv.indexOf(serviceCommand);//eventually change this to custom command arg --service...
let isDebug = process.argv.indexOf("--debug") >= 0;
if(!isDebug){
    project.addDefine("NDEBUG");
}
let service_flags = []; 
if (index >= 0) {
    service_flags = process.argv.splice(index,2);
    if(service_flags[1] !== "raylib" && service_flags[1] !== "kinc"){
        console.error(`Error: Service provider ${service_flags[1]} not supported.`);
        process.exit(1);
    }
}

await project.addProject("./Libraries",service_flags);
project.addFiles('Sources/**');
project.setDebugDir('Deployment');

project.flatten();

resolve(project);
