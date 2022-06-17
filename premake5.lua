
workspace "GLW"
	architecture "x64"
	startproject "GLW"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "GLW"
	location "GLW"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/GLEW/include",
		"%{prj.name}/vendor/stb_image",
		"%{prj.name}/vendor/glm"
	}
	
	links {
		"GLFW",
		"opengl32",
		"GLEW"
	}

	defines {
		"GLEW_STATIC"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		
		defines {
			
		}
		
	filter "configurations:Debug" 
		defines "DEBUG"
		symbols "On"
	
	filter "configurations:Release" 
		defines "Release"
		optimize "On"
	
	filter "configurations:Dist" 
		defines "DIST"
		optimize "On"


include "GLW/vendor/GLFW/premake5.lua"
include "GLW/vendor/GLEW/premake5.lua"