#include "chess.hpp"

using namespace std;

ChessPiece::ChessPiece() : color(PlayerColor::White) {}

ChessPiece::ChessPiece(PlayerColor color, int file, int rank) : color(color) {
    this->field = new Field(file,rank);
}

ChessPiece::ChessPiece(PlayerColor color, Field* field)
                       : color(color), field(field) {}

ostream& operator<<(ostream& out, const ChessPiece& cp)
{
    if(cp.getColor() == PlayerColor::White)
        out << "W";
    else
        out << "B";

    out << cp.toString();

    out << cp.field->toString();

    return out;
}

bool ChessPiece::friendlyPieceOnField(Field field, Chessboard cb){

    if(cb.board[field.file][field.rank] != nullptr){
        if(cb.board[field.file][field.rank]->getColor() == this->color)
            return true;
        else 
            return false;
    }

    return false;
}

bool ChessPiece::enemyPieceOnField(Field field, Chessboard cb){

    if(cb.board[field.file][field.rank] != nullptr){
        if(cb.board[field.file][field.rank]->getColor() != this->color)
            return true;
        else 
            return false;
    }

    return false;
}

bool ChessPiece::fieldAttackedOrOccupied(Field field, Chessboard cb){

    if(friendlyPieceOnField(field, cb))
        return true;

    if(this->color == PlayerColor::White){
        if(cb.attackedByBlack[field.file][field.rank])
            return true;
    }
    else if(this->color == PlayerColor::Black){
        if(cb.attackedByWhite[field.file][field.rank])
            return true;
    }

    return false;
}

PlayerColor ChessPiece::getColor() const {
    return this->color;
};

string ChessPiece::getName() const{
    return this->name;
};

ChessPiece* ChessPiece::movedPiece(PlayerColor color, Field* dest){
    return new ChessPiece(color, dest);
}

list<Field*> ChessPiece::getPlayableMoves(Chessboard cb){
    list<Field*> li;
    return li;
}

bool ChessPiece::checkIfLegal(Field field, Chessboard cb){
    return false;
}

bool ChessPiece::checkIfLegal(Move* move, Chessboard cb){
    this->checkIfLegal(*move->dest, cb);
}


//Utility
void ChessPiece::print() const{
    cout << this;
};

string ChessPiece::toString() const{
    return "";
}


//Display
void ChessPiece::display(int file, int rank){
    
}