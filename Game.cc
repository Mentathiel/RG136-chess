#include "chess.hpp"

extern int selFieldFile;
extern int selFieldRank;

Game::Game(){
	cb = new Chessboard();
}

Game::Game(Chessboard* cb){
	this->cb = cb;
}

bool Game::checkForCheck(PlayerColor color){
	bool checked = false;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr
			   && typeid(*cb->board[i][j]) == typeid(King)
			   && cb->board[i][j]->getColor() == color){
				if(color == PlayerColor::White && cb->attackedByBlack[i][j])
					return true;
				if(color == PlayerColor::Black && cb->attackedByWhite[i][j])
					return true;
			}
		}
	}	
	return false;
}

bool Game::checkForCheck(){
	return checkForCheck(cb->toMove);
}

//BUG: Doesn't detect mate
bool Game::checkForMate(){
	bool checked = checkForCheck();

	if(!checked)
		return false;

	list<Move*> moves;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr
			   && cb->board[i][j]->getColor() == cb->toMove){

				list<Field*> li = cb->board[i][j]->getPlayableMoves(*cb);
				if(!li.empty()){
					for(Field* f : li)
						moves.push_back(new Move(f, cb->board[i][j], *cb));

				}
			}
		}
	}

	PlayerColor color = cb->toMove;
	for(Move* move : moves){
		playMove(move);
		if(!checkForCheck(color)){
			cout << move->toString() << endl << endl;
			undoMove();
			return false;
		}
		undoMove();
		delete move;
	}
	return true;

}

bool Game::checkForDraw(){
	//Stalemate
	bool stalemate = true;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr
			   && typeid(*cb->board[i][j]) == typeid(King)
			   && cb->board[i][j]->getColor() == cb->toMove){
				if(cb->toMove == PlayerColor::White && cb->attackedByBlack[i][j])
					return false;
				if(cb->toMove == PlayerColor::Black && cb->attackedByWhite[i][j])
					return false;

				list<Field*> li = cb->board[i][j]->getPlayableMoves(*cb);
				if(!li.empty()){
					stalemate = false;
					for(Field* f : li)
						delete f;
				}

			}
		}
	}

	if(stalemate)
		return true;

	//TODO: Threefold repetition

	/* 75 Move Rule */
	//HACK: using playMove to check for opened check or
	//checkmate can end the game with a draw a move early
	if(movesSinceCapturePawnMove >= 75)
		return true;

	bool whiteKnight  = false;
	bool blackKnight  = false;
	bool whiteWBishop = false;
	bool whiteBBishop = false;
	bool blackWBishop = false;
	bool blackBBishop = false;
	int otherPieces = 0;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr){
				if(typeid(*cb->board[i][j]) == typeid(Knight)){
					if(cb->board[i][j]->getColor() == PlayerColor::White)
						whiteKnight = true;
					else
						blackKnight = true;
				}
				else if(typeid(*cb->board[i][j]) == typeid(Bishop)){
					if(cb->board[i][j]->getColor() == PlayerColor::White){
						if((i-j)%2)
							whiteBBishop = true;
						else
							whiteWBishop = true;
					}
					else
						if((i-j)%2)
							blackBBishop = true;
						else
							blackWBishop = true;
				}
				else
					otherPieces++;
			}
		}
	}

	/*king versus king
	  king and bishop versus king
	  king and knight versus king
	  king and bishop versus king and bishop with the bishops on the same color.*/
	bool blackMatingMaterial = true;
	bool whiteMatingMaterial = true;
	if(otherPieces == 2){
		if(    (whiteKnight && !whiteWBishop && !whiteBBishop)
			|| (!whiteKnight && !whiteWBishop && !whiteBBishop)
			|| (whiteBBishop && !whiteWBishop && !blackWBishop)
			|| (whiteWBishop && !whiteBBishop && !blackBBishop))
			whiteMatingMaterial = false;
		if(    (blackKnight && !blackWBishop && !blackBBishop)
			|| (!blackKnight && !blackWBishop && !blackBBishop)
			|| (blackBBishop && !blackWBishop && !whiteWBishop)
			|| (blackWBishop && !blackBBishop && !whiteBBishop))
			blackMatingMaterial = false;

		if(!whiteMatingMaterial && !blackMatingMaterial)
			return true;
	}

	return false;
}


void Game::checkState(){
	if(gameFinished)
		return;

	if(checkForDraw()){
		gameFinished = true;
		return;
	}
	if(checkForMate()){
		gameFinished = true;
		return;
	}
	if(    (cb->toMove == PlayerColor::White && checkForCheck(PlayerColor::Black))
		|| (cb->toMove == PlayerColor::Black && checkForCheck(PlayerColor::White))){
		undoMove();
	}
}

void Game::playMove(Move* move){
	if(gameFinished)
		return;

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
	if(gameFinished)
		return;
	Move* move = new Move(dest, moving, *cb);
	playMove(move);
}

Move Game::undoMove(void){
	if(gameFinished)
		gameFinished = false;

	if(!moveHistory.empty()){
		Move* move = moveHistory.back();
		cb->board[move->from->file][move->from->rank] = move->moving;
		cb->board[move->dest->file][move->dest->rank] = move->eaten;
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
	if(gameFinished)
		return;
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