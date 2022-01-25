/**
 * \file
 * \brief functions header*/
#ifndef TICTACTOE_BIC2021_FUNCTIONS_H
#define TICTACTOE_BIC2021_FUNCTIONS_H
#define MAXPRINTLENG 75
#define MAXPLAYERNAME 15
/**
 * \brief external variables - global variables from main.c used in functions
 */

extern char board[3][3];
extern int game_mode;

/**
 * Länge sollte durch ein MAKRO definiert werden!
 */
struct logfile {
    char array1[MAXPRINTLENG];
    char array2[MAXPRINTLENG];
    char array3[MAXPRINTLENG];
    char array4[MAXPRINTLENG];
    char array5[MAXPRINTLENG];
    char array6[MAXPRINTLENG];
    char array7[MAXPRINTLENG];
};

/**
 * Länge sollte durch ein MAKRO definiert werden!
 */
struct player {
    char sign;
    char name[MAXPLAYERNAME];
    int statistics[7];
};

extern struct player one;
extern struct player two;

/**
 * \brief function prototypes - see functions.c for detailed decriptions
 */

void print_player_stats();

void player1_stats_load();

void player2_stats_load();

void player_stats_save();

void save_board();

void player_options();

char who_wins();

void fill_free_spaces();

void print_board();

int free_space();

void player_1_turn();

void player_2_turn();

#endif //TICTACTOE_BIC2021_FUNCTIONS_H
