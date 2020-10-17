//
//  BLG252E HW2
//
//  Cem Yusuf Aydoğdu
//  150120251
//

#include "hw2.h"
#include <cstring>
#include <cmath>
using namespace std;
// create all pieces from Piece class by inheritance and implement their own functions draw(), canmove()

	// Knight class
	//
class Knight:public Piece
{
    public:
        Knight(Color clr, Column clmn, int row):Piece(clr,clmn,row){ }       // { color=clr; x=clmn; y=row; }
        int canmove(Column col, int row) const;
        virtual const char * draw() const;
};

int Knight::canmove(Column col, int row) const
{
    if( ( abs(col - x)==2 &&  abs(row - y)==1 ) || ( abs(col - x)==1 &&  abs(row - y)==2 ) )
    {
        if(board[row][col]==NULL) return 1; //place is null, just move
        else if(board[row][col]->getcolor() == color) return 2;  //place is occupied by same color
        else return 3;  // opponent is here, capture the piece with move
    }
    else return 0; // throw CannotMove();
    //return 0;
}

const char * Knight::draw() const
{
    if(color==BLACK) return "* N *";
    else return ". N .";
}


	// Bishop class
	//
class Bishop:public Piece
{
    public:
        Bishop(Color clr, Column clmn, int row):Piece(clr,clmn,row){ }
        int canmove(Column col, int row) const;
        const char * draw() const;
};

int Bishop::canmove(Column col, int row) const
{
    if( abs(col - x)==abs(row - y ))    // cross check
    {
        if(board[row][col]!=NULL)      //if an occupied place is same color
            if (board[row][col]->getcolor() == color) return 2;


        for(int i=y,j=x; i!=row,j!=col; x<col?j++:j--, y<row?i++:i--)   //checking for blockage
        {
            if(i==y && j==x) continue;
            if(board[i][j] != NULL) return 0;
        }

        if(board[row][col]==NULL) return 1;
        else return 3;

    }
    else return 0;
}

const char * Bishop::draw() const
{
    if (color==BLACK) return "* B *";
    else return ". B .";
}

	// Rook class
	//
class Rook: public Piece
{
    public:
        Rook(Color clr, Column clmn, int row):Piece(clr,clmn,row){ }
        int canmove(Column col, int row) const;
        const char * draw() const;
};

int Rook::canmove(Column col, int row) const
{
    if( (col == x && row != y) || (row == y && col != x) )      //accept only straight moves
    {
        if (board[row][col]!=NULL)      //if the place is occupied place with same color
            if (board[row][col]->getcolor() == color) return 2;

        //blockage checking begin
        if(col == x)
        {
            for(int i=y; i!=row; y<row?i++:i--)
            {
                if(i==y) continue;
                if(board[i][col] != NULL) return 0;
            }

        }
        if(row == y)
        {
            for(int j=x; j!=col; x<col?j++:j--)
            {
                if(j==x) continue;
                if(board[row][j] != NULL) return 0;
            }

        }
        //blockage checking ends

        if(board[row][col]==NULL) return 1; //if place is empty, just move
        else return 3;                      //if opponent is here, delete the opponent
    }
    else return 0;
}

const char * Rook::draw() const
{
    if (color==BLACK) return "* R *";
    else return ". R .";
}

	// Queen class
	//
class Queen: public Piece
{
    public:
        Queen(Color clr, Column clmn, int row):Piece(clr,clmn,row){ }
        int canmove(Column col, int row) const;
        const char * draw() const;
};

int Queen::canmove(Column col, int row) const
{
    if( ((col == x && row != y) || (row == y && col != x)) || abs(col - x)==abs(row - y ) ) //accept straight or cross moves
    {
        if(board[row][col]!=NULL)      //if an occupied place is same color
            if (board[row][col]->getcolor() == color) return 2;

        //blockage check for cross move
        if(abs(col - x)==abs(row - y ))
        {
            for(int i=y,j=x; i!=row,j!=col; x<col?j++:j--, y<row?i++:i--)   //checking for blockage
            {
                if(i==y && j==x) continue;
                if(board[i][j] != NULL) return 0;
            }
        }

        //blockage check for straight move
        if((col == x && row != y) || (row == y && col != x))
        {
            if(col == x)
            {
                for(int i=y; i!=row; y<row?i++:i--)
                {
                    if(i==y) continue;
                    if(board[i][col] != NULL) return 0;
                }

            }
            if(row == y)
            {
                for(int j=x; j!=col; x<col?j++:j--)
                {
                    if(j==x) continue;
                    if(board[row][j] != NULL) return 0;
                }

            }
        }

        if(board[row][col]==NULL) return 1;
        else return 3;
    }

    return 0;
}

const char * Queen::draw() const
{
    if (color==BLACK) return "* Q *";
    else return ". Q .";
}

	// King class
	//
class King: public Piece
{
    public:
        King(Color clr, Column clmn, int row):Piece(clr,clmn,row){ }
        int canmove(Column col, int row) const;
        const char * draw() const;
};

int King::canmove(Column col, int row) const
{
    if((abs(col-x)==1 && abs(row-y)==1) || (col==x && abs(row-y)==1) || (row==y && abs(col-x)==1))
    {
        if (board[row][col]==NULL)
            return 1;
        else
        {
            if(board[row][col]->getcolor() == color)
                return 2;
            else
                return 3;
        }

    }
    else return 0;
}

const char * King::draw() const
{
    if (color==BLACK) return "* K *";
    else return ". K .";
}

	// Pawn class
	//
class Pawn: public Piece
{
    public:
        Pawn(Color clr, Column clmn, int row):Piece(clr,clmn,row){ }
        int canmove(Column col, int row) const;
        const char * draw() const;
};

int Pawn::canmove(Column col, int row) const
{
    int rowDifference = row - y;

    if (col==x && (( y==2 && (rowDifference==1 || rowDifference==2)) ||        // white first move
                   ( y==7 && (rowDifference==-1 || rowDifference==-2)) ||         //black first move
                   ( color == WHITE && rowDifference==1 ) ||                    //while normal move
                   ( color == BLACK && rowDifference==-1 )))                  //black normal move
    {
        if (board[row][col]==NULL)      //if place null, just move
            return 1;
        else                        // if not null, cannot move whether occupied by same color or not
            return 2;

    }

    if (abs(col-x)==1 && ((color == WHITE && rowDifference==1) || (color == BLACK && rowDifference==-1))) //attack control
    {
        if (board[row][col]!=NULL)
        {
            if(board[row][col]->getcolor() == color)
                return 2;       // same color
            else
                return 3;       // eliminate
        }
        else return 0;          // cannot move

    }
    return 0;
}

const char * Pawn::draw() const
{
    if (color==BLACK) return "* P *";
    else return ". P .";
}

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
