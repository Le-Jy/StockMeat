#include "piece.h"

void newpiece (struct piece *newpiece, int x, int y,enum Color color)
{
    newpiece->x=x;
    newpiece->y=y;
    newpiece->color = color;
    if(y==1 || y==6)
        newpiece->role = PAWN;
    else if((y==0||y==7) && (x==0 || x==7))
        newpiece->role = ROOK;
    else if((y==0||y==7) && (x==1 || x==6))
        newpiece->role = KNIGHT;
    else if((y==0||y==7) && (x==2 || x==5))
        newpiece->role = BISHOP;
    else if((y == 0 && x == 3)||(y==7 && x == 4))
        newpiece->role = KING;
    else if((y == 0 && x == 4)||(y==7 && x == 3))
        newpiece->role = QUEEN;
    else
    {
        newpiece->role = EMPTY;
    }

}