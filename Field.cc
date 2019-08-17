#include "chess.hpp"

string Field::fileName(int n){
	string res = "";

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
			res += "{corrupted file marker}";
	}

	return res;
}

string Field::toString(){
	string res = "";

	res += fileName(file);

	res += to_string(rank);

	return res;
}