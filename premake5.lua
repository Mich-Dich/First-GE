workspace "Gluttony"
    architecture "x64"
    startproject "Sandbox"
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputs = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VendorIncludeDir = {}
VendorIncludeDir["GLFW"] = "Gluttony/vendor/GLFW/include"
VendorIncludeDir["Glad"] = "Gluttony/vendor/Glad/include"
VendorIncludeDir["ImGui"] = "Gluttony/vendor/imgui"

include "Gluttony/vendor/GLFW"
include "Gluttony/vendor/Glad"
include "Gluttony/vendor/imgui"

project "Gluttony"
    location "Gluttony"
    kind "SharedLib"
    language "C++"
    staticruntime "On" 

    targetdir ("bin/" .. outputs .. "/%{prj.name}")
    objdir ("bin-int/" .. outputs .. "/%{prj.name}")

    pchheader "glpch.h"
    pchsource "Gluttony/src/glpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{VendorIncludeDir.GLFW}",
        "%{VendorIncludeDir.Glad}",
        "%{VendorIncludeDir.ImGui}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
	    "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GL_PLATFORM_WINDOWS",
            "GL_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputs .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "GL_DEBUG"
        buildoptions "/MDd"
        symbols "On"
        
    filter "configurations:Release"
        defines "GL_RELEASE"
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist"
        defines "GL_DIST"
        buildoptions "/MD"
        optimize "On"

    filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"
		
project "Sandbox"
    location "Gluttony"
    kind "ConsoleApp"
    language "C++"
    staticruntime "On" 

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
        buildoptions "/MDd"
        symbols "On"
        
    filter "configurations:Release"
        defines "GL_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "GL_DIST"
        buildoptions "/MD"
        optimize "On"

    filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"
		