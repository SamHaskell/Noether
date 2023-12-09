workspace "Noether"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "emmy"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
	include "engine/vendor/glfw"
group ""

group "Engine"
	include "engine/premake5.lua"
group ""

group "Tools"
    include "editor/premake5.lua"
group ""