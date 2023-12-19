# test
project(test)

# source
aux_source_directory("./Source" test_source)

# out
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

# executable
add_executable(test WIN32 ${test_source} "./Resource/Test.rc"
        Resource/resource.h)

# include
target_include_directories(test PRIVATE "../")

# link
target_link_libraries(test PRIVATE GenesisCubeEngine)

