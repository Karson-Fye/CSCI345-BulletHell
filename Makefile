SRC=src
HEADERS=$(SRC)/Exception.hpp $(SRC)/MediaManager.hpp $(SRC)/Game.hpp $(SRC)/Particle.hpp
MAINSRC=$(SRC)/main.cpp 
BIN=bin/Simple
SDL2CFLAGS=-I/usr/local/include/SDL2 -D_THREAD_SAFE
SDL2LIBS=-L/usr/local/lib -lSDL2

all: $(BIN)

$(BIN): $(MAINSRC) $(HEADERS) 
		g++ -g $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS) -DRELEASE
		
debug: $(BIN)
	gdb $(BIN)
		
run:  $(BIN)
	$(BIN)
