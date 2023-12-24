add_executable(ConsoleTest "Main.cpp")
target_link_libraries(ConsoleTest PRIVATE GenesisCubeEngine)


# include
target_include_directories(ConsoleTest PRIVATE "../")
