cmake_minimum_required(VERSION "3.7.1")
project(geoCpt)

set(CMAKE_C_STANDARD 99)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# 添加 math 子目录
add_subdirectory(src)

# 添加链接库
target_link_libraries(${PROJECT_NAME} geoMath)