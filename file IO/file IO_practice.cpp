/*
* DESCRIPTION		:
* 	A program that calculates the winning rate through the results of the game entered in the file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

// Prototypes
int processGames(char teamResults[]);
void parseLine(char gameResult[], char opponetTeamName[], int* score, int* otherScore);

// Constant
#define kMaxLine 40

int main(void)
{	
	char teamList[kMaxLine] = { 0 };
	int errorLevel = 0;
	int check = 0;

	FILE* fpTeam = NULL;

	// Open teams.txt for reading
	fpTeam = fopen("teams.txt", "r");
	
	// Check for error upon opening
	if (fpTeam == NULL)
	{
		printf("Error: Can't open teams.txt\n");
		errorLevel--;
		return errorLevel;
	}

	// Get each of the lines from the file
	while (!feof(fpTeam))
	{
		if (fgets(teamList, sizeof teamList, fpTeam) > 0)
		{
			// If there's an empty line, skip it
			if (strcmp(teamList, "\n") == 0)
			{
				continue;
				errorLevel--;
			}
			// processGames() function call
			else
			{
				check = processGames(teamList);
				if (check != 0)
				{
					errorLevel--;
				}
			}
		}		
	}
	// Close the file we are reading from 
	if (fclose(fpTeam) != 0)
	{
		printf("Error: Can't close teams.txt\n");
		errorLevel--;
		return errorLevel;
	}

	// more error checking
	// Display the number of errors that have occurred
	if (errorLevel == 0)
	{
		printf("It worked perfectly\n");
	}
	else
	{
		printf("It didn't work perfectly.\n");
		printf("The number of errors: %d", -errorLevel);
	}

	return 0;
}

// Function		: processGames()
// Description	: Get the results from the file and calculate the winning rate
// Parameters	: char teamResults[]: The name of the team file
// Return Values: int errorCheck	: Check the number of errors
int processGames(char teamResults[])
{
	char gameResults[kMaxLine] = { 0 };
	char myTeamName[kMaxLine] = { 0 };
	char gResult[kMaxLine] = { 0 };
	char teamName[kMaxLine] = { 0 };
	int count = 0;
	int count2 = 0;
	int myScore = 0;
	int oppScore = 0;;
	int errorCheck = 0;
	int winCount = 0;
	int drawCount = 0;
	int loseCount = 0;
	double winRate = 0;

	FILE* fpTeamResult = NULL;
	
	// Remove the line change value after the file name
	strcpy(gameResults, teamResults);
	for (count; gameResults[count] != 0; count++)
	{
		if (gameResults[count] == '\n')
		{
			gameResults[count] = 0;
			break;
		}
	}

	// Remove the extension value after the file name
	strcpy(myTeamName, teamResults);
	for (count2; myTeamName[count2] != 0; count2++)
	{
		if (myTeamName[count2] == '.')
		{
			myTeamName[count2] = 0;
			break;
		}
	}

	// Open team name file for reading
	fpTeamResult = fopen(gameResults, "r");
	if (fpTeamResult == NULL)
	{
		printf("Warning: Can't open %s. Skipping team.\n", gameResults);
		errorCheck--;
		return errorCheck;
	}

	printf("Processing %s:\n", gameResults);

	// Get each of the lines from the file
	while (!feof(fpTeamResult))
	{
		if (fgets(gResult, sizeof gResult, fpTeamResult) > 0)
		{
			// parseLine() function call
			parseLine(gResult, teamName, &myScore, &oppScore);

			// If there's an empty line, skip it
			if (strcmp(gResult, "\n") == 0)
			{
				printf("Warning: malformed line. Skipping game.\n");
				errorCheck--;
			}
			// Saving the value of win, lose, and tie
			else if (myScore > oppScore)
			{
				printf("\t%s beat %s %d-%d\n", myTeamName, teamName, myScore, oppScore);
				winCount++;
			}
			else if (myScore == oppScore)
			{
				printf("\t%s and %s tied at %d\n", myTeamName, teamName, myScore);
				drawCount++;
			}
			else
			{
				printf("\t%s lost to %s %d-%d\n", myTeamName, teamName, myScore, oppScore);
				loseCount++;
			}
		}		
	}

	// The winning rate calculation formula
	winRate = (2 * (double) winCount + drawCount) / (2 * ((double) winCount + (double) loseCount + (double) drawCount));
	printf("Season result for %s: %.3lf (%d-%d-%d)\n\n", myTeamName, winRate, winCount, loseCount, drawCount);
	
	// Close the file we are reading from
	if (fclose(fpTeamResult) != 0)
	{
		printf("Can't close the file\n");
		errorCheck--;
		return errorCheck;
	}
	return errorCheck;
}

// Function		: parseLine()
// Description	: Separate the values read from the file
// Parameters	: char gameResult[]		 : The value to read from the file
//				: char opponentTeamName[]: The name of the other team
//				: int *score		  	 : My score
//				: int *otherScore		 : Opponent score
// Return Values: None
void parseLine(char gameResult[], char opponetTeamName[], int* score, int* otherScore)
{
	char result[kMaxLine] = { 0 };
	char* scoreMyTeam[kMaxLine] = { 0 };
	char *scoreOppTeam[kMaxLine] = { 0 };
	int count = 0;

	// Store the received string in a variable
	strcpy(result, gameResult);

	// Check the specification of the variable value
	if (strchr(result,'-') && strchr(result,',') != NULL)
	{
		// Separate the name of the other team
		strcpy(opponetTeamName, gameResult);
		for (count; opponetTeamName[count] != 0; count++)
		{
			if (opponetTeamName[count] == ',')
			{
				opponetTeamName[count] = 0;
				break;
			}
		}

		// Save my team's score and the other team's score
		*scoreMyTeam = strchr(result, ',') + 1;
		*score = atoi(*scoreMyTeam);
		*scoreOppTeam = strchr(result, '-') + 1;
		*otherScore = atoi(*scoreOppTeam);
	}
	else
	{
		strcpy(gameResult, "\n");
	}
}