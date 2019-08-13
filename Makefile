PROGRAM   = Chess
CC        = g++
CXXFLAGS  = -I -Wall -Wextra -g -std=c++0x
LDFLAGS   = -lGL -lGLU -lglut
DEPS      = chess.hpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o ChessPiece.o King.o Chessboard.o
	$(CC) -o $(PROGRAM) main.o ChessPiece.o $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
