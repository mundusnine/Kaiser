let project = new Project('Test');

const isDebug = process.argv.indexOf("--debug") > -1 ? "Debug" : "Release";
await project.addProject("../..",
    { service_provider:"raylib",options: ["2D",isDebug]}
);

project.addFiles('Sources/**');
project.setDebugDir('Deployment');

resolve(project);