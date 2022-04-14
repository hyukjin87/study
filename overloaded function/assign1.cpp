/*
* DESCRIPTION		:
* 	It is a program that receives a user's value and outputs a value corresponding to the condition.
*/

#include <stdio.h>
#include <string.h>
#include "assessGrade.h"
#pragma warning(disable: 4996)

int main(void)
{
	int loop = 1;
	char input[kSize] = { 0 };
	char testFile[kSize] = { 0 };
	char fileInput[kSize] = { 0 };
	FILE* fpTestFile = NULL;

	while (loop != 0)
	{
		printf("Enter Student's Grade(s) >>> ");
		fgets(input, sizeof(input), stdin);

		// If the user's input is 'X', the program ends
		if (input[0] == 'X')
		{
			printf("End the program\n");
			return 0;
		}

		// If the user's input is 'Z' and fileName (ex, Z myTestFile.dat), to start File I/O
		else if (input[0] == 'Z')
		{
			strcpy(testFile, input + 2);
			clearCR(testFile);

			fpTestFile = fopen(testFile, "r");
			if (fpTestFile == NULL)
			{
				printf("** File I / O ERROR\n");
				return kFailure;
			}

			while (fgets(fileInput, sizeof fileInput, fpTestFile) > 0)
			{
				parseUserInput(fileInput);

				if (feof(fpTestFile))
				{
					break;
				}
				if (ferror(fpTestFile))
				{
					printf("** File I / O ERROR\n");
					if (fclose(fpTestFile) != 0)
					{
						printf("** File I / O ERROR\n");
						return kFailure;
					}
				}
			}
			if (fclose(fpTestFile) != 0)
			{
				printf("** File I / O ERROR\n");
				return kFailure;
			}
		}
		// Transfer the value to the parseUserInput function if it is a value other than that
		else
		{
			parseUserInput(input);
		}
	}
	return 0;
}