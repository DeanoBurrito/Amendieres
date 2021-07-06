#environment setup
CC=g++
CFLAGS=-g -std=c++17

#build setup
BUILD_DIR=obj
ASSETS_DIR=assets
INCLUDE_DIRS=-Ilibs/sfml-2.5.1/include
LIB_DIRS=-Llibs/sfml-2.5.1/lib
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
TARGET=amendieres
SRCS=main.cpp JsonParser.cpp JsonNode.cpp AssetManager.cpp AssetBase.cpp JsonAsset.cpp

#auto-populated vars
BIN=$(BUILD_DIR)/$(TARGET).exe
OBJS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
include make.rules

.PHONY: build run debug clean

build: $(BUILD_DIR) $(OBJS)
	@echo Linking executable ...
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_DIRS) $(LIBS) -o $(BIN)
	@echo Copying libraries ...
	@powershell Copy-Item -Path libs/sfml-2.5.1/bin/* -Destination obj -Recurse
	@echo Done.

run: build
	@$(BIN) --assets=$(ASSETS_DIR)

debug: build
	@gdb $(BIN)

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

clean:
	@echo Cleaning up
	@powershell Remove-Item $(BUILD_DIR) -Force -Recurse