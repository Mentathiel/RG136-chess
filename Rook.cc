#include "chess.hpp"

//Constructors
Rook::Rook(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Rook::Rook(PlayerColor color, Field* field) : ChessPiece(color,field){}

//Chess Related
list<Field*> Rook::getPlayableMoves(Chessboard cb){
	//TODO: Move would open check
	list<Field*> res;
	Field* field;

	//moving horizontally
	for(int i=this->field->rank-1; i>0; i--){
		field = new Field(this->field->file, i);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb)){
			delete field;
			break;
		}
		res.push_back(field);
	}
	for(int i=this->field->rank+1; i<8; i++){
		field = new Field(this->field->file, i);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb)){
			delete field;
			break;
		}
		res.push_back(field);
	}

	//moving vertically
	for(int i=this->field->file-1; i>0; i--){
		field = new Field(i, this->field->rank);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb)){
			delete field;
			break;
		}
		res.push_back(field);
	}
	for(int i=this->field->file+1; i<8; i++){
		field = new Field(i, this->field->rank);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb)){
			delete field;
			break;
		}
		res.push_back(field);
	}

	//queen-side castle
	field = new Field(2,0);
	if(this->inStartingPos && field->file==2
	   && cb.board[4][0] != nullptr
	   && typeid(*cb.board[5][0])==typeid(King)
	   && cb.board[4][0]->inStartingPos){
		res.push_back(field);
	}
	else delete field;

	//king-side castle
	field = new Field(5,0);
	if(this->inStartingPos && field->file==5
	   && cb.board[4][0] != nullptr
	   && typeid(*cb.board[5][0])==typeid(King)
	   && cb.board[4][0]->inStartingPos){
		res.push_back(field);
	}
	else delete field;

	return res;
}

bool Rook::checkIfLegal(Field field, Chessboard cb){
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

//Utility
string Rook::toString() const{
	string res = "R";
	return res;
}

//Display
void Rook::display(int file, int rank){
	glPushMatrix();
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