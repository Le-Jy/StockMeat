#include "Game/game.h"

void main()
{
    struct list* piece;
    struct list** board;
    getMoves(board,piece);
    sortMoves(board,piece);
    for(struct list* moves = piece->possibleMoves;moves!=NULL;moves=moves->next)
    {
        printf("%i\n",moves->data);
    }
}