namespace logic{
	enum TypeOfPiece{
		King,
		Queen,
		Bishop,
		Rock,
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

	void startGame();
};