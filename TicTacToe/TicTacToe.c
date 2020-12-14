#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "consts.h"

int field[3][3];
int shouldComputerPlay = 1;


void processNewMove();

void computerMove(int unavailableNumbers[], int unavailableNumbersSize, int pick);

void printPlayground();

int checkIfGameIsOver();

int currentWinner();


void fillPlayground()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			field[i][j] = VALUE_FREE;
		}
	}
}

void main()
{
	fillPlayground();
	srand(time(NULL));

	if (DEBUG_MODE == 1)
	{
		char answer;
		printf(OUTPUT_DEBUG_COMPUTER_ON_OFF);
		scanf("%c", &answer);

		switch (answer)
		{
		case 'Y':
		case 'y':
			shouldComputerPlay = 1;
			break;

		case 'N':
		case 'n':
			shouldComputerPlay = 0;
		}
	}

	processNewMove();
}

void processNewMove()
{
	int fieldNumber;

	printPlayground();

	printf(OUTPUT_NEW_MOVE);
	scanf("%d", &fieldNumber);

	if (fieldNumber < 0 || fieldNumber > 8)
	{
		printf(OUTPUT_ERROR_FIELD_NOT_IN_RANGE);
		processNewMove();
		return;
	}

	//Check if the fields are already filled
	if (fieldNumber >= 6)
	{
		if (field[2][fieldNumber - 6] == VALUE_FREE)
		{
			field[2][fieldNumber - 6] = VALUE_USER;
		}
		else
		{
			printf(OUTPUT_ERROR_FIELD_ALREADY_FILLED);
			processNewMove();
			return;
		}
	}
	else if (fieldNumber >= 3 && fieldNumber < 6)
	{
		if (field[1][fieldNumber - 3] == VALUE_FREE)
		{
			field[1][fieldNumber - 3] = VALUE_USER;
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
		if (field[0][fieldNumber] == VALUE_FREE)
		{
			field[0][fieldNumber] = VALUE_USER;
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
	if (shouldComputerPlay == 0)
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

	if (DEBUG_MODE == 1)
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