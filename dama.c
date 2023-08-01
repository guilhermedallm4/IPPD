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
    int column;
    int columnOperation;
    int critical;
} Playing;

Playing play[4];
Playing validatePlay[4];

int lastRowMove = 0;
int lastColumnMove = 0;
int piecesTeamWhite = 0;
int piecesTeamBlack = 0;
int counterAux = 0;

void levantamentPlaying(int player, int rowOrigin, int columnOrigin);
void generateBoard(int board[SIZE_BOARD][SIZE_BOARD]);
void showBoard(int board[SIZE_BOARD][SIZE_BOARD]);
void verifyLevantament(int player);
void movePiece(int indice, int player);
void clear();
void menu();
void startGame();

void levantamentPlaying(int player, int rowOrigin, int columnOrigin){
    
    counter = 0;
    if(board[rowOrigin][columnOrigin] == player){
        if(rowOrigin+1<= SIZE_BOARD){
            if((columnOrigin - 1) >= 0){
                play[counter].row = rowOrigin + 1;
                play[counter].column = columnOrigin -1;
                play[counter].rowOperation = 1;
                play[counter].columnOperation = -1;
                counter++;
                }
                if((columnOrigin + 1) <= SIZE_BOARD){
                    play[counter].row = rowOrigin +1;
                    play[counter].column = columnOrigin + 1;
                    play[counter].rowOperation = 1;
                    play[counter].columnOperation = 1;
                    counter++;
                }
            }
        if((rowOrigin - 1) >= 0){
            if((columnOrigin - 1) >= 0){
                play[counter].row = rowOrigin - 1;
                play[counter].column = columnOrigin - 1;
                play[counter].rowOperation = -1;
                play[counter].columnOperation = -1;
                counter++;
            }
            if((columnOrigin + 1) <= SIZE_BOARD){
                play[counter].row = rowOrigin - 1;
                play[counter].column = columnOrigin + 1;
                play[counter].rowOperation = -1;
                play[counter].columnOperation = 1;
                counter++;
            }
        }
        verifyLevantament(player);
    }
    else{
        if(counter == 0){
            printf("Nao ha jogadas disponiveis");
            printf("\n");
        }
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
                if(player != board[play[i].row][play[i].column]){
                    if(board[play[i].row][play[i].column] == 0){ 
                        validatePlay[counterAux].row = play[i].row;
                        validatePlay[counterAux].column = play[i].column;
                        validatePlay[counterAux].rowOperation = 0;
                        validatePlay[counterAux].columnOperation = 0;
                        validatePlay[counterAux].critical = 0;
                        counterAux++;
                    }
                    else if(board[play[i].row][play[i].column] == BLACKPIECES || board[play[i].row][play[i].column] == WHITEPIECES){
                        int aux = board[play[i].row][play[i].column] - player;
                        if(((play[i].row + play[i].rowOperation) >= 0 && (play[i].row + play[i].rowOperation) < SIZE_BOARD) && ((play[i].column + play[i].columnOperation) >= 0 && (play[i].column + play[i].columnOperation) < SIZE_BOARD)){ 
                        if(aux == 0){
                            
                            if(board[(play[i].row)][(play[i].column)] == BLACKPIECES && board[(play[i].row + play[i].rowOperation)][(play[i].column + play[i].columnOperation)] == 0 ){
                                validatePlay[counterAux].row = (play[i].row + play[i].rowOperation);
                                validatePlay[counterAux].column = (play[i].column + play[i].columnOperation);
                                validatePlay[counterAux].rowOperation = play[i].rowOperation;
                                validatePlay[counterAux].columnOperation = play[i].columnOperation;
                                validatePlay[counterAux].critical = 1;
                                counterAux++;
                            }
                        }
                        else{
                            if(board[(play[i].row)][(play[i].column)] == WHITEPIECES && board[(play[i].row + play[i].rowOperation)][(play[i].column + play[i].columnOperation)] == 0 ){
                                validatePlay[counterAux].row = (play[i].row + play[i].rowOperation);
                                validatePlay[counterAux].column = (play[i].column + play[i].columnOperation);
                                validatePlay[counterAux].rowOperation = play[i].rowOperation;
                                validatePlay[counterAux].columnOperation = play[i].columnOperation;
                                validatePlay[counterAux].critical = 1;
                                counterAux++;
                                
                            }
                        }
                        }
                    }
                    else{
                        printf("\nJogada invalida, selecione novamente\n");
                    }

                }
                
            }
    }
    
}

void movePiece(int indice, int player){
    int aux = board[((validatePlay[indice].row - validatePlay[indice].rowOperation)- validatePlay[indice].rowOperation)][((validatePlay[indice].column - validatePlay[indice].columnOperation)- validatePlay[indice].columnOperation)]; 
    board[((validatePlay[indice].row - validatePlay[indice].rowOperation)- validatePlay[indice].rowOperation)][((validatePlay[indice].column - validatePlay[indice].columnOperation)- validatePlay[indice].columnOperation)] = 0;
    board[(validatePlay[indice].row - validatePlay[indice].rowOperation)][(validatePlay[indice].column - validatePlay[indice].columnOperation)] = 0;
    board[validatePlay[indice].row][validatePlay[indice].column] = player;
    lastRowMove = validatePlay[indice].row;
    lastColumnMove = validatePlay[indice].column;
    clear();
    if(player == WHITEPIECES){
        piecesTeamWhite++;
    }
    else if(player == BLACKPIECES){
        piecesTeamBlack++;
    }
    else{
        printf("\nNenhuma peca comida\n");
    }
    showBoard(board);
}

int main(){
    Playing *play;   
    generateBoard(board);
    board[4][3] = 20;
    board[3][4] = 10;
    board[3][2] = 10;
    board[2][5] = 0;
    board[0][3] = 0;
    board[2][1] = 0;
    flag = 1;
    showBoard(board);
    printf("\n");
    printf("\n");
    lastRowMove = 4;
    lastColumnMove = 3;
    int verifyPiece = 0;
    do{ 
        verifyPiece = piecesTeamBlack;
        levantamentPlaying(BLACKPIECES, lastRowMove, lastColumnMove);
        for(int i = 0; i<counterAux;++i){
            if(validatePlay[i].critical == 1){
                printf("\nJogada valida\n");
                printf("\nLinha: %d\nColuna: %d\n", validatePlay[i].row, validatePlay[i].column);
                movePiece(i, BLACKPIECES);
                break;
            }
        }
    }while(verifyPiece != piecesTeamBlack);
    printf("Quantidade de peças comidas pelo time preto: %d", piecesTeamBlack);
}


void menu(){
    int option = 0;
    do{
    printf("Seja bem vindo ao jogo de Dama, digite sua opcao: \n");
    printf("1- Jogar");
    printf("2 - Sair");
    scanf("%d", &option);
    printf("\n");
    }while(option > 2 && option < 1);
    int optionPiece = 0; 
    if(option == 1){
        do{
        printf("Escolha a cor que deseja jogar: \n 1- Branca \n 2- Preto\n");
        scanf("%d", &optionPiece);
        }while(optionPiece > 2 && optionPiece < 1);
        switch (option)
        {
        case 1:
            printf("\nJogador escolheu as peças Brancas\n");
            break;
        case 2:
            printf("\nJogador escolheu as peças Pretas\n");
            break;
        default:
            printf("Opcao invalida");
            break;
        }
    }
    else{
        printf("\nSaindo do jogo!\n");
        exit(0);
    }
}

void clear(){
    for(int i = 0; i < counterAux; i++){
        validatePlay[i].row = 0;
        validatePlay[i].column = 0;
        validatePlay[i].rowOperation = 0;
        validatePlay[i].columnOperation = 0;
        validatePlay[i].critical = 0;
        counterAux = 0;
    }
}

void startGame(){

}
