#include "chess.hpp"

using namespace std;

Chessboard::Chessboard(){
	initializeBoard();
}

void Chessboard::print() const{
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(board[j][i] == nullptr)
				cout << "    ";
			else
				cout << *board[j][i];
		}
		cout << endl;
	}

}

void Chessboard::updateAttacked(){}

void Chessboard::initializeBoard(){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			this->board[i][j] = nullptr;
		}
	}

	//initializing pawns
	for(int i=0; i<8; i++){
		board[i][1] = new Pawn(PlayerColor::White, i, 1);
		board[i][6] = new Pawn(PlayerColor::Black, i, 6);
	}

	//initializing rooks
	board[0][0] = new Rook(PlayerColor::White, 0, 0);
	board[7][0] = new Rook(PlayerColor::White, 7, 0);
	board[0][7] = new Rook(PlayerColor::Black, 0, 7);
	board[7][7] = new Rook(PlayerColor::Black, 7, 7);

	//initializing knights
	board[1][0] = new Knight(PlayerColor::White, 1, 0);
	board[6][0] = new Knight(PlayerColor::White, 6, 0);
	board[1][7] = new Knight(PlayerColor::Black, 1, 7);
	board[6][7] = new Knight(PlayerColor::Black, 6, 7);

	//initializing bishops
	board[2][0] = new Bishop(PlayerColor::White, 2, 0);
	board[5][0] = new Bishop(PlayerColor::White, 5, 0);
	board[2][7] = new Bishop(PlayerColor::Black, 2, 7);
	board[5][7] = new Bishop(PlayerColor::Black, 5, 7);

	//initializing queens
	board[3][0] = new Queen(PlayerColor::White, 3, 0);
	board[3][7] = new Queen(PlayerColor::Black, 3, 7);

	//initializing kings
	board[4][0] = new King(PlayerColor::White, 4, 0);
	board[4][7] = new King(PlayerColor::Black, 4, 7);
}