cmake_minimum_required(VERSION 3.8)

# project
project(GenesisCubeEngineProject)

# C++ 20
set(CMAKE_CXX_STANDARD 20)

if (${GenesisCubeBuildType} STREQUAL "Game")
    add_definitions(-DGenesisCubeGame)
elseif (${GenesisCubeBuildType} STREQUAL "Editor")
    add_definitions(-DGenesisCubeEditor)
endif ()

add_definitions("-utf-8" "-DUNICODE" "-D_UNICODE")

# GenesisCubeBase
add_subdirectory("./GenesisCubeBase")

# GenesisCube
add_subdirectory("./GenesisCubeEngine")

# GenesisCubeLanguage
add_subdirectory("./GenesisCubeLanguage")

# Simple
add_subdirectory("Simple")


