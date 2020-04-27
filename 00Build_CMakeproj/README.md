### 2.4. CMake外部构建
上面的介绍已经让我们初步学习到了如何使用CMake构建项目。然而，可以发现，上面的方法会在项目根目录产生众多的中间文件。外部构建的方法可以解决这个问题，并让项目更像一个工程。
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

最后执行后项目tree如下，可以看出，根目录除了``include``、``src``外只增加了``build``文件夹，并且生成的中间文件以及执行文件都被放入到了``build``中。
```Shell
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