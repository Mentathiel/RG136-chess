#include "chess.hpp"

/* Field selected in main through the 
   visual interface. */
extern int selFieldFile;
extern int selFieldRank;

/* CONSTRUCTORS */

Game::Game(){
	cb = new Chessboard();
}

Game::Game(Chessboard* cb){
	this->cb = cb;
}


/* CHESS RELATED */

bool Game::checkForCheck(PlayerColor color){
	// assume not checked
	bool checked = false;

	// check entire board to find the king
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr
			   && typeid(*cb->board[i][j]) == typeid(King)
			   && cb->board[i][j]->getColor() == color){
			   	// if the king of respective color is checked, return true
				if(color == PlayerColor::White && cb->attackedByBlack[i][j])
					return true;
				if(color == PlayerColor::Black && cb->attackedByWhite[i][j])
					return true;
			}
		}
	}

	/* If we checked the whole board and the king wasn't
	   checked, return false. */
	return false;
}


/* Overloaded so it would call the function for the player
   next to move by default. */
bool Game::checkForCheck(){
	return checkForCheck(cb->toMove);
}



bool Game::checkForMate(){
	// the player has to be checked to be mated
	bool checked = checkForCheck();

	// if he isn't checked, return false immediately
	if(!checked)
		return false;

	/* Go through the entire board and record all possible moves
	   for the player whose turn it is. */
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

	/* Go through all the possible moves and see if you can find one
	   that would result in the player not being checked anymore. If
	   so, the player hasn't been mated. */
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
	
	/* Stalemate */
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

	/* 75 Move Rule 
	   HACK: using playMove to check for opened check or
	   checkmate can end the game with a draw a move early */
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

	/* Draw by insufficient mating material
	   - king versus king
	   - king and bishop versus king
	   - king and knight versus king
	   - king and bishop versus king and bishop with the bishops on the same color.*/
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


/* Check if the game should end or if the player tried to play
   an unrelated move while checked. */
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
	// don't play moves if the game is finished
	if(gameFinished)
		return;

	// deselect field
	selected = false;

	// if the selected move is legal for the selected piece...
	if(move->moving->checkIfLegal(*move->dest, *cb)
	   // and the piece seleced belongs to the player whose turn it is
	   && cb->toMove == move->moving->getColor()){

	   	// move a piece from from to dest
		cb->board[move->from->file][move->from->rank] = nullptr;
		cb->board[move->dest->file][move->dest->rank] = 
			move->moving->movedPiece(move->moving->getColor(), 
					   new Field(move->dest->file,move->dest->rank));

		// indicate that the piece was moved (for castling)
		cb->board[move->dest->file][move->dest->rank]->inStartingPos = false;

		// update which fields are attacked on the chessboard
		cb->updateAttacked();

		// add the move into the move history
		moveHistory.push_back(move);

		// update info for draw conditions
		if(typeid(*move->moving) != typeid(Pawn))
			movesSinceCapturePawnMove++;
		else
			movesSinceCapturePawnMove = 0;

		// switch whose turn it is
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
	// don't play moves if the game is finished
	if(gameFinished)
		return;

	// otherwise call the above function
	// overloaded for convenience
	Move* move = new Move(dest, moving, *cb);
	playMove(move);
}



Move Game::undoMove(void){
	// if you're undoing the move that finished the game
	// uh, "unfinish" it
	if(gameFinished)
		gameFinished = false;

	// if there are moves in move history
	if(!moveHistory.empty()){
		// get the last move
		Move* move = moveHistory.back();

		//switch things back
		cb->board[move->from->file][move->from->rank] = move->moving;
		cb->board[move->dest->file][move->dest->rank] = move->eaten;
		move->moving->field = new Field(move->from->file,move->from->rank);
		
		//TODO: inStartingPos isn't updated here
		
		// update fields which are attacked
		cb->updateAttacked();

		// delete the last move from history after undoing it
		moveHistory.pop_back();

		// switch the player whose turn it is
		if(cb->toMove == PlayerColor::White){
			cb->toMove = PlayerColor::Black;
		}
		else if(cb->toMove == PlayerColor::Black){
			cb->toMove = PlayerColor::White;
		}
	}
}

void Game::selectField(){
	// don't let the player select a field if the game is finished
	if(gameFinished)
		return;

	// if the selected field isn't empty
	if(cb->board[selFieldFile][selFieldRank] != nullptr
	   // and the piece on the field belongs to the player whose turn it is
	   && cb->board[selFieldFile][selFieldRank]->getColor() == cb->toMove){
	   		// select the field and change accompanying global info
			selected = true;
			selFile = selFieldFile;
			selRank = selFieldRank;
	}
}

/* If a piece is currently selected, then the player is picking which move
   to play with it. Otherwise, he's still selecting a piece to play with. */
bool Game::pickingMove(){
	return selected;
}


/* DISPLAY */

void Game::display(int file, int rank){

	// print chessboard
	cb->display(file, rank, selected, selFile, selRank);

	// print pieces on the chessboard
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(cb->board[i][j] != nullptr && cb->board[i][j]->onBoard){
				cb->board[i][j]->display(i,j);
			}
		}
	}
}