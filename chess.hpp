#include <string>
#include <iostream>

using namespace std;

enum PlayerColor{
	White,
	Black
};

class ChessPiece {
	public:
		//Constructors
		ChessPiece(PlayerColor color, int file, int rank);

		PlayerColor getColor() const;
		string getName() const;
		void print() const;
		int file;
		int rank;

	private:
		const PlayerColor color;
		const string name;
		friend ostream& operator<<(ostream& out, const ChessPiece& p);
};

class King : ChessPiece {

};

class Queen : ChessPiece {

};

class Rook : ChessPiece {

};

class Knight : ChessPiece {

};

class Bishop : ChessPiece {

};

class Pawn : ChessPiece {

};