project "Glad"
	kind "StaticLib"
	language "C"
    staticruntime "On" 
	warnings "off"

	targetdir ("bin/" .. outputs .. "/%{prj.name}")
	objdir ("bin-int/" .. outputs .. "/%{prj.name}")

	files {
  
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

    includedirs {
        "include"
    }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"
		