#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NEGATIVEINFINITY -1000
#define POSITIVEINFINITY 1000
#define SIZE_BOARD 8
#define WHITEPIECES 10
#define BLACKPIECES 20
#define IMPOSSIBLEMOVE -1
#define EMPTY_HOUSE 0
#define SIZEPLAYING 4

int board[SIZE_BOARD][SIZE_BOARD];
int counter;
int flag = 0;

typedef struct{
    int row;
    int rowOperation;
    int colum;
    int columOperation;

} Playing;

Playing play[4];
Playing validatePlay[4];

int lastRowMove = 0;
int lastColumnMove = 0;
int piecesTeamWhite = 0;
int piecesTeamBlack = 0;
int counterAux = 0;

void levantamentPlaying(int player, int rowOrigin, int columOrigin);
void generateBoard(int board[SIZE_BOARD][SIZE_BOARD]);
void showBoard(int board[SIZE_BOARD][SIZE_BOARD]);
void verifyLevantament(int player);
void verifyPieces(int player, int rowOrigin, int columnOrigin, int i, int operationRow, int operationColumn);


void levantamentPlaying(int player, int rowOrigin, int columOrigin){
    
    counter = 0;
    if(player == WHITEPIECES){
        if(board[rowOrigin][columOrigin] == player){
            if(rowOrigin+1<= SIZE_BOARD){
                if((columOrigin - 1) >= 0){
                    play[counter].row = rowOrigin + 1;
                    play[counter].colum = columOrigin -1;
                    play[counter].rowOperation = 1;
                    play[counter].columOperation = -1;
                    //printf("1: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                    counter++;
                }
                if((columOrigin + 1) <= SIZE_BOARD){
                    play[counter].row = rowOrigin +1;
                    play[counter].colum = columOrigin + 1;
                    play[counter].rowOperation = 1;
                    play[counter].columOperation = 1;
                    //printf("2: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                    counter++;
                }
            }
            if((rowOrigin - 1) >= 0){
                if((columOrigin - 1) >= 0){
                    play[counter].row = rowOrigin - 1;
                    play[counter].colum = columOrigin - 1;
                    play[counter].rowOperation = -1;
                    play[counter].columOperation = -1;
                    //printf("3: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                    counter++;
                }
                if((columOrigin + 1) <= SIZE_BOARD){
                        play[counter].row = rowOrigin - 1;
                        play[counter].colum = columOrigin + 1;
                        play[counter].rowOperation = -1;
                        play[counter].columOperation = 1;
                        //printf("4: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                        counter++;
                }
            }
        }
        else{
            if(counter == 0){
                flag = 0;
                printf("Nao ha jogadas disponiveis");
                printf("\n");
            }
        }
    }
    else if(player == BLACKPIECES){
                if(board[rowOrigin][columOrigin] == player){
            if(rowOrigin+1<= SIZE_BOARD){
                if((columOrigin - 1) >= 0){
                    play[counter].row = rowOrigin + 1;
                    play[counter].colum = columOrigin -1;
                    play[counter].rowOperation = 1;
                    play[counter].columOperation = -1;
                    //printf("1: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                    counter++;
                }
                if((columOrigin + 1) <= SIZE_BOARD){
                    play[counter].row = rowOrigin +1;
                    play[counter].colum = columOrigin + 1;
                    play[counter].rowOperation = 1;
                    play[counter].columOperation = 1;
                    //printf("2: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                    counter++;
                }
            }
            if((rowOrigin - 1) >= 0){
                if((columOrigin - 1) >= 0){
                    play[counter].row = rowOrigin - 1;
                    play[counter].colum = columOrigin - 1;
                    play[counter].rowOperation = -1;
                    play[counter].columOperation = -1;
                    //printf("3: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                    counter++;
                }
                if((columOrigin + 1) <= SIZE_BOARD){
                        play[counter].row = rowOrigin - 1;
                        play[counter].colum = columOrigin + 1;
                        play[counter].rowOperation = -1;
                        play[counter].columOperation = 1;
                        //printf("4: \n Jogada linha: %d\nJogada Coluna:%d\n", play[counter].row, play[counter].colum);
                        counter++;
                }
            }
        }
        else{
            if(counter == 0){
                flag = 0;
                printf("Nao ha jogadas disponiveis");
                printf("\n");
            }
        }
    }
    else{
        printf("Opção invalida");
    }
}

void generateBoard(int board[SIZE_BOARD][SIZE_BOARD]){
    int j = 0;
    #pragma omp parallel
    {

        #pragma omp for schedule(dynamic)
        for(int i = 0; i<SIZE_BOARD;i++){
            j = omp_get_thread_num();
            if(i % 2 == 0){
                if(i == 0 || i == 2){
                    board[i][1] = WHITEPIECES;
                    board[i][3] = WHITEPIECES;
                    board[i][5] = WHITEPIECES;
                    board[i][7] = WHITEPIECES;
                    board[i][0] = IMPOSSIBLEMOVE;
                    board[i][2] = IMPOSSIBLEMOVE;
                    board[i][4] = IMPOSSIBLEMOVE;
                    board[i][6] = IMPOSSIBLEMOVE;
                }
                else if(i == 6){
                    board[i][1] = BLACKPIECES;
                    board[i][3] = BLACKPIECES;
                    board[i][5] = BLACKPIECES;
                    board[i][7] = BLACKPIECES;
                    board[i][0] = IMPOSSIBLEMOVE;
                    board[i][2] = IMPOSSIBLEMOVE;
                    board[i][4] = IMPOSSIBLEMOVE;
                    board[i][6] = IMPOSSIBLEMOVE;
                }
                else{
                    board[i][1] = EMPTY_HOUSE;
                    board[i][3] = EMPTY_HOUSE;
                    board[i][5] = EMPTY_HOUSE;
                    board[i][7] = EMPTY_HOUSE;
                    board[i][0] = IMPOSSIBLEMOVE;
                    board[i][2] = IMPOSSIBLEMOVE;
                    board[i][4] = IMPOSSIBLEMOVE;
                    board[i][6] = IMPOSSIBLEMOVE;
                }
            }
            else{
                if(i == 1){
                    board[i][1] = IMPOSSIBLEMOVE;
                    board[i][3] = IMPOSSIBLEMOVE;
                    board[i][5] = IMPOSSIBLEMOVE;
                    board[i][7] = IMPOSSIBLEMOVE;
                    board[i][0] = WHITEPIECES;
                    board[i][2] = WHITEPIECES;
                    board[i][4] = WHITEPIECES;
                    board[i][6] = WHITEPIECES;
                }
                else if(i == 5 || i == 7){
                    board[i][1] = IMPOSSIBLEMOVE;
                    board[i][3] = IMPOSSIBLEMOVE;
                    board[i][5] = IMPOSSIBLEMOVE;
                    board[i][7] = IMPOSSIBLEMOVE;
                    board[i][0] = BLACKPIECES;
                    board[i][2] = BLACKPIECES;
                    board[i][4] = BLACKPIECES;
                    board[i][6] = BLACKPIECES;
                }
                else{
                    board[i][0] = EMPTY_HOUSE;
                    board[i][2] = EMPTY_HOUSE;
                    board[i][4] = EMPTY_HOUSE;
                    board[i][6] = EMPTY_HOUSE;
                    board[i][1] = IMPOSSIBLEMOVE;
                    board[i][3] = IMPOSSIBLEMOVE;
                    board[i][5] = IMPOSSIBLEMOVE;
                    board[i][7] = IMPOSSIBLEMOVE;
                }

            }
        }
    }
}

void showBoard(int board[SIZE_BOARD][SIZE_BOARD]){
        for(int i = 0; i< SIZE_BOARD;i++){
            for(int j = 0; j <SIZE_BOARD;j++ ){
                printf(" %d\t", board[i][j]);
            }
            printf("\n");
        }
}

void verifyLevantament(int player){
    counterAux = 0;
    #pragma omp parallel 
    {
        #pragma omp for schedule(dynamic)
            for(int i = 0; i<counter; ++i){
                //printf("\nPeca no tabuleiro: %d \n", board[play[i].row][play[i].colum]);
                if(player != board[play[i].row][play[i].colum]){
                    if(board[play[i].row][play[i].colum] == 0){ 
                        validatePlay[counterAux].row = play[i].row;
                        validatePlay[counterAux].colum = play[i].colum;
                        counterAux++;
                    }
                    else if(board[play[i].row][play[i].colum] == BLACKPIECES || board[play[i].row][play[i].colum] == WHITEPIECES){
                        int aux = board[play[i].row][play[i].colum] - WHITEPIECES;
                        if(aux == 0){
                            verifyPieces(WHITEPIECES, play[i].row, play[i].colum, i, play[i].rowOperation, play[i].columOperation);
                            if(counterAux == 0){
                                #pragma omp cancel for
                                lastRowMove = (play[i].row+play[i].rowOperation);
                                lastColumnMove = (play[i].colum+play[i].columOperation);
                            }
                        }
                        else{
                            verifyPieces(BLACKPIECES, play[i].row, play[i].colum, i, play[i].rowOperation, play[i].columOperation); 
                            if(counterAux == 0){
                                #pragma omp cancel for
                                lastRowMove = (play[i].row+play[i].rowOperation);
                                lastColumnMove = (play[i].colum+play[i].columOperation);
                            }
                        }
                    }

                }
                
            }
            
//#pragma omp cancellation point for
        /*#pragma omp for schedule(dynamic)
            for(int i = 0; i<counterAux;++i){
                printf("%d: \nJogada linha: %d\nJogada Coluna:%d\n", i+1, validatePlay[i].row, validatePlay[i].colum);
            }*/
    }
    //return verify;
}

void verifyPieces(int player, int rowOrigin, int columnOrigin, int i, int operationRow, int operationColumn){
    if(board[rowOrigin+(operationRow)][columnOrigin+(operationColumn)] == EMPTY_HOUSE){
            int aux = board[rowOrigin-(operationRow)][columnOrigin-(operationColumn)];
            board[rowOrigin][columnOrigin] = 0;
            board[rowOrigin+(operationRow)][columnOrigin+(operationColumn)] = aux;
            board[rowOrigin-(operationRow)][columnOrigin-(operationColumn)] = 0;
            piecesTeamWhite++;
            counterAux = 0;
            flag = 1;
            return ;
    }
} 

int main(){
    Playing *play;   
    generateBoard(board);
    board[4][3] = 20;
    board[3][4] = 10;
    board[2][5] = 0;
    board[0][3] = 0;
    board[2][1] = 0;
    flag = 1;
    showBoard(board);
    printf("\n");
    printf("\n");
    lastRowMove = 4;
    lastColumnMove = 3;
    while(flag == 1){
        levantamentPlaying(20, lastRowMove, lastColumnMove);
        verifyLevantament(20);
        showBoard(board);
        printf("\n");
        printf("\n");
        printf("FLAG: %d\n", flag);
    }
    printf("\nQuantidade de pecass Capturadas pelo time branco: %d\n", piecesTeamWhite);
    
}
