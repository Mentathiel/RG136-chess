#include "chess.hpp"

using namespace std;

/* CONSTRUCTORS */

Chessboard::Chessboard(){
	initializeBoard();
}

void Chessboard::print() const{
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(board[j][i] == nullptr)
				cout << "     ";
			else
				cout << *board[j][i] << " ";
		}
		cout << endl;
	}

}


/* CHESS LOGIC */

void Chessboard::updateAttacked(){
	// initialize all fields to not attacked
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			attackedByWhite[i][j] = false;
			attackedByBlack[i][j] = false;		
		}
	}

	// check the entire chessboard
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(board[i][j] != nullptr){
				// if a player of this color
				PlayerColor color = board[i][j]->getColor();
				// has a legitimate move to this field
				list<Field*> li = board[i][j]->getPlayableMoves(*this);
				// then he is attacking this field
				for(Field* f : li){
					if(color == PlayerColor::White){
						attackedByWhite[f->file][f->rank] = true;
					}
					else if(color == PlayerColor::Black){
						attackedByBlack[f->file][f->rank] = true;
					}
					delete f;
				}
			}
		}
	}
}


void Chessboard::initializeBoard(){
	toMove = PlayerColor::White;

	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			this->board[i][j] = nullptr;
		}
	}

	//initializing pawns
	for(int i=0; i<8; i++){
		board[i][1] = new Pawn(PlayerColor::White, i, 1);
		board[i][6] = new Pawn(PlayerColor::Black, i, 6);
	}

	//initializing rooks
	board[0][0] = new Rook(PlayerColor::White, 0, 0);
	board[7][0] = new Rook(PlayerColor::White, 7, 0);
	board[0][7] = new Rook(PlayerColor::Black, 0, 7);
	board[7][7] = new Rook(PlayerColor::Black, 7, 7);

	//initializing knights
	board[1][0] = new Knight(PlayerColor::White, 1, 0);
	board[6][0] = new Knight(PlayerColor::White, 6, 0);
	board[1][7] = new Knight(PlayerColor::Black, 1, 7);
	board[6][7] = new Knight(PlayerColor::Black, 6, 7);

	//initializing bishops
	board[2][0] = new Bishop(PlayerColor::White, 2, 0);
	board[5][0] = new Bishop(PlayerColor::White, 5, 0);
	board[2][7] = new Bishop(PlayerColor::Black, 2, 7);
	board[5][7] = new Bishop(PlayerColor::Black, 5, 7);

	//initializing queens
	board[3][0] = new Queen(PlayerColor::White, 3, 0);
	board[3][7] = new Queen(PlayerColor::Black, 3, 7);

	//initializing kings
	board[4][0] = new King(PlayerColor::White, 4, 0);
	board[4][7] = new King(PlayerColor::Black, 4, 7);
}


/* CHESS LOGIC */

bool Chessboard::operator==(const Chessboard& a){
	if(typeid(*this->pawnMovedLast) != typeid(*a.pawnMovedLast)
	   || this->toMove != a.toMove)
		return false;

	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(typeid(*this->board[i][j]) != typeid(*a.board[i][j])
			   || this->attackedByWhite[i][j] != a.attackedByWhite[i][j]
			   || this->attackedByBlack[i][j] != a.attackedByBlack[i][j])
				return false;
		}
	}

	return true;
}


bool Chessboard::operator!=(const Chessboard& a){
	if(typeid(*this->pawnMovedLast) != typeid(*a.pawnMovedLast)
	   || this->toMove != a.toMove)
		return true;

	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if(typeid(*this->board[i][j]) != typeid(*a.board[i][j])
			   || this->attackedByWhite[i][j] != a.attackedByWhite[i][j]
			   || this->attackedByBlack[i][j] != a.attackedByBlack[i][j])
				return true;
		}
	}

	return false;
}


/* DISPLAY */

void Chessboard::display(int file, int rank, bool selected, int selFile, int selRank){
	glDisable(GL_LIGHTING);

	// lower left quadrant
	for(int i=4; i>0; i--){
		for(int j=4; j>0; j--){
		    glPushMatrix();

		    if((i-1)==file && (j-1)==rank){
		    	glColor3f( 0.4, 0.3, 0.2 );
		    }
		    else if((i-j)%2==0){
			    glColor3f( 0.2, 0.1, 0 );

			}
			else{
				glColor3f( 0.8, 0.7, 0.6 );
			}

		    if(selected && selRank+1 == j && selFile+1 == i){
		    	glColor3f( 0.8, 0.5, 0.4 );
		    }

		    glTranslatef(-4.5+i, -4.5+j, 10);
		    glutSolidCube(1);		    
		    glPopMatrix();
		}
	}
	// upper right  quadrant
	for(int i=4; i<8; i++){
		for(int j=4; j<8; j++){
		    glPushMatrix();

		    if(i==file && j==rank){
		    	glColor3f( 0.4, 0.3, 0.2 );
		    }
		    else if((i-j)%2==0){
			    glColor3f( 0.2, 0.1, 0 );

			}
			else{
				glColor3f( 0.8, 0.7, 0.6 );
			}

		    if(selected && selRank == j && selFile == i){
		    	glColor3f( 0.8, 0.5, 0.4 );
		    }

		    glTranslatef(-3.5+i, -3.5+j, 10);
		    glutSolidCube(1);		    
		    glPopMatrix();
		}
	}

	// lower right  quadrant
	for(int i=4; i<8; i++){
		for(int j=4; j>0; j--){
		    glPushMatrix();

		    if(i==file && (j-1)==rank){
		    	glColor3f( 0.4, 0.3, 0.2 );
		    }
		    else if((i-j)%2==0){
		    	glColor3f( 0.8, 0.7, 0.6 );

			}
			else{
				glColor3f( 0.2, 0.1, 0 );
			}

		    if(selected && selRank+1 == j && selFile == i){
		    	glColor3f( 0.8, 0.5, 0.4 );
		    }

		    glTranslatef(-3.5+i, -4.5+j, 10);
		    glutSolidCube(1);		    
		    glPopMatrix();
		}
	}

	// upper left  quadrant
	for(int i=4; i>0; i--){
		for(int j=4; j<8; j++){
		    glPushMatrix();

		    if((i-1)==file && j==rank){
		    	glColor3f( 0.4, 0.3, 0.2 );
		    }
		    else if((i-j)%2==0){
				glColor3f( 0.8, 0.7, 0.6 );
			}
			else{
				glColor3f( 0.2, 0.1, 0 );
			}

		    if(selected && selRank == j && selFile+1 == i){
		    	glColor3f( 0.8, 0.5, 0.4 );
		    }

		    glTranslatef(-4.5+i, -3.5+j, 10);
		    glutSolidCube(1);		    
		    glPopMatrix();
		}
	}

	glColor3f( 0.01, 0.01, 0.01 );
	glBegin( GL_QUADS );
		//left
		glVertex3f(-4.0, -4.0, 9.5);
		glVertex3f(-3.5, -4.0, 9.5);
		glVertex3f(-3.5,  3.5, 9.5);
		glVertex3f(-4.0,  3.5, 9.5);

		//right
		glVertex3f(3.5, -4.0, 9.5);
		glVertex3f(4.0, -4.0, 9.5);
		glVertex3f(4.0,  3.5, 9.5);
		glVertex3f(3.5,  3.5, 9.5);	

		//bottom
		glVertex3f(-4.0, -4.0, 9.5);
		glVertex3f( 4.0, -4.0, 9.5);
		glVertex3f( 4.0, -3.5, 9.5);
		glVertex3f(-4.0, -3.5, 9.5);

		//top
		glVertex3f(-4.0, 3.5, 9.5);
		glVertex3f( 4.0, 3.5, 9.5);
		glVertex3f( 4.0, 4.0, 9.5);
		glVertex3f(-4.0, 4.0, 9.5);	
	glEnd();

	glEnable(GL_LIGHTING);
}