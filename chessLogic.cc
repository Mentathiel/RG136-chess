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

// true  - moved
// false - open check
bool moveIfNoOpenCheck(logic::Piece selected, int destFile, int destRank){
	//TODO: move
	updateFieldsUnderAttack();
	logic::Piece w = white[King];
	logic::Piece b = black[King];
	if(playerToMove == logic::White && board[w.rank][w.file].underAttackByBlack){
		//TODO: revert move
		return false;
	}
	else if(playerToMove == logic::Black && board[b.rank][b.file].underAttackByWhite){
		//TODO: revert move
		return false;
	}
}

int abs(int x){
	if(x<0)
		return -x;
	else
		return x;
}

std::list<logic::Field> kingCanMoveTo(){

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


/* 0 - moved successfully
** 1 - cannot move king to a field under attack
** 2 - that piece does not move to that field
** 3 - move would open check to self
** 4 - castling over an attacked field
** 5 - friendly piece on that field
** 6 - pieces in the way
** FOLLOWING SHOULDN'T HAPPPEN:
** 7 - trying to move opponents piece
** 8 - no piece selected
**/
int movePiece(int fromFile, int fromRank, int toFile, int toRank){
	//needed to calculate legitimacy of some moves
	int fileDiff = abs(fromFile - toFile);
	int rankDiff = abs(fromRank - toRank);

	//find the selected piece on board
	logic::Piece selectedP;
	if(board[fromRank][fromFile].piece != nullptr)
		selectedP = *(board[fromRank][fromFile].piece);
	else
		return 8;

	//find the selected field on board
	logic::Field destField = board[fromRank][fromFile];

	//if a friendly piece is on the field, return regardless of the legitimacy of the move otherwise
	if(destField.piece != nullptr && (destField.piece)->color == playerToMove)
		return 5;

	//trying to move opponent's piece
	if(selectedP.color != playerToMove)
		return 7;

	//move according to rules for each piece
	switch(selectedP.type){
		case logic::King:
		{
			//if it's one of the adjecent fields
			if((rankDiff == 1 || fileDiff == 1) && (rankDiff+fileDiff)<=2){
				//if the king would step into check
				if(playerToMove == logic::White && destField.underAttackByBlack){
					return 1;
				}
				if(playerToMove == logic::Black && destField.underAttackByWhite){
					return 1;
				}
				//TODO: MOVE PIECE
			}
			//else if castling
			else
				return 2;
			break;
		}
		case logic::Queen:
		{
			//moving horizontally if it doesn't open check
			if(fromRank == toRank){
				//check if pieces are in the way
				int tmp1, tmp2;
				if(fromFile<toFile){tmp1=fromFile; tmp2=toFile;}
				else			   {tmp1=toFile;   tmp2=fromFile;}
				for(int i=tmp1+1; i<tmp2; i++){
					if(board[fromRank][i].piece != nullptr)
						return 6;
				}
				return moveIfNoOpenCheck(selectedP, toFile, toRank) ? 0 : 3;
			}
			//moving vertically if it doesn't open check
			else if(fromFile == toFile){
				//check if pieces are in the way
				int tmp1, tmp2;
				if(fromRank<toRank){tmp1=fromRank; tmp2=toRank;}
				else			   {tmp1=toRank;   tmp2=fromRank;}
				for(int i=tmp1+1; i<tmp2; i++){
					if(board[i][fromFile].piece != nullptr)
						return 6;
				}
				return moveIfNoOpenCheck(selectedP, toFile, toRank) ? 0 : 3;
			}
			//moving diagonally if it doesn't open check
			else if(fileDiff==rankDiff){
				//check if pieces are in the way

				return moveIfNoOpenCheck(selectedP, toFile, toRank) ? 0 : 3;
			}
			//illegitimate move
			else
				return 2;
			break;
		}
		case logic::Bishop:
		{

			break;
		}
		case logic::Knight:
		{

			break;
		}
		case logic::Rook:
		{

			break;
		}
		case logic::Pawn:
		{

			break;
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