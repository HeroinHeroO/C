#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//#include <windows.h>

char board[3][3];
int statistics_p1[7] = {0, 0, 0, 0, 0, 0, 0}; // Games played, wins, losses, ties, X games, O games, signs placed
char player_one = 'X';
char player_one_name[21];
int statistics_p2[7] = {0, 0, 0, 0, 0, 0, 0}; // Games played, wins, losses, ties, X games, O games, signs placed
char player_two = 'O';
char player_two_name[21] = "COMPUTER";
int game_mode = 0;

void print_player_stats() {
    if (game_mode == 3) {
        return;
    } else if (game_mode == 2) {
        printf("\n\nPLAYER STATISTICS:\n\n");
        printf("LIFETIME GAMES PLAYED: %d - PATHETIC!\n", statistics_p1[0]);
        printf("TOTAL WINS: %d - WEAK!\n", statistics_p1[1]);
        printf("GAMES LOST: %d - SOUL CRUSHING!\n", statistics_p1[2]);
        printf("TIE GAMES: %d - EMBARRASSING!\n", statistics_p1[3]);
        printf("You have picked the X %d times and the O %d times - BAD CHOICE!\n", statistics_p1[4],statistics_p1[5]);
        printf("You have marked the BATTLEFIELD OF BLOOD %d times! - BLOOD FOR THE BLOOD GOD!\n", statistics_p1[6]);
    } else if (game_mode == 1) {
        printf("\n\nPLAYER STATISTICS:\n\n");
        printf("LIFETIME GAMES PLAYED: %s: %d - %s: %d - PATHETIC!\n", player_one_name, statistics_p1[0], player_two_name, statistics_p2[0]);
        printf("TOTAL WINS: %s: %d - %s: %d: - WEAK!\n", player_one_name, statistics_p1[1], player_two_name, statistics_p2[1]);
        printf("GAMES LOST: %s: %d - %s: %d - SOUL CRUSHING!\n", player_one_name, statistics_p1[2], player_two_name, statistics_p2[2]);
        printf("TIE GAMES: %s: %d - %s: %d - EMBARRASSING!\n", player_one_name, statistics_p1[3], player_two_name, statistics_p2[3]);
        printf("%s has picked the X %d times and the O %d times - BAD CHOICE!\n", player_one_name, statistics_p1[4],statistics_p1[5]);
        printf("%s chose X %d times placed the O %d times - ROOKIE MISTAKE!\n", player_two_name, statistics_p2[4],statistics_p2[5]);
        printf("%s has marked the BATTLEFIELD OF BLOOD %d times!\n", player_one_name, statistics_p1[6]);
        printf("%s scorched their sign into SACRED GROUND %d times!\n", player_two_name, statistics_p2[6]);
        printf("\n\n THE BATTLE IS OVER! You may flee now - or return IF YOU DARE!!!\n\n");
    }
    return;
}

void player1_stats_load() {
    char player_one_file[25];
    strcpy(player_one_file, player_one_name);
    strcat(player_one_file, ".txt");

    FILE *fptr;
    int num;
    if ((fptr = fopen(player_one_file, "r")) == NULL) {
        printf("You seem to be new here, %s, good luck!\n", player_one_name);
    } else {
        for (int i = 0; i < 7; i++) {
            fscanf(fptr, "%d", &num);
            statistics_p1[i] = num;
        }
        if (fflush(fptr) != 0) {
            fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", player_one_name);
            return;
        }
        if (fclose(fptr) != 0) {
            fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", player_one_name);
            return;
        }
    }
}

void player2_stats_load() {
    char player_two_file[25];
    strcpy(player_two_file, player_two_name);
    strcat(player_two_file, ".txt");

    FILE* fptr2;
    int num;
    if ((fptr2 = fopen(player_two_file, "r")) == NULL) {
        printf("You seem to be new here, %s, good luck!\n", player_two_name);
    }else {
        for (int i = 0; i < 7; i++) {
            fscanf(fptr2, "%d", &num);
            statistics_p2[i] = num;
        }
        if (fflush(fptr2) != 0) {
            fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", player_two_name);
            return;
        }
        if (fclose(fptr2) != 0) {
            fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", player_one_name);
            return;
        }
    }
}

void player_stats_save() {
    char player_one_file[25];
    strcpy(player_one_file, player_one_name);
    strcat(player_one_file, ".txt");

    FILE* fptr;
    if ((fptr = fopen(player_one_file, "w")) == NULL) {
        fprintf(stderr, "ERROR: Cannot open statistics file for %s!\n", player_one_name);
        return;
    }
    for (int i = 0; i < 7; i++) {
        fprintf(fptr, "%d ", statistics_p1[i]);
    }
    if (game_mode != 3){
        printf("Statistics for %s saved!\n", player_one_name);
    }
    if (fflush(fptr) != 0) {
        fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", player_one_name);
        return;
    }
    if (fclose(fptr) != 0) {
        fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", player_one_name);
        return;
    }

    if (game_mode == 1) {
        FILE *fptr2;
        char player_two_file[25];
        strcpy(player_two_file, player_two_name);
        strcat(player_two_file, ".txt");

        if ((fptr2 = fopen(player_two_file, "w")) == NULL) {
            fprintf(stderr, "ERROR: Cannot open statistics file for %s!\n", player_two_name);
            return;
        }
        for (int i = 0; i < 7; i++) {
            fprintf(fptr2, "%d ", statistics_p2[i]);
        }
        printf("Statistics for %s saved!\n", player_two_name);

        if (fflush(fptr2) != 0) {
            fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", player_two_name);
            return;
        }
        if (fclose(fptr2) != 0) {
            fprintf(stderr, "ERROR: Closing statistics file for %d was unsuccessful!\n", player_one_name);
            return;
        }
    }
}

void playeroptions() {
    char player_one_sign;

    printf("Player One - Enter your name (max. 20 characters):");
    fgets(player_one_name, 20, stdin);
    player_one_name[strlen(player_one_name) - 1] = '\0';

    if (game_mode != 3) {
        player1_stats_load();
    }

    int tmpmode;
    printf("\nChoose a game mode!\n1: Human versus Human\n2: Human versus Machine\n3: BATTLE OF THE MACHINES!\nPress 4 to flee now!\n");
    tmpmode = getchar();
    getchar();
    tmpmode = tmpmode -48; // 1-9 on ASCII TABLE
    switch (tmpmode) {
        case 1:
            game_mode = 1;
            break;
        case 2:
            game_mode = 2;
            break;
        case 3:
            game_mode = 3;
            break;
        case 4:
            exit(EXIT_SUCCESS);
        default:
            printf("Invalid choice! You will be forced to watch a BATTLE OF THE MACHINES!\n");
            game_mode = 3;
            break;
    }

    sign:
    if (game_mode != 3) {
        printf("%s, chose your sign: X or O\n", player_one_name);
        player_one_sign = getchar();
        getchar();
        if (player_one_sign == 'x' || player_one_sign == 'X') {
            player_one = 'X';
            player_two = 'O';
            statistics_p1[4]++;
            statistics_p2[5]++;
        } else if (player_one_sign == 'o' || player_one_sign == 'O') {
            player_one = 'O';
            player_two = 'X';
            statistics_p1[5]++;
            statistics_p2[4]++;
        } else {
            printf("Invalid Sign! Choose X or O, FOOL!\n");
            goto sign;
        }
    }
    if (game_mode == 1) {
        printf("Player Two - Enter your name (max. 20 characters):");
        fgets(player_two_name, 20, stdin);
        player_two_name[strlen(player_two_name) - 1] = '\0';

        player2_stats_load();
    }
    printf("\n");
}


char who_wins() {
    for (int i = 0; i < 3; i++) { //checks rows for matching signs
        if ((board[i][0] == board[i][1]) && (board[i][0] == board[i][2])) {
            return board[i][0];
        }
    }

    for (int i = 0; i < 3; i++) { //checks columns for matching signs
        if ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i])) {
            return board[0][i];
        }
    }

    if ((board[0][0] == board[1][1]) && (board[0][0] == board[2][2])) {        //andere Lösung?
        return board[0][0];
    }
    if ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0])) {
        return board[0][2];
    }
    return ' ';
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

int freeSpace() {       // return 1 if full, return 0 if not
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

void player_1_turn() {
    int x, y;

    do {
        if (game_mode != 3) {
            printf("Player 1: Enter row# and column# seperated by SPACE (1-3):");
            scanf("%d %d", &x, &y);
            x--, y--;
            //printf("%d - %d", x, y);

            if (board[x][y] != ' ') {
                printf("This field has already been used!\n");
            } else {
                board[x][y] = player_one;
                statistics_p1[6]++;
                break;
            }
        }else {                                         //checks all empty field for number of adjecent (computer) player signs
            printf("COMPUTER'S TURN!\n");
            int computer_count[8] = {0, 0, 0, 0, 0, 0, 0, 0};      // counts fields the computer has already picked
            int computer_pick[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};                             // counts free fields
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int pos = i + (j * 3);
                    if (board[j][i] != ' ') {
                        computer_pick[pos] = 1;
                    } else {
                        computer_pick[pos] = 0;
                    }
                }

            }
            for (int i = 0; i < 3; i++) {                       // checks rows and columns sum of own player signs
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == player_one) {
                        computer_count[i]++;
                    }
                    if (board[j][i] == player_one) {
                        computer_count[i + 3]++;
                    }
                }
            }
            for (int k = 0;
                 k < 3; k++) {                           //checks diagonals - relevant for positions 0/2/4/6/8
                if (board[k][k] == player_one) {
                    computer_count[6]++;
                }
                if (board[2 - k][k] == player_one) {
                    computer_count[7]++;
                }
            }
            // get position of best empty field
            int record[3] = {0, 0, 0};             //0 = rows, 1 = columns, 2 = diagonals
            int lastbest;                      //start on random field OVERWRITES PLAYER TURN!!! do While-Loop (computerpick[lastbest] == 0)

            do {
                lastbest = rand() % 9;
            } while (computer_pick[lastbest] == 1);

            for (int k = 0; k < 9; k++) {
                //int j = computer_pick[k] % 3;               // for diagonals
                int i = computer_pick[k] / 3;

                if (computer_pick[k] == 0) {                 // if field is empty
                    if (computer_count[i] > record[0]) {   //checks rows for best fields
                        record[0] = computer_count[i];
                        lastbest = k;
                    }
                    if (computer_count[i + 3] > record[1]) { //checks columns for best fields
                        record[1] = computer_count[i + 3];
                        lastbest = k;
                    }
                }
            }
            y = lastbest % 3;
            x = lastbest / 3;
            sleep(1);
            board[x][y] = player_one;
            break;
        }
    } while (board[x][y] != ' ');
}

void player_2_turn() {
    int x, y;
        do {
            if (game_mode == 1) {
                printf("Player 2: Enter row# and column# seperated by SPACE (1-3):");
                scanf("%d %d", &x, &y);
                x--, y--;

                if (board[x][y] != ' ') {
                    printf("This field has already been used!\n");
                } else {
                    board[x][y] = player_two;
                    statistics_p2[6]++;
                    break;
                }
            } else {                                         //checks all empty field for number of adjecent (computer) player signs
                printf("COMPUTER'S TURN!\n");
                int computer_count[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // counts fields the computer has already picked
                int computer_pick[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};   // counts free fields
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int pos = i + (j * 3);
                        if (board[j][i] != ' ') {
                            computer_pick[pos] = 1;
                        } else {
                            computer_pick[pos] = 0;
                        }
                    }

                }
                for (int i = 0; i < 3; i++) {                       // checks rows and columns sum of own player signs
                    for (int j = 0; j < 3; j++) {
                        if (board[i][j] == player_two) {
                            computer_count[i]++;
                        }
                        if (board[j][i] == player_two) {
                            computer_count[i + 3]++;
                        }
                    }
                }
                for (int k = 0; k < 3; k++) {                           //checks diagonals - relevant for positions 0/2/4/6/8
                    if (board[k][k] == player_two) {
                        computer_count[6]++;
                    }
                    if (board[2 - k][k] == player_two) {
                        computer_count[7]++;
                    }
                }
                // get position of best empty field
                int record[3] = {0, 0, 0};             //0 = rows, 1 = columns, 2 = diagonals
                int lastbest;

                do {
                    lastbest = rand() % 9;                                   //start on random field - OVERWRITES PLAYER TURN!
                } while (computer_pick[lastbest] == 1);

                for (int k = 0; k < 9; k++) {
                    //int j = computer_pick[k] % 3;               // for diagonals
                    int i = computer_pick[k] / 3;

                    if (computer_pick[k] == 0) {                 // if field is empty
                        if (computer_count[i] > record[0]) {   //checks rows for best fields
                            record[0] = computer_count[i];
                            lastbest = k;
                        }
                        if (computer_count[i + 3] > record[1]) { //checks columns for best fields
                            record[1] = computer_count[i + 3];
                            lastbest = k;
                        }
                    }
                }
                y = lastbest % 3;
                x = lastbest / 3;
                sleep(1);
                board[x][y] = player_two;
                break;
            }
        } while (board[x][y] != ' ');
}


int main() {

    srand(time(NULL));
    char winner = ' ';
    int starting_player = (rand() % 2);

    winner = ' ';
    fillFreeSpace();
    playeroptions();

    while(winner == ' ' && freeSpace() != 9) {
        printBoard();
        if (starting_player == 0){
            player_1_turn();
        }else {
            player_2_turn();
        }
        winner = who_wins();
        freeSpace();
        starting_player++;
        starting_player = (starting_player % 2);

        if (winner != ' ' || freeSpace() == 9) {
            break;
        }
    }
    printBoard();

    if (winner != ' ' || freeSpace() == 9) {
        if(winner == player_one){
            if (game_mode == 3) {
                printf("The MACHINE wins!\n\nThe mind is nothing more than an involuntary ejaculation of the unavoidable entropy of infinite space.");
            }else {
                printf("%s WINS!\n\nAfter the sacrificing to the great Cthulhu comes the good feeling!", player_one_name);
                statistics_p1[0]++;
                statistics_p1[1]++;
                if (game_mode == 1) {
                    statistics_p2[0]++;
                    statistics_p2[2]++;
                }
            }
        }else if(winner == player_two) {
            printf("%s WINS!\n\nAfter the sacrificing to the great Cthulhu comes the good feeling!", player_two_name);
            if (game_mode == 1) {
                statistics_p1[0]++;
                statistics_p1[2]++;
                statistics_p2[0]++;
                statistics_p2[1]++;
            }
        }else {
            printf("THERE IS NO WINNER!\n\nThe mind is nothing more than an involuntary ejaculation of the unavoidable entropy of infinite space.");
            if (game_mode == 1) {
                statistics_p1[0]++;
                statistics_p1[3]++;
                statistics_p2[0]++;
                statistics_p2[3]++;
            }
        }
    }
    print_player_stats();
    player_stats_save();
    return 0;
}
/* To do:
 * Falsche Felder bei user Input abfangen: do while while (y < 0 || y > 2 || x < 0 || x > 2); funktioniert nicht??
 * freespace funktion: return 1 wenn full, return 0 wenn nicht???
 * Create function sourcefile and header*/

/*Check strlen of ech array! If full repeat Algorithm!
 * struct bla
 * Char Array1[max length of 5 fields]; <- Board[0][0]
 * Char Array2[max length of 5 fields]; <- Zierzeile
 * Char Array3[max length of 5 fields]; <- Board[1][1]
 * Char Array4[max length of 5 fields]; <- Zierzeile
 * Char Array5[max length of 5 fields]; <- Board[2][2]
 * Char ArrayPlayer1[Max length of char name[] * 5];
 * Char ArrayPlayer2[Max length of char name[] * 5];
 *
 * Fscanf in jedes der Arrays. dann mit strlen checken ob sie voll sind.
 * Wenn nein: strcat aktuelles Feld -> fseek zu file Anfang -> fprintf.
 * Wenn ja: vom gleichen FB (Zeiger ist jetzt am Ende der letzten Zeile von 5 Feldern) aus die Funktion wiederholen
 * (also arrays neu ausfüllen und wieder checken ob sie voll sind) */