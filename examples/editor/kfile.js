let project = new Project('Kolosseum');

const isDebug = process.argv.indexOf("--debug") > -1 ? "Debug" : "Release";
await project.addProject("../..",
    { service_provider:"raylib",options: ["3D",isDebug]}
);

project.addIncludeDir("Libraries/cJSON");
project.addIncludeDir("Sources");

project.addFiles(
    'Sources/**',
    'Libraries/cJSON/**'
);
project.setDebugDir('Deployment');

resolve(project);