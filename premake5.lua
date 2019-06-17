workspace "Element"
	configurations { "Debug", "Release" }
	staticruntime "On"
	startproject "Element"

	filter "system:windows"
		platforms   { "x86", "x64" }
		flags {"MultiProcessorCompile" }
	filter "configurations:Debug"
		Symbols "On"

	project "Element"
		warnings "Extra"

		filter "configurations:Debug"
			defines     "ELM_DEBUG"
			flags       { "Symbols" }

		filter "configurations:Release"
			optimize    "Full"
			flags { "NoIncrementalLink", "LinkTimeOptimization" }
			