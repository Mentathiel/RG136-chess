#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <GL/glut.h>

using namespace std;

class Field;
class Move;
class Chessboard;
class ChessPiece;
class King;
class Queen;
class Rook;
class Knight;
class Bishop;
class Pawn;
class ObjHandler;

enum PlayerColor{
	White,
	Black
};

class ObjHandler{
	public:
		~ObjHandler();
		void loadModel(const char* fileName);

		void draw();
		
		typedef struct Vector3f{
			float x;
			float y;
			float z;
		} Vector3f;

		typedef struct Vector2f{
			float x;
			float y;
		} Vector2f;

	private:
	    vector<Vector3f*> vertices;
	    //vector<Vector2f> textureOrd;
        vector<int*> indices;
	    vector<Vector3f*> normalsOrd;

		static vector<int*> tokenizeF(string s);
};

class Game{
	public:
		Game();
		Game(Chessboard* cb);
		
		Chessboard* cb;
		int movesSinceCapturePawnMove = 0;

		void playMove(Move* move);
		void playMove(Field* dest, ChessPiece* moving);

		Move undoMove(void);

		bool checkForDraw();
		bool checkForMate();


		void selectField();

		void display(int file, int rank);

	private:
		bool selected = false;
		int selFile = 0;
		int selRank = 0;
		list<Move*> moveHistory;
		//TODO: unordered_map<Chessboard*, int> positionCount;
};

class Field {
	public:
		Field(){}
		Field(int file, int rank) : file(file), rank(rank){}

		int file;
		int rank;

		string toString(void);

		static string fileName(int n);

		bool operator==(const Field& a);
		bool operator!=(const Field& a);
};

class Move{
	public:
		Move(Field* dest, ChessPiece* moving, Chessboard cb);

		Field* from;
		Field* dest;
		ChessPiece* moving;
		ChessPiece* eaten = nullptr;

		string toString(void);
};

class ChessPiece {
	public:
		//Constructors
		ChessPiece();
		ChessPiece(PlayerColor color, int file, int rank);
		ChessPiece(PlayerColor color, Field* field);

		//Fields
		Field* field;
		bool onBoard = true;
		bool inStartingPos = true;

		//Chess Related
		virtual list<Field*> getPlayableMoves(Chessboard cb);
		virtual bool checkIfLegal(Field field, Chessboard cb);
		bool checkIfLegal(Move* move, Chessboard cb);
		bool friendlyPieceOnField(Field field, Chessboard cb);
		bool fieldAttackedOrOccupied(Field field, Chessboard cb);
		
		//Display
		virtual void display(int file, int rank);

		//Getters
		PlayerColor getColor(void) const;
		string getName(void) const;
		
		//Utility
		void print(void) const;
		virtual string toString(void) const;
		
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
		ChessPiece* pawnMovedLast = nullptr;
		PlayerColor toMove;
		void print(void) const;
		void updateAttacked(void);

		//Display
		virtual void display(int file, int rank, bool selected, int selFile, int selRank);

	private:
		void initializeBoard(void);
		bool operator==(const Chessboard& a);
		bool operator!=(const Chessboard& a);
};


class King : public ChessPiece {
	public:
		//Constructors
		King(PlayerColor color, int file, int rank);
		King(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);
		
		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};

class Queen : public ChessPiece {
	public:
		//Constructors
		Queen(PlayerColor color, int file, int rank);
		Queen(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);
		
		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};

class Rook : public ChessPiece {
	public:
		//Constructors
		Rook(PlayerColor color, int file, int rank);
		Rook(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);
		
		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};

class Knight : public ChessPiece {
	public:
		//Constructors
		Knight(PlayerColor color, int file, int rank);
		Knight(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);
		
		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};

class Bishop : public ChessPiece {
	public:
		//Constructors
		Bishop(PlayerColor color, int file, int rank);
		Bishop(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};

class Pawn : public ChessPiece {
	public:
		//Constructors
		Pawn(PlayerColor color, int file, int rank);
		Pawn(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);

		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};