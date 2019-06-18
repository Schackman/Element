workspace "Element"
	configurations { "Debug", "Release" }
	staticruntime "On"
	startproject "Element"
	platforms   { "x86", "x64" }	
	outputdir = "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/"
	
	filter "platforms:x86"
		architecture "x86"
	filter "platforms:x64"
		architecture "x64"
	
	filter "system:windows"
		flags {"MultiProcessorCompile" }
	filter "configurations:Debug"
		symbols "On"

	project "Element"
		location "Element"
		language "C++"
		cppdialect "C++17"
		warnings "Extra"
		
		includedirs{
		"Element/src/",
		"Element/src/pch/",
		"thirdparty/glad/include/"
		}
		
		files
		{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		}
		
		links 
		{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
		}
		pchheader "pch.h"
		pchsource "src/pch/pch.cpp"

		filter "configurations:Debug"
			kind("ConsoleApp")
			defines     "ELM_DEBUG"

		filter "configurations:Release"
			kind("WindowedApp")
			optimize "Full"
			flags { "NoIncrementalLink", "LinkTimeOptimization" }
	
group "thirdparty"
	project "glad"
		location "%{prj.group}/%{prj.name}"
		language "C"
		kind("StaticLib")
		warnings "off"
		
		includedirs{
		"%{prj.location}/include/"
		}
		
		srcDir = "%{prj.group}/{prj.name}/src/"
		
		files
		{
		srcDir .. "**.h",
		srcDir .. "**.cpp"
		}			
		filter "configurations:Release"
			optimize "Full"
			flags { "NoIncrementalLink", "LinkTimeOptimization" }
group ""
			