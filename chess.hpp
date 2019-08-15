#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <algorithm>

using namespace std;

class Chessboard;

enum PlayerColor{
	White,
	Black
};

typedef struct Field {
	Field(){}
	Field(int file, int rank) : file(file), rank(rank){}

	int file;
	int rank;

	bool operator==(const Field& a){
		Field b = *this;
	    if(a.file == b.file && a.rank == b.rank)
	    	return true;
	    else
	    	return false;
	}

	bool operator!=(const Field& a){
		Field b = *this;
		if(a.file == b.file && a.rank == b.rank)
			return false;
		else
			return true;
	}

} Field;

class ChessPiece {
	public:
		//Constructors
		ChessPiece();
		ChessPiece(PlayerColor color, int file, int rank);
		ChessPiece(PlayerColor color, Field* field);

		//Fields
		Field* field;
		bool onBoard = true;

		//Chess Related
		virtual list<Field*> getPlayableMoves(Chessboard cb);
		virtual bool checkIfLegal(Field field);
		bool friendlyPieceOnField(Field field, Chessboard cb);
		bool fieldAttackedOrOccupied(Field field, Chessboard cb);

		//Getters
		PlayerColor getColor() const;
		string getName() const;
		
		//Utility
		void print() const;
		virtual string toString() const;
		


	protected:
		//Fields
		const PlayerColor color;
		const string name;

	private:
		//Utility
		friend ostream& operator<<(ostream& out, const ChessPiece& p);
};


class Chessboard {
	public:
		Chessboard();
		ChessPiece* board[8][8];
		bool attackedByWhite[8][8];
		bool attackedByBlack[8][8];
		void print() const;

	private:
		void updateAttacked();
		void initializeBoard();
};


class King : public ChessPiece {
	public:
		//Constructors
		King(PlayerColor color, int file, int rank);
		King(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Utility
		string toString() const;
};

class Queen : public ChessPiece {
	public:
		//Constructors
		Queen(PlayerColor color, int file, int rank);
		Queen(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Utility
		string toString() const;
};

class Rook : public ChessPiece {
	public:
		//Constructors
		Rook(PlayerColor color, int file, int rank);
		Rook(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Utility
		string toString() const;
};

class Knight : public ChessPiece {
	public:
		//Constructors
		Knight(PlayerColor color, int file, int rank);
		Knight(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Utility
		string toString() const;
};

class Bishop : public ChessPiece {
	public:
		//Constructors
		Bishop(PlayerColor color, int file, int rank);
		Bishop(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Utility
		string toString() const;
};

class Pawn : public ChessPiece {
	public:
		//Constructors
		Pawn(PlayerColor color, int file, int rank);
		Pawn(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Utility
		string toString() const;
};