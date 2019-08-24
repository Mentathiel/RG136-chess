#include "chess.hpp"

/* UTILITY */

string Field::fileName(int n){
	string res = "";

	// chess notation file names
	switch(n){
		case 0:
			res += "a";
			break;
		case 1:
			res += "b";
			break;
		case 2:
			res += "c";
			break;
		case 3:
			res += "d";
			break;
		case 4:
			res += "e";
			break;
		case 5:
			res += "f";
			break;
		case 6:
			res += "g";
			break;
		case 7:
			res += "h";
			break;
		default:
			// corrupted file marker
			res += "$";
			break;
	}

	return res;
}

string Field::toString(){
	string res = "";

	res += fileName(file);

	// rank, +1 because the array starts at 0,
	// and in chess it should start at 1
	res += to_string(rank+1);

	return res;
}


/* OPERATOR OVERLOADING */

bool Field::operator==(const Field& a){
	Field b = *this;
    if(a.file == b.file && a.rank == b.rank)
    	return true;
    else
    	return false;
}

bool Field::operator!=(const Field& a){
	Field b = *this;
	if(a.file == b.file && a.rank == b.rank)
		return false;
	else
		return true;
}