
GCC=g++
VS=-std=c++11

SDL_DIR=dependencies/SDL2
BUILD_FLAGS=-O2 -c

SRC=src
BUILD=build/objectFiles



ifeq ($(OS),Windows_NT)
	RM=del
	SDL_DIR=dependencies/SDL2/WIN
	SDL_gfx_DIR=dependencies/SDL2_gfx/WIN
	DEP=-lmingw32 -lSDL2main -lSDL2 -lSDL2_gfx
	PROGRAM_FILE=build/program.exe
else
	UNAME_S:=$(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		RM=rm
		SDL_DIR=dependencies/SDL2/LINUX
		SDL_gfx_DIR=dependencies/SDL2_gfx/LINUX
		DEP=-lSDL2 -lSDL2_gfx
		PROGRAM_FILE=build/program
    endif
    ifeq ($(UNAME_S),Darwin)
		RM=rm
		SDL_DIR=dependencies/SDL2/MAC
		SDL_gfx_DIR=dependencies/SDL2_gfx/MAC
		DEP=-lSDL2-2.0.0 -lSDL2_gfx
		PROGRAM_FILE=build/program
    endif
endif

INC= -I$(SDL_DIR)/include -I$(SDL_gfx_DIR)/include
LIB= -L$(SDL_DIR)/lib -L$(SDL_gfx_DIR)/lib




all: $(PROGRAM_FILE)

$(PROGRAM_FILE): $(BUILD)/Main.o $(BUILD)/Application.o $(BUILD)/Debug.o $(BUILD)/Gate.o $(BUILD)/GateHandler.o $(BUILD)/Connection.o $(SRC)/MyMath.h
	$(GCC) $(INC) $(LIB) $(VS) $(AP_FLAGS) -o $(PROGRAM_FILE) $(BUILD)/Main.o $(BUILD)/Application.o $(BUILD)/Debug.o $(BUILD)/Gate.o $(BUILD)/GateHandler.o $(BUILD)/Connection.o $(DEP)

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

$(BUILD)/Connection.o: $(SRC)/Connection.cpp $(SRC)/Connection.h
	$(GCC) $(INC) $(LIB) $(VS) -o $@ $(BUILD_FLAGS) $< $(DEP)

run:
	./$(PROGRAM_FILE)

setup:
	export LD_LIBRARY_PATH="$$LD_LIBRARY_PATH":/home/isak/dev/Logical/dependencies/SDL2_gfx/LINUX/lib/
	export LD_LIBRARY_PATH="$$LD_LIBRARY_PATH":/home/isak/dev/Logical/dependencies/SDL2/LINUX/lib/

clean:
	$(RM) $(BUILD)/*.o
	$(RM) $(PROGRAM_FILE)