SRC=src
HEADERS=$(SRC)/Exception.hpp $(SRC)/MediaManager.hpp $(SRC)/Game.hpp $(SRC)/Particle.hpp $(SRC)/Animation.hpp
MAINSRC=$(SRC)/main.cpp 
BIN=bin/Simple
SDL2CFLAGS=-I/usr/local/include/SDL2 -D_THREAD_SAFE
SDL2LIBS=-L/usr/local/lib -lSDL2  -lSDL2_mixer
WINSDL2CFLAGS=-I/i686-w64-mingw32/include/SDL2
WINSDL2LIBS=-L/i686-w64-mingw32/lib -L/i686-w64-mingw32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

all: $(BIN)

$(BIN): $(MAINSRC) $(HEADERS) 
	g++ -g $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS) -DRELEASE

win: $(BIN)
	g++ -g $(MAINSRC) $(WINSDL2CFLAGS) -o $(BIN) $(WINSDL2LIBS) -DRELEASE
		
debug: $(BIN)
	gdb $(BIN)
		
run: 	$(BIN)
	$(BIN)
