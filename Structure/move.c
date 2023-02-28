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
    switch(piece->role)
    {
        case PAWN:
        getPawnMoves(board, piece, playercolor);
        break;
    }
    
}

void getPawnMoves(struct piece** board, struct piece* piece, int playercolor)
{
    if(playercolor == piece->color)
    {
        int v = respectedRangeVertical(board, piece, -1);
        int h = respectedRangeHorizontal(board, piece, -1);
        if(v && board[piece->x+(piece->y-1)*8]->role==EMPTY)//front 1 box
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+(piece->y-1)*8;
            piece->possibleMoves = newmove;

        }
        if(h && v && board[piece->x-1+(piece->y-1)*8]->color!=playercolor && board[piece->x+1+(piece->y-1)*8]->color!=NONE)//left diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x-1+(piece->y-1)*8;
            piece->possibleMoves = newmove;
        }
        h = respectedRangeHorizontal(board, piece, 1);
        if(h && v && board[piece->x+1+(piece->y-1)*8]->color!=playercolor && board[piece->x+1+(piece->y-1)*8]->color!=NONE)//right diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+1+(piece->y-1)*8;
            piece->possibleMoves = newmove;
            
        }
        if(piece->y==6)
        {
            int v = respectedRangeVertical(board, piece, -2);
            if(v && board[piece->x+(piece->y-2)*8]->role==EMPTY)//front 2 boxes
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x+(piece->y-2)*8;
                piece->possibleMoves = newmove;
            }

        }
    }
    else
    {
        int v = respectedRangeVertical(board, piece, 1);
        int h = respectedRangeHorizontal(board, piece, 1);
        if(v && board[piece->x+(piece->y+1)*8]->role==EMPTY)//front 1 box
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+(piece->y+1)*8;
            piece->possibleMoves = newmove;

        }
        if(h && v && board[piece->x-1+(piece->y+1)*8]->color!=playercolor && board[piece->x+1+(piece->y+1)*8]->color!=NONE)//left diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x-1+(piece->y+1)*8;
            piece->possibleMoves = newmove;
        }
        h = respectedRangeHorizontal(board, piece, 1);
        if(h && v && board[piece->x+1+(piece->y+1)*8]->color!=playercolor && board[piece->x+1+(piece->y+1)*8]->color!=NONE)//right diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+1+(piece->y+1)*8;
            piece->possibleMoves = newmove;
            
        }
        if(piece->y==1)
        {
            int v = respectedRangeVertical(board, piece, 2);
            if(v && board[piece->x+(piece->y+2)*8]->role==EMPTY)//front 2 boxes
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x+(piece->y+2)*8;
                piece->possibleMoves = newmove;
            }

        }
    }

}