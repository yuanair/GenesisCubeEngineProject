# GenesisCubeEngine
project(GenesisCubeEngine)

# source
file(GLOB GenesisCubeEngine_source "./*/*.cpp")

# library
add_library(GenesisCubeEngine ${GenesisCubeEngine_source})

# precompile header
target_precompile_headers(GenesisCubeEngine PUBLIC "Core/Header.h")


#
# 参考
#
# 1. 抽象和解耦让扩展代码更快更容易，
# 但除非确信需要灵活性，否则不要在这上面浪费时间。
#
# 2. 在整个开发周期中为性能考虑并做好设计，
# 但是尽可能推迟那些底层的，基于假设的优化，那会难以编写代码。
#
# 3. 相信我，发布项目前两个月不是开始思考“游戏运行只有1FPS”这种问题的时候。
#
# 4. 快速地探索游戏的设计空间，但不要跑得太快，在身后留下烂摊子。毕竟你总得回来打扫。
#
# 5. 如果打算抛弃这段代码，就不要尝试将其写完美。
#
# 6. 如果你想要做出让人享受的东西，那就享受做它的过程。
#
# 7. 避免在处理事件的代码中发送事件。
#
# PS: 使用组件时，我最不喜欢的就是组件Component这个单词的长度。
#

