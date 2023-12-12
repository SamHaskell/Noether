workspace "Noether"
    configurations { "Debug", "Release" }
    startproject "emmy"

OutputDir = "%{cfg.system}/%{cfg.buildcfg}"

group "Dependencies"
	include "engine/vendor/glfw/premake5.lua"
group ""

group "Engine"
	include "engine/premake5.lua"
group ""

group "Tools"
    include "editor/premake5.lua"
group ""

group "Examples"
    include "examples/template/premake5.lua"    
    include "examples/lighting/premake5.lua"
group ""