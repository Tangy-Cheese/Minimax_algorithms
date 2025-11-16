#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define HUMAN 1
#define AI 2

static void print_board(int a[6][7]) { //Loop over the board and print out the state of the whole board
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int array[7][6] = {0};
    print_board(array);

    return 0;
}