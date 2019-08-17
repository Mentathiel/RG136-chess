#include "chess.hpp"

Game::Game(){
	cb = new Chessboard();
}

Game::Game(Chessboard* cb){
	this->cb = cb;
}

void Game::playMove(Move* move){
	if(move->moving->checkIfLegal(*move->dest, *cb)){
		cb->board[move->from->file][move->from->rank] = nullptr;
		cb->board[move->dest->file][move->dest->rank] = 
			new ChessPiece(move->moving->getColor(), 
						   new Field(move->dest->file,move->dest->rank));
		cb->updateAttacked();
		moveHistory.push_back(move);
	}
	else{
		//the move is illegal and won't be played
	}
}

void Game::playMove(Field* dest, ChessPiece* moving){
	Move* move = new Move(dest, moving, *cb);
	playMove(move);
}

Move Game::undoMove(void){
	if(!moveHistory.empty()){
		Move* move = moveHistory.back();
		cb->board[move->from->file][move->from->rank] = move->moving;
		cb->board[move->dest->file][move->dest->rank] = move->eaten;
		delete move->moving->field;
		move->moving->field = new Field(move->from->file,move->from->rank);
		cb->updateAttacked();
		moveHistory.pop_back();
	}
}