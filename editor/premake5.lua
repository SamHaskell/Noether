project "emmy"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files { 
        "src/**.h", 
        "src/**.cpp" 
    }

    includedirs {
        "src",
	    "../engine/src",
        "../engine/vendor/imgui"
    }

    links {
        "noether",
        "glfw"
    }

    targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

    filter "system:macosx"
        defines { "PLATFORM_MAC" }
        targetextension ""
        links {
            "Cocoa.framework",
            "IOKit.framework",
            "OpenGL.framework"
        }

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