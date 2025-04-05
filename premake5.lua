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
        "%{prj.name}/vendor/spdlog/include"
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
            "WGE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
        }

    filter "configurations:Debug"
        defines
        {
            "WGE_DEBUG"
        }
        symbols "On"
        
    filter "configurations:Release"
        defines
        {
            "WGE_RELEASE"
        }
        optimize "On"

    filter "configurations:Dist"
        defines
        {
            "WGE_DIST"
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
        symbols "On"
        
    filter "configurations:Release"
        defines
        {
            "WGE_RELEASE"
        }
        optimize "On"

    filter "configurations:Dist"
        defines
        {
            "WGE_DIST"
        }
        optimize "On"