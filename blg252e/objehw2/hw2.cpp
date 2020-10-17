//
//  BLG252E HW2
//
//  Cem Yusuf Aydoğdu
//  150120251
//

#include <iostream>
using namespace std;
#include "hw2.h"

Piece::Piece(Color cl, Column co, int i){
    if (i < 1 || i > 8 || co < A || co > H)
        throw OutofBoard();
    if(cl!=BLACK && cl!=WHITE)
        throw InvalidColor();
    if(board[i][co] != NULL)
        throw Occupied();
    else
        board[i][co] = this;
    color=cl;
    x=co;
    y=i;
}

void Piece::move(Column clmn, int row){
    if (row < 1 || row > 8 || clmn < A || clmn > H)
        throw OutofBoard();
    if(board[y][x] == NULL)
        throw EmptyCell();
    int moveContrl = board[y][x]->canmove(clmn,row);
    switch (moveContrl)
    {
        case 0:
            throw CannotMove();
            break;
        case 1: //move
            board[row][clmn] = board[y][x];
            board[y][x] = NULL;
            y = row;
            x = clmn;
            break;
        case 2:
            throw Occupied();
            break;
        case 3://capture and move
            cout << "captured: " << board[row][clmn]->draw() << " at " << coltoname[clmn] << row << endl;
            board[row][clmn] = board[y][x];
            board[y][x] = NULL;
            y = row;
            x = clmn;
            break;
    }

}

Piece * Piece::getpiece(Column clmn, int row){
	if(board[row][clmn]==NULL)
        throw EmptyCell();

    return board[row][clmn];
}
