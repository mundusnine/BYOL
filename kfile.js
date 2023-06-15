let project = new Project('GOAL');

project.kore = false;

project.addFile('Sources/**');
project.setDebugDir('Deployment');

await project.addProject('Libraries/replxx');
await project.addProject('Libraries/fmt');

project.flatten();

resolve(project);
