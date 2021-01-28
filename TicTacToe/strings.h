static const char *INPUT_YES = "j";
static const char *INPUT_NO = "n";

static const char *INPUT_DIFFICULTY_EASY = "Leicht";
static const char *INPUT_DIFFICULTY_HARD = "Schwer";
static const char *INPUT_DIFFICULTY_PLAYER_VS_PLAYER = "2-Spieler-Modus";

static const char *OUTPUT_QUESTION_DIFFICULTY = "Schwierigkeitsgrad auswählen (Leicht/Schwer/2-Spieler-Modus): ";

static const char *OUTPUT_NEW_MOVE = "Bitte Zahl (1-9) eingeben: ";
static const char *OUTPUT_MOVED = "Gesetzt!\n";
static const char *OUTPUT_COMPUTER_MOVE_DONE = "Der Computer hat gespielt!\n";
static const char *OUTPUT_COMPUTER_MOVE_SKIPPED = "Der Computer hat diese Runde uebersprungen.\n";
static const char *OUTPUT_CURRENT_BOARD = "Aktuelles Feld:%s%s";
static const char *OUTPUT_CURRENT_BOARD_H_OUTLINES = "-------------\n";
static const char *OUTPUT_CURRENT_BOARD_MARGIN_CHARS = "\n\n";

static const char *OUTPUT_GAME_OVER_VICTORY = "Gewonnen! Du hast den Computer besiegt! GG! :)\n";
static const char *OUTPUT_GAME_OVER_TIE = "Unentschieden! Keiner von euch hat gewonnen! Erneut versuchen?\n";
static const char *OUTPUT_GAME_OVER_LOSS = "Verloren! Der Computer hat dich besiegt! :(\n";

static const char *OUTPUT_ERROR_FIELD_NOT_IN_RANGE = "Fehler: Die Zahl ist nicht innerhalb von 1 bis 9.\n";
static const char *OUTPUT_ERROR_FIELD_ALREADY_FILLED = "Fehler: Dieses Feld ist schon belegt.\n";

static const char *OUTPUT_ERROR_GENERIC_INVALID_INPUT = "Ungueltige Eingabe!\n";
static const char *OUTPUT_ERROR_GENERIC_HOW_DID_WE_GET_HERE = "How did we get here?!";

static const char *OUTPUT_DEBUG_COMPUTER_ON_OFF = "Soll der Computer spielen? (J/N): ";
static const char *OUTPUT_DEBUG_DUMP_FIELD = "Soll das Feld ausgegeben werden? (J/N): ";
