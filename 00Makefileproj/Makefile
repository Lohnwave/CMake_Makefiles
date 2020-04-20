GXX :=g++
OBJ = cube.o sphere.o main.o
TOPDIR := $(PWD)
OBJDIR := $(TOPDIR)/obj
SRCDIR := $(TOPDIR)/src
BINDIR := $(TOPDIR)/bin
SUBDIR := obj# 拥有Makefile的子目录
INCPATH := include

OBJHEAD := $(INCPATH)/cube.h $(INCPATH)/geometry.h $(INCPATH)/sphere.h
OBJLINK := --std=c99
BIN := pro1-app 

export GXX TOPDIR OBJDIR BINDIR BIN OBJLINK OBJ INCPATH SRCDIR
CFLAGS = -g -Wall -O

all:CHECKDIR $(SUBDIR)
CHECKDIR:
	mkdir -p $(SUBDIR) $(BINDIR)
$(SUBDIR) : RUN
	make -C $@
RUN:

clean:
	rm $(BINDIR)/$(BIN) $(OBJDIR)/*.o
