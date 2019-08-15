PROGRAM   = Chess
CC        = g++
CXXFLAGS  = -I -Wall -Wextra -g -std=c++0x
LDFLAGS   = -lGL -lGLU -lglut
DEPS      = chess.hpp
PIECES    = ChessPiece.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o Chessboard.o $(PIECES)
	$(CC) -o $(PROGRAM) main.o Chessboard.o $(PIECES) $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
