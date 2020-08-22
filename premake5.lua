workspace "cpp-game"
	language "C++"
	cppdialect "C++17"

	configurations {"Debug", "Release"}
	platforms { "Win64", "Linux64" }

	startproject = "cpp-game"

	filter {"platforms:Win64"}
		system "windows"
		architecture "x64"
	filter {"platforms:Linux64"}
		system "linux"
		architecture "x64"

	filter {"configurations:Debug"}
		symbols "On"
	filter {"configurations:Release"}
		optimize "On"
	filter {}

	targetdir ("build/%{cfg.buildcfg}/%{prj.name}/bin")
	objdir ("build/%{cfg.buildcfg}/%{prj.name}/obj")

	
	filter {"platforms:Win64"}
		defines { "GLEW_STATIC", "PLATFORM_WIN64" }
		-- links {"glfw3", "glew32s", "opengl32", "Gdi32", "legacy_stdio_definitions"}
	filter {"platforms:Linux64"}
		defines { "PLATFORM_LINUX64" }
		-- links {"glfw", "GLEW", "GL"}
	filter {}

	project "cpp-game"
		location ("../%{wks.name}/%{prj.name}")
		kind "ConsoleApp"

		files "%{prj.name}/src/**"
		files "%{prj.name}/include/**"
		includedirs
		{
			"%{prj.name}/src/",
			"%{prj.name}/include/"
		}

		filter {"platforms:Win64"}
			defines { "GLEW_STATIC", "PLATFORM_WIN64" }
			links {"glfw3", "glew32s", "opengl32", "Gdi32", "legacy_stdio_definitions"}
		filter {"platforms:Linux64"}
			defines { "PLATFORM_LINUX64" }
			links {"glfw", "GLEW", "GL"}
		filter {}
	 	libdirs {"%{prj.name}/lib/%{cfg.platform}"}