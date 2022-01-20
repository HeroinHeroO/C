#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

char board[3][3];
int game_mode = 0; // 1 = Player v Player, 2 = Player vs PC, 3 = PC v PC.
struct player one = {'X', "Human", 0, 0, 0, 0, 0, 0, 0};
struct player two = {'O', "MACHINE", 0, 0, 0, 0, 0, 0, 0};

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

/* put players in structs
 struct player {
 char sign;
 char name[15];
 int statistics[7]
 }*/
