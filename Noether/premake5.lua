project "noether"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files { 
        -- project
        "src/**.h", 
        "src/**.cpp",

        -- imgui
        "vendor/imgui/*.h",
        "vendor/imgui/*.cpp",
        "vendor/imgui/backends/imgui_impl_opengl3.h",
        "vendor/imgui/backends/imgui_impl_opengl3.cpp",
        "vendor/imgui/backends/imgui_impl_glfw.h",
        "vendor/imgui/backends/imgui_impl_glfw.cpp",

        -- stb
        "vendor/stb/stb_impl.cpp",
        "vendor/stb/stb_image.h",
        "vendor/stb/stb_image_write.h",

        -- json
        "vendor/json/json.hpp",

        -- tinygltf
        "vendor/tiny/tiny_impl.cpp",
        "vendor/tiny/tiny_gltf.h",
        "vendor/tiny/tiny_obj_loader.h",

        -- glad
        "vendor/glad/src/glad.c",
    }

    includedirs {
        -- project
        "src",

        -- vendor
        "vendor/imgui",
        "vendor/stb",
        "vendor/json",
        "vendor/tiny",
        "vendor/glad/include",
    }

    links {
        "glfw"
    }

    targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"

    filter "system:macosx"
        defines { "PLATFORM_MAC" }