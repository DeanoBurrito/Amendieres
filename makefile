#environment setup
CC=g++
CFLAGS=-g -std=c++17 -DDEBUG_ALL
#linux
#REMOVE_DIR=rm -rf
#COPY_LIBS=cp libs/sfml-2.5.1/bin/* obj
#GUARD_OBJ_DIR=mkdir -p $@
#windows
REMOVE_DIR=powershell Remove-Item -Force -Recurse
COPY_DIR=powershell Copy-Item -Path libs/sfml-2.5.1/bin/* -Destination obj -Recurse 
GUARD_OBJ_DIR=powershell '$$dir = Split-Path $@; mkdir $$dir -Force | Out-Null'

#build setup
BUILD_DIR=obj
ASSETS_DIR=assets
INCLUDE_DIRS=-Ilibs/sfml-2.5.1/include -Ilibs/stb_image-2.27 -Ilibs/freetype-2.10.0/include
LIB_DIRS=-Llibs/sfml-2.5.1/lib -Llibs/freetype-2.10.0/objs
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lfreetype
TARGET=amendieres
SRCS=main.cpp AssetManager.cpp AssetBase.cpp

#include files from subdirectories
include Gfx/make.include
include Json/make.include
include Windowing/make.include

#auto-populated vars
BIN=$(BUILD_DIR)/$(TARGET).exe
OBJS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
include make.rules

.PHONY: build run debug clean

build: $(OBJS)
	@echo Linking executable ...
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_DIRS) $(LIBS) -o $(BIN)
	@echo Copying libraries ...
	@$(COPY_LIBS)
	@echo Done.

run: build
	@$(BIN) --assets=$(ASSETS_DIR)

debug: build
	@gdb $(BIN)

clean:
	@echo Cleaning up
	@$(REMOVE_DIR) $(BUILD_DIR)