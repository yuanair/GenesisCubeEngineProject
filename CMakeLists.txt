cmake_minimum_required(VERSION 3.27)

# project
project(GenesisCubeEngineProject)

# C++ 17
set(CMAKE_CXX_STANDARD 17)

#define
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DDEBUG)
else ()
    add_definitions(-DRELEASE)
endif ()

if (${GenesisCubeBuildType} STREQUAL "GameDebug")
    add_definitions(-DGenesisCubeGameDebug)
elseif (${GenesisCubeBuildType} STREQUAL "GameRelease")
    add_definitions(-DGenesisCubeGameRelease)
elseif (${GenesisCubeBuildType} STREQUAL "EditorDebug")
    add_definitions(-DGenesisCubeEditorDebug)
elseif (${GenesisCubeBuildType} STREQUAL "EditorRelease")
    add_definitions(-DGenesisCubeEditorRelease)
endif ()

add_definitions(-DUNICODE -utf-8)

# GenesisCubeEngine
add_subdirectory("./GenesisCubeEngine")

# test
add_subdirectory("test")
