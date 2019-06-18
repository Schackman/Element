workspace "Element"
	configurations { "Debug", "Release" }
	staticruntime "On"
	startproject "Element"
	platforms   { "x86", "x64" }	
	outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/"
	print(outputdir)
	dependenciesDir = "thirdparty/"
	
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
		warnings "Default"
		
		pchheader "pch.h"
		pchsource "Element/src/pch/pch.cpp"
		
		targetdir ("bin/" .. outputdir .. "%{prj.name}/")
		objdir ("intermediates/" .. outputdir .. "%{prj.name}/")
		
		prjDeps = "%{prj.location}/thirdparty/"
		vulkanDir = os.getenv("VULKAN_SDK") .. "/"
		
		includedirs{
			prjDeps .. "include/",
			dependenciesDir .. "glad/include/",
			vulkanDir .. "include/",
			"%{prj.location}/src/",
			"%{prj.location}/src/pch/"
		}
		
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}
		
		links 
		{ 
			"glfw3",
			"glad",
			"opengl32",
			"vulkan-1"
		}
		
		libdirs { 
			prjDeps .. "lib/%{cfg.platform}",
		}
		
		filter "platforms:x64"
			-- libdirs{vulkanDir .. "Lib"}
		filter "platforms:x86"
			-- libdirs{vulkanDir .. "Lib32"}
			
		filter "configurations:Debug"
			kind("ConsoleApp")
			defines "_DEBUG"

		filter "configurations:Release"
			kind("WindowedApp")
			optimize "Full"
			flags { "NoIncrementalLink", "LinkTimeOptimization" }
	
group("thirdparty")
	project "glad"
		location(dependenciesDir .. "%{prj.name}")
		language "C"
		kind("StaticLib")
		warnings "off"
		
		targetdir ("bin/" .. outputdir .. "%{prj.name}/")
		objdir ("intermediates/" .. outputdir .. "%{prj.name}/")
		
		includedirs{
			"%{prj.location}/include/"
		}
		
		files{"%{prj.location}/**.h", "%{prj.location}/**.c"}
		
		filter "configurations:Release"
			optimize "Full"
			flags { "NoIncrementalLink", "LinkTimeOptimization" }
group ""
			