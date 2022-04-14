/*
* NAME				: PioneerWorld
* PURPOSE			: The PioneerWorld class is set to the child class of the PioneerAM class.
*					  Like PioneerAM radio, only the AM band frequency is available. 
*					  Only the frequency band (531 to 1602 kHz) available on PioneerWorld radios can be used. 
*					  In addition, changing the frequency band changes by 9 kHz, unlike other radios.
*/

#include "PioneerAM.h"

#ifndef _PIONEERWORLD
#define _PIONEERWORLD

// Constants
#define kAMWorld 531
#define kMaxAMWorld 1602
#define kScanAMWorld 9

class PioneerWorld : public PioneerAM
{
public:
	/* constructor */
	// FUNCTION		: PioneerWorld()
	// DESCRIPTION	: Initialize private data members when instantiating
	// PARAMETERS	: None
	// RETURN		: None
	PioneerWorld(void)
	{
		SetRadioName("Pioneer XS440-WRLD");				// Set the radio name
		SetCurrentStation(kAMWorld);					// Set the initial frequency band to PioneerWorld radio
		for (int i = 0; i < kButton; i++)				// Set the initial preset button to PioneerWorld radio
		{
			SetButton(i);
		}
	};

	/* destructor */
	// FUNCTION		: ~PioneerWorld()
	// DESCRIPTION	: Object destruction function
	// PARAMETERS	: None
	// RETURN		: None
	virtual ~PioneerWorld(void)
	{
		/* output destruction message when output function is on */
		if (GetDisplayOut() == true)
		{
			printf("Destroying Pioneer XS440-WRLD Radio\n");
		}
	};

	// FUNCTION		: ScanUp()
	// DESCRIPTION	: virtual function that increases the frequency of the radio
	// PARAMETERS	: None
	// RETURN		: None
	virtual void ScanUp(void)
	{
		if (strcmp("AM", GetCurrent_Band()) == 0)
		{
			//if current_station is 1602, the current_station becomes 531
			if (GetCurrent_Station() == kMaxAMWorld)
			{
				SetCurrentStation(kAMWorld);
			}
			else
			{
				// raise the current frequency by 9 kHz
				SetCurrentStation(GetCurrent_Station() + kScanAMWorld);
			}
		}
		else
		{
			// exceptional processing is performed if it is not AM is used AM frequency
			throw "The frequency band is not AM";
		}
		// Display the output when the output option is turned on
		if (GetDisplayOut() == true)
		{
			printf("\nCurrent station: %f %s\n", GetCurrent_Station(), GetCurrent_Band());
		}
	};

	// FUNCTION		: ScanUp()
	// DESCRIPTION	: virtual function that lowers radio frequencies
	// PARAMETERS	: None
	// RETURN		: None
	virtual void ScanDown(void)
	{
		if (strcmp("AM", GetCurrent_Band()) == 0)
		{
			//if current_station is 531, the current_station becomes 1602
			if (GetCurrent_Station() == kAMWorld)
			{
				SetCurrentStation(kMaxAMWorld);
			}
			else
			{
				// reduce the current frequency by 9 kHz
				SetCurrentStation(GetCurrent_Station() - kScanAMWorld);
			}
		}
		else
		{
			// exceptional processing is performed if it is not AM is used AM frequency
			throw "The frequency band is not AM";
		}

		// Display the output when the output option is turned on
		if (GetDisplayOut() == true)
		{
			printf("\nCurrent station: %f %s\n", GetCurrent_Station(), GetCurrent_Band());
		}
	};
};
#endif