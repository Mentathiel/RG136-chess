#include "chess.hpp"

/* CONSTRUCTORS */

Bishop::Bishop(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Bishop::Bishop(PlayerColor color, Field* field) : ChessPiece(color,field){}


/* CHESS RELATED */

list<Field*> Bishop::getPlayableMoves(Chessboard cb){

	// result variable
	list<Field*> res;
	// current field that we're checking
	Field* field;
	
	/* Moving diagonally, we stop: 
	   - when we encounter a piece
	   -- friendly means we can't go to that field
	   -- enemy we can eat, but can't go further
	   - on the edge of the board */

	/* bools to tell us whether we've encountered
	   a piece in a particular direction */
	bool downRight = false;
	bool downLeft  = false;
	bool upRight   = false;
	bool upLeft    = false;

	// i is the diagonal distance from the current position
	for(int i=1; i<8; i++){
		// moving down left
		if(!downLeft && this->field->file-i >= 0 && this->field->rank-i >=0){
			field = new Field(this->field->file-i,this->field->rank-i);
			if(ChessPiece::friendlyPieceOnField(*field,cb)){
				delete field;
				downLeft = true;
			}
			else if(ChessPiece::enemyPieceOnField(*field,cb)){
				res.push_back(field);
				downLeft = true;
			}
			else
				res.push_back(field);			
		}
		// moving up left
		if(!upLeft && this->field->file-i >= 0 && this->field->rank+i < 8){
			field = new Field(this->field->file-i,this->field->rank+i);
			if(ChessPiece::friendlyPieceOnField(*field,cb)){
				delete field;
				upLeft = true;
			}
			else if(ChessPiece::enemyPieceOnField(*field,cb)){
				res.push_back(field);
				upLeft = true;
			}
			else
				res.push_back(field);			
		}
		// moving up right
		if(!upRight && this->field->file+i < 8 && this->field->rank+i < 8){
			field = new Field(this->field->file+i,this->field->rank+i);
			if(ChessPiece::friendlyPieceOnField(*field,cb)){
				delete field;
				upRight = true;
			}
			else if(ChessPiece::enemyPieceOnField(*field,cb)){
				res.push_back(field);
				upRight = true;
			}
			else
				res.push_back(field);			
		}
		// moving down right
		if(!downRight && this->field->file+i < 8 && this->field->rank-i >= 0){
			field = new Field(this->field->file+i,this->field->rank-i);
			if(ChessPiece::friendlyPieceOnField(*field,cb)){
				delete field;
				downRight = true;
			}
			else if(ChessPiece::enemyPieceOnField(*field,cb)){
				res.push_back(field);
				downRight = true;
			}
			else
				res.push_back(field);			
		}
	}

	return res;
}


bool Bishop::checkIfLegal(Field field, Chessboard cb){

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
ChessPiece* Bishop::movedPiece(PlayerColor color, Field* dest){
    return new Bishop(color, dest);
}


/* UTILITY */

string Bishop::toString() const{
	string res = "B";
	return res;
}


/* DISPLAY */

void Bishop::display(int file, int rank){
	glPushMatrix();
		ChessPiece::setMats();
		if(this->getColor()==PlayerColor::White){
			glColor3f( 0.9, 0.8, 0.7 );
		}
		else{
			glColor3f( 0.3, 0.2, 0.1 );
		}
	
	    glTranslatef(-3.5+file,-3.5+rank,10);
	   	glRotatef(45,0,0,1);
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