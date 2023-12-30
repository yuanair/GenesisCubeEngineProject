project(ConsoleTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#
add_executable(ConsoleTest "Main.cpp")

# include
target_include_directories(ConsoleTest PRIVATE "../..")

# link
target_link_libraries(ConsoleTest PRIVATE GenesisCubeEngine GenesisCubeLanguage)


# Resource
add_custom_command(TARGET ConsoleTest
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/bin/Data
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory
        ${PROJECT_SOURCE_DIR}/Resource
        ${PROJECT_BINARY_DIR}/bin/Data
)
