/*
* DESCRIPTION		:
* 	run the program, provide the right UI for the user, and test the functional behavior
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#pragma warning(disable:4996)

int main(void)
{
	PioneerCarRadio jazzy;		// PioneerCarRadio class variable
	char input;					// user input variable

	while (1)
	{
		jazzy.ShowCarRadioSetting();		// output radio settings
		input = getch();					// user input value
		system("cls");						// Organize the screen and provide it to the user
		// conditions for termination of a program
		if (jazzy.SetInputKeyPresses(input) == true)
		{
			break;
		}
		
	}
	return 0;
}