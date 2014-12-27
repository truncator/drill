solution "drill"

	configurations
	{
		"Debug"
	}

	project "drill"
		kind "ConsoleApp"
		language "C++"

		buildoptions
		{
			"-std=c++11"
		}

		includedirs
		{
			"../library/stb_image/"
		}

		files
		{
			"../source/**.hpp",
			"../source/**.cpp",
			"../library/stb_image/stb_image.cpp"
		}

		links
		{
			"GLEW",
			"glfw3",
			"GL",
			"GLU",
			"X11",
			"Xxf86vm",
			"Xrandr",
			"Xcursor",
			"Xinerama",
			"Xi",
			"pthread"
		}

		pchheader "../source/precompiled.hpp"
		pchsource "../source/precompiled.cpp"

		configuration "Debug"
			targetdir "../binary/debug/"
			location "../build/"
			flags { "Symbols", "ExtraWarnings" }
