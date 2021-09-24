SRC=src
MAINSRC=$(SRC)/main.cpp
BIN=bin/Simple
WINSDL2CFLAGS=-I/i686-w64-mingw32/include/SDL2
WINSDL2LIBS=-L/i686-w64-mingw32/lib -L/i686-w64-mingw32 -lmingw32 -lSDL2main -lSDL2

win: $(BIN)
$(BIN): $(MAINSRC)
	g++ $(MAINSRC) $(WINSDL2CFLAGS) -o $(BIN) $(WINSDL2LIBS)

winrun: $(BIN)
	$(BIN)
