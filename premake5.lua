workspace "WTEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "WTEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "WTEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "WTEngine/vendor/imgui"

include "WTEngine/vendor/GLFW"
include "WTEngine/vendor/Glad"
include "WTEngine/vendor/imgui"

project "WTEngine"
	location "WTEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wtfpch.h"
	pchsource "WTEngine/src/wtfpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WTF_PLATFORM_WINDOWS",
			"WTF_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
			--"WTF_ENABLE_ASSERTS"
		}

		postbuildcommands
		{
			--("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "WTF_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WTF_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WTF_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"WTEngine/vendor/spdlog/include",
		"WTEngine/src"
	}

	links
	{
		"WTEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"WTF_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "WTF_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WTF_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WTF_DIST"
		runtime "Release"
		optimize "On"