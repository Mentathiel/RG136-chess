#include "chess.hpp"

//Constructors
Queen::Queen(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Queen::Queen(PlayerColor color, Field field) : ChessPiece(color,field){}

//Chess Related
list<Field*> Queen::getPlayableMoves(Chessboard cb){
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

bool Queen::checkIfLegal(Field field, Chessboard cb){
	if(abs((this->field).rank - abs((this->field).file) == field.rank - field.file) &&
	   this->field != field &&
	   !fieldAttackedOrOccupied(field,cb)){
		return true;
	}
	else
		return false;
}

//Utility
string Queen::toString() const{
	string res = "Q";
	return res;
}