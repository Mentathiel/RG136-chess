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


/* Class for parsing Wavefront .obj files, which hasn't ended up
   in the finished project because of bugs, but is here in hopes
   I fix it one day. */
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


/* This is a class which will contain current state of the game,
   as well as all of the functions for player interaction with
   the game. */
class Game{
	public:
		Game();
		Game(Chessboard* cb);

		Chessboard* cb;
		int movesSinceCapturePawnMove = 0;
		bool gameFinished = false;

		void playMove(Move* move);
		void playMove(Field* dest, ChessPiece* moving);

		Move undoMove(void);

		bool checkForCheck();
		bool checkForCheck(PlayerColor color);
		bool checkForDraw();
		bool checkForMate();
		void checkState();

		void selectField();
		bool pickingMove();

		int selFile = 0;
		int selRank = 0;

		void display(int file, int rank);

	private:
		bool selected = false;
		list<Move*> moveHistory;
		//TODO: unordered_map<Chessboard*, int> positionCount;
};

/* A class containing informations about a field, namely
   its rank, file, and toString() function converting it into its
   proper chess notation. */
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

/* A class containing one move, including field from whicha and to
   which we're moving a piece, piece that we're moving, and a possible
   piece that we're eating. Eaten piece is necessary for undoing moves. */
class Move{
	public:
		Move(Field* dest, ChessPiece* moving, Chessboard cb);

		Field* from;
		Field* dest;
		ChessPiece* moving;
		ChessPiece* eaten = nullptr;

		string toString(void);
};

/* An parent class to all pieces, containing all of their shared info.
   Contains current state of a piece, its color and name, virtual functions
   for determening legal moves with that piece, setting materials for and
   displaying chess pieces on the board. */
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
		virtual ChessPiece* movedPiece(PlayerColor color, Field* dest);
		bool checkIfLegal(Move* move, Chessboard cb);
		bool friendlyPieceOnField(Field field, Chessboard cb);
		bool enemyPieceOnField(Field field, Chessboard cb);
		bool fieldAttackedOrOccupied(Field field, Chessboard cb);
		
		//Display
		virtual void display(int file, int rank);
		void setMats(void);

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


/* The class containing the chessboard with pieces on it, info on attacked
   fields, player whose turn it is, displaying the board itself, initializing
   the starting position. */
class Chessboard {
	public:
		Chessboard();
		ChessPiece* board[8][8]; //nullptr if no piece is on the field
		bool attackedByWhite[8][8];
		bool attackedByBlack[8][8];
		ChessPiece* pawnMovedLast = nullptr;
		PlayerColor toMove = PlayerColor::White;
		void print(void) const;
		void updateAttacked(void);

		//Display
		virtual void display(int file, int rank, bool selected, int selFile, int selRank);

	private:
		void initializeBoard(void);
		bool operator==(const Chessboard& a);
		bool operator!=(const Chessboard& a);
};


/* DECLARATION OF INDIVIDUAL PIECES */

class King : public ChessPiece {
	public:
		//Constructors
		King(PlayerColor color, int file, int rank);
		King(PlayerColor color, Field* field);

		//Chess Related
		list<Field*> getPlayableMoves(Chessboard cb);
		bool checkIfLegal(Field field, Chessboard cb);
		ChessPiece* movedPiece(PlayerColor color, Field* dest);
		
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
		ChessPiece* movedPiece(PlayerColor color, Field* dest);
		
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
		ChessPiece* movedPiece(PlayerColor color, Field* dest);
		
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
		ChessPiece* movedPiece(PlayerColor color, Field* dest);
		
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
		ChessPiece* movedPiece(PlayerColor color, Field* dest);

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
		ChessPiece* movedPiece(PlayerColor color, Field* dest);

		//Display
		void display(int file, int rank);

		//Utility
		string toString(void) const;
};