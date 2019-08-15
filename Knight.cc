#include "chess.hpp"

//Constructors
Knight::Knight(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){}

Knight::Knight(PlayerColor color, Field* field) : ChessPiece(color,field){}

//Chess Related
list<Field*> Knight::getPlayableMoves(Chessboard cb){
	//TODO: Move would open check
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

bool Knight::checkIfLegal(Field field, Chessboard cb){
	int rankDiff = abs(field.rank - this->field->rank);
	int fileDiff = abs(field.file - this->field->file);
	if((rankDiff==1 && fileDiff==2) || (rankDiff==2 && fileDiff==1)
		&& !friendlyPieceOnField(field,cb)){
		return true;
	}
	return false;
}

//Utility
string Knight::toString() const{
	string res = "N";
	return res;
}