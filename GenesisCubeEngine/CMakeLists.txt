# GenesisCubeEngine
project(GenesisCubeEngine)

# source
file(GLOB GenesisCubeEngine_source "./*/*.cpp")

# out
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

# library
add_library(GenesisCubeEngine ${GenesisCubeEngine_source})

# link
target_link_libraries(GenesisCubeEngine "dbghelp.lib")

# precompile header
target_precompile_headers(GenesisCubeEngine PUBLIC "Core/Header.h")

