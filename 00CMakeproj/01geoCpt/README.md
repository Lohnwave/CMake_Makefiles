### 2.3. 多个目录、多个源文件
当存在多个目录和多个源文件时，如下计算几何体体积程序：
```Shell
$ tree
.
├── CMakeLists.txt
├── include
│   ├── cube.h
│   ├── geometry.h
│   └── sphere.h
├── main.cpp
└── src
    ├── CMakeLists.txt
    ├── cube.cpp
    └── sphere.cpp

2 directories, 8 files
```
1) 创建静态链接库

    先将 src目录里的文件编译成静态库再由 根目录main调用。
* 子目录src下的``CMakeLists.txt``:
```CMake
# 查找src目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)
# 指定生成 geoUtils 链接库
add_library (geoMath ${DIR_LIB_SRCS})#命令 add_library 将 src 目录中的源文件编译为静态链接库。
```
2) 根目录main调用链接库生成程序
* 根目录下的``CMakeLists.txt``:
```CMake
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
```
终端执行``cmke .``后再执行``make``
```vim
$ make
Scanning dependencies of target geoMath
[ 20%] Building CXX object src/CMakeFiles/geoMath.dir/cube.cpp.o
[ 40%] Building CXX object src/CMakeFiles/geoMath.dir/sphere.cpp.o
[ 60%] Linking CXX static library libgeoMath.a
[ 60%] Built target geoMath
Scanning dependencies of target geoCpt
[ 80%] Building CXX object CMakeFiles/geoCpt.dir/main.cpp.o
[100%] Linking CXX executable geoCpt
[100%] Built target geoCpt
```