#include "consts.h"

const int DEBUG_MODE = 0;

const int VALUE_USER = 1;
const int VALUE_FREE = 0;
const int VALUE_COMPUTER = -1;

const int WIN_USER_WON = 1;
const int WIN_COMPUTER_WON = -1;
const int WIN_TIE = 2;
const int WIN_NO_WIN_YET = 0;

const char INPUT_YES_UPPERCASE = 'Y';
const char INPUT_YES_LOWERCASE = 'y';
const char INPUT_NO_UPPERCASE = 'N';
const char INPUT_NO_LOWERCASE = 'n';

const char *OUTPUT_NEW_MOVE = "Please enter a number (0-8): ";
const char *OUTPUT_MOVED = "Set!\n";
const char *OUTPUT_COMPUTER_MOVE_DONE = "The computer has played!\n";
const char *OUTPUT_COMPUTER_MOVE_SKIPPED = "The computer skipped this round.\n";
const char *OUTPUT_CURRENT_BOARD = "Current board:%s%s";
const char *OUTPUT_CURRENT_BOARD_H_OUTLINES = "-------------\n";
const char *OUTPUT_CURRENT_BOARD_MARGIN_CHARS = "\n\n";

const char *OUTPUT_GAME_OVER_VICTORY = "You win! You defeated the computer! GG! :)\n";
const char *OUTPUT_GAME_OVER_TIE = "Tie! No one won. Try again?\n";
const char *OUTPUT_GAME_OVER_LOSS = "You lose! The computer defeated you! :(\n";

const char *OUTPUT_ERROR_FIELD_NOT_IN_RANGE = "Error: Please enter a number ranging from 0 to 8.\n";
const char *OUTPUT_ERROR_FIELD_ALREADY_FILLED = "Error: This cell is already set.\n";

const char *OUTPUT_DEBUG_COMPUTER_ON_OFF = "Should the computer play? (Y/N): ";