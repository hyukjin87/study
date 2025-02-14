/*
* DESCRIPTION		:
* 	A set of functions that set and output conditions suitable for the input value.
*/

#pragma warning(disable:4996)

#include "PioneerCarRadio.h"

// FUNCTION		: PioneerCarRadio()
// DESCRIPTION	: Initialize private data members when instantiating
// PARAMETERS	: None
// RETURN		: None
PioneerCarRadio::PioneerCarRadio(void) : AmFmRadio(false)
{
	inputKeyPresses = { 0 };
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
bool PioneerCarRadio::SetInputKeyPresses(int newInput)
{
	bool retCode = false;

	switch (newInput)
	{
	case 'o':								//	option to turn on the radio
		AmFmRadio::PowerToggle();
		break;
	case '+':
		AmFmRadio::SetVolume(kVolume);		//	option to volume up
		break;
	case '_':
		AmFmRadio::SetVolume(-kVolume);		//	option to volume down
		break;
	case '=':
		AmFmRadio::ScanUp();				//	option to radio frequency up
		break;
	case '-':
		AmFmRadio::ScanDown();				//	option to radio frequency down
		break;
	case 'b':
		AmFmRadio::ToggleFrequency();		//	option to change radio frequency band
		break;
	case '!':
		AmFmRadio::SetButton(0);			//	option to save frequency in the button 1
		break;
	case '@':
		AmFmRadio::SetButton(1);			//	option to save frequency in the button 2
		break;
	case '#':
		AmFmRadio::SetButton(2);			//	option to save frequency in the button 3
		break;
	case '$':
		AmFmRadio::SetButton(3);			//	option to save frequency in the button 4
		break;
	case '%':
		AmFmRadio::SetButton(4);			//	option to save frequency in the button 5
		break;
	case '1':
		AmFmRadio::SelectCurrentStation(0);	//	option to load frequency in the button 1
		break;
	case '2':
		AmFmRadio::SelectCurrentStation(1); //	option to load frequency in the button 2
		break;
	case '3':
		AmFmRadio::SelectCurrentStation(2); //	option to load frequency in the button 3
		break;
	case '4':
		AmFmRadio::SelectCurrentStation(3); //	option to load frequency in the button 4
		break;
	case '5':
		AmFmRadio::SelectCurrentStation(4); //	option to load frequency in the button 5
		break;
	case 'x':
		retCode = true;
		break;
	default:
		break;
	}

	return retCode;
}

// FUNCTION		: ShowCarRadioSetting()
// DESCRIPTION	: A function that outputs the current setting value of the radio
// PARAMETERS	: None
// RETURN		: None
void PioneerCarRadio::ShowCarRadioSetting(void)
{
	char curFreqs[kFrequency] = { 0 };

	if (AmFmRadio::IsRadioOn() == false)
	{
		printf("Pioneer XS440\n");
		printf("Radio is off\n");
	}
	else
	{
		printf("Pioneer XS440\n");
		printf("Radioi is on\n");
		printf("Volume: %d\n", AmFmRadio::GetCurrent_Volume());
		printf("Current Station:");

		strcpy(curFreqs, AmFmRadio::GetCurrent_Band());		// check the current radio frequency band

		if (strcmp(curFreqs, "AM") == 0)
		{
			printf("%6d %s\n", (int)AmFmRadio::GetCurrent_Station(), curFreqs);
		}
		else
		{
			printf("%6.1f %s\n", AmFmRadio::GetCurrent_Station(), curFreqs);
		}

		printf("AM Buttons:\n");
		
		for (int i = 0; i < kButton; i++)
		{
			printf("%d: %6d", i + 1, AmFmRadio::GetRadioPresets()[i].AMButton);
			// syntax for commas specification
			if (i < kButton - 1)
			{
				printf(", ");
			}
		}
		printf("\nFM Buttons:\n");
		for (int j = 0; j < kButton; j++)
		{
			printf("%d: %6.1f", j + 1, AmFmRadio::GetRadioPresets()[j].FMButton);
			// syntax for commas specification
			if (j < kButton - 1)
			{
				printf(", ");
			}
		}
		printf("\n");
	}
}
