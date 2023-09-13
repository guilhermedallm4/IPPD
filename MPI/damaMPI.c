/*CODIGO DESENVOLVIDO POR:
GUILHERME DALLMANN LIMA
JOAO PAULO BRITO DE ALMEIDA*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <mpi.h>

#define SIZE_BOARD 8
#define WHITEPIECES 10
#define BLACKPIECES 20
#define IMPOSSIBLEMOVE -1
#define EMPTY_HOUSE 0
#define SIZEPLAYING 4

int board[SIZE_BOARD][SIZE_BOARD];
int counter;
int flag = 0;
int playerTurn = 0;
int countTurn = 0;
int totalMovimentsPossible = 0;

typedef struct{
    int row;
    int rowOperation;
    int column;
    int columnOperation;
    int critical;
} Playing;

Playing play[4];
Playing validatePlay[4];
int vectorRow[2];
int vectorColumn[2];
int processRank = 0;
int rank = 0;
int lastRowMove = 0;
int lastColumnMove = 0;
int piecesTeamWhite = 0;
int piecesTeamBlack = 0;
int counterAux = 0;
int criticalFlag = 0;
int counterGet = 0;

void levantamentPlaying(int player, int rowOrigin, int columnOrigin);
void generateBoard(int board[SIZE_BOARD][SIZE_BOARD]);
void showBoard(int board[SIZE_BOARD][SIZE_BOARD]);
void verifyLevantament(int player);
void movePieceSeveralMoviment(int indice, int player);
void clear();
int menu();
void sendData(int processRank);
void recvData(int processRank);
int startGame(int playerOne, int playerMachine);
int moveGetPiece(int player);
int playingMachine(int playerMachine);
int playingPlayer(int playerOne);
int selectPlay(int playerOne);
void verifyPiecesForPlay(int player);
int movePlayerOnePieceMoviment(int indice);
int verifyPiecePlayer(int player);
void introduction();

void introduction() {
    printf(" \n\n\n");
    printf("_  _  _  _                 _              _           _              _                _  _  _  _     \n");
    printf("(_)(_)(_)(_)              _(_)_           (_) _     _ (_)           _(_)_            _(_)(_)(_)(_)_   \n");
    printf(" (_)      (_)_          _(_) (_)_         (_)(_)   (_)(_)         _(_) (_)_         (_)          (_)  \n");
    printf(" (_)        (_)       _(_)     (_)_       (_) (_)_(_) (_)       _(_)     (_)_       (_)_  _  _  _     \n");
    printf(" (_)        (_)      (_) _  _  _ (_)      (_)   (_)   (_)      (_) _  _  _ (_)        (_)(_)(_)(_)_   \n");
    printf(" (_)       _(_)      (_)(_)(_)(_)(_)      (_)         (_)      (_)(_)(_)(_)(_)       _           (_)  \n");
    printf(" (_)_  _  (_)        (_)         (_)      (_)         (_)      (_)         (_)      (_)_  _  _  _(_)  \n");
    printf("(_)(_)(_)(_)         (_)         (_)      (_)         (_)      (_)         (_)        (_)(_)(_)(_)    \n");
    printf(" \n\n\n");

}

int menu(){
    introduction();
    int option = 0;
    do{
    printf("Seja bem vindo ao jogo de Dama, digite sua opcao: \n");
    printf("\n1- Jogar\n");
    printf("\n2 - Sair\n");
    scanf("%d", &option);
    printf("\n");
    }while(option > 2 && option < 1);
    int optionPiece = 0; 
    if(option == 1){
        return WHITEPIECES;
    }
    else{
        printf("\nSaindo do jogo!\n");
        exit(0);
    }
}

void generateBoard(int board[SIZE_BOARD][SIZE_BOARD]){
    int j = 0;
    #pragma omp parallel
    {

        #pragma omp for schedule(dynamic)
        for(int i = 0; i<SIZE_BOARD;i++){
            //j = omp_get_thread_num();
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

void showBoard(int board[SIZE_BOARD][SIZE_BOARD]) {
    printf("   ");
    for (int i = 0; i < SIZE_BOARD; i++) {
        printf("    %d", i + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE_BOARD; i++) {
        printf("        %d   ", i + 1);
        for (int j = 0; j < SIZE_BOARD; j++) {
            int piece = board[i][j];
            if (piece == WHITEPIECES) {
                printf("| W ");
            } else if (piece == BLACKPIECES) {
                printf("| B ");
            } else if (piece == WHITEPIECES + 5) { 
                printf("|DW ");
            } else if (piece == BLACKPIECES + 5) { 
                printf("|DB ");
            } else {
                printf("|   ");
            }
        }
        printf("|\n");
    }
}

void clear(){
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for(int i = 0; i < counterAux; i++){
            validatePlay[i].row = 0;
            validatePlay[i].column = 0;
            validatePlay[i].rowOperation = 0;
            validatePlay[i].columnOperation = 0;
            validatePlay[i].critical = 0;
        }
    }
    counterAux = 0;

}

void levantamentPlaying(int player, int rowOrigin, int columnOrigin){

            counter = 0;
            if(board[rowOrigin][columnOrigin] == player){
            #pragma omp sections
            {    
                #pragma omp section
                {
                if(rowOrigin+1< SIZE_BOARD){
                
                    if((columnOrigin - 1) >= 0){
                        play[counter].row = rowOrigin + 1;
                        play[counter].column = columnOrigin -1;
                        play[counter].rowOperation = + 1;
                        play[counter].columnOperation = -1;
                        counter++;
                        }
                        if((columnOrigin + 1) < SIZE_BOARD){
                            play[counter].row = rowOrigin +1;
                            play[counter].column = columnOrigin + 1;
                            play[counter].rowOperation = + 1;
                            play[counter].columnOperation = + 1;
                            counter++;
                        }
                    }
                }
            #pragma omp section
            {    
                if((rowOrigin - 1) >= 0){
                    if((columnOrigin - 1) >= 0){
                        play[counter].row = rowOrigin - 1;
                        play[counter].column = columnOrigin - 1;
                        play[counter].rowOperation = -1;
                        play[counter].columnOperation = -1;
                        counter++;
                    }
                    if((columnOrigin + 1) < SIZE_BOARD){
                        play[counter].row = rowOrigin - 1;
                        play[counter].column = columnOrigin + 1;
                        play[counter].rowOperation = -1;
                        play[counter].columnOperation = 1;
                        counter++;
                    }
                }
            }
            #pragma omp section_wait
        }
            verifyLevantament(player);
        }
         else{
                if(counter == 0){
return;
                }
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
                        if(player == WHITEPIECES && play[i].rowOperation > 0){
                            validatePlay[counterAux].row = play[i].row;
                            validatePlay[counterAux].column = play[i].column;
                            validatePlay[counterAux].rowOperation = play[i].rowOperation;
                            validatePlay[counterAux].columnOperation = play[i].columnOperation;
                            validatePlay[counterAux].critical = 0;
                            counterAux++;
                        }
                        else if(player == BLACKPIECES && play[i].rowOperation < 0){
                            validatePlay[counterAux].row = play[i].row;
                            validatePlay[counterAux].column = play[i].column;
                            validatePlay[counterAux].rowOperation = play[i].rowOperation;
                            validatePlay[counterAux].columnOperation = play[i].columnOperation;
                            validatePlay[counterAux].critical = 0;
                            counterAux++;
                        }

                    }
                    else if(board[play[i].row][play[i].column] == BLACKPIECES || board[play[i].row][play[i].column] == WHITEPIECES){
                        int aux = board[play[i].row][play[i].column] - player;
                        if(((play[i].row + play[i].rowOperation) >= 0 && (play[i].row + play[i].rowOperation) < SIZE_BOARD) && ((play[i].column + play[i].columnOperation) >= 0 && (play[i].column + play[i].columnOperation) < SIZE_BOARD)){ 
                            if(player == WHITEPIECES){
                                if(board[(play[i].row)][(play[i].column)] == BLACKPIECES && board[(play[i].row + play[i].rowOperation)][(play[i].column + play[i].columnOperation)] == 0){
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

                }
                
            }
    }
    
    
}

int moveGetPiece(int player){ 
        int verifyPiece;
        if(player == WHITEPIECES){
            verifyPiece = piecesTeamWhite;
        }
        else{
            verifyPiece = piecesTeamBlack;
        }
        int validate;
        #pragma omp parallel
        {
            #pragma omp for schedule(dynamic)
                for(int i = 0; i<counterAux;i++){
                    if((validatePlay[i].critical == 1)){
                        //Ao encontrar uma jogada critica ele executa ela, e caso sim ele retorna o valor da FLAG 1.

                        movePieceSeveralMoviment(i, player);
                        flag = 1;
                        if(player == WHITEPIECES){
                            validate = (verifyPiece != piecesTeamWhite);
                            #pragma omp cancel for
                        }
                        else{
                            validate = (verifyPiece != piecesTeamBlack);
                            #pragma omp cancel for
                        }
                    }
                }
        }
        return validate;
        
}

void movePieceSeveralMoviment(int indice, int player){
            int aux = board[(validatePlay[indice].row - validatePlay[indice].rowOperation) - validatePlay[indice].rowOperation][(validatePlay[indice].column - validatePlay[indice].columnOperation)- validatePlay[indice].columnOperation];
            board[(validatePlay[indice].row - validatePlay[indice].rowOperation)- validatePlay[indice].rowOperation][(validatePlay[indice].column - validatePlay[indice].columnOperation)- validatePlay[indice].columnOperation] = 0;
            board[(validatePlay[indice].row - validatePlay[indice].rowOperation)][(validatePlay[indice].column - validatePlay[indice].columnOperation)] = 0;
            board[validatePlay[indice].row][validatePlay[indice].column] = aux;
            lastRowMove = validatePlay[indice].row;
            lastColumnMove = validatePlay[indice].column;
            if(player == WHITEPIECES){
                piecesTeamWhite++;
                counterGet++;
            }
            else if(player == BLACKPIECES){
                piecesTeamBlack++;
                counterGet++;
            }
            else{
                printf("\nNenhuma peca comida\n");
            
            }
            //showBoard(board);
            flag = 1;
    return ;
}

void movePieceOneMoviment(){
    int lower_bound = 0;
    int upper_bound = counterAux;

    srand(time(NULL));
    int random_number = lower_bound + (rand() % (upper_bound - lower_bound));
    int piece = board[lastRowMove][lastColumnMove];
    int aux = board[validatePlay[random_number].row][validatePlay[random_number].column];
    board[lastRowMove][lastColumnMove] = aux;
    board[validatePlay[random_number].row][validatePlay[random_number].column] = piece;
    lastRowMove = validatePlay[random_number].row;
    lastColumnMove = validatePlay[random_number].column;
    flag = 1;
    
}

int movePlayerOnePieceMoviment(int indice){
    int piece = board[lastRowMove][lastColumnMove];
    int aux = board[validatePlay[indice].row][validatePlay[indice].column];
    board[lastRowMove][lastColumnMove] = aux;
    board[validatePlay[indice].row][validatePlay[indice].column] = piece;
    lastRowMove = validatePlay[indice].row;
    lastColumnMove = validatePlay[indice].column;
    flag = 1;
    
}

void verifyPiecesForPlay(int player){
    int row, column, initialRow, endRow, initialColumn, endColumn;  
        if(player == WHITEPIECES){
                for(int i = 0; i< SIZE_BOARD;++i){
                    for(int j = 0;j<SIZE_BOARD; ++j){
                        if(board[i][j] == WHITEPIECES){
                            row = i;
                            column = j;
                            levantamentPlaying(player, row, column);
                            if(counterAux > 0 ){
                                for(int w = 0;w<counterAux;w++){
                                    if((validatePlay[w].critical == 1)){
                                        lastRowMove = i;
                                        lastColumnMove = j;
                                        criticalFlag++;
                                        clear();
                                        return ;                                  
                                    }
                                }
                                    
                            }
                            counter = 0;
                            counterAux = 0;
                        }
                    }
                }
        }

        if(player == BLACKPIECES){
                int lower_bound = 0;
                int upper_bound = 2;
                srand(time(NULL));
                int random_number = lower_bound + (rand() % (upper_bound - lower_bound));
                if(random_number == 0){
                    initialRow = vectorRow[0];
                    endRow = vectorRow[1];
                    random_number = lower_bound + (rand() % (upper_bound - lower_bound));
                    if(random_number == 0){
                        initialColumn = vectorRow[0];
                        endColumn = vectorRow[1];
                        for(int i = initialRow; i<=endRow;++i){
                            for(int j = initialColumn;j<=endColumn; ++j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        for(int w = 0;w<counterAux;w++){
                                            if(validatePlay[w].critical == 1){
                                                lastRowMove = i;
                                                lastColumnMove = j;
                                                clear();
                                                return;
                                            }
                                        }
                                    counterAux = 0;
                                    counter = 0;
                                    }
                                }
                            }
                        }
                        for(int i = initialRow; i<=endRow;++i){
                            for(int j = initialColumn;j<=endColumn; ++j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        lastRowMove = i;
                                        lastColumnMove = j;
                                        clear();
                                        return;
                                    }
                                counter = 0;
                                counterAux = 0;
                            }
                        }
                    }                        
                    }
                    else{
                        initialColumn = vectorRow[1];
                        endColumn = vectorRow[0];
                        for(int i = initialRow; i<=endRow;++i){
                            for(int j = initialColumn;j>=endColumn; --j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        for(int w = 0;w<counterAux;w++){
                                            if(validatePlay[w].critical == 1){
                                                lastRowMove = i;
                                                lastColumnMove = j;
                                                printf("%d", validatePlay[w].critical);
                                                clear();
                                                return;
                                            }
                                        }
                                    counterAux = 0;
                                    counter = 0;
                                    }
                                }
                            }
                        }
                        for(int i = initialRow; i<=endRow;++i){
                            for(int j = initialColumn;j>=endColumn; --j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        lastRowMove = i;
                                        lastColumnMove = j;
                                        clear();
                                        return;
                                    }
                                counter = 0;
                                counterAux = 0;
                            }
                        }
                    }
                }
            }
                else{
                    initialRow = vectorRow[1];
                    endRow = vectorRow[0];
                    random_number = lower_bound + (rand() % (upper_bound - lower_bound));
                    if(random_number == 0){
                        initialColumn = vectorRow[0];
                        endColumn = vectorRow[1];
                        for(int i = initialRow; i>=endRow;--i){
                            for(int j = initialColumn;j<=endColumn; ++j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        for(int w = 0;w<counterAux;w++){
                                            if(validatePlay[w].critical == 1){
                                                lastRowMove = i;
                                                lastColumnMove = j;
                                                printf("%d", validatePlay[w].critical);
                                                clear();
                                                return;
                                            }
                                        }
                                    counterAux = 0;
                                    counter = 0;
                                    }
                                }
                            }
                        }
                        for(int i = initialRow; i>=endRow;--i){
                            for(int j = initialColumn;j<=endColumn; ++j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        lastRowMove = i;
                                        lastColumnMove = j;
                                        clear();
                                        return;
                                    }
                                counter = 0;
                                counterAux = 0;
                            }
                        }
                    }
                    }
                    else{
                        initialColumn = vectorRow[1];
                        endColumn = vectorRow[0];
                        for(int i = initialRow; i>=endRow;--i){
                            for(int j = initialColumn;j>=endColumn; --j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        for(int w = 0;w<counterAux;w++){
                                            if(validatePlay[w].critical == 1){
                                                lastRowMove = i;
                                                lastColumnMove = j;
                                                printf("%d", validatePlay[w].critical);
                                                clear();
                                                return;
                                            }
                                        }
                                    counterAux = 0;
                                    counter = 0;
                                    }
                                }
                            }
                        }
                         for(int i = initialRow; i>=endRow;--i){
                            for(int j = initialColumn;j>=endColumn; --j){
                                if(board[i][j] == BLACKPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    if(counterAux > 0 ){
                                        lastRowMove = i;
                                        lastColumnMove = j;
                                        clear();
                                        return;
                                    }
                                counter = 0;
                                counterAux = 0;
                        }
                    }
                }
            }
        }
        
    }
}

int playingMachine(int playerMachine){
    vectorRow[0] = 0;
    vectorColumn[0] = 0;
    vectorRow[1] = SIZE_BOARD;
    vectorColumn[1] = SIZE_BOARD;
    flag = 0;
    int valuePieces;
    int validate;
    verifyPiecePlayer(playerMachine); // Verifica se h� possibilidades de jogadas na rodada
    if(totalMovimentsPossible == 0){
        if(playerMachine == WHITEPIECES){
            printf("\nPe�as Pretas ganharam!\n");
            exit(0);
        }
        else{
            printf("\nPe�as Brancas ganharam!\n");
            exit(0);
        }
    }
    clear();
    totalMovimentsPossible = 0;
    do{ 
    
    verifyPiecesForPlay(BLACKPIECES); //Buscar linhas para jogar
    
    levantamentPlaying(BLACKPIECES, lastRowMove, lastColumnMove);

    
    valuePieces = piecesTeamBlack; //Armazena o estado das pe�as da quantidade de pe�as
    
    validate =  moveGetPiece(BLACKPIECES); // pega o valor de retorno da fun��o que retorna 1 caso seja alguma pe�a capturada e 0 caso n�o haja pe�a capturada.
    
    //Caso o valor de valuePieces == piecesTeamBlack e FLAG = 0, significa que n�o foi comida pe�as nessa rodada.
    if((valuePieces == piecesTeamBlack) && (flag == 0)){ 
        
        movePieceOneMoviment();
        printf("\n");
        printf("\n");
        if(validate == 0 && playerMachine == WHITEPIECES){
            playerTurn = BLACKPIECES;
        }
        else{
            playerTurn = WHITEPIECES;
        }
    }
    }while(valuePieces != piecesTeamBlack);

    //Identifica se houve pe�as comidas com a flag counterGet e compara os valores de valuePieces e piecesTeamBlack
    if(counterGet > 0 && (valuePieces == piecesTeamBlack)){
        clear();
        counterGet = 0;
        if(validate == 0 && playerMachine == WHITEPIECES){
            playerTurn = BLACKPIECES;
        }
        else{
            playerTurn = WHITEPIECES;
        }
        return 1;
    }
    else{
        clear();
        return 1;
    }
}

int playingPlayer(int playerOne){
    int valuePieces;
    int validate;
    flag = 0;
    verifyPiecePlayer(playerOne);
    if(totalMovimentsPossible == 0){ // Verifica se h� jogadas dispon�veis
        if(playerOne == WHITEPIECES){
            printf("\nPe�as Pretas ganharam!\n");
            exit(0);
        }
        else{
            printf("\nPe�as Brancas ganharam!\n");
            exit(0);
        }
    }
    clear();
    totalMovimentsPossible = 0;
    int option;
    
    do{
        
        if(flag == 0){
            verifyPiecesForPlay(playerOne);
            if(criticalFlag == 0){
                selectPlay(playerOne);
            }
            levantamentPlaying(playerOne, lastRowMove, lastColumnMove);
            valuePieces = piecesTeamWhite;
        }
        if(counterAux > 0){
            for(int i = 0; i<counterAux;i++){
                if(criticalFlag == 0 && validatePlay[i].critical == 0){
                    printf("\nOpcao: %d", i+1);
                    printf("\nLinha: %d\nColuna: %d\n", validatePlay[i].row+1, validatePlay[i].column+1);
                }
                else if(validatePlay[i].critical == 1){
                    printf("\nOpcao: %d", i+1);
                    printf("\nLinha: %d\nColuna: %d\n", validatePlay[i].row+1, validatePlay[i].column+1);
                }
            }

            do{
                printf("\nEscolha a sua opcao de jogada: \n");
                scanf("%d", &option);
            }while(option < 1 && option >= counterAux);
            criticalFlag = 0;
            while(validatePlay[option - 1].critical == 1){
                flag = 1;
                movePieceSeveralMoviment(option-1, playerOne);
                lastRowMove = validatePlay[option -1].row;
                lastColumnMove = validatePlay[option - 1].column;
                levantamentPlaying(playerOne, lastRowMove, lastColumnMove);
                valuePieces = piecesTeamWhite;
                int flagDo = 0;
                int printBoard = 0;
                if(counterAux > 0){
                    
                    for(int i = 0; i<counterAux;i++){
                        if(validatePlay[i].critical == 1){
                            if(printBoard == 0){
                                showBoard(board);
                                printBoard = 1;
                            }
                            flagDo++;
                            printf("\nOpcao: %d", i+1);
                            printf("\nLinha: %d\nColuna: %d\n", validatePlay[i].row+1, validatePlay[i].column+1);
                        }
                    }
                    if(flagDo){ 
                        do{
                            printf("\nEscolha a sua opcao de jogada: \n");
                            scanf("%d", &option);
                        }while(option < 1 && option >= counterAux);
                    }
                }
            else{
                if(playerOne == WHITEPIECES){
                    playerTurn = BLACKPIECES;
                    clear();
                    return 1;
                }
                else{
                    playerTurn = WHITEPIECES;
                    clear();
                    return 1;
                }
                clear();
                return 1;
            }
        }
        if((valuePieces == piecesTeamWhite) && (flag == 0)){
            movePlayerOnePieceMoviment(option-1);
            printf("\n");
            if(playerOne == WHITEPIECES){
                playerTurn = BLACKPIECES;
                clear();
                return 1;
                }
            else{
                playerTurn = WHITEPIECES;
                clear();
                return 1;
                }
            }
        }
    }while(valuePieces != piecesTeamWhite);
        
    counterGet = 0;
    if(playerOne == WHITEPIECES){
        playerTurn = BLACKPIECES;
    }
    else{
        playerTurn = WHITEPIECES;
    }
    clear();
    return 1;
}

void sendData(int processRank){
    if (processRank == 0) {
        // Processo 0 envia o tabuleiro para o processo 1
        MPI_Send(&board, SIZE_BOARD * SIZE_BOARD, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Processo 0 envia a vari�vel playerTurn para o processo 1
        MPI_Send(&playerTurn, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    }
    else if(processRank == 1){

        // Processo 1 envia o tabuleiro modificado de volta para o processo 0
        MPI_Send(&board, SIZE_BOARD * SIZE_BOARD, MPI_INT, 0, 2, MPI_COMM_WORLD);

        // Processo 1 envia a vari�vel playerTurn de volta para o processo 0
        MPI_Send(&playerTurn, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }
}

void recvData(int processRank){
        if (processRank == 0) {
        // Processo 0 recebe o tabuleiro modificado do processo 1
        MPI_Recv(&board, SIZE_BOARD * SIZE_BOARD, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Processo 0 recebe a vari�vel playerTurn do processo 1
        MPI_Recv(&playerTurn, 1, MPI_INT, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (processRank == 1) {
        // Processo 1 recebe o tabuleiro do processo 0
        MPI_Recv(board, SIZE_BOARD * SIZE_BOARD, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Processo 1 recebe a vari�vel playerTurn do processo 0
        MPI_Recv(&playerTurn, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

int startGame(int playerOne, int playerMachine){
    int verify = 1;

    
    //showBoard(board);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);    
    if(processRank == 0){
        showBoard(board);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    while (verify) {

        MPI_Barrier(MPI_COMM_WORLD);
        if(processRank == 0){
            

            printf("\n%d - TURNO DAS BRANCAS:\n", countTurn + 1);
            verify = playingPlayer(playerOne);
            sendData(processRank);
            // Use MPI_Send para enviar dados para o processo 1 aqui
        }
        else{
            recvData(processRank);
            do {
                verify = playingMachine(playerMachine);
            } while (verify == 2);
            sendData(processRank);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        if(processRank == 0){
           recvData(processRank);
           showBoard(board);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        
        // Use MPI_Barrier para sincronizar todos os processos
        //MPI_Barrier(MPI_COMM_WORLD);
        //exit(0);
        countTurn++;
    }
    return 0;
}

int main(){
    int playerOne, playerMachine;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    if(rank == 0){
    playerOne = menu();
    playerMachine = 0;
    if(playerOne == WHITEPIECES) {
        playerMachine = BLACKPIECES;}
    else {
        playerMachine = WHITEPIECES;
    }
    playerTurn = WHITEPIECES;
    vectorRow[0] = 0;
    vectorRow[1] = SIZE_BOARD-1;
    vectorColumn[0] = 0;
    vectorColumn[1] = SIZE_BOARD-1;
    generateBoard(board);
    //showBoard(board);
    }
    printf("\n");
    printf("\n");
    if(rank == 0){
            sendData(rank);
    }
    else{
            recvData(rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    startGame(playerOne, playerMachine);
    MPI_Finalize();
    
}

int selectPlay(int playerOne){
    int row, column;
    do{
        clear();
        printf("\nEscolha a linha que queira jogar: \n");
        scanf("%d", &row);
        printf("\nEscolha a coluna que queira jogar: \n");
        scanf("%d", &column);
        if(board[row-1][column-1] != playerOne){
            printf("\nPeca invalida\n");
        }
        else{
            levantamentPlaying(playerOne, row-1, column-1);
            if(counterAux == 0){
                printf("Jogada invalida, selecione outra novamente!");
            }
        }
    }while((board[row-1][column-1] != playerOne) || (counterAux <= 0));
    lastRowMove = row-1;
    lastColumnMove = column-1;
}

int verifyPiecePlayer(int player){
    totalMovimentsPossible = 0;


            if(player == WHITEPIECES){
                        for(int i = 0; i< SIZE_BOARD;++i){
                            for(int j = 0;j<SIZE_BOARD; ++j){
                                if(board[i][j] == WHITEPIECES){
                                    lastRowMove = i;
                                    lastColumnMove = j;
                                    levantamentPlaying(player, lastRowMove, lastColumnMove);
                                    //printf("CounterAux: %d\n", counterAux);
                                    if(counterAux > 0 ){
                                        totalMovimentsPossible++;
                                    }
                                    clear();
                                    counter = 0;
                                    counterAux = 0;
                                }
                            }
                        }
                }
            else{
                            for(int i = 7; i>= 0;--i){
                                for(int j = 0;j<SIZE_BOARD; ++j){
                                    if(board[i][j] == BLACKPIECES){
                                        lastRowMove = i;
                                        lastColumnMove = j;
                                        levantamentPlaying(BLACKPIECES, lastRowMove, lastColumnMove);
                                        //printf("CounterAux: %d\n", counterAux);
                                        if(counterAux > 0 ){
                                            totalMovimentsPossible++;
                                            clear();
                                            return 0;
                                        }
                                        clear();
                                        counter = 0;
                                        counterAux = 0;
                                    }
                                }
                        }
                    }
}
