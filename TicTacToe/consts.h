static const double VERSION = 0.5;
static const long BUILD_TIMESTAMP = 1608024689;

static const int DEBUG_MODE = 0;

static const int VALUE_USER = 1;
static const int VALUE_FREE = 0;
static const int VALUE_COMPUTER = -1;

static const int WIN_USER_WON = 1;
static const int WIN_COMPUTER_WON = -1;
static const int WIN_TIE = 2;
static const int WIN_NO_WIN_YET = 0;

static const char INPUT_YES_UPPERCASE = 'J';
static const char INPUT_YES_LOWERCASE = 'j';
static const char INPUT_NO_UPPERCASE = 'N';
static const char INPUT_NO_LOWERCASE = 'n';

static const char *OUTPUT_NEW_MOVE = "Bitte Zahl (0-8) eingeben: ";
static const char *OUTPUT_MOVED = "Gesetzt!\n";
static const char *OUTPUT_COMPUTER_MOVE_DONE = "Der Computer hat gespielt!\n";
static const char *OUTPUT_COMPUTER_MOVE_SKIPPED = "Der Computer hat diese Runde uebersprungen.\n";
static const char *OUTPUT_CURRENT_BOARD = "Aktuelles Feld:%s%s";
static const char *OUTPUT_CURRENT_BOARD_H_OUTLINES = "-------------\n";
static const char *OUTPUT_CURRENT_BOARD_MARGIN_CHARS = "\n\n";

static const char *OUTPUT_GAME_OVER_VICTORY = "Gewonnen! Du hast den Computer besiegt! GG! :)\n";
static const char *OUTPUT_GAME_OVER_TIE = "Unentschieden! Keiner von euch hat gewonnen! Erneut versuchen?\n";
static const char *OUTPUT_GAME_OVER_LOSS = "Verloren! Der Computer hat dich besiegt! :(\n";

static const char *OUTPUT_ERROR_FIELD_NOT_IN_RANGE = "Fehler: Die Zahl ist nicht innerhalb von 0 bis 8.\n";
static const char *OUTPUT_ERROR_FIELD_ALREADY_FILLED = "Fehler: Dieses Feld ist schon belegt.\n";

static const char *OUTPUT_DEBUG_COMPUTER_ON_OFF = "Soll der Computer spielen? (J/N): ";