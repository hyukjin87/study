/*
* NAME				: PioneerCarRadio
* PURPOSE			: The PioneerCarRadio class is set to the child class of the AmFmRadio class. 
*					  Allows the radio function to operate according to the set key setting of the user's input key. 
*					  You can control the radio frequency, change the frequency band, and adjust the volume. 
*					  It also sets the radio preset according to the key and outputs the set.
*/

#include <stdio.h>
#include <string.h>
#include "AmFmRadio.h"

#ifndef _PIONEERCARRADIO
#define _PIONEERCARRADIO

// Constant
#define kVolume 1

class PioneerCarRadio : public AmFmRadio
{
private:
	char* inputKeyPresses;			// user-input key value
	char radioName[50];				// radio name value
	bool onlyAM;					// only AM frequency check value

public:
	/* constructor */
	PioneerCarRadio(void);

	/* destructor */
	virtual ~PioneerCarRadio(void);

	/* accessors */
	char* GetInputKeyPresses(void);
	char* GetRadioName(void);
	bool GetOnlyAM(void);

	/* mutators */
	void SetInputKeyPresses(void);
	void SetRadioName(const char* newRadioName);
	void SetOnlyAM(void);

	// output current radio settings
	void ShowCarRadioSetting(void);
};
#endif