---------------- Workspace Settings ----------------
workspace "WinterGameEngine"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

----------------- Global Var --------------------------

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "WinterGameEngine/vendor/spdlog/include"
IncludeDir["GLFW"] = "WinterGameEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "WinterGameEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "WinterGameEngine/vendor/imgui"

-- Include other premake5.lua files
include "WinterGameEngine/vendor/GLFW"
include "WinterGameEngine/vendor/Glad"
include "WinterGameEngine/vendor/imgui"

---------------- WGE Project Settings ----------------
project "WinterGameEngine"
    location "WinterGameEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "wgepch.h"
    pchsource "WinterGameEngine/src/wgepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
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

    buildoptions
    {
        "/utf-8"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "WGE_PLATFORM_WINDOWS",
            "WGE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
        }

    filter "configurations:Debug"
        defines
        {
            "WGE_DEBUG",
            "WGE_ENABLE_ASSERTS"
        }

        buildoptions
        {
            "/MDd"
        }

        symbols "On"
        
    filter "configurations:Release"
        defines
        {
            "WGE_RELEASE"
        }

        buildoptions
        {
            "/MD"
        }

        optimize "On"

    filter "configurations:Dist"
        defines
        {
            "WGE_DIST"
        }

        buildoptions
        {
            "/MD"
        }

        optimize "On"

---------------- Sandbox Project Settings ----------------
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
        "WinterGameEngine/vendor/spdlog/include",
        "WinterGameEngine/src"
    }

    links
    {
        "WinterGameEngine"
    }

    buildoptions
    {
        "/utf-8"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "WGE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines
        {
            "WGE_DEBUG"
        }

        buildoptions
        {
            "/MDd"
        }

        symbols "On"
        
    filter "configurations:Release"
        defines
        {
            "WGE_RELEASE"
        }

        buildoptions
        {
            "/MD"
        }

        optimize "On"

    filter "configurations:Dist"
        defines
        {
            "WGE_DIST"
        }

        buildoptions
        {
            "/MD"
        }
        
        optimize "On"