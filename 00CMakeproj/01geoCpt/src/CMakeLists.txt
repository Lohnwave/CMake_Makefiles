# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
# 指定生成 geoUtils 链接库
add_library (geoMath ${DIR_LIB_SRCS})#命令 add_library 将 src 目录中的源文件编译为静态链接库。