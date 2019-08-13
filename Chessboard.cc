#include "chess.hpp"

using namespace std;

Chessboard::Chessboard(){
	initializeBoard();
}

void Chessboard::print() const{}

void Chessboard::updateAttacked(){}

void Chessboard::initializeBoard(){
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			this->board[i][j] = nullptr;
		}
	}

	//TODO: Initialize the pieces
}