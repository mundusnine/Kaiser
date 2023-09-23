const fieldName = "service_provider";
const optsName = "options";
let project = new Project('Kaiser');
if (typeof Options === 'object' && Options !== null && Options.hasOwnProperty(fieldName)) {
    let service_flags = [Options.service_provider];
    if(service_flags[0] !== "raylib" && service_flags[0] !== "kinc"){
        console.error(`Error: Service provider ${service_flags[1]} not supported.`);
        process.exit(1);
    }
    if(optsName in Options){
        const opts = Options[optsName];
        if(Array.isArray(opts)){
            for(let i =0; i < opts.length;++i ){
                service_flags.push(opts[i]);
            }
        }
        if(opts.indexOf("Debug") > -1){
            console.log("Debug Mode");
            project.addDefine("_DEBUG");
        }
        else{
            project.addDefine("NDEBUG");
        }
    }
    await project.addProject("./Libraries",service_flags);
    project.addFiles('Sources/**');
    project.flatten();

    resolve(project);
}
else {
    console.log(`You didn't pass an object with the field ${fieldName} to the addProject function i.e. project.addProject("Kaiser/Folder/path",{${fieldName}: "raylib"})`)
    exit(1);
}
