/**
 * \file
 * \brief main file*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"

/**
 *  \brief Global variables that are used in most if not all functions.
 *
 * board[3][3] saves the player signs placed on the battlefield.
 * game_mode is used to select a mode: Player v Player, 2 = Player vs PC, 3 = PC v PC.
 * player one and two are used to store the players' sign, name and their statistics:
 * [0]games played, [1]wins, [2]losses, [3]tie games, [4]games with 'X' sign, [5]games with O sign, [6]total signs placed.
 */
char board[3][3];
int game_mode = 0;
struct player one = {'X', "Human", 0, 0, 0, 0, 0, 0, 0};
struct player two = {'O', "MACHINE", 0, 0, 0, 0, 0, 0, 0};

/**
 * \brief The Game.
 *
 * Game loops a sequence of functions as long as the winner variable == whitespace or the free_space function
 * doesn't return 9 (all fields full).
 *
 * Idea for winner variable taken from https://www.usna.edu/Users/cs/roche/courses/s17si204/notes/06/files.php?f=tictactoe.c
 */
int main(void) {

    srand(time(NULL));
    char winner = ' ';
    int starting_player = (rand() % 2);

    fill_free_spaces();
    player_options();

    while(winner == ' ' && free_space() != 9) {
        print_board();
        if (starting_player == 0){
            player_1_turn();
        }else {
            player_2_turn();
        }
        winner = who_wins();
        free_space();
        starting_player++;
        starting_player = (starting_player % 2);

        if (winner != ' ' || free_space() == 9) {
            break;
        }
    }
    print_board();

    if (winner != ' ' || free_space() == 9) {
        if(winner == one.sign){
            if (game_mode == 3) {
                printf("The MACHINE wins!\n\nThe mind is nothing more than an involuntary ejaculation of the unavoidable entropy of infinite space.");
            } else {
                printf("%s WINS!\n\nAfter the sacrificing to the great Cthulhu comes the good feeling!", one.name);
                one.statistics[0]++;
                one.statistics[1]++;
                if (game_mode == 1) {
                    two.statistics[0]++;
                    two.statistics[2]++;
                }
            }
        } else if(winner == two.sign) {
            printf("%s WINS!\n\nAfter the sacrificing to the great Cthulhu comes the good feeling!", two.name);
            if (game_mode == 1) {
                one.statistics[0]++;
                one.statistics[2]++;
                two.statistics[0]++;
                two.statistics[1]++;
            }
        } else {
            printf("THERE IS NO WINNER!\n\nThe mind is nothing more than an involuntary ejaculation of the unavoidable entropy of infinite space.");
            if (game_mode == 1) {
                one.statistics[0]++;
                one.statistics[3]++;
                two.statistics[0]++;
                two.statistics[3]++;
            }
        }
    }
    print_player_stats();
    player_stats_save();
    save_board();

    return 0;
}
