#include "algo.h"



float* playMove(struct piece** board, enum Color ColorPlayer, int turn){
    char FEN=(getFEN(board, ColorPlayer));
    int res=0;
    int res2=0;
    int res3=0;
    int val=0;
    int color=0;
    float* list;
    if (ColorPlayer==WHITE){
        color=1;
    }
    if (turn<5){
        list=database(FEN);
        if (list[1]!=-1){
            return list;
        }
        else{
            list = miniMax(board, 3, -1000, 1000, color);
        }
    }
    else{
        list = miniMax(board, 3, -1000, 1000, color);
    }
    return list;
}


float* miniMax(struct piece** board, int depth, float pruninga, float pruningb, int whiteturn){
    float* list=malloc(4*sizeof(float));
    if (depth==0){
        list[0]=getEval(board, whiteturn);
        list[1]=NULL;
        list[2]=NULL;
        list[3]=NULL;
        return list;
    }
    struct piece*** listOfBoards = malloc(64*sizeof(struct piece));
    int datalist[300];
    int datalistb[128];
    int cpt=0;
    int destcoord=0;
    int startcoordx=0;
    int startcoordy=0;
    float* list2=malloc(4*sizeof(float));

    if (whiteturn){
        int maxEval=-1000;
        for (int i=0;i<64;i++){
            if (board[i]->role!=0){
                getMoves(board,board[i]);
                sortMoves(board,board[i]);
                for (struct list* moves = board[i]->possibleMoves;moves!=NULL,moves=moves->next){
                    struct piece** newBoard = malloc(64*sizeof(struct piece));
                    int j = 0;
                    for(struct piece p = board[j], j<64,j++)
                    {
                        newBoard[j] = malloc(sizeof(struct piece));
                        newBoard[j]->role = p->role;
                        newBoard[j]->x = p->x;
                        newBoard[j]->y = p->y;
                        newBoard[j]->color = p->color;
                        newBoard[j]->value = p->value;
                        newBoard[j]->realPlayerColor = p->realPlayerColor;
                        newBoard[j]->hasMoved = p->hasMoved;
                    }
                    int dest_x = moves->data%8;
                    int dest_y = moves->data/8;
                    move(struct piece** newBoard, struct piece* newBoard[i], int dest_x, int dest_y);
                    datalist[cpt]=moves->data;
                    datalistb[2*cpt]=board[i]->x;
                    datalistb[2*cpt+1]=board[i]->y;
                    cpt++;
                    realloc(listOfBoards,cpt*64*sizeof(struct piece));
                }
            }
        }
        for (int k=0;k<cpt;k++){
            position=listOfBoards[k];
            list2=minimax(position,depth-1, pruninga, pruningb, 0);
            if (list2[0]>maxEval){
                maxEval=list2[0];
                destcoord=datalist[k];
                startcoordx=datalistb[k];
                startcoordy=datalistb[k+1];
            }
            maxEval=max(maxEval,list2[0]);
            pruninga=max(pruninga,list2[0]);
            if (pruningb<=pruninga){
                break;
            }
        }
        list[0]=maxEval;
        list[1]=destcoord;
        list[2]=startcoordx;
        list[3]=startcoordy;
        return list;
    }
    else{
        int minEval=1000;
        for (int i=0;i<64;i++){
            if (board[i]->role!=0){
                getMoves(board,board[i]);
                sortMoves(board,board[i]);
                for (struct list* moves = board[i]->possibleMoves;moves!=NULL,moves=moves->next){
                    struct piece** newBoard = malloc(64*sizeof(struct piece));
                    int j = 0;
                    for(struct piece p = board[j], j<64,j++)
                    {
                        newBoard[j] = malloc(sizeof(struct piece));
                        newBoard[j]->role = p->role;
                        newBoard[j]->x = p->x;
                        newBoard[j]->y = p->y;
                        newBoard[j]->color = p->color;
                        newBoard[j]->value = p->value;
                        newBoard[j]->realPlayerColor = p->realPlayerColor;
                        newBoard[j]->hasMoved = p->hasMoved;
                    }
                    int dest_x = moves->data%8
                    int dest_y = moves->data/8
                    move(struct piece** newBoard, struct piece* newBoard[i], int dest_x, int dest_y);
                    datalist[cpt]=moves->data;
                    datalistb[2*cpt]=board[i]->x;
                    datalistb[2*cpt+1]=board[i]->y;
                    cpt++;
                    realloc(listOfBoards,cpt*64*sizeof(struct piece));
                }
            }
        }
        for (int k=0;k<cpt;k++){
            position=listOfBoards[k];
            list2=minimax(position,depth-1,pruninga, pruningb, 1);
            if (list2[0]<minEval){
                maxEval=list2[0];
                destcoord=datalist[k];
                startcoordx=datalistb[k];
                startcoordy=datalistb[k+1];
            }
            minEval=min(minEval,eval);
            pruningb=min(pruningb,eval);
            if (pruningb<=pruninga){
                break;
            }
        }
        list[0]=minEval;
        list[1]=destcoord;
        list[2]=startcoordx;
        list[3]=startcoordy;
        return list;
    }
}