/*
* DESCRIPTION		:
* 	A set of functions that set and output conditions suitable for the input value.
*/

#pragma warning(disable:4996)
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "PioneerCarRadio.h"

// FUNCTION		: PioneerCarRadio()
// DESCRIPTION	: Initialize private data members when instantiating
// PARAMETERS	: None
// RETURN		: None
PioneerCarRadio::PioneerCarRadio(void) : AmFmRadio(false)
{
	inputKeyPresses = { 0 };
	strcpy(radioName, "Pioneer XS440");
	SetRadioName(radioName);
	onlyAM = false;
}

// FUNCTION		: ~PioneerCarRadio()
// DESCRIPTION	: Object destruction function
// PARAMETERS	: None
// RETURN		: None
PioneerCarRadio::~PioneerCarRadio(void)
{
	if (AmFmRadio::GetDisplayOut() == true)
	{
		printf("Descroying AmFmRadio\n");
	}
}

// FUNCTION		: GetInputKeyPresses()
// DESCRIPTION	: A function of accessing inputKeyPresses private data
// PARAMETERS	: None
// RETURN		: char : current user's input value copy data
char* PioneerCarRadio::GetInputKeyPresses(void)
{
	char newInputKeyPresses[kFrequency];
	strcpy(newInputKeyPresses, inputKeyPresses);
	return newInputKeyPresses;
}

// FUNCTION		: SetInputKeyPresses()
// DESCRIPTION	: Change radio settings according to user input key
// PARAMETERS	: int newInput		: user-entered value
// RETURN		: bool				: Check the end of the program according to the user's input
void PioneerCarRadio::SetInputKeyPresses(void)
{
	bool retCode = false;
	char input;

	while (retCode == false)
	{
		system("cls");
		ShowCarRadioSetting();
		input = getch();
		switch (input)
		{
		case 'o':								//	option to turn on the radio
			PowerToggle();
			break;
		case '+':								//	option to volume up
			SetVolume(kVolume);					
			break;
		case '_':								//	option to volume down
			SetVolume(-kVolume);		
			break;
		case '=':								//	option to radio frequency up
			ScanUp();				
			break;
		case '-':								//	option to radio frequency down
			ScanDown();				
			break;
		case 'b':								//	option to change radio frequency band
			ToggleFrequency();		
			break;
		case '!':								//	option to save frequency in the button 1
			SetButton(0);			
			break;
		case '@':								//	option to save frequency in the button 2
			SetButton(1);			
			break;
		case '#':								//	option to save frequency in the button 3
			SetButton(2);			
			break;
		case '$':								//	option to save frequency in the button 4
			SetButton(3);			
			break;
		case '%':								//	option to save frequency in the button 5
			SetButton(4);			
			break;
		case '1':								//	option to load frequency in the button 1
			SelectCurrentStation(0); 
			break;
		case '2':								//	option to load frequency in the button 2
			SelectCurrentStation(1); 
			break;
		case '3':								//	option to load frequency in the button 3
			SelectCurrentStation(2); 
			break;
		case '4':								//	option to load frequency in the button 4
			SelectCurrentStation(3); 
			break;
		case '5':								//	option to load frequency in the button 5
			SelectCurrentStation(4); 
			break;
		case 'x':								// terminate the keystroke process
			retCode = true;
			break;
		default:
			break;
		}
	}	
}

// FUNCTION		: ShowCarRadioSetting()
// DESCRIPTION	: A function that outputs the current setting value of the radio
// PARAMETERS	: None
// RETURN		: None
void PioneerCarRadio::ShowCarRadioSetting(void)
{
	char curFreqs[kFrequency] = { 0 };

	if (AmFmRadio::IsRadioOn() == false)		// check whether the radio is on
	{
		printf("%s\n",GetRadioName());
		printf("Radio is off\n");
	}
	else
	{
		printf("%s\n",GetRadioName());
		printf("Radioi is on\n");
		printf("Volume: %d\n", GetCurrent_Volume());
		printf("Current Station:");

		strcpy(curFreqs, GetCurrent_Band());	// check the current radio frequency band

		if (strcmp(curFreqs, "AM") == 0)
		{
			printf("%6d %s\n", (int)GetCurrent_Station(), curFreqs);
		}
		else
		{
			printf("%6.1f %s\n", GetCurrent_Station(), curFreqs);
		}

		printf("AM Buttons:\n");
		
		for (int i = 0; i < kButton; i++)
		{
			printf("%d: %6d", i + 1, GetRadioPresets()[i].AMButton);
			// syntax for commas specification
			if (i < kButton - 1)
			{
				printf(", ");
			}
		}

		if (onlyAM == false)					// make sure that only AM frequencies are used
		{
			printf("\nFM Buttons:\n");
			for (int j = 0; j < kButton; j++)
			{
				printf("%d: %6.1f", j + 1, GetRadioPresets()[j].FMButton);
				// syntax for commas specification
				if (j < kButton - 1)
				{
					printf(", ");
				}
			}
			printf("\n");
		}		
	}
}

// FUNCTION		: GetRadioName()
// DESCRIPTION	: A function of accessing radioName private data
// PARAMETERS	: None
// RETURN		: char : current radioName value copy data
char* PioneerCarRadio::GetRadioName(void)
{
	char whichRadio[50] = { 0 };
	strcpy(whichRadio, radioName);
	return whichRadio;
}

// FUNCTION		: SetRadioName()
// DESCRIPTION	: radio-renaming function
// PARAMETERS	: const char* newRadioName	: parameters for receiving radio name
// RETURN		: None
void PioneerCarRadio::SetRadioName(const char* newRadioName)
{
	strcpy(radioName, newRadioName);	
}

// FUNCTION		: GetOnlyAM()
// DESCRIPTION	: A function of accessing onlyAM private data
// PARAMETERS	: None
// RETURN		: bool : Whether to use only AM frequency or not
bool PioneerCarRadio::GetOnlyAM(void)
{
	return onlyAM;
}

// FUNCTION		: SetOnlyAM()
// DESCRIPTION	: function that changes to use only AM frequencies
// PARAMETERS	: None
// RETURN		: None
void PioneerCarRadio::SetOnlyAM(void)
{
	if (onlyAM == false)
	{
		onlyAM = true;
	}
}
