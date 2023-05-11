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
IncludeDir["ImGui"] = "CM_Engine/vendor/imgui/include"

include "CM_Engine/vendor/imgui"

project "CM_Engine"
	location "CM_Engine"
	kind "SharedLib"
	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

		defines
		{
			"_WINDLL",
			"CM_BUILD_DLL",
			"CM_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "CM_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "CM_RELEASE"
			buildoptions "/MD"
			symbols "On"

		filter "configurations:Dist"
			defines "CM_DIST"
			buildoptions "/MD"
			symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"

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
		"CM_Engine/src"
	}

	links
	{
		"CM_Engine",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

		defines
		{
			"_WINDLL",
			"CM_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "CM_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "CM_RELEASE"
			buildoptions "/MD"
			symbols "On"

		filter "configurations:Dist"
			defines "CM_DIST"
			buildoptions "/MD"
			symbols "On"