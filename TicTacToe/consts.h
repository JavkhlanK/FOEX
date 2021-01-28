#include <stdbool.h>
#include "strings.h"

static const bool DEBUG = true;
static const double VERSION = 0.5;
static const long BUILD_TIMESTAMP = 1610540087;
static const char *BUILD_FLAVOR_DEBUG = "Debug";
static const char *BUILD_FLAVOR_RELEASE = "Release";

static const int NO_COMMANDS_PROCESSED = 1;
static const int COMMAND_PROCESSED_SUCCESS = 0;
static const int COMMAND_PROCESSED_ERROR = -1;

static const int VALUE_USER = 1;
static const int VALUE_FREE = 0;
static const int VALUE_COMPUTER = -1;

static const int WIN_USER_WON = VALUE_USER;
static const int WIN_COMPUTER_WON = VALUE_COMPUTER;
static const int WIN_TIE = 2;
static const int WIN_NO_WIN_YET = 0;
