project(test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# executable
add_executable(test WIN32 "Source/Main.cpp" "../../GenesisCubeEngine/Resource/resource.rc"
        ../../GenesisCubeEngine/Resource/resource.h)

# include
target_include_directories(test PRIVATE "../..")

# link
target_link_libraries(test PRIVATE GenesisCubeEngine)


# Resource
add_custom_command(TARGET test
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/bin/Data
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory
        ${PROJECT_SOURCE_DIR}/Resource
        ${PROJECT_BINARY_DIR}/bin/Data
)

