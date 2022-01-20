#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

/**
 * \brief function prompts the player to enter name, desired sign ('X' or 'O') and game mode.
 *
 * Player name is written into global player struct in main.c
 * Game mode is picked: 1 = Player v Player, 2 = Player vs PC, 3 = PC v PC.
 * If game mode == 2, player two will also pick a name.
 *
 * calls the player_stats_load function as soon as player names are chosen.
 *
 * void function, no return value.
 */
void player_options() {
    char player_one_sign;

    printf("Player One - Enter your name (max. 14 characters):");
    fgets(one.name, 14, stdin);
    one.name[strlen(one.name) - 1] = '\0';

    if (game_mode != 3) {
        player1_stats_load();
    }

    int tmpmode;
    printf("\nChoose a game mode!\n1: Human versus Human\n2: Human versus Machine\n3: BATTLE OF THE MACHINES!\nPress 4 to flee now!\n");
    tmpmode = getchar();
    getchar();
    tmpmode = tmpmode -48; /// 1-9 on ASCII TABLE
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
        printf("%s, chose your sign: X or O\n", one.name);
        player_one_sign = getchar();
        getchar();
        if (player_one_sign == 'x' || player_one_sign == 'X') {
            one.sign = 'X';
            two.sign = 'O';
            one.statistics[4]++;
            two.statistics[5]++;
        } else if (player_one_sign == 'o' || player_one_sign == 'O') {
            one.sign = 'O';
            two.sign = 'X';
            one.statistics[5]++;
            two.statistics[4]++;
        } else {
            printf("Invalid Sign! Choose X or O, FOOL!\n");
            goto sign;
        }
    }
    if (game_mode == 1) {
        printf("Player Two - Enter your name (max. 14 characters):");
        fgets(two.name, 14, stdin);
        two.name[strlen(two.name) - 1] = '\0';

        player2_stats_load();
    }
    printf("\n");
}

/**
 * \brief function to load statistics from <playername>.txt into player statistics global variable.
 *
 * If fopen() with "r" fails (no file exists) player will be greeted as new.
 * If fflush() or fclose() fails game will abort.
 *
 * void function, no return value.
 */
void player1_stats_load() {
    char player_one_file[25];
    strcpy(player_one_file, one.name);
    strcat(player_one_file, ".txt");

    FILE *fptr;
    int num;
    if ((fptr = fopen(player_one_file, "r")) == NULL) {
        printf("You seem to be new here, %s, good luck - you WILL need it!\n", one.name);
    } else {
        for (int i = 0; i < 7; i++) {
            fscanf(fptr, "%d", &num);
            one.statistics[i] = num;
        }
        if (fflush(fptr) != 0) {
            fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", one.name);
            return;
        }
        if (fclose(fptr) != 0) {
            fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", one.name);
            return;
        }
    }
}

/**
 * \brief function to load statistics from <playername>.txt into player statistics global variable.
 *
 * same as player1_stats_load but only called if player vs player mode is selected.
 * If fopen() with "r" fails (no file exists) player will be greeted as new.
 * If fflush() or fclose() fails game will abort.
 *
 * void function, no return value.
 */
void player2_stats_load() {
    char player_two_file[25];
    strcpy(player_two_file, two.name);
    strcat(player_two_file, ".txt");

    FILE* fptr2;
    int num;
    if ((fptr2 = fopen(player_two_file, "r")) == NULL) {
        printf("You seem to be new here, %s, good luck - you WILL need it!\n", two.name);
    }else {
        for (int i = 0; i < 7; i++) {
            fscanf(fptr2, "%d", &num);
            two.statistics[i] = num;
        }
        if (fflush(fptr2) != 0) {
            fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", two.name);
            return;
        }
        if (fclose(fptr2) != 0) {
            fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", one.name);
            return;
        }
    }
}

/**
 * \brief function to save player statistics into <playername>.txt file.
 *
 * Saves numbers from global player statistics variable (that has previously been loaded from file) into a textfile.
 * Repeats for player two if palyer v player mode was selected.
 *
 * Aborts program if any fflush() or fopen() fails.
 * void function, no return value.
 */
void player_stats_save() {
    char player_one_file[25];
    strcpy(player_one_file, one.name);
    strcat(player_one_file, ".txt");

    FILE* fptr;
    if ((fptr = fopen(player_one_file, "w")) == NULL) {
        fprintf(stderr, "ERROR: Cannot open statistics file for %s!\n", one.name);
        return;
    }
    for (int i = 0; i < 7; i++) {
        fprintf(fptr, "%d ", one.statistics[i]);
    }
    if (game_mode != 3){
        printf("Statistics for %s saved!\n", one.name);
    }
    if (fflush(fptr) != 0) {
        fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", one.name);
        return;
    }
    if (fclose(fptr) != 0) {
        fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", one.name);
        return;
    }

    if (game_mode == 1) {
        FILE *fptr2;
        char player_two_file[25];
        strcpy(player_two_file, two.name);
        strcat(player_two_file, ".txt");

        if ((fptr2 = fopen(player_two_file, "w")) == NULL) {
            fprintf(stderr, "ERROR: Cannot open statistics file for %s!\n", two.name);
            return;
        }
        for (int i = 0; i < 7; i++) {
            fprintf(fptr2, "%d ", two.statistics[i]);
        }
        printf("Statistics for %s saved!\n", two.name);

        if (fflush(fptr2) != 0) {
            fprintf(stderr, "ERROR: Flushing statistics file buffer for %s failed!\n", two.name);
            return;
        }
        if (fclose(fptr2) != 0) {
            fprintf(stderr, "ERROR: Closing statistics file for %s was unsuccessful!\n", one.name);
            return;
        }
    }
}

/**
 * \brief function to handle player and PC turns.
 *
 * Player is prompted to pick a row and column, then the global variable board[3][3] is set to player sign on corresponding index.
 * Invalid choices will lead to repeated prompt.
 *
 * If game mode PC v PC has been selected, function will instead execute the algorithm to pick a field:
 * First the 2D array will be scanned for horizontal, diagonal and vertical lines where the computer has already picked a field.
 * Then the array will be scanned for free fields.
 * Then tries to find a free field with the most computer signs in any line.
 * Prefers columns to rows and therefore often makes objectively bad picks.
 * First pick is random.
 *
 * sleep() function is used to make the computer opponent pause before its pick.
 *
 * void function, no return value.
 */
void player_1_turn() {
    int x = 0, y = 0;

    do {
        ///checks all empty field for number of adjecent (computer) player signs
        if (game_mode != 3) {
            printf("Player 1: Enter row# and column# seperated by SPACE (1-3):");
            scanf("%d %d", &x, &y);
            x--, y--;

            if (board[x][y] != ' ') {
                if (x < 0 || x > 2 || y < 0 || y > 2) {
                    printf("YOUR CHOICE IS BAD AND YOU SHOULD FEEL BAD!\n");
                } else {
                    printf("TOO SLOW! This field has already been used!\n");
                }
            } else {
                board[x][y] = one.sign;
                one.statistics[6]++;
                break;
            }
        }else {
            printf("COMPUTER'S TURN!\n");
            int computer_count[8] = {0, 0, 0, 0, 0, 0, 0, 0};              /// counts horizontal, diagonal and vertical lines where the computer has already picked a field
            int computer_pick[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};       /// counts free fields
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
            /// checks rows and columns sum of own player signs
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == one.sign) {
                        computer_count[i]++;
                    }
                    if (board[j][i] == one.sign) {
                        computer_count[i + 3]++;
                    }
                }
            }
            for (int k = 0;
                 k < 3; k++) {                           //checks diagonals - relevant for positions 0/2/4/6/8
                if (board[k][k] == one.sign) {
                    computer_count[6]++;
                }
                if (board[2 - k][k] == one.sign) {
                    computer_count[7]++;
                }
            }
            /// get position of best empty field
            int record[3] = {0, 0, 0};             ///0 = rows, 1 = columns, 2 = diagonals, weighs possible picks
            int lastbest;

            do {
                lastbest = rand() % 9;
            } while (computer_pick[lastbest] == 1);

            for (int k = 0; k < 9; k++) {
                //int j = computer_pick[k] % 3;               // for diagonals - unused
                int i = computer_pick[k] / 3;

                if (computer_pick[k] == 0) {                 /// if field is empty
                    if (computer_count[i] > record[0]) {   ///checks rows for best fields
                        record[0] = computer_count[i];
                        lastbest = k;
                    }
                    if (computer_count[i + 3] > record[1]) { ///checks columns for best fields
                        record[1] = computer_count[i + 3];
                        lastbest = k;
                    }
                }
            }
            y = lastbest % 3;
            x = lastbest / 3;
            sleep(1);
            board[x][y] = one.sign;
            break;
        }
    } while (board[x][y] != ' ');
}

/**
 * \brief function to handle player and PC turns.
 *
 * Player is prompted to pick a row and column, then the global variable board[3][3] is set to player sign on corresponding index.
 * Invalid choices will lead to repeated prompt.
 *
 * If game mode player v PC or PC v PC has been selected, function will instead execute the algorithm to pick a field:
 * First the 2D array will be scanned for horizontal, diagonal and vertical lines where the computer has already picked a field.
 * Then the array will be scanned for free fields.
 * Then tries to find a free field with the most computer signs in any line.
 * Prefers columns to rows and therefore often makes objectively bad picks.
 * First pick is random.
 *
 * sleep() function is used to make the computer opponent pause before its pick.
 *
 * void function, no return value.
 */
void player_2_turn() {
    int x, y;
    do {
        ///checks all empty field for number of adjecent (computer) player signs
        if (game_mode == 1) {
            printf("Player 2: Enter row# and column# seperated by SPACE (1-3):");
            scanf("%d %d", &x, &y);
            x--, y--;

            if (board[x][y] != ' ') {
                if (x < 0 || x > 2 || y < 0 || y > 2) {
                    printf("YOUR CHOICE IS BAD AND YOU SHOULD FEEL BAD!\n");
                } else {
                    printf("TOO SLOW! This field has already been used!\n");
                }
            } else {
                board[x][y] = two.sign;
                two.statistics[6]++;
                break;
            }
        } else {
            printf("COMPUTER'S TURN!\n");
            int computer_count[8] = {0, 0, 0, 0, 0, 0, 0, 0}; /// counts fields the computer has already picked
            int computer_pick[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};   /// counts free fields
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
            for (int i = 0; i < 3; i++) {                       /// checks rows and columns sum of own player signs
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == two.sign) {
                        computer_count[i]++;
                    }
                    if (board[j][i] == two.sign) {
                        computer_count[i + 3]++;
                    }
                }
            }
            for (int k = 0; k < 3; k++) {                           ///checks diagonals - relevant for positions 0/2/4/6/8
                if (board[k][k] == two.sign) {
                    computer_count[6]++;
                }
                if (board[2 - k][k] == two.sign) {
                    computer_count[7]++;
                }
            }
            /// get position of best empty field
            int record[3] = {0, 0, 0};             ///0 = rows, 1 = columns, 2 = diagonals
            int lastbest;

            do {
                lastbest = rand() % 9;                                   ///start on random field - OVERWRITES PLAYER TURN!
            } while (computer_pick[lastbest] == 1);

            for (int k = 0; k < 9; k++) {
                //int j = computer_pick[k] % 3;               // for diagonals unused
                int i = computer_pick[k] / 3;

                if (computer_pick[k] == 0) {                 /// if field is empty
                    if (computer_count[i] > record[0]) {   ///checks rows for best fields
                        record[0] = computer_count[i];
                        lastbest = k;
                    }
                    if (computer_count[i + 3] > record[1]) { ///checks columns for best fields
                        record[1] = computer_count[i + 3];
                        lastbest = k;
                    }
                }
            }
            y = lastbest % 3;
            x = lastbest / 3;
            sleep(1);
            board[x][y] = two.sign;
            break;
        }
    } while (board[x][y] != ' ');
}

/**
 * \brief function to check if the game has a winner.
 *
 * is called after every player or PC turn to evaluate all winning lines of three matching signs.
 *
 * @return returns the char that is stored in corresponding index of the global 2D array board[3][3] ('X' or 'O') or a whitespace if no winner is found.
 */
char who_wins() {
    ///checks rows for matching signs
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1]) && (board[i][0] == board[i][2])) {
            return board[i][0];
        }
    }

    ///checks columns for matching signs
    for (int i = 0; i < 3; i++) {
        if ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i])) {
            return board[0][i];
        }
    }

    ///check diagonals for matching signs
    if ((board[0][0] == board[1][1]) && (board[0][0] == board[2][2])) {
        return board[0][0];
    }
    if ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0])) {
        return board[0][2];
    }
    return ' ';
}

/**
 * \brief funtion to fill global board[3][3] array with whitespaces.
 *
 * Function is called at the start of every game to ensure all indexes are whitespaces.
 * Idea taken from http://www.cprogrammingnotes.com/question/tic-tac-toe-game.html
 *
 * void function, no return value.
 */
void fill_free_spaces() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

/**
 * \brief function to print out the board state after every turn.
 *
 * Prints the outlines of the board and fills them with the player sign chars stored in global array board[3][3].
 *
 * void function, no return value.
 */
void print_board() {
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

/**
 * \brief function to check board for free space
 *
 * function is called after every turn to determine if game is over due to no empty space being available.
 *
 * @return returns the number of taken fields on the field. Loop in main.c will terminate if this returns 9.
 */
int free_space() {
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

/**
 * \brief function to print last board state into logfile.txt file. Saves 5 boards and then overwrites file.
 *
 * Opens logfile.txt if it exists and reads content into logfile struct pointer (each line intro a different array). Empties arrays if 5 boards have been read using memset().
 * Puts board outlines and characters from global array board[3][3] into char array (one per line) unsing sprintf().
 * Adds current board state from arrays into logfile struct array pointers using strcat().
 * Prints arrays from logfile struct array pointers into logfile.txt, then prints the content of the file on stdout.
 *
 * Aborts program if any fflus() or fclose() fails.
 *
 * void function, no return value.
 */
void save_board() {

    //load or create logfile
    struct logfile *saves = calloc(1, sizeof(struct logfile));

    FILE* fptr3;
    char gamelog[12] = "logfile.txt";



    //fill player names with whitespace to match board length
    int p1end = strlen(one.name) -1;
    for (int i = 1; i <= (14 - p1end); i++) {
        one.name[p1end + i] = '.';
    }

    int p2end = strlen(two.name) -1;
    for (int i = 1; i <= (14 - p2end); i++) {
        two.name[p2end + i] = '.';
    }

    if ((fptr3 = fopen(gamelog, "r")) != NULL) {

        // scan file for prev. boards and save into struct. Overwrite File if 5 Boards are printed next to each other

        if(strlen(saves->array1) < 75) {
            fgets(saves->array1, 76, fptr3);
            saves->array1[strlen(saves->array1) - 1] = '\0';
            fgets(saves->array2, 76, fptr3);
            saves->array2[strlen(saves->array2) - 1] = '\0';
            fgets(saves->array3, 76, fptr3);
            saves->array3[strlen(saves->array3) - 1] = '\0';
            fgets(saves->array4, 76, fptr3);
            saves->array4[strlen(saves->array4) - 1] = '\0';
            fgets(saves->array5, 76, fptr3);
            saves->array5[strlen(saves->array5) - 1] = '\0';
            fgets(saves->array6, 76, fptr3);
            saves->array6[strlen(saves->array6) - 1] = '\0';
            fgets(saves->array7, 76, fptr3);
            saves->array7[strlen(saves->array7) - 1] = '\0';

            if (strlen(saves->array1) >= 74) {
                memset(saves->array1, 0, strlen(saves->array1));
                memset(saves->array2, 0, strlen(saves->array2));
                memset(saves->array3, 0, strlen(saves->array3));
                memset(saves->array4, 0, strlen(saves->array4));
                memset(saves->array5, 0, strlen(saves->array5));
                memset(saves->array6, 0, strlen(saves->array6));
                memset(saves->array7, 0, strlen(saves->array7));
            }
        }

        if (fflush(fptr3) != 0) {
            fprintf(stderr, "ERROR: Flushing logfile buffer failed!\n");
            return;
        }
        if (fclose(fptr3) != 0) {
            fprintf(stderr, "ERROR: Closing logfile was unsuccessful!\n");
            return;
        }
    }
    //add current board to each array

    char boardline1[16];
    char boardline2[16];
    char boardline3[16];

    sprintf(boardline1, "| %c || %c || %c |", board[0][0], board[0][1], board[0][2]);
    sprintf(boardline2, "| %c || %c || %c |", board[1][0], board[1][1], board[1][2]);
    sprintf(boardline3, "| %c || %c || %c |", board[2][0], board[2][1], board[2][2]);

    strcat(saves->array1, boardline1);
    strcat(saves->array2, "|---||---||---|");
    strcat(saves->array3, boardline2);
    strcat(saves->array4, "|---||---||---|");
    strcat(saves->array5, boardline3);
    strcat(saves->array6, one.name);
    strcat(saves->array7, two.name);

    //create logfile if it doesn't exist
    if ((fptr3 = fopen(gamelog, "w")) == NULL) {
        fprintf(stderr, "ERROR: Opening logfile failed!\n");
        return;
    }
    if (fflush(fptr3) != 0) {
        fprintf(stderr, "ERROR: Flushing logfile buffer failed!\n");
        return;
    }
    if (fclose(fptr3) != 0) {
        fprintf(stderr, "ERROR: Closing logfile was unsuccessful!\n");
        return;
    }
    //print arrays into logfile

    if ((fptr3 = fopen(gamelog, "a")) == NULL) {
        fprintf(stderr, "ERROR: Opening logfile failed!\n");
        return;
    }
    fprintf(fptr3, "%s\n", saves->array1);
    fprintf(fptr3, "%s\n", saves->array2);
    fprintf(fptr3, "%s\n", saves->array3);
    fprintf(fptr3, "%s\n", saves->array4);
    fprintf(fptr3, "%s\n", saves->array5);
    fprintf(fptr3, "%s\n", saves->array6);
    fprintf(fptr3, "%s\n", saves->array7);

    printf("\n\nPREVIOUSLY SAVED BOARDS:\n\n");
    printf("%s\n", saves->array1);
    printf("%s\n", saves->array2);
    printf("%s\n", saves->array3);
    printf("%s\n", saves->array4);
    printf("%s\n", saves->array5);
    printf("%s\n", saves->array6);
    printf("%s\n", saves->array7);

    if (fflush(fptr3) != 0) {
        fprintf(stderr, "ERROR: Flushing logfile buffer failed!\n");
        return;
    }
    if (fclose(fptr3) != 0) {
        fprintf(stderr, "ERROR: Closing logfile was unsuccessful!\n");
        return;
    }
    free(saves);
    return;
}

/**
 *\brief function to print player statistics after each game.
 *
 * Prints player statistics from statistics array in global player structs onto stdout according to game mode.
 */
void print_player_stats() {
    if (game_mode == 3) {
        return;
    } else if (game_mode == 2) {
        printf("\n\nPLAYER STATISTICS:\n\n");
        printf("LIFETIME GAMES PLAYED: %d - PATHETIC!\n", one.statistics[0]);
        printf("TOTAL WINS: %d - WEAK!\n", one.statistics[1]);
        printf("GAMES LOST: %d - SOUL CRUSHING!\n", one.statistics[2]);
        printf("TIE GAMES: %d - PITIFUL!\n", one.statistics[3]);
        printf("You have picked the X %d times and the O %d times - BAD CHOICE!\n", one.statistics[4],one.statistics[5]);
        printf("You have marked the BATTLEFIELD OF BLOOD %d times! - BLOOD FOR THE BLOOD GOD!\n", one.statistics[6]);
    } else if (game_mode == 1) {
        printf("\n\nPLAYER STATISTICS:\n\n");
        printf("LIFETIME GAMES PLAYED: %s: %d - %s: %d - PATHETIC!\n", one.name, one.statistics[0], two.name, two.statistics[0]);
        printf("TOTAL WINS: %s: %d - %s: %d: - WEAK!\n", one.name, one.statistics[1], two.name, two.statistics[1]);
        printf("GAMES LOST: %s: %d - %s: %d - SOUL CRUSHING!\n", one.name, one.statistics[2], two.name, two.statistics[2]);
        printf("TIE GAMES: %s: %d - %s: %d - PITIFUL!\n", one.name, one.statistics[3], two.name, two.statistics[3]);
        printf("%s has picked the X %d times and the O %d times - BAD CHOICE!\n", one.name, one.statistics[4],one.statistics[5]);
        printf("%s chose X %d times placed the O %d times - ROOKIE MISTAKE!\n", two.name, two.statistics[4],two.statistics[5]);
        printf("%s has marked the BATTLEFIELD OF BLOOD %d times!\n", one.name, one.statistics[6]);
        printf("%s scorched their sign into SACRED GROUND %d times!\n", two.name, two.statistics[6]);
        printf("\n\n THE BATTLE IS OVER! You may flee now - or return IF YOU DARE!!!\n\n");
    }
}