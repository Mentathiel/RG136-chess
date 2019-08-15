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
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb))
			break;
		res.push_back(field);
	}
	for(int i=this->field->rank+1; i<8; i++){
		field = new Field(this->field->file, i);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb))
			break;
		res.push_back(field);
	}

	//moving vertically
	for(int i=this->field->file-1; i>0; i--){
		field = new Field(i, this->field->rank);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb))
			break;
		res.push_back(field);
	}
	for(int i=this->field->file+1; i<8; i++){
		field = new Field(i, this->field->rank);
		if(!ChessPiece::fieldAttackedOrOccupied(*field,cb))
			break;
		res.push_back(field);
	}

	return res;
}

bool Rook::checkIfLegal(Field field, Chessboard cb){
	list<Field*> playable = this->getPlayableMoves(cb);
	for(Field* move : playable){
		if(*move == field){
			return true;
		}
	}
	return false;
}

//Utility
string Rook::toString() const{
	string res = "Q";
	return res;
}