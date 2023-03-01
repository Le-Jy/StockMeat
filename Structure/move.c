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
        case BISHOP:
        getBishopMoves(board,piece);
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

void getBishopMoves(struct piece** board, struct piece* piece)
{
    int posLeftDiag = 1;
    int frontRightDiag = 1;
    int negLeftDiag = 1;
    int backRightDiag = 1;
    int c = 1;
    for(int i=piece->x-1;(posLeftDiag || negLeftDiag) && i>=0;i--)//left diag both direction
    {
        int vpos = respectedRangeVertical(board, piece, c);
        int vneg = respectedRangeVertical(board, piece, -c);
        if(!vneg || (vneg && board[(i)+(piece->y-c)*8]->color==piece->color))
        {
            posLeftDiag = 0;
        }

        if(!vpos || (vpos && board[(i)+(piece->y+c)*8]->color==piece->color))
        {
            negLeftDiag = 0;
        }

        if(vneg && posLeftDiag && board[(i)+(piece->y-c)*8]->color == NONE)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y-c)*8;
            piece->possibleMoves = newmove;
        }

        if(vneg && posLeftDiag && board[(i)+(piece->y-c)*8]->color != NONE && board[(i)+(piece->y+c)*8]->color != piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y-c)*8;
            piece->possibleMoves = newmove;
            posLeftDiag = 0;
        }

        if(vpos && negLeftDiag && board[(i)+(piece->y+c)*8]->color == NONE)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y+c)*8;
            piece->possibleMoves = newmove;
        }

        if(vpos && negLeftDiag && board[(i)+(piece->y+c)*8]->color!=NONE && board[(i)+(piece->y+c)*8]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y+c)*8;
            piece->possibleMoves = newmove;
            negLeftDiag = 0;
        }
        c++;            
    }
    c = 1;
    for(size_t i = piece->x+1;(frontRightDiag || backRightDiag) && i<8;i++)//Right diag both direction
    {
        int vpos = respectedRangeVertical(board, piece, c);
        int vneg = respectedRangeVertical(board, piece, -c);
        if(!vpos || (vpos && board[(i)+(piece->y+c)*8]->color==piece->color))
        {
            frontRightDiag = 0;
        }

        if(!vneg || (vneg && board[(i)+(piece->y-c)*8]->color==piece->color))
        {
            backRightDiag = 0;
        }

        if(vneg && backRightDiag && board[(i)+(piece->y-c)*8]->color==NONE)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y-c)*8;
            piece->possibleMoves = newmove;
        }

        if(vneg && backRightDiag && board[(i)+(piece->y-c)*8]->color!=NONE && board[(i)+(piece->y-c)*8]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y-c)*8;
            piece->possibleMoves = newmove;
            backRightDiag = 0;
        }

        if(vpos && frontRightDiag && board[(i)+(piece->y+c)*8]->color==NONE)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y+c)*8;
            piece->possibleMoves = newmove;
        }

        if(vpos && frontRightDiag && board[(i)+(piece->y+c)*8]->color!=NONE && board[(i)+(piece->y+c)*8]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = (i)+(piece->y+c)*8;
            piece->possibleMoves = newmove;
            frontRightDiag = 0;
        }
        c++;
    }
   
}

void getKnightMoves(struct piece** board, struct piece* piece, int playercolor)
{
    return;
}

void getRookMoves(struct piece** board, struct piece* piece, int playercolor)
{
    return;
}

void getQueenMoves(struct piece** board, struct piece* piece, int playercolor)
{
    return;
}

void getKingMoves(struct piece** board, struct piece* piece, int playercolor)
{
    return;
}