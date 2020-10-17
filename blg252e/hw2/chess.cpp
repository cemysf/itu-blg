#include "hw2.h"

// create all pieces from Piece class by inheritance and implement their own functions draw(), canmove()
	
	// Knight class
	//
	// Bishop class
	//
	// Rook class
	//
	// Queen class
	//
	// King class
	//
	// Pawn class
	//

Piece *create(const char *piecename, Color clr, Column clmn, int row){
	if (row < 1 || row > 8 || clmn < A || clmn > H){
		throw OutofBoard();

	}
	else{
		if (strcmp(piecename, "pawn") == 0){
			Pawn* created = new Pawn(clr, clmn, row);
			return created;
		}
		else if (strcmp(piecename, "knight") == 0){
			Knight* created = new Knight(clr, clmn, row);
			return created;
		}
		else if (strcmp(piecename, "bishop") == 0){
			Bishop* created = new Bishop(clr, clmn, row);
			return created;
		}
		else if (strcmp(piecename, "rook") == 0){
			Rook* created = new Rook(clr, clmn, row);
			return created;
		}
		else if (strcmp(piecename, "queen") == 0){
			Queen* created = new Queen(clr, clmn, row);
			return created;
		}
		else if (strcmp(piecename, "king") == 0){
			King* created = new King(clr, clmn, row);
			return created;
		}
		else return NULL;
	}
}