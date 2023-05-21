workspace "CM_Engine"

architecture "x64"
startproject "Sandbox"
configurations
{
	"Debug",
	"Release",
	"Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "CM_Engine/vendor/imgui"

include "CM_Engine/vendor/imgui"

project "CM_Engine"
	location "CM_Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "CM_Engine/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include;",
		"%{prj.name}/src;",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_WINDLL",
			"CM_BUILD_DLL",
			"CM_PLATFORM_WINDOWS"
		}


		filter "configurations:Debug"
			defines "CM_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "CM_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "CM_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CM_Engine/vendor/spdlog/include;",
		"CM_Engine/src",
		"CM_Engine/vendor"
	}

	links
	{
		"CM_Engine",
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_WINDLL",
			"CM_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "CM_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "CM_RELEASE"
			runtime "Release"
			symbols "on"

		filter "configurations:Dist"
			defines "CM_DIST"
			runtime "Release"
			symbols "on"