workspace "WTEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "WTEngine"
	location "WTEngine"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WTF_PLATFORM_WINDOWS",
			"WTF_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "WTF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "WTF_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WTF_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WTF_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "WTF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "WTF_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WTF_DIST"
		optimize "On"