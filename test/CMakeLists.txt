# test
project(test)

# out
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

# executable
add_executable(test WIN32 "./Source/Main.cpp" "../GenesisCubeEngine/Resource/resource.rc"
        ../GenesisCubeEngine/Resource/resource.h)


# include
target_include_directories(test PRIVATE "../")

# link
target_link_libraries(test PRIVATE GenesisCubeEngine)

