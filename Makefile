
GCC=g++
VS=-std=c++11

PRINT = @echo

SDL_DIR=dep/SDL2
BUILD_FLAGS=-O2 -c -Wall -Wno-unused-command-line-argument -Wno-delete-non-abstract-non-virtual-dtor

SRC=src
UI=$(SRC)/GUI
GATES=$(SRC)/Gates
DEFAULT=$(GATES)/Default
UTILITIES=$(SRC)/Utilities

BUILD=build/objectFiles

ifeq ($(OS),Windows_NT)
	RM=del
	SDL_DIR=dep/SDL2/WIN
	SDL_gfx_DIR=dep/SDL2_gfx/WIN
	DEP=-lmingw32 -lSDL2main -lSDL2 -lSDL2_gfx
	PROGRAM_FILE=build/program.exe
else
	UNAME_S:=$(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		RM=rm
		SDL_DIR=dep/SDL2/LINUX
		SDL_gfx_DIR=dep/SDL2_gfx/LINUX
		DEP=-lSDL2 -lSDL2_gfx
		PROGRAM_FILE=build/program
    endif
    ifeq ($(UNAME_S),Darwin)
		RM=rm
		SDL_DIR=dep/SDL2/MAC
		SDL_gfx_DIR=dep/SDL2_gfx/MAC
		SDL_ttf_DIR=dep/SDL_ttf/MAC
		DEP=-lSDL2-2.0.0 -lSDL2_gfx  -lSDL2_ttf
		PROGRAM_FILE=build/program
    endif
endif

INC= -I$(SDL_DIR)/include -I$(SDL_gfx_DIR)/include -I$(SDL_ttf_DIR)/include  -I$(SRC) -I$(UTILITIES)
LIB= -L$(SDL_DIR)/lib -L$(SDL_gfx_DIR)/lib -L$(SDL_ttf_DIR)/lib

FILES=	$(BUILD)/Main.o \
		$(BUILD)/Application.o \
		$(BUILD)/Debug.o \
		$(BUILD)/Gate.o \
		$(BUILD)/GateHandler.o \
		$(BUILD)/Pin.o \
		$(BUILD)/Connection.o \
		$(BUILD)/FileManager.o \
		$(BUILD)/InputHandler.o \
		$(BUILD)/UI.o \
		$(BUILD)/UIButton.o \
		$(BUILD)/MouseState.o \
		$(BUILD)/AndGate.o \
		$(BUILD)/Button.o \
		$(BUILD)/Lamp.o \
		$(BUILD)/NotGate.o \
		$(BUILD)/OrGate.o \
		$(BUILD)/Clock.o
		

all: $(PROGRAM_FILE)

$(PROGRAM_FILE): $(FILES)
	$(GCC) $(INC) $(LIB) $(VS) $(AP_FLAGS) -o $(PROGRAM_FILE) $^  $(DEP)

$(BUILD)/Main.o: $(SRC)/Main.cpp $(SRC)/Application.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/%.o: $(UI)/%.cpp $(UI)/%.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/%.o: $(GATES)/%.cpp $(GATES)/%.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/%.o: $(DEFAULT)/%.cpp $(DEFAULT)/%.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/%.o: $(UTILITIES)/%.cpp $(UTILITIES)/%.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

database: $(BUILD)/Database.o
	g++ $(SRC)/Database/test.cpp -o build/Database $^ -lsqlite3
	./build/Database

$(BUILD)/%.o: $(SRC)/Database/%.cpp $(SRC)/Database/%.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

run: all
	./$(PROGRAM_FILE)

clean:
	$(RM) $(BUILD)/*.o
	$(RM) $(PROGRAM_FILE)