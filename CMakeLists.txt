cmake_minimum_required(VERSION 3.27)

# project
project(GenesisCubeEngineProject)

# C++ 20
set(CMAKE_CXX_STANDARD 20)

#define

if (${GenesisCubeBuildType} STREQUAL "Game")
    add_definitions(-DGenesisCubeGame)
elseif (${GenesisCubeBuildType} STREQUAL "Editor")
    add_definitions(-DGenesisCubeEditor)
endif ()

add_definitions(-DUNICODE -utf-8)

# GenesisCubeEngine
add_subdirectory("./GenesisCubeEngine")

# test
add_subdirectory("test")
