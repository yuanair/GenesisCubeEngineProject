# GenesisCube
project(GenesisCubeEngine)

# source
file(GLOB GenesisCubeEngineSource "./*/*.cpp")

# library
add_library(GenesisCubeEngine ${GenesisCubeEngineSource})

# link
target_link_libraries(GenesisCubeEngine PRIVATE GenesisCubeBase)

# precompile header
target_precompile_headers(GenesisCubeEngine PUBLIC "Core/Header.h")

