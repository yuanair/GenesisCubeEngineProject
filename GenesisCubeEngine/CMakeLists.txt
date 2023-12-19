# GenesisCubeEngine
project(GenesisCubeEngine)

# source
file(GLOB GenesisCubeEngine_source "./*/*.cpp")

# out
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

# library
add_library(GenesisCubeEngine ${GenesisCubeEngine_source})

# precompile header
target_precompile_headers(GenesisCubeEngine PRIVATE "./Core/GenesisCubeEngine.h")

