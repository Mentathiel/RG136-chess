#include "chess.hpp"

using namespace std;

ChessPiece::ChessPiece(PlayerColor color, int file, int rank)
                       : color(color), file(file), rank(rank) {}

ostream& operator<<(ostream& out, const ChessPiece& cp)
{
    if(cp.getColor() == PlayerColor::White)
        out << "White ";
    else
        out << "Black ";

    out << &cp.getName()[0] << " on ";

    switch(cp.file){
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

    out << cp.rank;

    return out;
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