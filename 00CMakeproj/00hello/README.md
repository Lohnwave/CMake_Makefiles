### 2.1. 单源文件项目helloworld
```Shell
$ tree
.
├── CMakeLists.txt
└── hello.cpp

0 directories, 2 files
```
1. ``CMakeLists.txt``是CMake的必备
```CMake
# Version 1
cmake_minimum_required(VERSION "3.7.1") # CMake版本号要求

project("helloworld") # 项目

add_executable(${PROJECT_NAME} hello.cpp) # 指定生成目标
```
2. 终端输入
```Shell
$ cmake .
$ make
```
3. 项目生成：
```Shell
$ tree
.
├── CMakeCache.txt
├── CMakeFiles
│   ├── 3.10.2
│   │   ├── CMakeCCompiler.cmake
│   │   ├── CMakeCXXCompiler.cmake
│   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   ├── CMakeSystem.cmake
│   │   ├── CompilerIdC
│   │   │   ├── a.out
│   │   │   ├── CMakeCCompilerId.c
│   │   │   └── tmp
│   │   └── CompilerIdCXX
│   │       ├── a.out
│   │       ├── CMakeCXXCompilerId.cpp
│   │       └── tmp
│   ├── cmake.check_cache
│   ├── CMakeDirectoryInformation.cmake
│   ├── CMakeOutput.log
│   ├── CMakeTmp
│   ├── feature_tests.bin
│   ├── feature_tests.c
│   ├── feature_tests.cxx
│   ├── helloworld.dir
│   │   ├── build.make
│   │   ├── cmake_clean.cmake
│   │   ├── CXX.includecache
│   │   ├── DependInfo.cmake
│   │   ├── depend.internal
│   │   ├── depend.make
│   │   ├── flags.make
│   │   ├── hello.cpp.o
│   │   ├── link.txt
│   │   └── progress.make
│   ├── Makefile2
│   ├── Makefile.cmake
│   ├── progress.marks
│   └── TargetDirectories.txt
├── cmake_install.cmake
├── CMakeLists.txt
├── hello.cpp
├── helloworld "可执行文件"
└── Makefile

8 directories, 35 files
```
### 2.2. 多源文件下自动查找源文件
* 当源文件有多个时，可以通过在``add_executable``添加多个源文件：
```CMake
add_executable(${PROJECT_NAME} hello.cpp other.cpp ) # 添加多个源文件
```CMake
# aux_source_directory(<dir> <variable>)
aux_source_directory(. DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
```
* 另一种更为高效的方法是使用``aux_source_directory``命令，该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名。

可以很明显的看到，上面的``CMakeLists.txt``存在许多问题：
* 产生了很多的垃圾文件
* 需要手动指定编译文件
* 在有子目录的情况下无法适用