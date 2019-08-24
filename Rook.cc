#include "chess.hpp"

/* CONSTRUCTORS */

Rook::Rook(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Rook::Rook(PlayerColor color, Field* field) : ChessPiece(color,field){}


/* CHESS RELATED */

list<Field*> Rook::getPlayableMoves(Chessboard cb){

	// result variable
	list<Field*> res;
	// current field that we're checking
	Field* field;

	/* Moving horizonally/vertically, we stop: 
	   - when we encounter a piece
	   -- friendly means we can't go to that field
	   -- enemy we can eat, but can't go further
	   - on the edge of the board */

	// moving down
	for(int i=this->field->rank-1; i>=0; i--){
		field = new Field(this->field->file, i);
		if(ChessPiece::friendlyPieceOnField(*field,cb)){
			delete field;
			break;
		}
		else if(ChessPiece::enemyPieceOnField(*field,cb)){
			res.push_back(field);
			break;
		}
		res.push_back(field);
	}
	// moving up
	for(int i=this->field->rank+1; i<8; i++){
		field = new Field(this->field->file, i);
		if(ChessPiece::friendlyPieceOnField(*field,cb)){
			delete field;
			break;
		}
		else if(ChessPiece::enemyPieceOnField(*field,cb)){
			res.push_back(field);
			break;
		}
		res.push_back(field);
	}

	// moving left
	for(int i=this->field->file-1; i>=0; i--){
		field = new Field(i, this->field->rank);
		if(ChessPiece::friendlyPieceOnField(*field,cb)){
			delete field;
			break;
		}
		else if(ChessPiece::enemyPieceOnField(*field,cb)){
			res.push_back(field);
			break;
		}
		res.push_back(field);
	}
	// moving right
	for(int i=this->field->file+1; i<8; i++){
		field = new Field(i, this->field->rank);
		if(ChessPiece::friendlyPieceOnField(*field,cb)){
			delete field;
			break;
		}
		else if(ChessPiece::enemyPieceOnField(*field,cb)){
			res.push_back(field);
			break;
		}
		res.push_back(field);
	}

	return res;
}

bool Rook::checkIfLegal(Field field, Chessboard cb){

	/* If the move is within this piece's list of playable moves,
	   it is a legal move.*/

	list<Field*> playable = this->getPlayableMoves(cb);
	bool res = false;
	for(Field* move : playable){
		if(*move == field){
			res = true;
		}
		delete move;
	}
	return res;
}


/* Returns a new piece after moving it. Needed so we could access
   the functionality from a pointer of ChessPiece* type instead of
   checking typeof for every piece. */
ChessPiece* Rook::movedPiece(PlayerColor color, Field* dest){
    return new Rook(color, dest);
}


/* UTILITY */

string Rook::toString() const{
	string res = "R";
	return res;
}


/* DISPLAY */

void Rook::display(int file, int rank){
	glPushMatrix();
		ChessPiece::setMats();
		if(this->getColor()==PlayerColor::White){
			glColor3f( 0.9, 0.8, 0.7 );
		}
		else{
			glColor3f( 0.3, 0.2, 0.1 );
		}
	
	    glTranslatef(-3.5+file,-3.5+rank,10);
	    glutSolidCube(0.5);
	glPopMatrix();
}