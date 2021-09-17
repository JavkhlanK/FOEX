#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TicTacToe.h"
#include "settings.h"

#ifdef _WIN32
#include <string.h>
#define strcasecmp _stricmp
#else	//assuming POSIX or BSD compliant system
#include <strings.h>
#endif

/*
	Field comments:
	 - X:	Field to fill in
	 - O:	One of all O's is not the same as the others
	 - A:	Any entity (currently Computer or Player)
	 - C:	Computer only
	 - U:	User only
*/

int field[3][3];


/* Core methods */

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
	
	char input[30];
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


	/* Check if the fields are already filled */

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


	/* Has someone won yet? */

	if (isGameOverAndPrintMessages())
	{
		return;
	}


	/* Game isn't over yet */

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
		computerMoveModeHard();
	}
	else if (DIFFICULTY == DIFFICULTY_PLAYER_VS_PLAYER)
	{
		//TODO: Add 2 player game mode
	}
	else
	{
		printf("%s", OUTPUT_ERROR_GENERIC_HOW_DID_WE_GET_HERE);
	}
	
	if (isGameOverAndPrintMessages())
	{
		return;
	}

	printf("%s", OUTPUT_COMPUTER_MOVE_DONE);
	processNewMove();
}

/* Helper methods */

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
				A A A		_ _ _		_ _ _
				_ _ _	or	A A A	or	_ _ _
				_ _ _		_ _ _		A A A
			*/

			winner = currentEntity;
			break;
		}
		else if ((field[0][0] == currentEntity && field[1][0] == currentEntity && field[2][0] == currentEntity) || (field[0][1] == currentEntity && field[1][1] == currentEntity && field[2][1] == currentEntity) || (field[0][2] == currentEntity && field[1][2] == currentEntity && field[2][2] == currentEntity))
		{
			/*
				A _ _		_ A _		_ _ A
				A _ _	or	_ A _	or	_ _ A
				A _ _		_ A _		_ _ A
			*/

			winner = currentEntity;
			break;
		}
		else if ((field[0][0] == currentEntity && field[1][1] == currentEntity && field[2][2] == currentEntity) || (field[0][2] == currentEntity && field[1][1] == currentEntity && field[2][0] == currentEntity))
		{
			/*
				A _ _		_ _ A
				_ A _	or	_ A _
				_ _ A		A _ _
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
}

void computerMoveModeHard()
{
	if (field[1][1] == VALUE_FREE)
	{
		field[1][1] = VALUE_COMPUTER;
		return;
	}

	/* At first: check if anything should be hindered/done to win,
	   like the computer/user being 1 move away from winning */

	for (int entityType = 0; entityType < 2; entityType++)
	{
		int entity = entityType == 0 ? VALUE_COMPUTER : VALUE_USER;

		/*
			O _ _		_ O _		_ _ O
			O _ _	or	_ O _	or	_ _ O
			O _ _		_ O _		_ _ O
		*/

		for (int column = 0; column < 3; column++)
		{
			if (field[column][0] == entity && field[column][1] == entity && field[column][2] == VALUE_FREE)
			{
				field[column][2] = VALUE_COMPUTER;
				return;
			}
			else if (field[column][1] == entity && field[column][2] == entity && field[column][0] == VALUE_FREE)
			{
				field[column][0] = VALUE_COMPUTER;
				return;
			}
			else if (field[column][0] == entity && field[column][2] == entity && field[column][1] == VALUE_FREE)
			{
				field[column][1] = VALUE_COMPUTER;
				return;
			}
		}


		/*
			O O O		_ _ _		_ _ _
			_ _ _	or	O O O	or	_ _ _
			_ _ _		_ _ _		O O O
		*/

		for (int row = 0; row < 3; row++)
		{
			int entity = entityType == 0 ? VALUE_COMPUTER : VALUE_USER;
			if (field[0][row] == entity && field[1][entity] == entity && field[2][row] == VALUE_FREE)
			{
				field[2][row] = VALUE_COMPUTER;
				return;
			}
			else if (field[1][row] == entity && field[2][row] == entity && field[0][row] == VALUE_FREE)
			{
				field[0][row] = VALUE_COMPUTER;
				return;
			}
			else if (field[0][row] == entity && field[2][row] == entity && field[1][row] == VALUE_FREE)
			{
				field[1][row] = VALUE_COMPUTER;
				return;
			}
		}


		/* 
			A _ _		X _ _		A _ _
			_ A _	or	_ A _	or	_ X _
			_ _ X		_ _ A		_ _ A
		*/

		if (field[0][0] == entity && field[1][1] == entity && field[2][2] == VALUE_FREE)
		{
			field[2][2] = VALUE_COMPUTER;
			return;
		}
		else if (field[1][1] == entity && field[2][2] == entity && field[0][0] == VALUE_FREE)
		{
			field[0][0] = VALUE_COMPUTER;
			return;
		}
		else if (field[0][0] == entity && field[2][2] == entity && field[1][1] == VALUE_FREE)
		{
			field[1][1] = VALUE_COMPUTER;
			return;
		}


		/*
			_ _ A		_ _ X		_ _ A
			_ A _	or	_ A _	or	_ X _
			X _ _		A _ _		A _ _
		*/

		if (field[0][2] == entity && field[1][1] == entity && field[2][0] == VALUE_FREE)
		{
			field[2][0] = VALUE_COMPUTER;
			return;
		}
		else if (field[1][1] == entity && field[2][0] == entity && field[0][2] == VALUE_FREE)
		{
			field[0][2] = VALUE_COMPUTER;
			return;
		}
		else if (field[0][2] == entity && field[2][0] == entity && field[1][1] == VALUE_FREE)
		{
			field[1][1] = VALUE_COMPUTER;
			return;
		}
	}


	/*
		X C _		_ C X		_ _ _		_ _ _
		C _ _	or	_ _ C	or	_ _ C	or	C _ _
		_ _ _		_ _ _		_ C X		X C _
	*/

	if (field[0][1] == VALUE_COMPUTER && field[1][0] == VALUE_COMPUTER && field[0][0] == VALUE_FREE)
	{
		field[0][0] = VALUE_COMPUTER;
		return;
	}
	if (field[0][1] == VALUE_COMPUTER && field[1][2] == VALUE_COMPUTER && field[0][2] == VALUE_FREE)
	{
		field[0][2] = VALUE_COMPUTER;
		return;
	}
	if (field[1][0] == VALUE_COMPUTER && field[2][1] == VALUE_COMPUTER && field[2][0] == VALUE_FREE)
	{
		field[2][0] = VALUE_COMPUTER;
		return;
	}
	if (field[2][1] == VALUE_COMPUTER && field[1][2] == VALUE_COMPUTER && field[2][2] == VALUE_FREE)
	{
		field[2][2] = VALUE_COMPUTER;
		return;
	}
}
