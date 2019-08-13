#include "chess.hpp"

using namespace std;

ChessPiece::ChessPiece() : color(PlayerColor::White) {}

ChessPiece::ChessPiece(PlayerColor color, int file, int rank) : color(color) {
    //HACK: Leaking memory
    this->field = *(new Field(file,rank));
}

ChessPiece::ChessPiece(PlayerColor color, Field field)
                       : color(color), field(field) {}

ostream& operator<<(ostream& out, const ChessPiece& cp)
{
    if(cp.getColor() == PlayerColor::White)
        out << "White ";
    else
        out << "Black ";

    out << &cp.getName()[0] << " on ";

    switch(cp.field.file){
        case 0:
            out << "A";
            break;
        case 1:
            out << "B";
            break;
        case 2:
            out << "C";
            break;
        case 3:
            out << "D";
            break;
        case 4:
            out << "E";
            break;
        case 5:
            out << "F";
            break;
        case 6:
            out << "G";
            break;
        case 7:
            out << "H";
            break;
    }

    out << cp.field.rank;

    return out;
}

bool ChessPiece::fieldAttackedOrOccupied(Field field, Chessboard cb){
    //if the player is white and the field is not attacked by black
    if(this->color == PlayerColor::White && !cb.attackedByBlack[field.file][field.rank]){
        if(cb.board[field.file][field.rank] != nullptr){
            if(cb.board[field.file][field.rank]->getColor() != this->color)
                return true;
            else //occupied by friendly 
                return false;
        }
        else return true;
    }
    //if the player is black and the field is not attacked by white
    else if(this->color == PlayerColor::Black && !cb.attackedByWhite[field.file][field.rank]){
        if(cb.board[field.file][field.rank] != nullptr){
            if(cb.board[field.file][field.rank]->getColor() != this->color)
                    return true;
            else //occupied by friendly 
                return false;
        }
        else return true;
    }
    return false;
}

PlayerColor ChessPiece::getColor() const {
    return this->color;
};

string ChessPiece::getName() const{
    return this->name;
};

void ChessPiece::print() const{
    cout << this;
};


list<Field*> ChessPiece::getPlayableMoves(Chessboard cb){
    list<Field*> li;
    return li;
}

bool ChessPiece::checkIfLegal(Field field){
    return false;
}

string ChessPiece::toString() const{
    return "";
}