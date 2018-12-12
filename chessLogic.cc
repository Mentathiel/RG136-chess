#include "chessLogic.hpp"
#include <stdio.h>
#include <list>

#define _NO_OF_PIECES 16
#define _FIRST_PAWN 8
#define _FILES 8
#define _RANKS 8

#define DEBUG

#ifdef DEBUG
void printPieceStates(void);
#endif

void initializeBoard();
void initializePlayersPieces();
void initialiePieceTypes();

/************************************
*          INTERNAL LOGIC           *
*************************************/

enum pieceInArray{
	Rook1, Knight1, BishopB, Queen, King,  BishopW, Knight2, Rook2,
	PawnA, PawnB,   PawnC,   PawnD, PawnE, PawnF,   PawnG,   PawnH	
};


//arrays that hold pieces for each player
logic::Piece white[_NO_OF_PIECES];
logic::Piece black[_NO_OF_PIECES];

//board matrix
logic::Field board[_RANKS][_FILES];

//saves whose move is it (as ColorOfPiece enum)
int playerToMove;


void initialiePieceTypes(){
	white[King].type = logic::King;
	white[Queen].type = logic::Queen;
	white[Rook1].type = logic::Rook;
	white[Rook2].type = logic::Rook;
	white[BishopB].type = logic::Bishop;
	white[BishopW].type = logic::Bishop;
	white[Knight1].type = logic::Knight;
	white[Knight2].type = logic::Knight;
	for(int i=_FIRST_PAWN; i<_NO_OF_PIECES; i++)
		white[i].type = logic::Pawn;

	black[King].type = logic::King;
	black[Queen].type = logic::Queen;
	black[Rook1].type = logic::Rook;
	black[Rook2].type = logic::Rook;
	black[BishopB].type = logic::Bishop;
	black[BishopW].type = logic::Bishop;
	black[Knight1].type = logic::Knight;
	black[Knight2].type = logic::Knight;
	for(int i=_FIRST_PAWN; i<_NO_OF_PIECES; i++)
		black[i].type = logic::Pawn;	
}

void initializePlayersPieces(){
	initialiePieceTypes();

	for(int i=0; i<_NO_OF_PIECES; i++){
		white[i].onBoard = true;
		black[i].onBoard = true;

		//Initializing piece colors
		white[i].color = logic::White;
		black[i].color = logic::Black;

		//Initializing starting files and ranks
		//sowwy for magic numbers
		if(i<_FIRST_PAWN){
			white[i].rank = 1;
			black[i].rank = 8;
			white[i].file = static_cast<logic::filePos>(i);
			black[i].file = static_cast<logic::filePos>(i);
		}
		else{
			white[i].rank = 2;
			black[i].rank = 7;
			white[i].file = static_cast<logic::filePos>(i-8);
			black[i].file = static_cast<logic::filePos>(i-8);
		}
	}
}

void initializeBoard(){
	initializePlayersPieces();
	//set whole board to null pieces
	for(int i; i < _RANKS; i++){
		for(int j; j < _FILES; j++){
			board[i][j].piece = nullptr;
		}
	}
	//copy piece references onto board
	//IMPORTANT: pieces in array and on board are the same!!
	for(int i = 0; i < _NO_OF_PIECES; i++){
		board[white[i].rank][white[i].file].piece = &white[i];
		board[black[i].rank][black[i].file].piece = &black[i];
	}
}

void updateFieldsUnderAttack(){

}


bool moveWouldOpenCheck(logic::Piece selected, int destFile, int destRank){
	//TODO: move
	updateFieldsUnderAttack();
	logic::Piece w = white[King];
	logic::Piece b = black[King];
	if(playerToMove == logic::White && board[w.rank][w.file].underAttackByBlack){
		//TODO: revert move
		return true;
	}
	else if(playerToMove == logic::Black && board[b.rank][b.file].underAttackByWhite){
		//TODO: revert move
		return true;
	}

	//TODO: revert move
}

int abs(int x){
	if(x<0)
		return -x;
	else
		return x;
}

bool friendlyPieceOnField(logic::Field field){
	return (field.piece != nullptr && (field.piece)->color == playerToMove);
}

std::list<logic::Field> kingCanMoveTo(logic::Piece king){
	std::list<logic::Field> res;
	logic::Field destField; //fields that we can go to

	//select adjecent fields
	int posRank = king.rank;
	int posFile = king.file;
	int minFile, maxFile, minRank, maxRank;
	if(posRank>0)minRank=posRank-1;
	else minRank=0;
	if(posRank<7)maxRank=posRank+1;
	else maxRank=7;
	if(posFile>0)minFile=posFile-1;
	else minFile=0;
	if(posFile<7)maxFile=posFile+1;
	else maxFile=7;

	//check which of them are legitimate moves
	for(int i=minRank; i<=maxRank; i++){
		for(int j=minFile; j<=maxFile; j++){

			destField = board[i][j];
			
			//can't stand on top of your own piece or stay in place
			if(friendlyPieceOnField(destField) || (posRank==i && posFile==j))
				continue;

			//if the king would not step into check
			if(playerToMove == logic::White && !destField.underAttackByBlack){
				res.push_back(destField);
			}
			if(playerToMove == logic::Black && !destField.underAttackByWhite){
				res.push_back(destField);
			}
		}
	}

	//TODO: castling

	return res;
}

std::list<logic::Field> queenCanMoveTo(logic::Piece queen){
	std::list<logic::Field> res;
	logic::Field destField; //fields that we can go to
	
	//moving horizontally
	for(int i=queen.rank-1; i>0; i--){
		destField = board[i][queen.file];
		if(friendlyPieceOnField(destField) || moveWouldOpenCheck(queen, destField.file, destField.rank))
			break;
		res.push_back(destField);
	}
	for(int i=queen.rank+1; i<_RANKS; i++){
		destField = board[i][queen.file];
		if(friendlyPieceOnField(destField) || moveWouldOpenCheck(queen, destField.file, destField.rank))
			break;
		res.push_back(destField);
	}

	//moving vertically
	for(int i=queen.file-1; i>0; i--){
		destField = board[queen.rank][i];
		if(friendlyPieceOnField(destField) || moveWouldOpenCheck(queen, destField.file, destField.rank))
			break;
		res.push_back(destField);
	}
	for(int i=queen.file+1; i<_FILES; i++){
		destField = board[queen.rank][i];
		if(friendlyPieceOnField(destField) || moveWouldOpenCheck(queen, destField.file, destField.rank))
			break;
		res.push_back(destField);
	}

	//moving diagonally
	
}

/************************************
*             INTERFACE             *
*************************************/

void logic::startGame(){
	//init pieces into starting position
	initializeBoard();
}

int getPlayerToMove(){
	return (playerToMove == logic::White ? logic::White : logic::Black);
}


void movePiece(int fromFile, int fromRank, int toFile, int toRank){
	//needed to calculate legitimacy of some moves
	int fileDiff = abs(fromFile - toFile);
	int rankDiff = abs(fromRank - toRank);

	//find the selected piece on board
	logic::Piece selectedP;
	if(board[fromRank][fromFile].piece != nullptr)
		selectedP = *(board[fromRank][fromFile].piece);

	//find the selected field on board
	logic::Field destField = board[fromRank][fromFile];

	//legitimate moves list
	std::list<logic::Field> moves;

	//move according to rules for each piece
	switch(selectedP.type){
		case logic::King:
			moves = kingCanMoveTo(selectedP);
			break;
		case logic::Queen:
			moves = queenCanMoveTo(selectedP);
			break;
		case logic::Bishop:
			break;
		case logic::Knight:
			break;
		case logic::Rook:
			break;
		case logic::Pawn:
			break;
	}

	for (auto const& i : moves) {
		if(i.file == destField.file && i.rank == destField.rank){
			//TODO: move
		}
	}
}



/************************************
*          DEBUGGING TOOLS          *
*************************************/
#ifdef DEBUG
void printPieceState(const int i, const char* name, const logic::ColorOfPiece color){
	if(color == logic::White)
		printf("type: %s\ncolor: White\nfile: %d\nrank: %d\nonBoard: %s\n\n",\
			name, white[i].file, white[i].rank, white[i].onBoard ? "True" : "False");
	else
		printf("type: %s\ncolor: Black\nfile: %d\nrank: %d\nonBoard: %s\n\n",\
			name, black[i].file, black[i].rank, black[i].onBoard ? "True" : "False");	
}

void printPieceStates(void){
	printf("P I E C E   S T A T E S\n\n");
	printf("#######################\n");
	printf("     W H I T E\n");
	printf("#######################\n");
	for(int i=0; i<_NO_OF_PIECES; i++){
		switch(white[i].type){
			case logic::King:
				printPieceState(i, "King",   logic::White);
				break;
			case logic::Queen:
				printPieceState(i, "Queen",  logic::White);
				break;
			case logic::Bishop:
				printPieceState(i, "Bishop", logic::White);
				break;
			case logic::Knight:
				printPieceState(i, "Knight", logic::White);
				break;
			case logic::Rook:
				printPieceState(i, "Rook",   logic::White);
				break;
			case logic::Pawn:
				printPieceState(i, "Pawn",   logic::White);
				break;
		};
		
	}

	printf("#######################\n");
	printf("     B L A C K\n");
	printf("#######################\n");
	for(int i=0; i<_NO_OF_PIECES; i++){
		switch(white[i].type){
			case logic::King:
				printPieceState(i, "King",   logic::Black);
				break;
			case logic::Queen:
				printPieceState(i, "Queen",  logic::Black);
				break;
			case logic::Bishop:
				printPieceState(i, "Bishop", logic::Black);
				break;
			case logic::Knight:
				printPieceState(i, "Knight", logic::Black);
				break;
			case logic::Rook:
				printPieceState(i, "Rook",   logic::Black);
				break;
			case logic::Pawn:
				printPieceState(i, "Pawn",   logic::Black);
				break;
		};
		
	}

}
#endif