#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

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
        printf(" %d ", i + 1);
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
                    else{
                        printf("\nJogada invalida, selecione novamente\n");
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
//Função para verificar as jogadas criticas e jogadas disponíveis para realizar.
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
    flag = 0;
    int valuePieces;
    int validate;
    verifyPiecePlayer(playerMachine); // Verifica se há possibilidades de jogadas na rodada
    if(totalMovimentsPossible == 0){
        if(playerMachine == WHITEPIECES){
            printf("\nPeças Pretas ganharam!\n");
            exit(0);
        }
        else{
            printf("\nPeças Brancas ganharam!\n");
            exit(0);
        }
    }
    clear();
    totalMovimentsPossible = 0;
    do{ 
    
    verifyPiecesForPlay(playerMachine); //Buscar linhas para jogar
    levantamentPlaying(playerMachine, lastRowMove, lastColumnMove);
    
    valuePieces = piecesTeamBlack; //Armazena o estado das peças da quantidade de peças
    
    validate =  moveGetPiece(playerMachine); // pega o valor de retorno da função que retorna 1 caso seja alguma peça capturada e 0 caso não haja peça capturada.

    //Caso o valor de valuePieces == piecesTeamBlack e FLAG = 0, significa que não foi comida peças nessa rodada.
    if((valuePieces == piecesTeamBlack) && (flag == 0)){ 
        movePieceOneMoviment();
        printf("\n");
        showBoard(board);
        printf("\n");
        if(validate == 0 && playerMachine == WHITEPIECES){
            playerTurn = BLACKPIECES;
        }
        else{
            playerTurn = WHITEPIECES;
        }
    }
    }while(valuePieces != piecesTeamBlack);

    //Identifica se houve peças comidas com a flag counterGet e compara os valores de valuePieces e piecesTeamBlack
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
    if(totalMovimentsPossible == 0){ // Verifica se há jogadas disponíveis
        if(playerOne == WHITEPIECES){
            printf("\nPeças Pretas ganharam!\n");
            exit(0);
        }
        else{
            printf("\nPeças Brancas ganharam!\n");
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
                if(counterAux > 0){
                    for(int i = 0; i<counterAux;i++){
                        if(validatePlay[i].critical == 1){
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
        showBoard(board);
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

int startGame(int playerOne, int playerMachine){
    int verify = 1;
    int validate = 0;
    while(verify)
    {
        if(playerTurn == WHITEPIECES){
            printf("\n%d - TURNO DAS BRANCAS:\n", countTurn+1);
        }
        else{
            printf("\n%d - TURNO DAS PRETAS\n", countTurn+1);
        }
        if(playerTurn == playerOne){
            verify = playingPlayer(playerOne);
            printf("\nQuantidade de pecas capturadas pelas Brancas %d\n", piecesTeamWhite);
        }
        else{
            do{ 
            verify = playingMachine(playerMachine);
            }while(verify == 2);
            printf("\nQuantidade de pecas capturadas pelas Pretas %d\n", piecesTeamBlack);
            showBoard(board);
            
            
        }
        countTurn++;
    }
}

int main(){
    int playerOne = menu();
    int playerMachine = 0;
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
    showBoard(board);
    printf("\n");
    printf("\n");
    startGame(playerOne, playerMachine);
     
    
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
                                        levantamentPlaying(player, lastRowMove, lastColumnMove);
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
}
