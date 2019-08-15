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
		}
	}
	return res;
}

bool King::checkIfLegal(Field field, Chessboard cb){
	if(abs(this->field->rank - field.rank) <= 1 &&
	   abs(this->field->file - field.file) <= 1 &&
	   *(this->field) != field &&
	   !fieldAttackedOrOccupied(field,cb)){
		return true;
	}
	else
		return false;
}

//Utility
string King::toString() const{
	string res = "K";
	return res;
}