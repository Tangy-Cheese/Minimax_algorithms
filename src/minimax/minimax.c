#include "minimax.h"
#include <stdbool.h>

static int minimax(int arr[3][3], bool MAX, int row, int col, int current_player, int depth){ //minimax function;

    /* If row/col are valid, check whether the last move produced a winner */
    if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
        int winner = game_checker_last(row, col, current_player, arr);

        if (winner == AI){
            return 10 - depth;
        }

        if (winner == HUMAN){
            return -10 + depth;
        }
    }

    bool DRAW = true;
    for (int i = 0; i < 3; i++){ 
        for (int j = 0; j < 3; j++){
            if (arr[i][j] == 0){
                DRAW = false;
            }
        }
    }  

    if (DRAW){
        return 0;
    }

    int move = (MAX ? AI : HUMAN);

    if (MAX){ //AI’s turn
        int best = -1000;
        for (int i = 0; i < 3; i++){
            for (int j = 0;j < 3; j++){
                if (arr[i][j] == 0){
                    arr[i][j] = move;

                    int value = minimax(arr, !MAX, i+1, j+1, move, depth + 1);

                    if (value > best){
                        best = value;
                    }

                    arr[i][j] = 0;
                }
            }
        }
        return best;
    }

    else{ //Human’s turn
        int best = 1000;
        for (int i = 0; i < 3; i++){
            for (int j = 0;j < 3; j++){
                if (arr[i][j] == 0){
                    arr[i][j] = move;
                    
                    int value = minimax(arr, !MAX, i+1, j+1, move, depth + 1);

                    if (value < best){
                        best = value;
                    }

                    arr[i][j] = 0;
                }
            }
        }
        return best;
    }
}
