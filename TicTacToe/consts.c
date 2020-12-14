#include "consts.h"

const int DEBUG_MODE = 0;

const int VALUE_USER = 1;
const int VALUE_FREE = 0;
const int VALUE_COMPUTER = -1;

const int WIN_USER_WON = 1;
const int WIN_COMPUTER_WON = -1;
const int WIN_TIE = 2;
const int WIN_NO_WIN_YET = 0;

const char *OUTPUT_NEW_MOVE = "Bitte Zahl (0-8) eingeben: ";
const char *OUTPUT_COMPUTER_MOVE_DONE = "Der Computer hat gespielt!\n";

const char *OUTPUT_GAME_OVER_VICTORY = "Gewonnen! Du hast den Computer besiegt! GG! :)\n";
const char *OUTPUT_GAME_OVER_TIE = "Unentschieden! Keiner von euch hat gewonnen! Erneut versuchen?\n";
const char *OUTPUT_GAME_OVER_LOSS = "Verloren! Der Computer hat dich besiegt! :(\n";

const char *OUTPUT_ERROR_FIELD_NOT_IN_RANGE = "Fehler: Die Zahl ist nicht innerhalb von 0 bis 8\n";
const char *OUTPUT_ERROR_FIELD_ALREADY_FILLED = "Fehler: Dieses Feld ist schon belegt\n";