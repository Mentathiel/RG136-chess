namespace logic{
	enum TypeOfPiece{
		King,
		Queen,
		Bishop,
		Rook,
		Knight,
		Pawn
	};

	enum ColorOfPiece{
		Black,
		White
	};

	enum filePos{
		A, B, C, D, E, F, G, H
	};

	typedef struct Piece
	{
		TypeOfPiece type;
		ColorOfPiece color;
		filePos file;
		int rank;
		bool onBoard;
	} Piece;

	typedef struct Field
	{
		Piece* piece;
		bool underAttackByWhite;
		bool underAttackByBlack;
		filePos file;
		int rank;
	} Field;

	void startGame();
	int getPlayerToMove();
	int movePiece(int fromFile, int fromRank, int toFile, int toRank);
};