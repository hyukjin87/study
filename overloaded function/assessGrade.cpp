/*
* DESCRIPTION		:
* 	A set of functions that set and output conditions suitable for the input value.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "assessGrade.h"
#pragma warning(disable: 4996)

// Function		: parseUserInput()
// Description	: A function of dividing a value input from a user by condition
// Parameters	: char *userInput: The value received from the user
// Return Values: None
void parseUserInput(char* userInput)
{
	char inputChecker[kSize] = { 0 };
	int num[kSize] = { 0 };
	double fNum = 0;
	int count = 0;
	int numCount = 0;
	char* number = { 0 };
	int* pNum = { 0 };

	strcpy(inputChecker, userInput);

	// If the value is a real number, pass it as a function
	if (strchr(inputChecker, '.') != NULL)
	{
		fNum = atof(inputChecker);
		assessGrade(fNum);
	}
	// If the value is the letters, pass it as a function
	else if (isdigit(inputChecker[0]) == 0)
	{
		assessGrade(inputChecker);
	}
	// If the value is the integers, pass it as a function
	else
	{
		number = inputChecker;
		for (count; inputChecker[count] != '\n'; count++)
		{
			if (inputChecker[count] == ' ')
			{
				num[numCount++] = atoi(number);
				number = inputChecker + count + 1;
			}
		}
		num[numCount] = atoi(number);
		
		assessGrade(num);

	}
}

// Function		: assessGrade()
// Description	: Check the condition of the real number received
// Parameters	: double num: Real number delivered through the parseUserInput function
// Return Values: None
void assessGrade(double num)
{
	// Transfer the value corresponding to the condition to the showGrade function
	if (num <= 0 || num > 100)
	{
		showGrade(kFailure);
	}
	else
	{
		showGrade(num);
	}	
}

// Function		: assessGrade()
// Description	: Check the condition of the letters received
// Parameters	: char *str: Letters delivered through the parseUserInput function
// Return Values: None
void assessGrade(char* str)
{
	char strInput[kSize] = { 0 };
	double score = 0;

	strcpy(strInput, str);
	clearCR(strInput);

	// Deliver the score corresponding to the conditions of each grade to the output function
	if (strcmp(strInput, "A+") == 0)
	{
		score = 95;
		showGrade(score);
	}
	else if (strcmp(strInput, "A") == 0)
	{
		score = 85;
		showGrade(score);
	}
	else if (strcmp(strInput, "B+") == 0)
	{
		score = 77;
		showGrade(score);
	}
	else if (strcmp(strInput, "B") == 0)
	{
		score = 72;
		showGrade(score);
	}
	else if (strcmp(strInput, "C+") == 0)
	{
		score = 67;
		showGrade(score);
	}
	else if (strcmp(strInput, "C") == 0)
	{
		score = 62;
		showGrade(score);
	}
	else if (strcmp(strInput, "D") == 0)
	{
		score = 57;
		showGrade(score);
	}
	else if (strcmp(strInput, "F") == 0)
	{
		score = 50;
		showGrade(score);
	}
	// Special conditions
	else if (strcmp(strInput, "I") == 0)
	{
		printf("Student has Special Situation : I (Incomplete)\n");
	}
	else if (strcmp(strInput, "Q") == 0)
	{
		printf("Student has Special Situation : Q (Withdrawal After Drop/Refund Date)\n");
	}
	else if (strcmp(strInput, "AU") == 0)
	{
		printf("Student has Special Situation : AU (Audit Condition)\n");
	}
	else if (strcmp(strInput, "DNA") == 0)
	{
		printf("Student has Special Situation : DNA (Did Not Attend)\n");
	}
	else if (strcmp(strInput, "I/P") == 0)
	{
		printf("Student has Special Situation : I/P (In Process)\n");
	}
	else
	{
		showGrade(kFailure);
	}
}

// Function		: assessGrade()
// Description	: Check the condition of the integers array received
// Parameters	: int num[]: Integers array delivered through the parseUserInput function
// Return Values: Error check for ending function
int assessGrade(int num[])
{
	int number[10] = { 0 };
	int count = 0;
	int numCount = 5;
	int arrCheck = 0;
	double sum = 0;	

	// To check the number of arrangements
	for (numCount; numCount < 10; numCount++)
	{
		arrCheck = arrCheck + num[numCount];
	}

	for (count; count < 10; count++)
	{
		// Error output when it exceeds that range
		if (num[count] > 100 || num[count] < 0)
		{
			showGrade(kFailure);
			return kFailure;
		}
		// Error output when a value exists in an array of 5th or higher
		else if (arrCheck != 0)
		{
			showGrade(kFailure);
			return kFailure;
		}
		// Add the values of the array in order
		else
		{
			number[count] = num[count];
			sum = sum + number[count];
		}
	}
	// Calculate the average value
	sum = sum / 5;
	showGrade(sum);
	
	return kSuccess;
}

// Function		: showGrade()
// Description	: Output error or indicate whether the student's grades have passed
// Parameters	: double result: Student grades
// Return Values: None
void showGrade(double result)
{
	if (result < 0)
	{
		printf("**ERROR : Invalid Input\n");
	}
	else
	{
		if (result >= 54.50)
		{
			printf("Student achieved %.2lf %% which is a PASS condition.\n", result);
		}
		else
		{
			printf("Student achieved %.2lf %% which is a FAIL condition.\n", result);
		}
	}
	
}

// Function		: clearCR()
// Description	: To remove line change
// Parameters	: char *buf: String to remove
// Return Values: None
void clearCR(char* buf)
{
	char* whereCR = strchr(buf, '\n');
	if (whereCR != NULL)
	{
		*whereCR = '\0';
	}
}