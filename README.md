# Makefile与CMake学习
* ``"#"``在Makefile中是注释
* gcc/g++的常见指令
```Makefile
gcc -c #选项：只编译不链接，仅生成目标文件
gcc -o #选项：指定输出文件 -o tag obj / obj -o tag
gcc -O #优化编译
gcc -E #选项：生成预处理文件
gcc -S #选项：生成汇编文件
gcc -l #选项：手动添加链接库
gcc -L #使用-L选项，为 GCC 增加另一个搜索链接库的目录 $ gcc main.c -o main.out -L/usr/lib -lm
gcc -I #指定 include 包含文件的搜索目录
gcc -g # 生成调试信息，该程序可以被调试器调试
gcc -Wall #开启错误警告
```
* 安装 ``tree ``查看项目文件结构
```Shell
$ sudo snap install tree
 user@XXX:~/Workspace/Codefiles/00Hello$ tree
.
├── helloworld
├── helloworld.cpp
├── helloworld.o
├── Makefile
└── oldMakefile
    ├── v1_Makefile
    ├── V2_Makefile
    └── V3_Makefile
1 directory, 7 files
```
## 一、Makefile
* 在终端输入 ``make`` 接：
1)  ``-n``（Makefile将要执行的内容）
2) ``-k``（发现错误依然执行，而不是在第一个错误处停止）
3) ``-f filename`` （指定其他文件作为Makefile文件执行）
* 特殊宏或关节字

1) ``$*``：不包括后缀名的当前依赖文件的名称
2) ``$+``：所有的依赖文件，以空格分开，并以出现的先后为序，可能包含重复的依赖文件
3) ``$<``：第一个依赖文件的名称
4) ``$``：所有时间戳比目标文件晚的依赖文件，并以空格分开
5) ``$@``：目标文件的完整名称
6) ``$^``：所有不重复的目标依赖文件，以空格分开
7) ``-: ``：告诉make命令忽略所有的错误
8) ``@``：告诉make在执行命令前不要将改命令显示在标准输出上
* 可以通过 ``KEY = value``来定义变量，并通过``$(KEY)``或``${KEY}``来引用变量
### 1.1. 书写规范
Makefile由创建目标/依赖和目标指令构成
1) 目标文件:依赖文件
```Makefile
helloworld : helloworld.o
```
2) [TAB]指令
```Makefile
    g++ -o helloworld  helloworld.o
```
3) 伪目标（不生成目标文件的指令）
```Makefile
.PHONY:
clean:
    rm -rf helloworld.o helloworld.s helloworld.i
````
第一个目标是程序的最终目标
最后只需在项目目录Makefile文件夹下终端
* 输入：``make``即刻执行Makefile
* 输入：``make clean``执行清除伪目标指令
```Makefile
# Version: 1.0 书写规范
# 目标文件：依赖文件
# [TAB]指令
# 例子
# 目标 ：       依赖
helloworld : helloworld.o #第一个目标是最终目标
    g++ helloworld -o  helloworld.o
helloworld.o : helloworld.s
    g++ -c helloworld.s -o helloworld.o
helloworld.s : helloworld.i
    g++ -S helloworld.i -o helloworld.s
helloworld.i : helloworld.cpp
    g++ -E helloworld.cpp -o helloworld.i
.PHONY:
clean:
    rm -rf helloworld.o helloworld.s helloworld.i
```
- 注意若使用``vim``文本编辑器
出现: ``Makefile:3:***遗漏分隔符。停止`` 
```Vim
$ sudo vi ~/.vimrc
" 在vimrc文件中设置tab
set tabstop = 4 
"不要使用空格替换tab 
set expandtab "将tab转换成空格
```
~~set expandtab~~
### 1.2. 变量
变量化使得Makefile编写更加规则化，类似于宏
* 通过``=/ += / :=``对变量进行赋值，依次是等于/追加/横等于
* 使用变量通过:`` $(变量名)``

针对version 1.0进行升级
```Makefile
# Version: 2.0 变量
# TAR = 目标文件
# TAR += 目标文件2
# OBJ = 依赖文件
# CC:=g++ #针对横定不便的指令开头
# $(变量) 来使用变量
TAR = helloworld
OBJ = helloworld.o
CXX := g++
$(TAR) : $(OBJ)
    $(CXX) $(OBJ) -o $(TAR)
$(OBJ) : helloworld.cpp
    $(CXX) -c helloworld.cpp -o $(OBJ)
.PHONY:
clean:
    rm $(OBJ)
cleanall:
    rm $(OBJ) $(TAR)
```
### 1.3. 隐含规则
* 通过通配符来格式化依赖及指令
```Makefile
# %.c/ %.o/ *.c/ *.o
```
因此针对Version 2进行升级
```Makefile
# Version: 3.0 通配符 使用隐含规则：通配符来改进Makefile
# 隐含规则：使用通配符%.c/ %.o/ *.c/ *.o
TAR = helloworld
OBJ = helloworld.o
CXX := g++
$(TAR) : $(OBJ)
    $(CXX) $(OBJ) -o $(TAR)
*.o : *.cpp
    $(CXX) -c *.cpp -o *.o
.PHONY:
clean:
    rm $(OBJ)
cleanall:
    rm $(OBJ) $(TAR)
```
### 1.4. 通配符``$^/$@/$<``
* ``$^``: 所有的依赖对象 
* ``$@``: 所有的目标文件 
* ``$<``: 所有依赖文件的第一个文件
```Makefile
# Version: 4.0 通配符 $^/$@/$<
# 1、%.cpp %.o 说有的cpp 所有的object
# 2、$^:所有的依赖对象 $@所有的目标文件 $<所有依赖文件的第一个文件
TAR = helloworld
OBJ = helloworld.o
CXX := g++
#CFLAGS = -g -Wall -O
$(TAR) : $(OBJ)
    $(CXX) $^ -o $@
*.o : *.cpp
    $(CXX) -c $^ -o $@
#   $(CXX) $(CFLAGS) -c $^
.PHONY:
clean:
    rm $(OBJ)
cleanall:
    rm $(OBJ) $(TAR)
```
### 1.5. 多级目录下Makefile
* 工程文件夹下不同目录引用问题
1) ``.cpp``依赖的``.h``在同文件夹: ``#include "*.h"``
2) .h在上级文件夹: ``#include "../*.h"``
3) ``.cpp`` 在``src``，``.h``在include: ``#include "../include/*.h"``
* 当头文件和源文件被分开``./src``
、``./include``
```Vim
~/Workspace/Codefiles/00standproject$ tree
├── include
│   ├── cube.h
│   ├── geometry.h
│   └── sphere.h
├── Makefile
├── obj
│   └── Makefile
└── src
    ├── cube.cpp
    ├── main.cpp
    └── sphere.cpp

3 directories, 8 files
```
```C++
// main.cpp中引用cube.h sphere.h
#include "../include/cube.h"
#include "../include/sphere.h"
```
* 一级Makefile
```Makefile
# 主目录下Makefile
GXX :=g++
OBJ = cube.o sphere.o main.o
TOPDIR := $(PWD) # 声明顶级目录
OBJDIR := $(TOPDIR)/obj # 声明中间文件目录
SRCDIR := $(TOPDIR)/src # 声明源文件目录
BINDIR := $(TOPDIR)/bin # 声明编译生成执行文件目录
SUBDIR := obj# 拥有Makefile的子目录
INCPATH := include # 声明头文件目录
OBJHEAD := $(INCPATH)/cube.h $(INCPATH)/geometry.h $(INCPATH)/sphere.h #声明头文件
OBJLINK := --std=c99
BIN := pro1-app # 声明生存执行文件名词
export GXX TOPDIR OBJDIR BINDIR BIN OBJLINK OBJ INCPATH SRCDIR # 声明全局变量以便次级Makefile使用
CFLAGS = -g -Wall -O
all:CHECKDIR $(SUBDIR)
CHECKDIR:
    mkdir -p $(SUBDIR) $(BINDIR) # 检查目录，-p 没有则自动生成
$(SUBDIR) : RUN
    make -C $@ # 跳转次级目录并执行其中Makefile
RUN:

clean:
    rm $(BINDIR)/$(BIN) $(OBJDIR)/*.o
# 谨慎使用 rm -rf
```
* 次级目录的Makefile
```Makefile
$(BINDIR)/$(BIN) : $(OBJ)
    $(GXX) $^ -o $@ $(OBJHEAD) $(OBJLINK) # 链接生成最终可执行文件并存放入bin文件夹
    @echo "==========build end=============="
# 编译src中的源文件，生存各中间依赖文件，并存放到obj目录
cube.o : $(SRCDIR)/cube.cpp
    $(GXX) $(CFLAGS) -c $(SRCDIR)/cube.cpp  -I $(INCPATH)
sphere.o : $(SRCDIR)/sphere.cpp
    $(GXX) $(CFLAGS) -c $(SRCDIR)/sphere.cpp  -I $(INCPATH)
main.o : $(SRCDIR)/main.cpp
    $(GXX) $(CFLAGS) -c $(SRCDIR)/main.cpp  -I $(INCPATH)
    @echo "==========build object=========="
```
最终项目树：
```Vim
~/Workspace/Codefiles/00standproject$ tree
.
├── bin
│   └── pro1-app
├── include
│   ├── cube.h
│   ├── geometry.h
│   └── sphere.h
├── Makefile
├── obj
│   ├── cube.o
│   ├── main.o
│   ├── Makefile
│   └── sphere.o
└── src
    ├── cube.cpp
    ├── main.cpp
    └── sphere.cpp

4 directories, 12 files

```
## 二、CMake
* 当项目程序简单的时候可以通过手写Makefile来编译项目。但当项目复杂时，手动编写Makefile将不再现实。CMake的存在就是解决这种情况的。CMake并不直接建构出最终的软件，而是产生标准的建构文档。
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
可以很明显的看到，上面的``CMakeLists.txt``存在问题：
* 需要手动指定编译文件

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

可以很明显的看到，上面的``CMakeLists.txt``存在问题：
* 在有子目录的情况下无法适用

### 2.3. 多个目录、多个源文件
当main源文件依赖存在多个且分布在子目录下时，
如下计算几何体体积程序：
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
可以通过在子目录下建立静态链接库，再来让main调用。
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
### 2.4. CMake外部构建
上面的介绍已经让我们初步学习到了如何使用CMake构建项目。然而，可以发现，上面的方法会在项目根目录产生众多的中间文件。这是一件令人头疼的事。CMake外部构建可以解决这个问题，并让项目更像一个工程。
* 外部构建：通过编写``build.sh``脚本，在项目根目录创建``build``，并在``build``文件夹执行``cmake``指令，来自动将中间文件以及程序生成的执行文件放入到``build``。

1. ``bulid.sh``脚本编写如下：
```Shell
#!/bin/bash
mkdir -p build
cd build
cmake ..
make
```

* ``#!/bin/bash``声明使用``bash``来执行脚本
*   ``mkdir -p build``在根目录创建``build``文件夹，如果存在则不创建。
* 后面的指令则是进入``build``文件夹去执行根目录的``CMakeList.txt``。
2. 执行``build.sh``
* 为``build.sh``添加执行权限。
```Shell
$ chmod +x build.sh
```
* 终端输入：``./build.sh``执行``build.sh``。

最后执行后项目``tree``如下，可以看出，根目录除了``include``、``src``外只增加了``build``文件夹，并且生成的中间文件以及执行文件都被放入到了``build``中。
```Shell
$ tree
.
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.10.2
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeSystem.cmake
│   │   │   ├── CompilerIdC
│   │   │   │   ├── a.out
│   │   │   │   ├── CMakeCCompilerId.c
│   │   │   │   └── tmp
│   │   │   └── CompilerIdCXX
│   │   │       ├── a.out
│   │   │       ├── CMakeCXXCompilerId.cpp
│   │   │       └── tmp
│   │   ├── cmake.check_cache
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── CMakeOutput.log
│   │   ├── CMakeTmp
│   │   ├── feature_tests.bin
│   │   ├── feature_tests.c
│   │   ├── feature_tests.cxx
│   │   ├── geoCpt.dir
│   │   │   ├── build.make
│   │   │   ├── cmake_clean.cmake
│   │   │   ├── CXX.includecache
│   │   │   ├── DependInfo.cmake
│   │   │   ├── depend.internal
│   │   │   ├── depend.make
│   │   │   ├── flags.make
│   │   │   ├── link.txt
│   │   │   ├── main.cpp.o
│   │   │   └── progress.make
│   │   ├── Makefile2
│   │   ├── Makefile.cmake
│   │   ├── progress.marks
│   │   └── TargetDirectories.txt
│   ├── cmake_install.cmake
│   ├── geoCpt
│   ├── Makefile
│   └── src
│       ├── CMakeFiles
│       │   ├── CMakeDirectoryInformation.cmake
│       │   ├── geoMath.dir
│       │   │   ├── build.make
│       │   │   ├── cmake_clean.cmake
│       │   │   ├── cmake_clean_target.cmake
│       │   │   ├── cube.cpp.o
│       │   │   ├── CXX.includecache
│       │   │   ├── DependInfo.cmake
│       │   │   ├── depend.internal
│       │   │   ├── depend.make
│       │   │   ├── flags.make
│       │   │   ├── link.txt
│       │   │   ├── progress.make
│       │   │   └── sphere.cpp.o
│       │   └── progress.marks
│       ├── cmake_install.cmake
│       ├── libgeoMath.a
│       └── Makefile
├── build.sh
├── CMakeLists.txt
├── include
│   ├── cube.h
│   ├── geometry.h
│   └── sphere.h
├── main.cpp
├── README.md
└── src
    ├── CMakeLists.txt
    ├── cube.cpp
    └── sphere.cpp

14 directories, 60 files
```