#include "chess.hpp"

extern int selFieldFile;
extern int selFieldRank;

Game::Game(){
	cb = new Chessboard();
}

Game::Game(Chessboard* cb){
	this->cb = cb;
}

bool Game::checkForMate(){
	//TODO
	return false;
}

bool Game::checkForDraw(){
	//Stalemate
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr
			   && typeid(*cb->board[i][j]) == typeid(King)
			   && cb->board[i][j]->getColor() == cb->toMove){
			   	//TODO: Check if surrounding is attacked/occupied
			   	//without king being under check
				break;
			}
		}
	}

	//TODO: Threefold repetition

	//75 move rule
	if(movesSinceCapturePawnMove >= 75)
		return true;

	//TODO: Insufficient material
	/*king versus king
	  king and bishop versus king
	  king and knight versus king
	  king and bishop versus king and bishop with the bishops on the same color.*/
}

void Game::playMove(Move* move){
	selected = false;

	if(move->moving->checkIfLegal(*move->dest, *cb)
	   && cb->toMove == move->moving->getColor()){
		cb->board[move->from->file][move->from->rank] = nullptr;
		cb->board[move->dest->file][move->dest->rank] = 
			move->moving->movedPiece(move->moving->getColor(), 
					   new Field(move->dest->file,move->dest->rank));
		cb->updateAttacked();
		moveHistory.push_back(move);

		if(typeid(*move->moving) != typeid(Pawn))
			movesSinceCapturePawnMove++;
		else
			movesSinceCapturePawnMove = 0;

		if(checkForDraw()){
			//TODO: draw
			//HACK: using playMove to check for opened check
			//can end the game with a draw a move early
		//TODO: win
		}

		
		if(cb->toMove == PlayerColor::White){
			cb->toMove = PlayerColor::Black;
		}
		else if(cb->toMove == PlayerColor::Black){
			cb->toMove = PlayerColor::White;
		}
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

	if(cb->toMove == PlayerColor::White){
		cb->toMove = PlayerColor::Black;
	}
	else if(cb->toMove == PlayerColor::Black){
		cb->toMove = PlayerColor::White;
	}
}

void Game::selectField(){
	if(cb->board[selFieldFile][selFieldRank] != nullptr
	   && cb->board[selFieldFile][selFieldRank]->getColor() == cb->toMove){
		selected = true;
		selFile = selFieldFile;
		selRank = selFieldRank;
	}
}

bool Game::pickingMove(){
	return selected;
}

void Game::display(int file, int rank){
	cb->display(file, rank, selected, selFile, selRank);


	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr && cb->board[i][j]->onBoard){
				cb->board[i][j]->display(i,j);
			}
		}
	}
}