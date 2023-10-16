
GCC=g++
VS=-std=c++11

SDL_DIR=dep/SDL2
BUILD_FLAGS=-O2 -c

SRC=src
UI=$(SRC)/GUI
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
		DEP=-lSDL2-2.0.0 -lSDL2_gfx
		PROGRAM_FILE=build/program
    endif
endif

INC= -I$(SDL_DIR)/include -I$(SDL_gfx_DIR)/include
LIB= -L$(SDL_DIR)/lib -L$(SDL_gfx_DIR)/lib

all: $(PROGRAM_FILE)

$(PROGRAM_FILE): $(BUILD)/Main.o $(BUILD)/Application.o $(BUILD)/Debug.o $(BUILD)/Gate.o $(BUILD)/GateHandler.o $(BUILD)/Pin.o $(SRC)/MyMath.h $(BUILD)/Connection.o $(BUILD)/UI.o $(BUILD)/UIButton.o $(BUILD)/MouseState.o
	$(GCC) $(INC) $(LIB) $(VS) $(AP_FLAGS) -o $(PROGRAM_FILE) $(BUILD)/Main.o $(BUILD)/Application.o $(BUILD)/Debug.o $(BUILD)/Gate.o $(BUILD)/GateHandler.o $(BUILD)/Pin.o $(BUILD)/Connection.o $(BUILD)/UI.o $(BUILD)/UIButton.o $(BUILD)/MouseState.o $(DEP)

$(BUILD)/Main.o: $(SRC)/Main.cpp $(SRC)/Application.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/Application.o: $(SRC)/Application.cpp $(SRC)/Application.h $(SRC)/Debug.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/Debug.o: $(SRC)/Debug.cpp $(SRC)/Debug.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/GateHandler.o: $(SRC)/GateHandler.cpp $(SRC)/GateHandler.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/Gate.o: $(SRC)/Gate.cpp $(SRC)/Gate.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/Pin.o: $(SRC)/Pin.cpp $(SRC)/Pin.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/Connection.o: $(SRC)/Connection.cpp $(SRC)/Connection.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/MouseState.o: $(SRC)/MouseState.cpp $(SRC)/MouseState.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/UI.o: $(UI)/UI.cpp $(UI)/UI.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

$(BUILD)/UIButton.o: $(UI)/UIButton.cpp $(UI)/UIButton.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

run:
	./$(PROGRAM_FILE)

clean:
	$(RM) $(BUILD)/*.o
	$(RM) $(PROGRAM_FILE)