let project = new Project('Kolosseum');

const isDebug = process.argv.indexOf("--debug") > -1 ? "Debug" : "Release";
await project.addProject("../..",
    { service_provider:"raylib",options: ["3D",isDebug]}
);

project.addFiles('Sources/**');
project.setDebugDir('Deployment');

resolve(project);