/*
* NAME				: PioneerAM
* PURPOSE			: The PioneerAM class is set to the child class of the PioneerCarRadio class.
*					  Unlike PioneerCarRadio, it is a radio that can only use the AM frequency band. 
*					  Accordingly, the radio frequency band cannot be changed, 
*					  and the FM frequency band cannot be output.
*/

#include "PioneerCarRadio.h"
#pragma warning(disable:4996)

#ifndef _PIONEERAM
#define _PIONEERAM

class PioneerAM : public PioneerCarRadio
{
public:
	/* constructor */
	// FUNCTION		: PioneerAM()
	// DESCRIPTION	: Initialize private data members when instantiating
	// PARAMETERS	: None
	// RETURN		: None
	PioneerAM(void)
	{
		SetRadioName("Pioneer XS440-AM");			// Set the radio name
		SetOnlyAM();								// Configure to use only AM frequency
	};

	/* destructor */
	// FUNCTION		: ~PioneerAM()
	// DESCRIPTION	: Object destruction function
	// PARAMETERS	: None
	// RETURN		: None
	virtual ~PioneerAM(void)
	{
		/* output destruction message when output function is on */
		if (GetDisplayOut() == true)
		{
			printf("Destroying Pioneer XS440-AM Radio\n");
		}
	};

	// FUNCTION		: ToggleFrequency()
	// DESCRIPTION	: Set the function in the virtual function so that the function cannot operate 
	//				  because it is initialized in the AM band when the radio object is raw
	// PARAMETERS	: None
	// RETURN		: None
	virtual void ToggleFrequency(void) { };	
};
#endif