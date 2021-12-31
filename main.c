#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char board[3][3];
char player_one = 'X';
char player_two = 'O'; // CANNOT BE ' ' !!!
char computer_one = 'O';
char computer_two = 'X';
int game_mode = 1;

char who_wins() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board [i][j] == board[i][j + 1] && board [i][j] == board[i][j + 2]) {
                return board[i][j];
            }

        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board [j][i] == board[j][i + 1] && board [j][i] == board[j][i + 2]) {
                return board[j][i];
            }

        }

    }

    if (board[0][0] == board[1][1] && board [0][0] == board[0][2]) {        //andere Lösung?
        return ' ';
    }
    if (board[0][2] == board[1][1] && board [0][2] == board[2][0]) {
        return ' ';
    }
}

void fillFreeSpace() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("| %c |", board[i][j]);
        }
        if (i < 2) {
            printf("\n|---||---||---|\n");
        }
    }
    printf("\n");
}

int freeSpace() {
    int spaces = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
            spaces++;
            }
        }
    }
    return spaces;
}

void player_1_Turn() {
    int x, y;

    do {
        printf("Player 1: Enter row# and column# (1-3):");
        scanf("%d %d", &x, &y);
        x--, y--;
        //printf("%d - %d", x, y);

        if (board[x][y] != ' ') {
            printf("This field has already been used!\n");
        }else {
            board[x][y] = player_one;
            break;
        }
    } while (board[x][y] != ' ');
}

void player_2_Turn() {
    int x, y;
        do {
            if (game_mode != 1) {
                break;
            }
            printf("Player 2: Enter row# and column# (1-3):");
            scanf("%d %d", &x, &y);
            x--, y--;
            //printf("%d - %d", x, y);

            if (board[x][y] != ' ') {
                printf("This field has already been used!\n");
            } else {
                board[x][y] = player_two;
                break;
            }
        } while (board[x][y] != ' ');
}

void computer_turn() {

}

int main() {

    char winner = ' ';

    //do {
        winner = ' ';
        fillFreeSpace();

        while(winner == ' ' && freeSpace() != 9) {
            printBoard();
            player_1_Turn();
            winner = who_wins();

            if (winner != ' ' || freeSpace() == 9) {
                break;
            }

            printBoard();
            player_2_Turn();
            winner = who_wins();

            if (winner != ' ' || freeSpace() == 9) {
                break;
            }
        }
        printBoard();
   // }


    return 0;
}