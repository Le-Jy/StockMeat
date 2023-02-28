#include "move.h"

int respectedRangeVertical(struct piece** board, struct piece* piece, int i)
{
    if(piece->y+i<8 && piece->y+i>-1)
        return 1;
    return 0;
}

int respectedRangeHorizontal(struct piece** board, struct piece* piece, int i)
{
    if(piece->x+i<8 && piece->x+i>-1)
        return 1;
    return 0;
}


void getMoves(struct piece** board, struct piece* piece, int playercolor)
{
    if(piece->color == playercolor)
    {
        int v = respectedRangeVertical(board, piece, -1);
        int h = respectedRangeHorizontal(board, piece, -1);
        switch(piece->role)
        {
            case PAWN:
            if(v && board[piece->x+(piece->y-1)*8]->role==EMPTY)//front
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = NULL;
                newmove->data = piece->x+(piece->y-1)*8;
                piece->possibleMoves->next = newmove;
                piece->possibleMoves = piece->possibleMoves->next;

            }
            if(h && v && board[piece->x-1+(piece->y-1)*8]->color!=playercolor && board[piece->x+1+(piece->y-1)*8]->color!=NONE)//left diag (can eat)
            {
                printf("2\n");
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = NULL;
                newmove->data = piece->x-1+(piece->y-1)*8;
                piece->possibleMoves->next = newmove;
                piece->possibleMoves = piece->possibleMoves->next;
            }
            v = respectedRangeVertical(board, piece, 1);
            h = respectedRangeHorizontal(board, piece, 1);
            if(h && v && board[piece->x+1+(piece->y-1)*8]->color!=playercolor && board[piece->x+1+(piece->y-1)*8]->color!=NONE)//right diag (can eat)
            {
                printf("3\n");
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = NULL;
                newmove->data = piece->x+1+(piece->y-1)*8;
                piece->possibleMoves->next = newmove;
                piece->possibleMoves = piece->possibleMoves->next;
            }
            break;
        }
    }
}