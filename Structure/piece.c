#include "piece.h"

void list_init(struct list *list)
{
    list->next = NULL;
    list->data=-1;
}

int list_is_empty(struct list *list)
{
    return list->next == NULL;
}

void newpiece (struct piece *newpiece, int x, int y,enum Color color, int index)
{
    newpiece->hasMoved = 0;
    newpiece->x=x;
    newpiece->y=y;
    newpiece->color = color;
    newpiece->possibleMoves = malloc(sizeof(struct list));
    list_init(newpiece->possibleMoves);
    if(y==1 || y==6)
    {
        newpiece->role = PAWN;
        newpiece->value = 1;
        newpiece->index = index;
    }
    else if((y==0||y==7) && (x==0 || x==7))
    {
        newpiece->role = ROOK;
        newpiece->value = 5;
        newpiece->index = index;
        
    }
    else if((y==0||y==7) && (x==1 || x==6))
    {
        newpiece->role = KNIGHT;
        newpiece->value = 3;
        newpiece->index = index;
    }
    else if((y==0||y==7) && (x==2 || x==5))
    {
        newpiece->role = BISHOP;
        newpiece->value = 3;
        newpiece->index = index;
    }
    
    else if((y == 0 && x == 4)||(y==7 && x == 4))
    {
        newpiece->role = KING;
        newpiece->value = 32767;
        newpiece->index = index;
    }
    else if((y == 0 && x == 3)||(y==7 && x == 3))
    {
        newpiece->role = QUEEN;
        newpiece->value = 9;
        newpiece->index = index;
    }
    else
    {
        newpiece->role = EMPTY;
        newpiece->value = 0;
    }

}

void freeMoves(struct piece* piece)
{
    while(piece->possibleMoves!=NULL)
    {
        struct list* tmp = piece->possibleMoves->next;
        free(piece->possibleMoves);
        piece->possibleMoves = tmp; 
    }
    free(piece->possibleMoves);
}

void freePiece(struct piece* piece)
{
    freeMoves(piece);
    free(piece);

}