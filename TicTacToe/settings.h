#include <stdbool.h>
#include "consts.h"

static bool COMPUTER_ACTIVE = true;
static bool DUMP_FIELD = DEBUG;
static enum difficulty {
    DIFFICULTY_PLAYER_VS_PLAYER,
    DIFFICULTY_COMPUTER_EASY,
    DIFFICULTY_COMPUTER_HARD
} DIFFICULTY = DIFFICULTY_COMPUTER_EASY;
