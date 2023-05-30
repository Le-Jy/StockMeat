#include "fen.h"

char* getFEN(struct piece** board, enum ColorPlayer){
    char FEN="";
    int blank=0;
    int pieceHere=0;
    int castleRes1;
    int castleRes2;
    int castleRes3;
    int castleRes4;
    for (size_t i=0;i<8;i++){
        if (i>0){
            strcat(FEN,'/');
        }
        for (size_t j=0;j<8;j++){
            piecehere=0;
            for elm in piece{
                if (elm->x==i && elm->y==j){
                    piecehere=1;
                    if (blank>0){
                        strcat(FEN,blank);
                        blank=0;
                    }
                    if (elm->role==PAWN){
                        if (elm->color==BLACK){
                            strcat(FEN,'p');
                        }
                        else{
                            strcat(FEN,'P');
                        }
                    }
                    if (elm->role==KNIGHT){
                        if (elm->color==BLACK){
                            strcat(FEN,'n');
                        }
                        else{
                            strcat(FEN,'N');
                        }
                    }
                    if (elm->role==BISHOP){
                        if (elm->color==BLACK){
                            strcat(FEN,'b');
                        }
                        else{
                            strcat(FEN,'B');
                        }
                    }
                    if (elm->role==ROOK){
                        if (elm->color==BLACK){
                            strcat(FEN,'r');
                        }
                        else{
                            strcat(FEN,'R');
                        }
                    }
                    if (elm->role==QUEEN){
                        if (elm->color==BLACK){
                            strcat(FEN,'q');
                        }
                        else{
                            strcat(FEN,'Q');
                        }
                    }
                    if (elm->role==KING){
                        if (elm->color==BLACK){
                            strcat(FEN,'k');
                            castleRes3=canShortCastle((struct piece** board,struct piece* elm));
                            castleRes4=canLongCastle((struct piece** board,struct piece* elm));
                        }
                        else{
                            strcat(FEN,'K');
                            castleRes1=canShortCastle((struct piece** board,struct piece* elm));
                            castleRes2=canLongCastle((struct piece** board,struct piece* elm));
                        }
                    }
                }
            }
            if (piecehere==0){
                blank++;
            }
        }
    }
    FEN.append(' ');
    if (ColorPlayer==WHITE){
        strcat(FEN,'w');
    }
    else{
        strcat(FEN,'b');
    }
    strcat(FEN,' ');
    check=1;
    if (castleRes1==1){
        strcat(FEN,'K');
        check=0;
    }
    if (castleRes2==1){
        strcat(FEN,'Q');
        check=0;
    }
    if (castleRes3==1){
        strcat(FEN,'k');
        check=0;
    }
    if (castleRes4==1){
        strcat(FEN,'q');
        check=0;
    }
    if (check==1){
        strcat(FEN,'-');
    }
    strcat(FEN,' ');
    strcat(FEN,'-');
    strcat(FEN,' ');
    strcat(FEN,'0');
    strcat(FEN,' ');
    strcat(FEN,'1');
    return FEN;
}

float* database(char FEN){
    int randnum=0;
    float* list=malloc(4*sizeof(float));
    list[0]=-1;
    list[1]=-1;
    list[2]=-1;
    list[3]=-1;
    
    if (strcmp(FEN,"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=36;
            list[2]=4;
            list[3]=6;
        }
        else{
            list[1]=35;
            list[2]=3;
            list[3]=6;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=28;
            list[2]=4;
            list[3]=1;
        }
        else{
            list[1]=26;
            list[2]=2;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=45;
            list[2]=6;
            list[3]=7;
        }
        else{
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=18;
            list[2]=1;
            list[3]=0;
        }
        else{
            list[1]=19;
            list[2]=3;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"r1bqkbnr/pppp1ppp/2n5/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=21;
            list[2]=6;
            list[3]=0;
        }
        else{
            list[1]=19;
            list[2]=3;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=43;
            list[2]=3;
            list[3]=6;
        }
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=26;
            list[2]=5;
            list[3]=0;
        }
        else{
            list[1]=36;
            list[2]=5;
            list[3]=2;
        }
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1ppp/2n5/4p3/2B1n3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 1")==0){
        list[1]=36;
        list[2]=2;
        list[3]=5;
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1ppp/2n5/4p3/2B1N3/5N2/PPPP1PPP/R1BQK2R b KQkq - 0 1")==0){
        list[1]=27;
        list[2]=3;
        list[3]=1;
    }

    if (strcmp(FEN,"r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=43;
            list[2]=3;
            list[3]=6;
        }
        else{
            list[1]=63;
            list[2]=4;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/3P1N2/PPP2PPP/RNBQK2R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=26;
            list[2]=5;
            list[3]=0;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/3P1N2/PPP2PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=2;
            list[3]=6;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1pp1/2n2n1p/4p3/2B1P3/3P1N2/PPP2PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=2;
            list[3]=6;
        }
        else{
            list[1]=51;
            list[2]=1;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/ppp2ppp/2np4/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=2;
            list[3]=6;
        }
        else{
            list[1]=35;
            list[2]=3;
            list[3]=6;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/ppp2ppp/2np4/4p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=12;
            list[2]=5;
            list[3]=0;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/ppp2pp1/2np3p/4p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=35;
            list[2]=3;
            list[3]=6;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqk1nr/ppp1bppp/2np4/4p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=41;
            list[2]=3;
            list[3]=7;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/ppp2ppp/2np4/4p3/2BPP3/5N2/PPP2PPP/RNBQK2R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=35;
            list[2]=4;
            list[3]=3;
        }
        else{
            list[1]=21;
            list[2]=6;
            list[3]=0;
        }
    }

    if (strcmp(FEN,"r1bqkb1r/ppp2ppp/2np1n2/4p3/2BPP3/5N2/PPP2PPP/RNBQK2R w KQkq - 0 1")==0){
        list[1]=27;
        list[2]=4;
        list[3]=3;
    }

    if (strcmp(FEN,"r1bqkbnr/ppp2ppp/2np4/8/2BpP3/5N2/PPP2PPP/RNBQK2R w KQkq - 0 1")==0){
        list[1]=35;
        list[2]=5;
        list[3]=5;
    }

    if (strcmp(FEN,"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R b KQkq - 0 1")==0){
        list[1]=21;
        list[2]=6;
        list[3]=0;
    }

    if (strcmp(FEN,"r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkbnr/ppp2ppp/3p4/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=47;
            list[2]=7;
            list[3]=6;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/ppp2ppp/3p4/4p3/4P3/5N1P/PPPP1PP1/RNBQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=21;
            list[2]=6;
            list[3]=0;
        }
        else{
            list[1]=26;
            list[2]=2;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/pp3ppp/3p4/2p1p3/4P3/5N1P/PPPP1PP1/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkbnr/pp3ppp/3p4/2p1p3/2B1P3/5N1P/PPPP1PP1/RNBQK2R b KQkq - 0 1")==0){
        list[1]=21;
        list[2]=6;
        list[3]=0;
    }

    if (strcmp(FEN,"rnbqkb1r/pp3ppp/3p1n2/2p1p3/2B1P3/5N1P/PPPP1PP1/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=30;
            list[2]=5;
            list[3]=5;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2ppp/3p1n2/4p3/4P3/5N1P/PPPP1PP1/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=35;
            list[2]=3;
            list[3]=6;
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2ppp/3p1n2/4p3/3PP3/5N1P/PPP2PP1/RNBQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=35;
            list[2]=4;
            list[3]=3;
        }
        else{
            list[1]=12;
            list[2]=5;
            list[3]=0;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2ppp/3p1n2/8/3pP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=35;
        list[2]=3;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqk2r/ppp1bppp/3p1n2/4p3/3PP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=44;
            list[2]=2;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/ppp2ppp/3p4/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R b KQkq - 0 1")==0){
        list[1]=21;
        list[2]=6;
        list[3]=0;
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2ppp/3p1n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1")==0){ 
        list[1]=32;
        list[2]=0;
        list[3]=6;
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2ppp/3p1n2/4p3/P3P3/2N2N2/1PPP1PPP/R1BQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
        else{
            list[1]=26;
            list[2]=2;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2pp1/3p1n1p/4p3/P3P3/2N2N2/1PPP1PPP/R1BQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=47;
            list[2]=7;
            list[3]=6;
        }
        else{
            list[1]=34;
            list[2]=5;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/pp3ppp/3p1n2/2p1p3/P3P3/2N2N2/1PPP1PPP/R1BQKB1R w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1")==0){
        list[1]=45;
        list[2]=6;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=20;
            list[2]=4;
            list[3]=1;
        }
        else{
            list[1]=18;
            list[2]=1;
            list[3]=0;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/pp1p1ppp/4p3/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=35;
        list[2]=3;
        list[3]=6;
    }

    if (strcmp(FEN,"rnbqkbnr/pp1p1ppp/4p3/2p5/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 1")==0){
        list[1]=35;
        list[2]=2;
        list[3]=3;
    }

    if (strcmp(FEN,"rnbqkbnr/pp1p1ppp/4p3/8/3pP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=35;
        list[2]=3;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkbnr/pp1p1ppp/4p3/8/3QP3/5N2/PPP2PPP/RNB1KB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=21;
            list[2]=6;
            list[3]=0;
        }
        else{
            list[1]=18;
            list[2]=1;
            list[3]=0;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/pp1p1ppp/4pn2/8/3QP3/5N2/PPP2PPP/RNB1KB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=43;
            list[2]=3;
            list[3]=4;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/8/3QP3/5N2/PPP2PPP/RNB1KB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=44;
            list[2]=3;
            list[3]=4;
        }
        else{
            list[1]=43;
            list[2]=3;
            list[3]=4;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp1ppppp/2n5/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            rlist[1]=25;
            list[2]=5;
            list[3]=7;
        }
        else{
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp1ppppp/2n5/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=19;
            list[2]=3;
            list[3]=1;
        }
        else{
            list[1]=20;
            list[2]=4;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp2pppp/2np4/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp2pppp/2np4/1Bp5/4P3/2N2N2/PPPP1PPP/R1BQK2R b KQkq - 0 1")==0){
        list[1]=20;
        list[2]=4;
        list[3]=1;
    }

    if (strcmp(FEN,"r1bqkbnr/pp2pppp/2np4/1Bp5/4P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 0 1")==0){
        list[1]=20;
        list[2]=4;
        list[3]=1;
    }

    if (strcmp(FEN,"r1bqkbnr/pp3ppp/2npp3/1Bp5/4P3/5N2/PPPP1PPP/RNBQ1RK1 w kq - 0 1")==0){
        list[1]=42;
        list[2]=1;
        list[3]=7;
    }

    if (strcmp(FEN,"r1bqkbnr/pp3ppp/2npp3/1Bp5/4P3/2N2N2/PPPP1PPP/R1BQK2R w kq - 0 1")==0){
        list[1]=23;
        list[2]=7;
        list[3]=1;
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w kq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=23;
            list[2]=7;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 0 1")==0){
        list[1]=19;
        list[2]=3;
        list[3]=1;
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/2N2N2/PPPP1PPP/R1BQK2R b kq - 0 1")==0){
        list[1]=19;
        list[2]=3;
        list[3]=1;
    }

    if (strcmp(FEN,"r1bqkbnr/pp1ppppp/2n5/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R b kq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=19;
            list[2]=3;
            list[3]=1;
        }
        else{
            list[1]=20;
            list[2]=4;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp2pppp/2np4/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R w kq - 0 1")==0){
        list[1]=25;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R w kq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=25;
            list[2]=5;
            list[3]=7;
        }
        else{
            list[1]=35;
            list[2]=3;
            list[3]=6;
        }
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/2p5/3PP3/2N2N2/PPP2PPP/R1BQKB1R b kq - 0 1")==0){
        list[1]=35;
        list[2]=2;
        list[3]=3;
    }

    if (strcmp(FEN,"r1bqkbnr/pp1p1ppp/2n1p3/8/3pP3/2N2N2/PPP2PPP/R1BQKB1R w kq - 0 1")==0){
        list[1]=35;
        list[2]=5;
        list[3]=5;
    }

    if (strcmp(FEN,"rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=27;
            list[2]=3;
            list[3]=1;
        }
        else{
            list[1]=21;
            list[2]=6;
            list[3]=0;
        }
    }

    if (strcmp(FEN,"rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=2;
        list[3]=6;
    }

    if (strcmp(FEN,"rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=2;
        list[3]=6;
    }

    if (strcmp(FEN,"rnbqkb1r/pppppppp/5n2/8/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1")==0){
        list[1]=27;
        list[2]=3;
        list[3]=1;
    }

    if (strcmp(FEN,"rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1")==0){
        list[1]=21;
        list[2]=6;
        list[3]=0;
    }

    if (strcmp(FEN,"rnbqkb1r/ppp1pppp/5n2/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=45;
            list[2]=6;
            list[3]=7;
        }
        else{
            list[1]=27;
            list[2]=2;
            list[3]=4;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/ppp1pppp/5n2/3P4/3P4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1")==0){
        list[1]=27;
        list[2]=3;
        list[3]=0;
    }

    if (strcmp(FEN,"rnb1kb1r/ppp1pppp/5n2/3q4/3P4/8/PP2PPPP/RNBQKBNR w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=45;
            list[2]=6;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"rnb1kb1r/ppp1pppp/5n2/3q4/3P4/2N5/PP2PPPP/R1BQKBNR b KQkq - 0 1")==0){
        list[1]=24;
        list[2]=3;
        list[3]=3;
    }

    if (strcmp(FEN,"rnb1kb1r/ppp1pppp/5n2/3q4/3P4/5N2/PP2PPPP/RNBQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=20;
            list[2]=4;
            list[3]=1;
        }
        else{
            list[1]=18;
            list[2]=1;
            list[3]=0;
        }
    }

    if (strcmp(FEN,"r1b1kb1r/ppp1pppp/2n2n2/3q4/3P4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=42;
        list[2]=1;
        list[3]=7;
    }

    if (strcmp(FEN,"rnb1kb1r/ppp2ppp/4pn2/3q4/3P4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=42;
        list[2]=1;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkb1r/ppp1pppp/5n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=34;
            list[2]=3;
            list[3]=3;
        }
        else{
            list[1]=18;
            list[2]=2;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/ppp1pppp/5n2/8/2pP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=44;
        list[2]=4;
        list[3]=6;
    }

    if (strcmp(FEN,"rnbqkb1r/ppp1pppp/5n2/8/2pP4/4PN2/PP3PPP/RNBQKB1R b KQkq - 0 1")==0){    
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=20;
            list[2]=4;
            list[3]=1;
        }
        else{
            list[1]=16;
            list[2]=0;
            list[3]=1;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/ppp2ppp/4pn2/8/2pP4/4PN2/PP3PPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkb1r/1pp1pppp/p4n2/8/2pP4/4PN2/PP3PPP/RNBQKB1R w KQkq - 0 1")==0){
        list[1]=34;
        list[2]=5;
        list[3]=7;
    }

    if (strcmp(FEN,"rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=27;
            list[2]=2;
            list[3]=4;
        }
        else{
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R b KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=34;
            list[2]=3;
            list[3]=3;
        }
        else{
            list[1]=20;
            list[2]=4;
            list[3]=2;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/pp2pppp/2p2n2/8/2pP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 1")==0){
        list[1]=36;
        list[2]=4;
        list[3]=6;
    }

    if (strcmp(FEN,"rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=44;
            list[2]=4;
            list[3]=6;
        }
        else{
            list[1]=27;
            list[2]=2;
            list[3]=4;
        }
    }

    if (strcmp(FEN,"rnbqkb1r/pp2pppp/2p2n2/3P4/3P4/5N2/PP2PPPP/RNBQKB1R b KQkq - 0 1")==0){
        list[1]=27;
        list[2]=2;
        list[3]=2;
    }

    if (strcmp(FEN,"rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 1")==0){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            list[1]=42;
            list[2]=1;
            list[3]=7;
        }
        else{
            list[1]=37;
            list[2]=2;
            list[3]=7;
        }
    }
    return list;
}