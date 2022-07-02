workspace "Flamex"
	architecture "x64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Flamex"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir("./bin/" .. outputdir)

	files {
		"include/**.c",
		"include/**.cpp",
		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp"
	}

	includedirs {
		"include/"
	}

	libdirs {
		"lib/"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"

	filter { "system:windows" }
		links { "OpenGL32" }
		links { "glfw3" }

	filter { "system:not windows" }
		links { "GL" }
		links { "glfw" }

	-- Because why not
	buildcommands {
		"make %{cfg.buildcfg}"
	}

	-- Correct "make clean" option
	cleancommands {
		"rm -rf ./bin/ ./obj/"
	}
