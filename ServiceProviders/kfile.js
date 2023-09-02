const system = platform === Platform.Windows ? "win32" :
			   platform === Platform.Linux   ? "linux" :
			   platform === Platform.OSX     ? "macos" :
			   platform === Platform.Wasm    ? "wasm" :
			   platform === Platform.Android ? "android" :
			   platform === Platform.iOS     ? "ios" :
			   								   "unknown";

let project = new Project('Provider');

let provider_filepath = [];
if(Options[1] === "raylib"){
    project.addIncludeDir("../Libraries/raylib/src");
    project.addIncludeDir("../Libraries/raylib/src/external");
    project.addIncludeDir("../Libraries/raylib/src/glfw/include");

    if(system === "win32"){
        project.addDefine("_WINSOCK_DEPRECATED_NO_WARNINGS");
        project.addDefine("_CRT_SECURE_NO_WARNINGS");

        project.addDefine("_WIN32");
        project.addLib("winmm");
        project.addLib("kernel32");
        project.addLib("opengl32");
        project.addLib("gdi32");
    }

    if(system === "linux"){
        project.addLib("pthread");
        project.addLib("GL");
        project.addLib("m");
        project.addLib("dl");
        project.addLib("rt");
        project.addLib("X11");
    }
    // provider_filepath.push(__dirname+"/../Libraries/raylib/src/**");
    //add this https://github.com/raysan5/raylib/blob/master/src/CMakeLists.txt
}
if(Options[1] === "kinc"){
    //@TODO: Add me baby
}
project.addIncludeDir("../Sources");
project.addFiles(`${__dirname}/${Options[1]}/**`,...provider_filepath);

project.flatten();

resolve(project);