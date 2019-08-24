#include "chess.hpp"

//Constructors
Queen::Queen(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Queen::Queen(PlayerColor color, Field* field) : ChessPiece(color,field){}

//Chess Related
list<Field*> Queen::getPlayableMoves(Chessboard cb){
	//TODO: Move would open check
	list<Field*> res;
	Field* field;

	//moving horizontally
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

	//moving vertically
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


	//moving diagonally

	bool downRight = false;
	bool downLeft  = false;
	bool upRight   = false;
	bool upLeft    = false;

	for(int i=1; i<8; i++){
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

bool Queen::checkIfLegal(Field field, Chessboard cb){
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

ChessPiece* Queen::movedPiece(PlayerColor color, Field* dest){
    return new Queen(color, dest);
}

//Utility
string Queen::toString() const{
	string res = "Q";
	return res;
}

//Display
void Queen::display(int file, int rank){
	glPushMatrix();
		ChessPiece::setMats();
		if(this->getColor()==PlayerColor::White){
			glColor3f( 0.9, 0.8, 0.7 );
		}
		else{
			glColor3f( 0.3, 0.2, 0.1 );
		}
	
	    glTranslatef(-3.5+file,-3.5+rank,10);
	    glScalef(0.8,0.8,1);
	    glPushMatrix();
	    	glTranslatef(-0.3,0,0);
	    	glScalef(0.3,1,0.3);
		    glutSolidCube(0.75);
		glPopMatrix();
    	glPushMatrix();
	    	glScalef(0.3,1,0.3);
		    glutSolidCube(0.75);
		glPopMatrix();
    	glPushMatrix();
	    	glTranslatef(+0.3,0,0);
	    	glScalef(0.3,1,0.3);
		    glutSolidCube(0.75);
		glPopMatrix();
    	glPushMatrix();
    		glTranslatef(0,-0.3,0);
	    	glScalef(1,0.3,0.3);
		    glutSolidCube(0.75);
		glPopMatrix();
	glPopMatrix();
}