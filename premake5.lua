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
IncludeDir["glm"] = "WTEngine/vendor/glm"

include "WTEngine/vendor/GLFW"
include "WTEngine/vendor/Glad"
include "WTEngine/vendor/imgui"

project "WTEngine"
	location "WTEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wtfpch.h"
	pchsource "WTEngine/src/wtfpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WTF_PLATFORM_WINDOWS",
			"WTF_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "WTF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WTF_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WTF_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"WTEngine/src",
		"WTEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"WTEngine",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"WTF_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "WTF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WTF_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WTF_DIST"
		runtime "Release"
		optimize "on"