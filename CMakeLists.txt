# Require CMAKE 3.12 or higher
cmake_minimum_required(VERSION 3.12)

# Project name
project(towerdefense)

# Build for C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Where any include files are
include_directories(Libraries/GLEW/include)
include_directories(Libraries/rapidjson/include)
include_directories(Libraries/SDL/include)
include_directories(Libraries/SOIL/include)

# Where any libraries are
if (WIN32)
	link_directories(Libraries/GLEW/lib/win/x86)
	link_directories(Libraries/SDL/lib/win/x86)
	link_directories(Libraries/SOIL/lib/win/x86)
elseif(APPLE)
	link_directories(Libraries/GLEW/lib/mac)
	link_directories(Libraries/SDL/lib/mac)
	link_directories(Libraries/SOIL/lib/mac)
endif()

# Set any compiler-specific settings
if (WIN32)
	set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /wd26812 /w34456 /w34457 /w34458 /w34459 /w35038 /we4715")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099 /ignore:4075")
elseif(APPLE)
	set(CMAKE_CXX_FLAGS "-Wall -Werror=return-type")
	find_library(COREFOUNDATION_LIBRARY CoreFoundation)
	find_library(OPENGL_LIBRARY OpenGL)
	set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Debug] "YES")
	set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=MinSizeRel] "NO")
	set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=RelWithDebInfo] "YES")
	set(CMAKE_XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Release] "NO")
endif()

# Subdirectories to build
add_subdirectory(src)
