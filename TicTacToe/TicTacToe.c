#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "settings.h"

#ifdef _WIN32
#include <string.h>
#define strcasecmp _stricmp
#else // assuming POSIX or BSD compliant system
#include <strings.h>
#endif


int field[3][3];

int parseCommandlineArguments();

void fillBoard();

void processNewMove();

void computerMoveModeEasy();

void computerMoveEasyPick(int unavailableNumbers[], int unavailableNumbersSize, int pick);

void printPlayground();

bool isGameOverAndPrintMessages();

int currentWinner();

bool isBoardFull();


int main(int _argc, char *_argv[])
{
	int parsingResult = parseCommandlineArguments(_argc, _argv);
	if (parsingResult == COMMAND_PROCESSED_SUCCESS)
	{
		return EXIT_SUCCESS;
	}
	else if (parsingResult == COMMAND_PROCESSED_ERROR)
	{
		return EXIT_FAILURE;
	}

	fillBoard();
	srand(time(NULL));
	
	char *input;
	do
	{
		printf("%s", OUTPUT_QUESTION_DIFFICULTY);
		scanf("%s", input);

		if (!strcasecmp(input, INPUT_DIFFICULTY_EASY))
		{
			DIFFICULTY = DIFFICULTY_COMPUTER_EASY;
		}
		else if (!strcasecmp(input, INPUT_DIFFICULTY_HARD))
		{
			DIFFICULTY = DIFFICULTY_COMPUTER_HARD;
		}
		else if (!strcasecmp(input, INPUT_DIFFICULTY_PLAYER_VS_PLAYER))
		{
			DIFFICULTY = DIFFICULTY_PLAYER_VS_PLAYER;
		}
		else
		{
			printf("%s", OUTPUT_ERROR_GENERIC_INVALID_INPUT);
		}
		
	} while (strcasecmp(input, INPUT_DIFFICULTY_EASY) && strcasecmp(input, INPUT_DIFFICULTY_HARD) && strcasecmp(input, INPUT_DIFFICULTY_PLAYER_VS_PLAYER));

	if (DEBUG)
	{
		do
		{
			printf("%s", OUTPUT_DEBUG_COMPUTER_ON_OFF);
			scanf("%s", input);
			
			if (!strcasecmp(input, INPUT_YES))
			{
				COMPUTER_ACTIVE = true;
			}
			else if (!strcasecmp(input, INPUT_NO))
			{
				COMPUTER_ACTIVE = false;
			}
			else
			{
				printf("%s", OUTPUT_ERROR_GENERIC_INVALID_INPUT);
			}
		} while (strcasecmp(input, INPUT_YES) && strcasecmp(input, INPUT_NO));

		do
		{
			printf("%s", OUTPUT_DEBUG_DUMP_FIELD);
			scanf("%s", input);

			if (!strcasecmp(input, INPUT_YES))
			{
				DUMP_FIELD = true;
			}
			else if (!strcasecmp(input, INPUT_NO))
			{
				DUMP_FIELD = false;
			}
			else
			{
				printf("%s", OUTPUT_ERROR_GENERIC_INVALID_INPUT);
			}
			
		} while (strcasecmp(input, INPUT_YES) && strcasecmp(input, INPUT_NO));
	}

	processNewMove();
	return EXIT_SUCCESS;
}

int parseCommandlineArguments(int _argc, char *_argv[])
{
	if (_argc == 1)
	{
		return NO_COMMANDS_PROCESSED;
	}

	if (!strcasecmp(_argv[1], "--version") || !strcasecmp(_argv[1], "-V"))
	{
		time_t build_timestamp = (time_t)BUILD_TIMESTAMP;
		printf("Tic Tac Toe\n - Version %.1lf (%s)\n - by Javkhlanbayar Khongorzul (1DHIF)\n - Build date: %s", VERSION, DEBUG ? BUILD_FLAVOR_DEBUG : BUILD_FLAVOR_RELEASE, ctime(&build_timestamp));
	}
	else if (!strcasecmp(_argv[1], "--help"))
	{
		printf("There are definitely no secrets in here ;)\n");
	}
	else
	{
		return NO_COMMANDS_PROCESSED;
	}

	return COMMAND_PROCESSED_SUCCESS;
}

void fillBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = VALUE_FREE;
		}
	}
}

void processNewMove()
{
	int fieldNumber;

	printPlayground();

	printf("%s", OUTPUT_NEW_MOVE);
	scanf("%d", &fieldNumber);

	if (fieldNumber < 1 || fieldNumber > 9)
	{
		printf("%s", OUTPUT_ERROR_FIELD_NOT_IN_RANGE);
		processNewMove();
		return;
	}

	//Check if the fields are already filled
	if (fieldNumber > 6)
	{
		if (field[2][fieldNumber - 7] == VALUE_FREE)
		{
			field[2][fieldNumber - 7] = VALUE_USER;
		}
		else
		{
			printf("%s", OUTPUT_ERROR_FIELD_ALREADY_FILLED);
			processNewMove();
			return;
		}
	}
	else if (fieldNumber > 3 && fieldNumber < 7)
	{
		if (field[1][fieldNumber - 4] == VALUE_FREE)
		{
			field[1][fieldNumber - 4] = VALUE_USER;
		}
		else
		{
			printf("%s", OUTPUT_ERROR_FIELD_ALREADY_FILLED);
			processNewMove();
			return;
		}
	}
	else
	{
		if (field[0][fieldNumber - 1] == VALUE_FREE)
		{
			field[0][fieldNumber - 1] = VALUE_USER;
		}
		else
		{
			printf("%s", OUTPUT_ERROR_FIELD_ALREADY_FILLED);
			processNewMove();
			return;
		}
	}
	printf("%s", OUTPUT_MOVED);

	//Has someone won yet?
	if (isGameOverAndPrintMessages())
	{
		return;
	}

	//Game isn't over yet
	if (!COMPUTER_ACTIVE)
	{
		printf("%s", OUTPUT_COMPUTER_MOVE_SKIPPED);
		processNewMove();
		return;
	}

	if (DIFFICULTY == DIFFICULTY_COMPUTER_EASY)
	{
		computerMoveModeEasy();
	}
	else if (DIFFICULTY == DIFFICULTY_COMPUTER_HARD)
	{
		//TODO: Add hard game mode
	}
	else if (DIFFICULTY == DIFFICULTY_PLAYER_VS_PLAYER)
	{
		//TODO: Add 2 player game mode
	}
	else
	{
		printf("%s", OUTPUT_ERROR_GENERIC_HOW_DID_WE_GET_HERE);
	}
	
}

void computerMoveModeEasy()
{
	int pick = rand() % 9;
	int unavailableNumbers[9];
	int unavailableNumbersSize = 0;

	for (int xAxis = 0; xAxis < 3; xAxis++)
	{
		for (int yAxis = 0; yAxis < 3; yAxis++)
		{
			if (field[xAxis][yAxis] != VALUE_FREE)
			{
				unavailableNumbers[unavailableNumbersSize] = (xAxis * 3) + yAxis;
				unavailableNumbersSize++;
			}
		}
	}

	computerMoveEasyPick(unavailableNumbers, unavailableNumbersSize, pick);
}

void computerMoveEasyPick(int unavailableNumbers[], int unavailableNumbersSize, int pick)
{
	for (int index = 0; index < unavailableNumbersSize; index++)
	{
		if (pick == unavailableNumbers[index])
		{
			pick = rand() % 9;
			computerMoveEasyPick(unavailableNumbers, unavailableNumbersSize, pick);
			return;
		}
	}

	if (pick >= 6)
	{
		field[2][pick - 6] = VALUE_COMPUTER;
	}
	else if (pick >= 3 && pick < 6)
	{
		field[1][pick - 3] = VALUE_COMPUTER;
	}
	else
	{
		field[0][pick] = VALUE_COMPUTER;
	}

	if (isGameOverAndPrintMessages())
	{
		return;
	}

	printf("%s", OUTPUT_COMPUTER_MOVE_DONE);
	processNewMove();
}

void printPlayground()
{
	printf(OUTPUT_CURRENT_BOARD, OUTPUT_CURRENT_BOARD_MARGIN_CHARS, OUTPUT_CURRENT_BOARD_H_OUTLINES);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (j == 2)
			{
				printf("%c", field[i][0] == VALUE_COMPUTER ? 'O' : field[i][0] == VALUE_USER ? 'X' : ' ');
			}
			else if (j == 6)
			{
				printf("%c", field[i][1] == VALUE_COMPUTER ? 'O' : field[i][1] == VALUE_USER ? 'X' : ' ');
			}
			else if (j == 10)
			{
				printf("%c", field[i][2] == VALUE_COMPUTER ? 'O' : field[i][2] == VALUE_USER ? 'X' : ' ');
			}
			else if (j == 13)
			{
				printf("\n");
			}
			else
			{
				printf((j % 2 == 0) ? "|" : " ");
			}
		}
	}
	printf("%s", OUTPUT_CURRENT_BOARD_H_OUTLINES);
	printf("%s", OUTPUT_CURRENT_BOARD_MARGIN_CHARS);

	if (DUMP_FIELD)
	{
		printf("Dump of field:\n[");
		for (int i = 0; i < 9; i++)
		{
			if (i == 8)
			{
				printf("%d (i = %d)]\n", field[2][2], i);
			}
			else
			{
				printf("%d (i = %d), ", field[i < 3 ? 0 : i < 6 ? 1 : 2][i % 3], i);
			}
		}
	}
}

bool isGameOverAndPrintMessages()
{
	int winner = currentWinner();

	if (winner == WIN_NO_WIN_YET)
	{
		return false;
	}
	printPlayground();

	if (winner == WIN_COMPUTER_WON)
	{
		printf("%s", OUTPUT_GAME_OVER_LOSS);
	}
	else if (winner == WIN_USER_WON)
	{
		printf("%s", OUTPUT_GAME_OVER_VICTORY);
	}
	else if (winner == WIN_TIE)
	{
		printf("%s", OUTPUT_GAME_OVER_TIE);
	}

	return true;
}

int currentWinner()
{
	int winner = WIN_NO_WIN_YET;
	for (int i = 0; i < 2; i++)
	{
		int currentEntity = ((i == 0) ? VALUE_COMPUTER : VALUE_USER);
		if (DEBUG) printf("Field check for %s!\n", currentEntity == VALUE_COMPUTER ? "computer" : currentEntity == VALUE_USER ? "player" : "unknown");

		if (((field[0][0] == currentEntity) && (field[0][1] == currentEntity) && (field[0][2] == currentEntity)) || ((field[1][0] == currentEntity) && (field[1][1] == currentEntity) && (field[1][2] == currentEntity)) || ((field[2][0] == currentEntity) && (field[2][1] == currentEntity) && (field[2][2] == currentEntity)))
		{
			/*
			    X X X        _ _ _        _ _ _
			    _ _ _   or   X X X   or   _ _ _
			    _ _ _        _ _ _        X X X
			*/
			winner = currentEntity;
			break;
		}
		else if ((field[0][0] == currentEntity && field[1][0] == currentEntity && field[2][0] == currentEntity) || (field[0][1] == currentEntity && field[1][1] == currentEntity && field[2][1] == currentEntity) || (field[0][2] == currentEntity && field[1][2] == currentEntity && field[2][2] == currentEntity))
		{
			/*
			    X _ _        _ X _        _ _ X
			    X _ _   or   _ X _   or   _ _ X
			    X _ _        _ X _        _ _ X
			*/
			winner = currentEntity;
			break;
		}
		else if ((field[0][0] == currentEntity && field[1][1] == currentEntity && field[2][2] == currentEntity) || (field[0][2] == currentEntity && field[1][1] == currentEntity && field[2][0] == currentEntity))
		{
			/*
				X _ _        _ _ X
				_ X _   or   _ X _
				_ _ X        X _ _

			*/
			winner = currentEntity;
			break;
		}
	}
	if (DEBUG) printf("Winner: %d\n", winner);

	if (winner == WIN_NO_WIN_YET && isBoardFull())
	{
		winner = WIN_TIE;
	}

	return winner;
}

bool isBoardFull()
{
	bool notFull = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!notFull)
			{
				break;
			}

			notFull = field[i][j] != VALUE_FREE;
		}

		if (!notFull)
		{
			break;
		}
	}

	return notFull;
}
