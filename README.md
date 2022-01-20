# C

FH Technikum BIC 1, HWSE Abschlussprojekt, Aelfric-Wieland Mayer ic21b111

#TicTacToe
##COMPILATION
gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter main.c functions.c -Iinclude -o tictactoe

##EXECUTE
./ tictactoe

No further arguments are needed, all player input happes during program runtime.

##GAMEPLAY
Player will be prompted to pick a name, a sign, and a game mode. Game modes include:
1. Player v Player
2. Player v PC
3. PC v PC
   In case of [2] the second player will also be prompted to pick a name but will be auto-assigned the leftover sign ('X' or 'O').
   Players will take turns assigning their sign to the board by inputting desired row and column. Game ends if either player scores three signs in a row or board is full.

##Logfiles
Game will create a file <playername>.txt to track individual player statistics (total games played, wins, losses, ties, times 'X' sign was picked, times 'O' sign was picked, total signs placed).
Game will also create a file logfile.txt which will save up to 5 previously played games (containing last board state and player names), after 5 saves the file will be overwritten.
Both files will automatically be printed at the end of the game (player statistics will only be printed if human players participated).

##TASKS
[x] Main Task

[x] 2. Task - Allow Human vs PC play and implement algorithm for PC turns.

[x] 3. Task - Extend the program to allow a PC vs PC play mode.

[x] 4. Task - Ask for player names and save player statistics into file.

[x] 5. Task - Save the result of the playfield including player names into a file.

[ ] 6. Task - Extend the program to use ncurses.