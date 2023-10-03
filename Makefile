
GCC=g++
VS=-std=c++11

SDL_DIR=dependencies/SDL2
SDL_gfx_DIR=dependencies/SDL2_gfx
BUILD_FLAGS=-O2 -c

SRC=src
BUILD=build/objectFiles

ifeq ($(OS),Windows_NT)
	RM=del
	SDL_DIR=dependencies/SDL2/WIN
	DEP=-lmingw32 -lSDL2main -lSDL2 -lSDL2_gfx
	PROGRAM_FILE=build/program.exe
else
	RM=rm
	SDL_DIR=dependencies/SDL2/MAC
	DEP=-lSDL2-2.0.0 -Qunused-arguments -lSDL2_gfx
	PROGRAM_FILE=build/program
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

clean:
	$(RM) $(BUILD)/*.o
	$(RM) $(PROGRAM_FILE)