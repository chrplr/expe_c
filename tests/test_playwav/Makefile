SRC= playwav_withsdl2.c
BIN= playwav_withsdl2

CFLAGS= -W -Wall $(shell sdl2-config --cflags)
LDFLAGS=-export-dynamic $(shell sdl2-config --libs)


all:
	cc $(CFLAGS) $(SRC) $(LDFLAGS)  -o $(BIN)

clean:
	rm $(BIN)
