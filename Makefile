SRC=src
MAINSRC=$(SRC)/main.cpp
BIN=bin/Simple
SDL2CFLAGS=-I/i686-w64-mingw32/include/SDL2
SDL2LIBS=-L/i686-w64-mingw32/lib -L/i686-w64-mingw32 -lmingw32 -lSDL2main -lSDL2

all: $(BIN)
$(BIN): $(MAINSRC)
	g++ $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)

run: $(BIN)
	$(BIN)
