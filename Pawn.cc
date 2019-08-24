#include "chess.hpp"

/* CONSTRUCTORS */

Pawn::Pawn(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Pawn::Pawn(PlayerColor color, Field* field) : ChessPiece(color,field){}

/* CHESS RELATED */

list<Field*> Pawn::getPlayableMoves(Chessboard cb){

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

bool Pawn::checkIfLegal(Field field, Chessboard cb){
	PlayerColor color = this->getColor();

	int rankDiff = field.rank - this->field->rank;
	int fileDiff = field.file - this->field->file;

	if(color == PlayerColor::Black){
		rankDiff = -rankDiff;
		fileDiff = -fileDiff;
	}


		 /* Moving one square forward... */
	if(( (rankDiff==1 && fileDiff==0 
		 	&& !friendlyPieceOnField(field,cb) && !enemyPieceOnField(field,cb))
		 /* or eating... */
		 || (rankDiff==1 && (fileDiff==1 || fileDiff == -1) 
		 		&& enemyPieceOnField(field,cb)) 
		 /* or moving two squares forward if in starting position... */
		 || (rankDiff==2 && field.file == this->field->file 
		 	&& (this->field->rank==1 || this->field->rank==6)
		 	&& !enemyPieceOnField(field,cb))
		 /* or En Passant. */
		 || (cb.pawnMovedLast != nullptr 
		 	 && *(cb.pawnMovedLast->field) == field
		 	 && cb.pawnMovedLast->field->rank == this->field->rank
		 	 && (cb.pawnMovedLast->field->file - this->field->file) == 1) )
		){
		
		return true;
	}
	return false;

}


/* Returns a new piece after moving it. Needed so we could access
   the functionality from a pointer of ChessPiece* type instead of
   checking typeof for every piece. */
ChessPiece* Pawn::movedPiece(PlayerColor color, Field* dest){
    return new Pawn(color, dest);
}


/* UTILITY */

string Pawn::toString() const{
	string res = "p";
	return res;
}


/* DISPLAY */

void Pawn::display(int file, int rank){
	glPushMatrix();
		ChessPiece::setMats();
		if(this->getColor()==PlayerColor::White){
			glColor3f( 0.9, 0.8, 0.7 );
		}
		else{
			glColor3f( 0.3, 0.2, 0.1 );
		}
	
		if(this->getColor()==PlayerColor::White){
			glColor3f( 0.9, 0.8, 0.7 );
		}
		else{
			glColor3f( 0.3, 0.2, 0.1 );
		}
	    glTranslatef(-3.5+file,-3.5+rank,10);
	    glutSolidSphere(0.3, 20, 20);
	glPopMatrix();
}