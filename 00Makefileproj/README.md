### 1.5 多级目录下Makefile
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