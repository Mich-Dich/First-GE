workspace "Gluttony"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputs = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Gluttony"
    location "Gluttony"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputs .. "/%{prj.name}")
    objdir ("bin-int/" .. outputs .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name/src}",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GL_PLATFORM_WINDOWS",
            "GL_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputs .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "GL_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "GL_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "GL_DIST"
        optimize "On"

project "Sandbox"
    location "Gluttony"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputs .. "/%{prj.name}")
    objdir ("bin-int/" .. outputs .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Gluttony/vendor/spdlog/include",
        "Gluttony/src"
    }

    links {
        "Gluttony"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GL_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "GL_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "GL_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GL_DIST"
        optimize "On"
