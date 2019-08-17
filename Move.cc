#include "chess.hpp"

Move::Move(Field* dest, ChessPiece* moving, Chessboard cb) : dest(dest), moving(moving) {
	from = moving->field;
	eaten = cb.board[dest->file][dest->rank];
}

string Move::toString(){
	string res = "";

	if(typeid(*moving) != typeid(Pawn))
		res += moving->toString();
	else if(eaten != nullptr){
		res += Field::fileName(from->file);
	}

	if(eaten != nullptr){
		res += "x";
	}

	res += dest->toString();
	return res;
}