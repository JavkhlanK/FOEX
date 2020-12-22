#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "consts.h"
#include "settings.h"

int field[3][3];


int parseCommandlineArguments();

void fillBoard();

void processNewMove();

void computerMove(int unavailableNumbers[], int unavailableNumbersSize, int pick);

void printPlayground();

int checkIfGameIsOver();

int currentWinner();


int main(int _argc, char *_argv[])
{
	int wasArgumentSuccessfullyParsed = parseCommandlineArguments(_argc, _argv);
	if (wasArgumentSuccessfullyParsed == COMMAND_PROCESSED_SUCCESS)
	{
		return EXIT_SUCCESS;
	}
	else if (wasArgumentSuccessfullyParsed == COMMAND_PROCESSED_ERROR)
	{
		return EXIT_FAILURE;
	}

	fillBoard();
	srand(time(NULL));

	if (DEBUG == 1)
	{
		char answer;
		printf(OUTPUT_DEBUG_COMPUTER_ON_OFF);
		scanf("%c", &answer);

		if (answer == INPUT_YES_UPPERCASE || answer == INPUT_YES_LOWERCASE)
		{
			COMPUTER_ACTIVE = 1;
		}
		else if (answer == INPUT_NO_UPPERCASE || answer == INPUT_NO_LOWERCASE)
		{
			COMPUTER_ACTIVE = 0;
		}
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

	if (strcmp(_argv[1], "--version") == 0)
	{
		time_t build_timestamp = (time_t) BUILD_TIMESTAMP;
		printf("Tic Tac Toe\n - Version %.1lf (%s)\n - by Javkhlanbayar Khongorzul (1DHIF)\n - Build date: %s", VERSION, DEBUG == 0 ? BUILD_FLAVOR_RELEASE : BUILD_FLAVOR_DEBUG, ctime(&build_timestamp));
	}
	else if (strcmp(_argv[1], "--help") == 0)
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

	printf(OUTPUT_NEW_MOVE);
	scanf("%d", &fieldNumber);

	if (fieldNumber < 1 || fieldNumber > 9)
	{
		printf(OUTPUT_ERROR_FIELD_NOT_IN_RANGE);
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
			printf(OUTPUT_ERROR_FIELD_ALREADY_FILLED);
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
			printf(OUTPUT_ERROR_FIELD_ALREADY_FILLED);
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
			printf(OUTPUT_ERROR_FIELD_ALREADY_FILLED);
			processNewMove();
			return;
		}
	}
	printf(OUTPUT_MOVED);

	//Has someone won yet?
	if (checkIfGameIsOver() != WIN_NO_WIN_YET)
	{
		return;
	}

	//Game isn't over yet
	if (COMPUTER_ACTIVE == 0)
	{
		printf(OUTPUT_COMPUTER_MOVE_SKIPPED);
		processNewMove();
		return;
	}
	//Easy AI mode
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
	computerMove(unavailableNumbers, unavailableNumbersSize, pick);
}

void computerMove(int unavailableNumbers[], int unavailableNumbersSize, int pick)
{
	for (int index = 0; index < unavailableNumbersSize; index++)
	{
		if (pick == unavailableNumbers[index])
		{
			pick = rand() % 9;
			computerMove(unavailableNumbers, unavailableNumbersSize, pick);
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

	printf(OUTPUT_COMPUTER_MOVE_DONE);
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
	printf(OUTPUT_CURRENT_BOARD_H_OUTLINES);
	printf(OUTPUT_CURRENT_BOARD_MARGIN_CHARS);

	if (DEBUG == 1)
	{
		printf("DUMPING field:\n[");
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

int checkIfGameIsOver()
{
	int winner = currentWinner();

	if (winner == WIN_NO_WIN_YET)
	{
		return WIN_NO_WIN_YET;
	}
	printPlayground();

	if (winner == WIN_COMPUTER_WON)
	{
		printf(OUTPUT_GAME_OVER_LOSS);
	}
	else if (winner == WIN_USER_WON)
	{
		printf(OUTPUT_GAME_OVER_VICTORY);
	}
	else
	{
		printf(OUTPUT_GAME_OVER_TIE);
	}

	return 1;
}

int currentWinner()
{
	int winner = WIN_NO_WIN_YET;
	for (int i = 0; i < 2; i++)
	{
		int counter = (i == 0 ? VALUE_COMPUTER : VALUE_USER);
		if ((field[0][0] == counter && field[0][1] == counter && field[0][2] == counter) || (field[1][0] == counter && field[1][1] == counter && field[1][2] == counter) || (field[2][0] == counter && field[2][1] == counter && field[2][2] == counter))
		{
			/*
			    X X X        _ _ _        _ _ _
			    _ _ _   or   X X X   or   _ _ _
			    _ _ _        _ _ _        X X X
			*/
			winner = counter;
		}
		else if ((field[0][0] == counter && field[1][0] == counter && field[2][0] == counter) || (field[0][1] == counter && field[1][1] == counter && field[2][1] == counter) || (field[0][2] == counter && field[1][2] == counter && field[2][2] == counter))
		{
			/*
			    X _ _        _ X _        _ _ X
			    X _ _   or   _ X _   or   _ _ X
			    X _ _        _ X _        _ _ X
			*/
			winner = counter;
		}
		else if ((field[0][0] == counter && field[1][1] == counter && field[2][2] == counter) || (field[0][2] == counter && field[1][1] == counter && field[2][0]))
		{
			/*
				X _ _        _ _ X
				_ X _   or   _ X _
				_ _ X        X _ _

			*/
			winner = counter;
		}
	}

	return winner;
}