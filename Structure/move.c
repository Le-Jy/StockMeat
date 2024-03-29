#include "move.h"

int respectedRangeVertical(struct piece* piece, int i)
{
    if(piece->y+i<8 && piece->y+i>-1)
        return 1;
    return 0;
}

int respectedRangeHorizontal(struct piece* piece, int i)
{
    if(piece->x+i<8 && piece->x+i>-1)
        return 1;
    return 0;
}

void getMoves(struct piece** board, struct piece* piece)
{
    switch(piece->role)
    {
        case PAWN:
            getPawnMoves(board, piece);
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
            break;
        default :
            break;
    }
    
}

void getPawnMoves(struct piece** board, struct piece* piece)
{
    freeMoves(piece);
    piece->possibleMoves = NULL;
    if(piece->realPlayerColor == piece->color)
    {
                
        int v = respectedRangeVertical(piece, -1);
        int h = respectedRangeHorizontal(piece, -1);
        if(v && board[piece->x+(piece->y-1)*8]->role==EMPTY)//front 1 box
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+(piece->y-1)*8;
            piece->possibleMoves = newmove;
            //printf("%i\n",newmove->data);

        }
        if(h && v && board[piece->x-1+(piece->y-1)*8]->color!=piece->color && board[piece->x-1+(piece->y-1)*8]->color!=NONE)//left diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x-1+(piece->y-1)*8;
            piece->possibleMoves = newmove;
            //printf("%i\n",newmove->data);
        }
        h = respectedRangeHorizontal(piece, 1);
        if(h && v && board[piece->x+1+(piece->y-1)*8]->color!=piece->color && board[piece->x+1+(piece->y-1)*8]->color!=NONE)//right diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+1+(piece->y-1)*8;
            piece->possibleMoves = newmove;
            //printf("%i\n",newmove->data);
            
            
        }
        if(piece->y==6)
        {
            int v = respectedRangeVertical(piece, -2);
            if(v && board[piece->x+(piece->y-2)*8]->role==EMPTY)//front 2 boxes
            {
                struct list *newmove = malloc(sizeof(struct list));
                newmove->next = piece->possibleMoves;
                newmove->data = piece->x+(piece->y-2)*8;
                piece->possibleMoves = newmove;
                //printf("%i\n",newmove->data);
            }

        }
    }
    else
    {
        int v = respectedRangeVertical(piece, 1);
        int h = respectedRangeHorizontal(piece, -1);
        if(v && board[piece->x+(piece->y+1)*8]->role==EMPTY)//front 1 box
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+(piece->y+1)*8;
            piece->possibleMoves = newmove;

        }
        if(h && v && board[piece->x-1+(piece->y+1)*8]->color!=piece->color && board[piece->x-1+(piece->y+1)*8]->color!=NONE)//left diag (can eat)
        {
            
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x-1+(piece->y+1)*8;
            piece->possibleMoves = newmove;
        }
        h = respectedRangeHorizontal(piece, 1);
        if(h && v && board[piece->x+1+(piece->y+1)*8]->color!=piece->color && board[piece->x+1+(piece->y+1)*8]->color!=NONE)//right diag (can eat)
        {
            struct list *newmove = malloc(sizeof(struct list));
            newmove->next = piece->possibleMoves;
            newmove->data = piece->x+1+(piece->y+1)*8;
            piece->possibleMoves = newmove;
            
        }
        if(piece->y==1)
        {
            int v = respectedRangeVertical(piece, 2);
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
    if(piece->role!=QUEEN)
    {
        freeMoves(piece);
        piece->possibleMoves = NULL;
    }
    int posLeftDiag = 1;
    int frontRightDiag = 1;
    int negLeftDiag = 1;
    int backRightDiag = 1;
    int c = 1;
    for(int i=piece->x-1;(posLeftDiag || negLeftDiag) && i>=0;i--)//left diag both direction
    {
        int vpos = respectedRangeVertical(piece, c);
        int vneg = respectedRangeVertical(piece, -c);
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

        if(vneg && posLeftDiag && board[(i)+(piece->y-c)*8]->color != NONE && board[(i)+(piece->y-c)*8]->color != piece->color)
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
        int vpos = respectedRangeVertical(piece, c);
        int vneg = respectedRangeVertical(piece, -c);
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
    freeMoves(piece);
    piece->possibleMoves = NULL;
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
    if(piece->role!=QUEEN)
    {
        freeMoves(piece);
        piece->possibleMoves = NULL;
    }
    int dirNegV = 1;
    int dirPosV = 1;
    int dirNegH = 1;
    int dirPosH = 1;
    int i = 1;
    int negV = respectedRangeVertical(piece,-i);
    int posV = respectedRangeVertical(piece,i);
    int negH = respectedRangeHorizontal(piece,-i);
    int posH = respectedRangeHorizontal(piece,i);
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
            negV = respectedRangeVertical(piece,-i);
        if(dirPosV && posV)
            posV = respectedRangeVertical(piece,i);
        if(dirNegH && negH)
            negH = respectedRangeHorizontal(piece,-i);
        if(dirPosH && posH)
            posH = respectedRangeHorizontal(piece,i);
    }
}

void getQueenMoves(struct piece** board, struct piece* piece)
{
    freeMoves(piece);
    piece->possibleMoves = NULL;
    getRookMoves(board,piece);
    getBishopMoves(board,piece);
}

void getKingMoves(struct piece** board, struct piece* piece)
{
    freeMoves(piece);
    piece->possibleMoves = NULL;
    int vNeg = respectedRangeVertical(piece, -1);
    int vPos = respectedRangeVertical(piece, 1);
    int hNeg = respectedRangeHorizontal(piece, -1);
    int hPos = respectedRangeHorizontal(piece, 1);
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

void sortMoves(struct piece** board, struct piece* piece)
{
    struct list* prev = NULL;
    struct list* sortedmoves = NULL;
    for(struct list* m = piece->possibleMoves;m!=NULL && piece->possibleMoves!=NULL;)
    {
        swap(board[m->data],piece);
        int check = isCheck(board,board[m->data]->color,m->data,piece->x+piece->y*8);
        if(check>=0)
        {
            
            struct list* tmp = m->next;
            swap(board[m->data],piece);
            if(prev == NULL)
                piece->possibleMoves = piece->possibleMoves->next;
            free(m);
            m = tmp;
        }
        if(check==-1)
        {
            struct list* newmove = malloc(sizeof(struct piece));
            swap(board[m->data],piece);
            newmove->next = sortedmoves;
            newmove->data = m->data;
            sortedmoves = newmove;
            prev = m;
            m=m->next;
        }
    }
    piece->possibleMoves = sortedmoves;
}

int isCheck(struct piece** board, int colorPlayed, int indexIgnored, int indexIgnored2)
{
    int res = -1;
    int i = 0;
    int max = 64;
    while(i<max && res==-1)
    {
        
        struct piece* p = board[i];
        if(i!= indexIgnored && i!=indexIgnored2 && board[i]->role && p->color !=colorPlayed)
        {
            getMoves(board, p);
            while(p->role !=0 && p->possibleMoves!=NULL && res==-1)
            {
                if(board[p->possibleMoves->data]->role == KING && board[p->possibleMoves->data]->color == colorPlayed)
                {
                    res = i;
                }
                p->possibleMoves = p->possibleMoves->next;
            }
        }
        i++;
    }
    return res;
}

int move(struct piece** board, struct piece* piece, int x, int y)
{
    getMoves(board,piece);
    if(piece->role != KING)
        sortMoves(board,piece);
    while(piece->possibleMoves)
    {
        if(piece->possibleMoves->data == x+y*8)
            break;
        piece->possibleMoves = piece->possibleMoves->next;
    }
    if(piece->possibleMoves == NULL)
    {
        return 0;
    }
        
    swap(piece,board[x+y*8]);
    if(board[x+y*8]->role == KING)
    {
        int isCheckIndex = isCheck(board, board[x+y*8]->color,x+y*8,piece->x+piece->y*8);
        if(isCheckIndex>=0)
        {
            swap(piece,board[x+y*8]);
            return 0;
        }
    }
    if(piece->role>=1)
    {
        int tmpx = piece->x;
        int tmpy = piece->y;
        freeMoves(board[tmpx+tmpy*8]);
        board[tmpx+tmpy*8]->role = EMPTY;
        board[tmpx+tmpy*8]->color = NONE;
        board[tmpx+tmpy*8]->value = 0;
        board[tmpx+tmpy*8]->x = tmpx;
        board[tmpx+tmpy*8]->y = tmpy;
        piece->hasMoved = 1;
        return x+y*8;
    }
    board[x+8*y]->hasMoved = 1;
    freeMoves(board[x+8*y]);
    
    return -1;
}

void swap(struct piece *A, struct piece *B)
{
    
    int tmpAx = A->x;
    A->x = B->x;
    B->x = tmpAx;
    int tmpAy = A->y;
    A->y = B->y; 
    B->y = tmpAy;
    struct piece temp = *A;
    *A = *B;
    *B = temp;
    
   
}

int canShortCastle(struct piece** board,struct piece* piece)
{
    int res = 0;
    if(!piece->hasMoved && !board[piece->x+3+piece->y*8]->hasMoved && !board[piece->x+piece->y*8+1]->role && !board[piece->x+piece->y*8+2]->role)
    {
        if(piece->role==KING)
        {
            res = 1;
            int i = 0;
            int max = 64;
            while(i<max && res==1)
            {
                struct piece* p = board[i];
                getMoves(board, p);
                while(p->role && p->possibleMoves!=NULL && res==1)
                {
                    if(p->color != piece->color && (board[p->possibleMoves->data]->y == piece->y && (board[p->possibleMoves->data]->x == piece->x+1 || board[p->possibleMoves->data]->x == piece->x+2)))
                    {
                        res = 0; 
                    }
                    p->possibleMoves = p->possibleMoves->next;
                }
                i++;
            }
        }
        
    }
    return res;

}

int canLongCastle(struct piece** board, struct piece* piece)
{
    int res = 0;
    if(!piece->hasMoved && !board[piece->x-4+piece->y*8]->hasMoved && !board[piece->x+piece->y*8-1]->role && !board[piece->x+piece->y*8-2]->role && !board[piece->x+piece->y*8-3]->role)
    {
        if(piece->role==KING)
        {
            res = 1;
            int i = 0;
            int max = 64;
            while(i<max && res==1)
            {
                struct piece* p = board[i];
                getMoves(board, p);
                while(p->role !=0 && p->possibleMoves!=NULL && res==1)
                {
                    if(p->color != piece->color && (board[p->possibleMoves->data]->y == piece->y && (board[p->possibleMoves->data]->x == piece->x-1 || board[p->possibleMoves->data]->x == piece->x-2 || board[p->possibleMoves->data]->x == piece->x-3)))
                    {
                        res = 0;
                    }
                    p->possibleMoves = p->possibleMoves->next;
                }
                i++;
            }
        }
        
    }
    return res;
}

void shortCastle(struct piece** board, struct piece* piece)
{
    if(canShortCastle(board, piece))
    {
        int x = piece->x;
        int y = piece->y;
        swap(board[x+2+y*8],piece);
        swap(board[x+1+y*8],board[x+3+y*8]);
        board[x+2+y*8]->hasMoved = 1;
    }

}

void longCastle(struct piece** board, struct piece* piece)
{
    if(canLongCastle(board, piece))
    {
        int x = piece->x;
        int y = piece->y;
        swap(board[x-2+y*8],piece);
        swap(board[x-1+y*8],board[x-4+y*8]);
        board[x-2+y*8]->hasMoved = 1;
    }
    
}

void promotion(struct piece* piece, int role)
{
    switch(role)
    {
        case(QUEEN):
            piece->role = QUEEN;
            piece->value = 9;
            break;
        case(ROOK):
            piece->role = ROOK;
            piece->value = 5;
            break;
        case(BISHOP):
            piece->role = BISHOP;
            piece->value = 3;
            break;
        case(KNIGHT):
            piece->role = KNIGHT;
            piece->value = 3;
            break;
    }
}

int canPromote(struct piece* piece)
{
    if(piece->role == 1 && piece->color == piece->realPlayerColor && piece->y==0)
    {
        return 1;
    }
    if(piece->role == 1 && piece->color != piece->realPlayerColor && piece->y==7)
    {
        return 1;
    }
    return 0;
}

int checkMate(struct piece** board,int KingColor,int x,int y)
{
    int check = 1;
    for(int i = 0;check == 1 && i<63;i++)
    {
        if(board[i]->role == KING && board[i]->color == KingColor)
        {
            getMoves(board,board[i]);
            int Kingx = board[i]->x;
            int Kingy = board[i]->y;
            int dangerousmoves[8];
            int cpt = 0;
            while(board[i]->possibleMoves != NULL && check == 1)
            {
                int px = (board[i]->possibleMoves->data)%8;
                int py = (board[i]->possibleMoves->data-px)/8;
                struct piece* tmp = malloc(sizeof(struct piece));
                tmp->color = board[px+py*8]->color;
                tmp->hasMoved = board[px+py*8]->hasMoved;
                tmp->realPlayerColor = board[px+py*8]->realPlayerColor;
                tmp->role = board[px+py*8]->role;
                tmp->value = board[px+py*8]->value;
                tmp->x = px;
                tmp->y = py;
                tmp->possibleMoves = NULL;
                int hm = 0;
                if(board[i]->hasMoved)
                    hm = 1;
                int moved = move(board,board[i],px,py);
                printf("moved : %i\n",moved);
                if(moved)
                {
                    swap(board[px+py*8],board[Kingx+Kingy*8]);
                    board[i]->hasMoved = hm;
                    if(moved>=1)
                    {
                        board[px+py*8]->color = tmp->color;
                        board[px+py*8]->hasMoved = tmp->hasMoved;
                        board[px+py*8]->realPlayerColor = tmp->realPlayerColor;
                        board[px+py*8]->role = tmp->role;
                        board[px+py*8]->value = tmp->value;
                        board[px+py*8]->x = px;
                        board[px+py*8]->y = py;
                    }
                    freePiece(tmp);
                    check = 0;
                }
                else
                {
                    dangerousmoves[cpt] = board[i]->possibleMoves->data;
                    board[i]->possibleMoves = board[i]->possibleMoves->next;
                    cpt+=1;
                    freePiece(tmp);
                }
            }
            if(check && board[x+y*8]->role!=KNIGHT)
                return cannotProtectKing(board,dangerousmoves,KingColor,cpt,x,y,i);
        }
       
    }
    return check;
}

int cannotProtectKing(struct piece** board,int dangerousmoves[8], int KingColor, int cpt, int x, int y,int Kindex)
{
    for(int i = 0;i<63;i++)
    {
        if(board[i]->color == KingColor && board[i]->role != KING)
        {
            struct piece* p = board[i];
            getMoves(board,p);
            sortMoves(board,p);
            int add;
            if(x-y == board[Kindex]->x)
            {
                if(y<board[Kindex]->y)
                    add = -7;
                else
                    add = 9;
            }
            else if(x == board[Kindex]->x)
            {
                if(y<board[Kindex]->y)
                    add = -8;
                else
                    add = 8;
            }
            else if(y==board[Kindex]->y)
            {
                if(x<board[Kindex]->x)
                    add = -1;
                else
                    add = 1;
            }
            else
            {
                if(y<board[Kindex]->y)
                    add = -9;
                else
                    add = 7;
            }
            while(p->possibleMoves != NULL)
            {
                for(int j = 0; j<cpt; j++)
                {
                    for(int k = 0; dangerousmoves[j]+k<=x+y*8;k+=add)
                    {
                        if(p->possibleMoves->data == dangerousmoves[j]+k)
                        {
                            dangerousmoves[j] = -1;          
                        }  
                    }        
                }
                p->possibleMoves = p->possibleMoves->next;
            }
        }
    }
    for(int i=0;i<cpt;i++)
    {
        if(dangerousmoves[i]!=-1)
        {
            return 1;
        }
    }
    return 0;
}