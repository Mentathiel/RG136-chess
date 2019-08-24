#include "chess.hpp"

/* CONSTRUCTORS */

King::King(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

King::King(PlayerColor color, Field* field) : ChessPiece(color,field){}


/* CHESS RELATED */

list<Field*> King::getPlayableMoves(Chessboard cb){
	list<Field*> res;
	Field* field;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			field = new Field(i,j);
			if(checkIfLegal(*field, cb)){
				res.push_back(field);
			}
			else delete field;
		}
	}
	return res;
}

bool King::checkIfLegal(Field field, Chessboard cb){
	/* Moving to an adjacent field, checking if the field is
	   adjacent, is it not the same field, and whether it's
	   attacked or occupied by a friendly piece. A king can't
	   be moved into check, so we also have to check if it's attacked,
	   as opposed to just whether it's occupied. */
	if(abs(this->field->rank - field.rank) <= 1 
	   && abs(this->field->file - field.file) <= 1 
	   && *(this->field) != field 
	   && !ChessPiece::fieldAttackedOrOccupied(field,cb)){
		return true;
	}
	
	/* Queen-side Castle */

	//white
	if(this->inStartingPos && field.file==2 && field.rank==0
	   && cb.board[0][0] != nullptr
	   && typeid(*cb.board[0][0])==typeid(Rook) 
	   && cb.board[0][0]->inStartingPos){
		return true;
	}
	//black
	if(this->inStartingPos && field.file==2 && field.rank==7
	   && cb.board[0][7] != nullptr
	   && typeid(*cb.board[0][7])==typeid(Rook) 
	   && cb.board[0][7]->inStartingPos){
		return true;
	}


	/* King-side Castle */
	
	//white
	if(this->inStartingPos && field.file==6 && field.rank==0
	   && cb.board[7][0] != nullptr
	   && typeid(*cb.board[7][0])==typeid(Rook) 
	   && cb.board[7][0]->inStartingPos){
		return true;
	}

	//black
	if(this->inStartingPos && field.file==6 && field.rank==7
	   && cb.board[7][7] != nullptr
	   && typeid(*cb.board[7][7])==typeid(Rook) 
	   && cb.board[7][7]->inStartingPos){
		return true;
	}

	return false;
}


/* Returns a new piece after moving it. Needed so we could access
   the functionality from a pointer of ChessPiece* type instead of
   checking typeof for every piece. */
ChessPiece* King::movedPiece(PlayerColor color, Field* dest){
    return new King(color, dest);
}


/* UTILITY */

string King::toString() const{
	string res = "K";
	return res;
}



/* DISPLAY */

void King::display(int file, int rank){
	glPushMatrix();
		ChessPiece::setMats();
		if(this->getColor()==PlayerColor::White){
			glColor3f( 0.9, 0.8, 0.7 );
		}
		else{
			glColor3f( 0.3, 0.2, 0.1 );
		}
	
	    glTranslatef(-3.5+file,-3.5+rank,10);
	    glPushMatrix();
	    	glScalef(0.3,1,0.3);
		    glutSolidCube(0.75);
		glPopMatrix();
    	glPushMatrix();
	    	glScalef(1,0.3,0.3);
		    glutSolidCube(0.75);
		glPopMatrix();
	glPopMatrix();
}