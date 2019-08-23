#include "chess.hpp"

//Constructors
King::King(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

King::King(PlayerColor color, Field* field) : ChessPiece(color,field){}

//Chess Related
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
	if(abs(this->field->rank - field.rank) <= 1 
	   && abs(this->field->file - field.file) <= 1 
	   && *(this->field) != field 
	   && !ChessPiece::fieldAttackedOrOccupied(field,cb)){
		return true;
	}
	
	//queen-side castle
	if(this->inStartingPos && field.file==2
	   && cb.board[0][this->field->rank] != nullptr
	   && typeid(*cb.board[0][this->field->rank])==typeid(Rook) 
	   && cb.board[0][this->field->rank]->inStartingPos){
		return true;
	}

	//king-side castle
	if(this->inStartingPos && field.file==6
	   && cb.board[7][this->field->rank] != nullptr
	   && typeid(*cb.board[7][this->field->rank])==typeid(Rook) 
	   && cb.board[7][this->field->rank]->inStartingPos){
		return true;
	}

	return false;
}

ChessPiece* King::movedPiece(PlayerColor color, Field* dest){
    return new King(color, dest);
}

//Utility
string King::toString() const{
	string res = "K";
	return res;
}


//Display
void King::display(int file, int rank){
	glPushMatrix();
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