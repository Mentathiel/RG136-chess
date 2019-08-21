#include "chess.hpp"

//Constructors
Bishop::Bishop(PlayerColor color, int file, int rank) : ChessPiece(color,file,rank){
	string str = "Pieces 3D/bishop.obj";
	objHandler.loadModel(str.c_str());
}

Bishop::Bishop(PlayerColor color, Field* field) : ChessPiece(color,field){
	string str = "Pieces 3D/bishop.obj";
	objHandler.loadModel(str.c_str());
}

//Chess Related
list<Field*> Bishop::getPlayableMoves(Chessboard cb){
	//TODO: Move would open check
	list<Field*> res;
	Field* field;
	
	//moving diagonally

	bool pieceLeft = false;
	bool pieceRight = false;
	for(int i=this->field->rank-1; i>0; i--){

		if(this->field->file-i >= 0 && !pieceLeft){
			field = new Field(this->field->file-i,i);
			if(!ChessPiece::friendlyPieceOnField(*field,cb))
				res.push_back(field);
			else{
				delete field;
				pieceLeft = true;
			}
		}

		if(this->field->file+i < 8 && !pieceRight){
			field = new Field(this->field->file+i,i);
			if(!(ChessPiece::friendlyPieceOnField(*field,cb)))
				res.push_back(field);
			else{
				delete field;
				pieceRight = true;
			}
		}
	}

	pieceLeft = false;
	pieceRight = false;
	for(int i=this->field->rank+1; i<8; i++){

		if(this->field->file-i >= 0 && !pieceLeft){
			field = new Field(this->field->file-i,i);
			if(!(ChessPiece::friendlyPieceOnField(*field,cb)))
				res.push_back(field);
			else{
				delete field;
				pieceLeft = true;
			}
		}

		if(this->field->file+i < 8 && !pieceRight){
			field = new Field(this->field->file+i,i);
			if(!(ChessPiece::friendlyPieceOnField(*field,cb)))
				res.push_back(field);
			else{
				delete field;
				pieceRight = true;
			}
		}
	}

	return res;
}

bool Bishop::checkIfLegal(Field field, Chessboard cb){
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
string Bishop::toString() const{
	string res = "B";
	return res;
}