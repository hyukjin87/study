/*
* DESCRIPTION		:
* 	A set of functions that set and output conditions suitable for the input value.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"
#pragma warning(disable:4996)

// FUNCTION		: GetCurrent_Station()
// DESCRIPTION	: A function of accessing current_station private data
// PARAMETERS	: None
// RETURN		: double : current_station
double AmFmRadio::GetCurrent_Station(void)
{
	return current_station;
}

// FUNCTION		: GetCurrent_volume()
// DESCRIPTION	: A function of accessing volume private data
// PARAMETERS	: None
// RETURN		: int : volume
int AmFmRadio::GetCurrent_Volume(void)
{
	return volume;
}

// FUNCTION		: GetRadioPresets()
// DESCRIPTION	: A function of accessing structure Freqs button private data
// PARAMETERS	: None
// RETURN		: Frequs : frequency copy data of each button
Freqs* AmFmRadio::GetRadioPresets(void)
{
	Freqs newButton[kButton] = { 0 };
	for (int i = 0; i < kButton; i++)
	{
		newButton[i] = button[i];
	}
	return newButton;
}

// FUNCTION		: GetCurrent_Band()
// DESCRIPTION	: A function of accessing frequency private data
// PARAMETERS	: None
// RETURN		: char : current band copy data
char* AmFmRadio::GetCurrent_Band(void)
{
	char newFrequency[kFrequency] = { 0 };
	strcpy(newFrequency, frequency);
	return newFrequency;
}

// FUNCTION		: GetDisplayOut()
// DESCRIPTION	: A function of accessing displayOut private data
// PARAMETERS	: None
// RETURN		: bool : displayOut
bool AmFmRadio::GetDisplayOut(void)
{
	return displayOut;
}

// FUNCTION		: AmFmRadio()
// DESCRIPTION	: Initialize private data members when instantiating
// PARAMETERS	: bool def			: Whether the radio should be on when instantiated
// RETURN		: None
AmFmRadio::AmFmRadio(bool def)
{
	// Check if the radio should be on during the initial setting
	if (def == true)
	{
		on = true;
	}
	else
	{
		on = false;
	}

	// Initialize all data members
	for (int i = 0; i < kButton; ++i)
	{
		button[i].AMButton = kAM;
	}
	for (int j = 0; j < kButton; ++j)
	{
		button[j].FMButton = kFM;
	}
	current_station = kAM;
	strcpy(frequency, "AM");
	volume = 0;
	beforeVolume = volume;
	beforeStation.AMButton = kAM;
	beforeStation.FMButton = kFM;
	displayOut = false;
}

// FUNCTION		: AmFmRadio()
// DESCRIPTION	: Initialize private data members when instantiating
// PARAMETERS	: bool def			: Whether the radio should be on when instantiated
//				: Freqs *newButton	: Initial radio preset value
// RETURN		: None
AmFmRadio::AmFmRadio(bool def, Freqs* newButton)
{
	// Check if the radio should be on during the initial setting
	if (def == true)
	{
		on = true;
	}
	else
	{
		on = false;		
	}
	// Initialize all data members
	for (int i = 0; i < kButton; ++i)
	{
		button[i].AMButton = newButton[i].AMButton;
	}
	for (int j = 0; j < kButton; ++j)
	{
		button[j].FMButton = newButton[j].FMButton;
	}
	current_station = kAM;
	strcpy(frequency, "AM");
	volume = 0;
	beforeVolume = volume;
	beforeStation.AMButton = kAM;
	beforeStation.FMButton = kFM;
	displayOut = false;
}


// FUNCTION		: ~AmFmRadio()
// DESCRIPTION	: Object destruction function
// PARAMETERS	: None
// RETURN		: None
AmFmRadio::~AmFmRadio(void)
{
	if (displayOut == true)
	{
		printf("Descroying AmFmRadio\n");
	}
}

// FUNCTION		: SetCurrent_Station()
// DESCRIPTION	: Change the data type casting to current_station
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::SetCurrentStation(double newStation)
{
	if (strcmp(frequency, "AM") == 0)
	{
		current_station = (int)newStation;
	}
	else
	{
		current_station = (float)newStation;
	}
}

// FUNCTION		: ToggleDisplayOutput()
// DESCRIPTION	: Display output option toggle function
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::ToggleDisplayOutput(void)
{
	if (displayOut == false)
	{
		displayOut = true;
	}
	else
	{
		displayOut = false;
	}
}

// FUNCTION		: PowerToggle()
// DESCRIPTION	: Radio power toggle option function
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::PowerToggle(void)
{
	if (on == false)
	{
		on = true;
		// Call the volume value you used before turning off the radio
		volume = beforeVolume;
	}
	else
	{
		on = false;
		// If I turn off the radio, the volume is zero
		volume = 0;
	}
}

// FUNCTION		: isRadioOn()
// DESCRIPTION	: Radio power option private data accessor
// PARAMETERS	: None
// RETURN		: bool : radio power data
bool AmFmRadio::IsRadioOn(void)
{
	return on;
}

// FUNCTION		: SetVolume()
// DESCRIPTION	: A function that sets the radio volume value
// PARAMETERS	: None
// RETURN		: int : Check the normal function
int AmFmRadio::SetVolume(void)
{
	char buf[20] = "";
	// output check
	if (displayOut == true)
	{
		printf("\nEnter the volume level (0 - 100). ");
	}	
	fgets(buf, sizeof buf, stdin);
	volume = atoi(buf);
	// Check the volume before turning off the radio
	beforeVolume = volume;

	if (volume < 0) //if user enters volume less than 0, volume = 0
	{
		volume = 0;
		// Check the volume before turning off the radio
		beforeVolume = volume;
		return 0;
	}

	if (volume > 100) //if user enters volume greater than 100, volume = 100
	{
		volume = 100;
		// Check the volume before turning off the radio
		beforeVolume = volume;
		return 2;
	}
	return 1;
}

// FUNCTION		: SetVolume()
// DESCRIPTION	: A function that sets the radio volume value
// PARAMETERS	: int newVolume		: radio volume value to be changed
// RETURN		: int				: Check the normal function
int AmFmRadio::SetVolume(int newVolume)
{
	// volume value to be changed
	volume += newVolume;
	// Check the volume before turning off the radio
	beforeVolume = volume;

	if (volume < 0) //if user enters volume less than 0, volume = 0
	{
		volume = 0;
		// Check the volume before turning off the radio
		beforeVolume = volume;
		return 0;
	}

	if (volume > 100) //if user enters volume greater than 100, volume = 100
	{
		volume = 100;
		// Check the volume before turning off the radio
		beforeVolume = volume;
		return 2;
	}
	return 1;
}

// FUNCTION		: ToggleFrequency()
// DESCRIPTION	: Radio frequency band toggle function
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::ToggleFrequency(void)
{
	if (strcmp(frequency, "AM") == 0)
	{
		strcpy(frequency, "FM");
		// Save the previous frequency value before toggle
		current_station = beforeStation.FMButton;
	}
	else
	{
		strcpy(frequency, "AM");
		// Save the previous frequency value before toggle
		current_station = beforeStation.AMButton;
	}
}

// FUNCTION		: SetButton()
// DESCRIPTION	: A function that stores the current frequency in the selected preset
// PARAMETERS	: int button_num	: The button value selected by the user
// RETURN		: int				: Check the normal function
int AmFmRadio::SetButton(int button_num)
{
	if ((button_num >= 0) && (button_num <= 4))
	{
		if (strcmp("AM", frequency) == 0)
		{
			// Store the current AM frequency value in the button selected by the user
			button[button_num].AMButton = (int)current_station;
		}
		else
		{
			// Store the current FM frequency value in the button selected by the user
			button[button_num].FMButton = (float)current_station;
		}
		return 1;
	}
	return 0;
}

// FUNCTION		: SelectCurrentStation()
// DESCRIPTION	: A function that brings up the preset saved by the user
// PARAMETERS	: int button_num	: The button value selected by the user
// RETURN		: int				: Check the normal function
int AmFmRadio::SelectCurrentStation(int button_num)
{
	if ((button_num >= 0) && (button_num <= 4))
	{
		if (strcmp("AM", frequency) == 0)
		{
			// Transfer the AM frequency value stored in the button
			current_station = button[button_num].AMButton;
		}
		else
		{
			// Transfer the FM frequency value stored in the button
			current_station = button[button_num].FMButton;
		}
		return 1;
	}
	return 0;
}

// FUNCTION		: ShowCurrentSettings()
// DESCRIPTION	: A function that outputs the current setting value of the radio
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::ShowCurrentSettings(void)
{
	if (on == true)
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", frequency);
	printf("Volume: %d\n", volume);
	printf("Current Station: %.1f %s\n", current_station, frequency);
	printf("AM Button Settings: ");
	for (int i = 0; i < 5; ++i)
	{
		printf("%d) %6d ", i + 1, button[i].AMButton);
	}

	printf("\nFM Button Settings: ");
	for (int j = 0; j < 5; ++j)
	{
		printf("%d) %6.1f ", j + 1, button[j].FMButton);
	}
}

// FUNCTION		: ScanUp()
// DESCRIPTION	: A function that increases the frequency of the radio
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::ScanUp(void)
{
	if (strcmp("AM", frequency) == 0)
	{
		//if current_station is 1700, the current_station becomes 530
		if (current_station == kMaxAM)
		{
			current_station = kAM;
		}
		else
		{
			current_station = current_station + kScanAM;
			// The changed frequency value is stored in the previous frequency data value
			beforeStation.AMButton = (int)current_station;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: AmFmRadios jump .2 for the FM. That's how it's modeled here.
		if (current_station >= kMaxFM)
		{
			current_station = kFM;
		}
		else
		{
			current_station = current_station + kScanFM;
			// The changed frequency value is stored in the previous frequency data value
			beforeStation.FMButton = (float)current_station;
		}
	}
	// Display the output when the output option is turned on
	if (displayOut == true)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}

// FUNCTION		: ScanDown()
// DESCRIPTION	: A function to lower the frequency value of the radio
// PARAMETERS	: None
// RETURN		: None
void AmFmRadio::ScanDown(void)
{
	if (strcmp("AM", frequency) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (current_station == kAM)
		{
			current_station = kMaxAM;
		}
		else
		{
			current_station = current_station - kScanAM;
			// The changed frequency value is stored in the previous frequency data value
			beforeStation.AMButton = (int)current_station;
		}
	}
	else
	{
		//if the current_station is 87.9, the current_station becomes 107.9
		//Note: AmFmRadios down .2 for the FM. That's how it's modeled here.
		if (current_station <= kFM)
		{
			current_station = kMaxFM;
		}
		else
		{
			current_station = current_station - kScanFM;
			// The changed frequency value is stored in the previous frequency data value
			beforeStation.FMButton = (float)current_station;
		}
	}
	// Display the output when the output option is turned on
	if (displayOut == true)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}
