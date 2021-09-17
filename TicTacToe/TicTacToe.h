
/* Core methods */

void fillBoard();

int parseCommandlineArguments();

void printPlayground();

void processNewMove();


/* Helper methods */

int currentWinner();

bool isBoardFull();

bool isGameOverAndPrintMessages();


/* Various computer "AI" methods */

void computerMoveEasyPick(int unavailableNumbers[], int unavailableNumbersSize, int pick);

void computerMoveModeEasy();

void computerMoveModeHard();