#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define HUMAN 1
#define AI 2

static void print_board(int a[3][3]) { //Loop over the board and print out the state of the whole board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

static void welcome(void) { //Welcome message
    printf("welcome to tictactoe.\n");
}

static void game(int row, int column, int current_player, int a[3][3]) { //Assigns the chosen square to the player
    a[row-1][column-1] = current_player; //Remember convention states row 1 = row 0
}

static int game_checker_last(int row, int col, int current_player, int a[3][3]) { //Checking for the win condition
    int r = row - 1, c = col - 1;

    if (a[r][0] == current_player && a[r][1] == current_player && a[r][2] == current_player) //checks the rows
        return current_player;

    if (a[0][c] == current_player && a[1][c] == current_player && a[2][c] == current_player) //checks the columns
        return current_player;

    if (r == c) {
        if (a[0][0] == current_player && a[1][1] == current_player && a[2][2] == current_player) //checks the forwards diagonal
            return current_player;
    }

    if (r + c == 2) {
        if (a[0][2] == current_player && a[1][1] == current_player && a[2][0] == current_player) //checks the backwards diagonal
            return current_player;
    }

    return 0;
}

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

/* Evaluate scores in a temporary array, pick best, place AI move and return chosen coords */
static void ai_turn(int arr[3][3], int moves, int *out_row, int *out_col){
    int scores[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            scores[i][j] = -10000;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (arr[i][j] == 0){
                /* Try AI move here */
                arr[i][j] = AI;
                int score = minimax(arr, false, i+1, j+1, AI, moves + 1);
                scores[i][j] = score;
                arr[i][j] = 0; /* restore */
            }
        }
    }

    int best = -100000;
    int best_row = 0, best_col = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            /* Only consider positions that were empty (scores set) */
            if (scores[i][j] != -10000 && scores[i][j] > best){
                best = scores[i][j];
                best_row = i;
                best_col = j;
            }
        }
    }

    arr[best_row][best_col] = AI;
    *out_row = best_row;
    *out_col = best_col;
    printf("The computer has picked column: %d and row: %d\n", best_col + 1, best_row + 1);
    print_board(arr);
}

static void mechanic(int a[3][3]){
    int moves = 0;
    
    print_board(a);

    while (moves < 9) {
        int current_player = ((moves+6) % 2) + 1;
        int row, col;

        printf("current_player %d, your turn:\n", current_player);
        
        if (current_player == HUMAN){
            printf("Row: ");
            if (scanf(" %d", &row) != 1) {
                printf("invalid input. try again.\n");
                exit(EXIT_FAILURE);
            }

            printf("Column: ");
            if (scanf(" %d", &col) != 1) {
                printf("invalid input. try again.\n");
                exit(EXIT_FAILURE);
            }
        }

        if (current_player == AI){
            int best_row, best_col;
            ai_turn(a, moves, &best_row, &best_col);
            if (game_checker_last(best_row + 1, best_col + 1, AI, a)) { //check AI win using the actual move
                printf("AI wins!\n");
                return;
            }
            moves++;
            if (moves == 9) {
                printf("it's a draw.\n");
                return;
            }
            continue;
        }

        if (row < 1 || row > 3 || col < 1 || col > 3) {
            printf("please pick a proper square (1..3).\n");
            continue;
        }

        if (a[row-1][col-1] != 0) {
            printf("space is taken.\n");
            continue;
        }

        game(row, col, current_player, a);
        print_board(a);

        if (game_checker_last(row, col, current_player, a)) {
            printf("current_player %d wins!\n", current_player);
            return;
        }

        moves++;

        if (moves == 9) {
            printf("it's a draw.\n");
            return;
        }
    }
}

int main(void){
    welcome();
    int board[3][3] = {0};
    mechanic(board);
    return 0;
}
