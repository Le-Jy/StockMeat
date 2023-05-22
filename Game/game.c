#include "game.h"

void initParty(struct piece** board, int color)
{
    initBoard(board,color);
}

void printColorTurn(unsigned long turn)
{
    if(turn%2 == 0)
        printf("White's turn\n");
    else
        printf("Black's turn\n");
    return;
}

int* choosePiece()
{
    printf("Choose a piece to move\n");
    int* line = malloc(2*sizeof(int));
    printf("x:");
    scanf("%d",&line[0]);
    printf("y:");
    scanf("%d",&line[1]);
    return line;
}

int* chooseDest()
{
    printf("Choose a destination\n");
    int* line = malloc(2*sizeof(int));
    printf("x:");
    scanf("%d",&line[0]);
    printf("y:");
    scanf("%d",&line[1]);
    return line;
}

int isValidPiece(int* coord, struct piece** board, int turn)
{
    int x = coord[0];
    int y = coord[1];
    if((turn%2 == 0 && board[x + 8*y]->color == WHITE) || (turn%2 == 1 && board[x + 8*y]->color == BLACK))
        return 1;
    return 0;
}

int isCheckinG(struct piece** board, int x, int y)
{
    getMoves(board,board[x+y*8],board[x+y*8]->realPlayerColor);
    
    printf("test\n");
    while(board[x+y*8]->possibleMoves!=NULL)
    {
        
        printf("role : %i\n",board[x+y*8]->possibleMoves->data);
        if(board[board[x+y*8]->possibleMoves->data]->role == KING && board[board[x+y*8]->possibleMoves->data]->color != board[x+y*8]->color)
        {
            return 1;
        }
        board[x+y*8]->possibleMoves = board[x+y*8]->possibleMoves->next;
    }
    return 0;
}