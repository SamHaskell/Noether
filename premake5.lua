workspace "Noether"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "NoetherEditor"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Engine"
	include "noether/premake5.lua"
group ""

include "editor/premake5.lua"