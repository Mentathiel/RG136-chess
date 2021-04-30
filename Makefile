PROGRAM   = Chess
CC        = g++
CXXFLAGS  = -I -Wall -Wextra -g -std=c++0x
LDFLAGS   = -lGL -lGLU -lglut
DEPS      = chess.hpp
PIECES    = ChessPiece.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o
SOURCES   = $(wildcard *.cc)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

main: main.o Chessboard.o Move.o Field.o Game.o ObjHandler.o $(PIECES)
	$(CC) -o $(PROGRAM) main.o Chessboard.o Move.o Field.o Game.o ObjHandler.o $(PIECES) $(LDFLAGS)

gcov: CXXFLAGS += --coverage
gcov:
	$(CC) -lgcov $(CXXFLAGS) $(SOURCES) -o $(PROGRAM)_gcov $(LDFLAGS)

.PHONY: clean_gcov clean dist

clean_gcov:
	-rm *.gcov *.gcda *.gcno

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
