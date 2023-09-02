let project = new Project('Kaiser');
const serviceCommand = "--tolang";
let index = process.argv.indexOf(serviceCommand);//eventually change this to custom command arg --service...
let service_flags = []; 
if (index >= 0) {
    service_flags = process.argv.splice(index,2);
    if(service_flags[1] !== "raylib" && service_flags[1] !== "kinc"){
        console.error(`Error: Service provider ${service_flags[1]} not supported.`);
        process.exit(1);
    }
}
await project.addProject("./ServiceProviders",service_flags);
project.addFile('Sources/**');
project.setDebugDir('Deployment');

resolve(project);
