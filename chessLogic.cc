#include "chessLogic.hpp"
#include <stdio.h>

#define _NO_OF_PIECES 16
#define _FIRST_PAWN 8

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
	Rock1, Knight1, BishopB, Queen, King,  BishopW, Knight2, Rock2,
	PawnA, PawnB,   PawnC,   PawnD, PawnE, PawnF,   PawnG,   PawnH	
};

logic::Piece white[_NO_OF_PIECES];
logic::Piece black[_NO_OF_PIECES];



void initialiePieceTypes(){
	white[King].type = logic::King;
	white[Queen].type = logic::Queen;
	white[Rock1].type = logic::Rock;
	white[Rock2].type = logic::Rock;
	white[BishopB].type = logic::Bishop;
	white[BishopW].type = logic::Bishop;
	white[Knight1].type = logic::Knight;
	white[Knight2].type = logic::Knight;
	for(int i=_FIRST_PAWN; i<_NO_OF_PIECES; i++)
		white[i].type = logic::Pawn;

	black[King].type = logic::King;
	black[Queen].type = logic::Queen;
	black[Rock1].type = logic::Rock;
	black[Rock2].type = logic::Rock;
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
}


/************************************
*             INTERFACE             *
*************************************/

void logic::startGame(){
	initializeBoard();
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
			case logic::Rock:
				printPieceState(i, "Rock",   logic::White);
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
			case logic::Rock:
				printPieceState(i, "Rock",   logic::Black);
				break;
			case logic::Pawn:
				printPieceState(i, "Pawn",   logic::Black);
				break;
		};
		
	}

}
#endif