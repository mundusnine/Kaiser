let project = new Project('Kaiser');


project.addFile('Sources/**');
project.setDebugDir('Deployment');

resolve(project);
