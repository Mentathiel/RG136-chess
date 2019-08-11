#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <algorithm>

using namespace std;

enum PlayerColor{
	White,
	Black
};

typedef struct Field {
	int file;
	int rank;

	bool operator==(const Field& a){
		Field b = *this;
	    if(a.file == b.file && a.rank == b.rank)
	    	return true;
	    else
	    	return false;
	}

} Field;

class ChessPiece {
	public:
		//Constructors
		ChessPiece(PlayerColor color, int file, int rank);
		ChessPiece(PlayerColor color, Field field);

		//Fields
		Field field;
		bool onBoard = true;

		//Chess Related
		virtual Field* getPlayableMoves() = 0;
		virtual bool checkIfLegal(Field field) = 0;

		//Getters
		PlayerColor getColor() const;
		string getName() const;
		
		//Utility
		void print() const;
		virtual string toString() const = 0;
		


	private:
		//Fields
		const PlayerColor color;
		const string name;

		//Utility
		friend ostream& operator<<(ostream& out, const ChessPiece& p);
};

class King : ChessPiece {
	public:
		//Constructors
		King(PlayerColor color, int file, int rank);
		King(PlayerColor color, Field field);

		//Chess Related
		list<Field> getPlayableMoves();
		bool checkIfLegal(Field field);

		//Utility
		string toString() const;
};

class Queen : ChessPiece {
	public:
		//Constructors
		Queen(PlayerColor color, int file, int rank);
		Queen(PlayerColor color, Field field);

		//Chess Related
		list<Field> getPlayableMoves();
		bool checkIfLegal(Field field);

		//Utility
		string toString() const;
};

class Rook : ChessPiece {
	public:
		//Constructors
		Rook(PlayerColor color, int file, int rank);
		Rook(PlayerColor color, Field field);

		//Chess Related
		list<Field> getPlayableMoves();
		bool checkIfLegal(Field field);

		//Utility
		string toString() const;
};

class Knight : ChessPiece {
	public:
		//Constructors
		Knight(PlayerColor color, int file, int rank);
		Knight(PlayerColor color, Field field);

		//Chess Related
		list<Field> getPlayableMoves();
		bool checkIfLegal(Field field);

		//Utility
		string toString() const;
};

class Bishop : ChessPiece {
	public:
		//Constructors
		Bishop(PlayerColor color, int file, int rank);
		Bishop(PlayerColor color, Field field);

		//Chess Related
		list<Field> getPlayableMoves();
		bool checkIfLegal(Field field);

		//Utility
		string toString() const;
};

class Pawn : ChessPiece {
	public:
		//Constructors
		Pawn(PlayerColor color, int file, int rank);
		Pawn(PlayerColor color, Field field);

		//Chess Related
		list<Field> getPlayableMoves();
		bool checkIfLegal(Field field);

		//Utility
		string toString() const;
};