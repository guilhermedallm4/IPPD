#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int board[8][8];

#define whitepieces 10
#define redpieces 20
#define whiteHouse -1
#define blackHouse 0

void createBoard();
void showBoard();

void createBoard(){
    int j = 0;
    #pragma omp parallel
    {

        #pragma omp for schedule(dynamic)
        for(int i = 0; i<8;i++){
            j = omp_get_thread_num();
            printf("Thread %d\n", j);
            if(i % 2 == 0){
                if(i == 0 || i == 2){
                    board[i][1] = whitepieces;
                    board[i][3] = whitepieces;
                    board[i][5] = whitepieces;
                    board[i][7] = whitepieces;
                    board[i][0] = whiteHouse;
                    board[i][2] = whiteHouse;
                    board[i][4] = whiteHouse;
                    board[i][6] = whiteHouse;
                }
                else if(i == 6){
                    board[i][1] = redpieces;
                    board[i][3] = redpieces;
                    board[i][5] = redpieces;
                    board[i][7] = redpieces;
                    board[i][0] = whiteHouse;
                    board[i][2] = whiteHouse;
                    board[i][4] = whiteHouse;
                    board[i][6] = whiteHouse;
                }
                else{
                    board[i][1] = blackHouse;
                    board[i][3] = blackHouse;
                    board[i][5] = blackHouse;
                    board[i][7] = blackHouse;
                    board[i][0] = whiteHouse;
                    board[i][2] = whiteHouse;
                    board[i][4] = whiteHouse;
                    board[i][6] = whiteHouse;
                }
            }
            else{
                if(i == 1){
                    board[i][1] = whiteHouse;
                    board[i][3] = whiteHouse;
                    board[i][5] = whiteHouse;
                    board[i][7] = whiteHouse;
                    board[i][0] = whitepieces;
                    board[i][2] = whitepieces;
                    board[i][4] = whitepieces;
                    board[i][6] = whitepieces;
                }
                else if(i == 5 || i == 7){
                    board[i][1] = whiteHouse;
                    board[i][3] = whiteHouse;
                    board[i][5] = whiteHouse;
                    board[i][7] = whiteHouse;
                    board[i][0] = redpieces;
                    board[i][2] = redpieces;
                    board[i][4] = redpieces;
                    board[i][6] = redpieces;
                }
                else{
                    board[i][0] = blackHouse;
                    board[i][2] = blackHouse;
                    board[i][4] = blackHouse;
                    board[i][6] = blackHouse;
                    board[i][1] = whiteHouse;
                    board[i][3] = whiteHouse;
                    board[i][5] = whiteHouse;
                    board[i][7] = whiteHouse;
                }

            }
        }
    }
}

void showBoard(){
        for(int i = 0; i< 8;i++){
            for(int j = 0; j <8;j++ ){
                printf(" %d ", board[i][j]);
            }
            printf("\n");
        }
}

int main(){
    createBoard();
    showBoard();

}

/*
void playing(){
    if( board[i][j] == 0 && (i-1) >= 0 && (i+1) <=7){

    }
}*/