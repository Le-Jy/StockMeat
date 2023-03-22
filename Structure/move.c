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
        case KNIGHT:
            getKnightMoves(board,piece);
            break;
        case ROOK:
            getRookMoves(board,piece);
            break;
        case QUEEN:
            getQueenMoves(board, piece);
            break;
        case KING:
            getKingMoves(board,piece);
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

void getKnightMoves(struct piece** board, struct piece* piece)
{
    int move = (piece->x+2)+(piece->y+1)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    move = (piece->x+2)+(piece->y-1)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    move = (piece->x-2)+(piece->y+1)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    move = (piece->x-2)+(piece->y-1)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    //next
    move = (piece->x+1)+(piece->y+2)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    move = (piece->x+1)+(piece->y-2)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    move = (piece->x-1)+(piece->y+2)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
    move = (piece->x-1)+(piece->y-2)*8;
    if(move<64 && move>-1)
    {
        if(board[move]->color!=piece->color)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = move;
            piece->possibleMoves = newmove;
        }
    }
}

void getRookMoves(struct piece** board, struct piece* piece)
{
    int dirNegV = 1;
    int dirPosV = 1;
    int dirNegH = 1;
    int dirPosH = 1;
    int i = 1;
    int negV = respectedRangeVertical(board,piece,-i);
    int posV = respectedRangeVertical(board,piece,i);
    int negH = respectedRangeHorizontal(board,piece,-i);
    int posH = respectedRangeHorizontal(board,piece,i);
    while((dirNegH || dirNegV || dirPosH || dirPosV) && i<8)
    {
        if(dirNegV && negV)
        {
            if(board[piece->x + (piece->y-i)*8]->color != piece->color)
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x + (piece->y-i)*8;
                piece->possibleMoves = newmove;
                if(board[piece->x + (piece->y-i)*8]->color != NONE)
                    dirNegV = 0;
            }
            else
                dirNegV = 0;
        }
        if(dirPosV && posV)
        {
            if(board[piece->x + (piece->y + i)*8]->color != piece->color)
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x + (piece->y+i)*8;
                piece->possibleMoves = newmove;
                if(board[piece->x + (piece->y + i)*8]->color != NONE)
                    dirPosV = 0;
            }
            else
                dirPosV = 0;
        }
        if(dirNegH && negH)
        {
            if(board[piece->x-i + piece->y*8]->color != piece->color)
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x-i + piece->y*8;
                piece->possibleMoves = newmove;
                if(board[piece->x - i + piece->y*8]->color != NONE)
                    dirNegH = 0;
            }
            else
                dirNegH = 0;
        }
        if(dirPosH && posH)
        {
            if(board[piece->x + i + piece->y*8]->color != piece->color)
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x + i + piece->y*8;
                piece->possibleMoves = newmove;
                if(board[piece->x + i + piece->y*8]->color != NONE)
                    dirPosH = 0;
            }
            else
                dirPosH = 0;
        }
        i++;
        if(dirNegV && negV)
            negV = respectedRangeVertical(board,piece,-i);
        if(dirPosV && posV)
            posV = respectedRangeVertical(board,piece,i);
        if(dirNegH && negH)
            negH = respectedRangeHorizontal(board,piece,-i);
        if(dirPosH && posH)
            posH = respectedRangeHorizontal(board,piece,i);
    }
}

void getQueenMoves(struct piece** board, struct piece* piece)
{
    getRookMoves(board,piece);
    getBishopMoves(board,piece);
}

void getKingMoves(struct piece** board, struct piece* piece)
{
    int vNeg = respectedRangeVertical(board, piece, -1);
    int vPos = respectedRangeVertical(board, piece, 1);
    int hNeg = respectedRangeHorizontal(board, piece, -1);
    int hPos = respectedRangeHorizontal(board, piece, 1);
    if(vNeg && board[piece->x+(piece->y-1)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x+(piece->y-1)*8;
        piece->possibleMoves = newmove;
    }
    if(hNeg && board[piece->x-1+(piece->y)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x-1+(piece->y)*8;
        piece->possibleMoves = newmove;
    }
    
    if(vPos && board[piece->x+(piece->y+1)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x+(piece->y+1)*8;
        piece->possibleMoves = newmove;
    }
    if(hPos && board[piece->x+1+(piece->y)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x+1+(piece->y)*8;
        piece->possibleMoves = newmove;
    }
    if(vNeg && hNeg && board[piece->x-1+(piece->y-1)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x-1+(piece->y-1)*8;
        piece->possibleMoves = newmove;
    }
    if(vPos && hPos && board[piece->x+1+(piece->y+1)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x+1+(piece->y+1)*8;
        piece->possibleMoves = newmove;
    }
    if(vNeg && hPos && board[piece->x+1+(piece->y-1)*8]->color != piece->color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x+1+(piece->y-1)*8;
        piece->possibleMoves = newmove;
    }
    if(vPos && hNeg && board[piece->x-1+(piece->y+1)*8]->color != piece-> color)
    {
        struct list* newmove = malloc(sizeof(struct list));
        newmove->next = piece->possibleMoves;
        newmove->data = piece->x-1+(piece->y+1)*8;
        piece->possibleMoves = newmove;
    }
}

int isCheck(struct piece** board, struct piece** listOfPieces)
{
    // for(size_t i = 0;i<32;i++)
    // {
    //     getMoves(board, listOfPieces[i],WHITE);
    //     printf("3\n");
    //     while(listOfPieces[i]->possibleMoves!=NULL)
    //     {
    //         printf("%i\n",listOfPieces[i]->possibleMoves->data);
    //         if(board[listOfPieces[i]->possibleMoves->data]->role==KING && board[listOfPieces[i]->possibleMoves->data]->color != listOfPieces[i]->color)
    //             return i;
    //         listOfPieces[i]->possibleMoves = listOfPieces[i]->possibleMoves->next;
    //     }
    // }
    // return 0;
}

int move(struct piece** board, struct piece* piece, int x, int y, struct piece** listOfPieces)
{
    while(piece->possibleMoves)
    {
        if(piece->possibleMoves->data == x+y*8)
            break;
        piece->possibleMoves = piece->possibleMoves->next;
    }
    if(piece->possibleMoves == NULL)
        return 0;
    struct piece* sw = board[x+y*8];

    board[piece->x+piece->y*8] = sw;
    board[x+y*8] = piece;

    int tmpx = piece->x;
    int tmpy = piece->y;
    piece->x = x;
    piece->y = y;
    // int isCheckIndex = isCheck(board, listOfPieces);
    // if(listOfPieces[isCheckIndex]->color != piece->color)
    // {
    //     board[piece->x+piece->y*8] = piece;
    //     piece->x = tmpx;
    //     piece->y = tmpy;
    //     board[x+y*8]=sw;
    // }


    
    return 1;
}