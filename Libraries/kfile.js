const system = platform === Platform.Windows ? "win32" :
			   platform === Platform.Linux   ? "linux" :
			   platform === Platform.OSX     ? "macos" :
			   platform === Platform.Wasm    ? "wasm" :
			   platform === Platform.Android ? "android" :
			   platform === Platform.iOS     ? "ios" :
			   								   "unknown";

let project = new Project('Provider');

project.addIncludeDir("xxHash");
if(Options[1] === "raylib"){
    project.addExclude("raylib/src/external/dirent.h");
    const raylib_path = "raylib/src";
    project.addIncludeDir(raylib_path);
    project.addIncludeDir("raylib/src/external/glfw/include");

    project.addDefine("RAYLIB_PROVIDER");
    project.addDefine("PLATFORM_DESKTOP");

    project.addFiles(
        raylib_path+"/rcore.c",
        raylib_path+"/rmodels.c",
        raylib_path+"/rshapes.c",
        raylib_path+"/rtext.c",
        raylib_path+"/rtextures.c",
        raylib_path+"/utils.c",
        raylib_path+"/raudio.c",
    );

    project.setCStd('c11');
    const GLFW_path = "raylib/src/external/glfw/src/";
    project.addFiles(
        GLFW_path+"internal.h",
        GLFW_path+"platform.h",
        GLFW_path+"mappings.h",
        GLFW_path+"context.c",
        GLFW_path+"init.c",
        GLFW_path+"input.c",
        GLFW_path+"monitor.c",
        GLFW_path+"platform.c",
        GLFW_path+"vulkan.c",
        GLFW_path+"window.c",
        GLFW_path+"egl_context.c",
        GLFW_path+"osmesa_context.c",
        GLFW_path+"null_platform.h",
        GLFW_path+"null_joystick.h",
        GLFW_path+"null_init.c",
        GLFW_path+"null_monitor.c",
        GLFW_path+"null_window.c",
        GLFW_path+"null_joystick.c"
    );
    if(system === "win32"){
        project.addDefine("_WINSOCK_DEPRECATED_NO_WARNINGS");
        project.addDefine("_CRT_SECURE_NO_WARNINGS");

        project.addDefine("_WIN32");
        project.addLib("winmm");
        project.addLib("kernel32");
        project.addLib("opengl32");
        project.addLib("gdi32");

        project.addDefine("_UNICODE");
        project.addDefine("_CRT_SECURE_NO_WARNINGS");
        project.addCFlag("/W3");

        project.addDefine("_GLFW_WIN32");
        project.addFiles(
            GLFW_path+"win32_time.h",
            GLFW_path+"win32_thread.h",
            GLFW_path+"win32_module.c",
            GLFW_path+"win32_time.c",
            GLFW_path+"win32_thread.c",
            GLFW_path+"win32_platform.h",
            GLFW_path+"win32_joystick.h",
            GLFW_path+"win32_init.c",
            GLFW_path+"win32_joystick.c",
            GLFW_path+"win32_monitor.c",
            GLFW_path+"win32_window.c",
            GLFW_path+"wgl_context.c"
        );

        // IF GNU GCC on WINDOWS
        // project.addFiles( 
        //     "context.c","init.c","input.c","monitor.c","platform.c",
        //     "vulkan.c","window.c","null_init.c","null_joystick.c","null_monitor.c",
        //     "null_window.c", "win32_init.c", "win32_joystick.c"," win32_module.c",
        //     "win32_monitor.c"," win32_time.c", "win32_thread.c", "win32_window.c",
        //     "wgl_context.c", "egl_context.c", "osmesa_context.c"); 
        // project.addCFlag("-Wdeclaration-after-statement");
        // END GNU WINDOWS

        //IF MINGW:
        // project.addLib("m -Wl,--nxcompat");
        // target_include_directories(glfw PRIVATE "${GLFW_SOURCE_DIR}/deps/mingw")
        // # NOTE: MinGW-w64 and Visual C++ do /not/ need this hack.
        // if (MINGW)
        // project.addDefine("WINVER=0x0501");
    }

    if(system === "linux"){
        project.addLib("pthread");
        project.addLib("GL");
        project.addLib("m");
        project.addLib("dl");
        project.addLib("rt");
        project.addLib("X11");

        project.addCFlag("-Wall");

        project.addDefine("_DEFAULT_SOURCE");
        project.addDefine("_GLFW_X11");
        project.addFiles(
            GLFW_path+"posix_time.h",
            GLFW_path+"posix_thread.h",
            GLFW_path+"posix_module.c",
            GLFW_path+"posix_time.c",
            GLFW_path+"posix_thread.c"
        );
        project.addFiles(
            GLFW_path+"linux_joystick.h",
            GLFW_path+"linux_joystick.c",
            GLFW_path+"posix_poll.h",
            GLFW_path+"posix_poll.c",
            //X11
            GLFW_path+"x11_platform.h",
            GLFW_path+"xkb_unicode.h",
            GLFW_path+"x11_init.c",
            GLFW_path+"x11_monitor.c",
            GLFW_path+"x11_window.c",
            GLFW_path+"xkb_unicode.c",
            GLFW_path+"glx_context.c"
            //END X11
        );
        // ALWAYS USE X11 for now
        // if (GLFW_BUILD_WAYLAND)
        // target_compile_definitions(glfw PRIVATE _GLFW_WAYLAND)
        // target_sources(glfw PRIVATE wl_platform.h xkb_unicode.h wl_init.c
        //                    wl_monitor.c wl_window.c xkb_unicode.c)
        // endif()
    }
}
if(Options[1] === "kinc"){
    //@TODO: Add me baby
}
project.addIncludeDir("../Sources");
project.addFiles(
    `ServiceProviders/${Options[1]}/*`,
    "xxHash/xxhash.c",
    "xxHash/xxhash.h",
);

project.flatten();

resolve(project);