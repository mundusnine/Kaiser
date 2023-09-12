let project = new Project('Test');

await project.addProject("../..",
    { service_provider:"raylib",options: ["2D"]}
);

project.addFiles('Sources/**');
project.setDebugDir('Deployment');

resolve(project);