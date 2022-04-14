/*
* NAME				: AmFmRadio
* PURPOSE			: The AmFmRadio class is responsible for controlling and configuring radio functions. 
*					  The radio has a valid AM FM frequency and functions to set a set volume. 
*					  The radio has five buttons, and you can save and load the frequency according to your settings. 
*					  It also has the function of reloading the previously configured settings after power is turned off. 
*					  It also has the ability to adjust the output of the radio.
*/

#ifndef _AMFMRADIO_H
#define _AMFMRADIO_H

// Constants
#define kFrequency 3
#define kButton 5
#define kAM 530
#define kFM 87.9f
#define kMaxAM 1700
#define kMaxFM 107.9f
#define kScanAM 10
#define kScanFM 0.2f

// Data Type
struct Freqs
{
	int AMButton;
	float FMButton;
};

class AmFmRadio
{
private:
	Freqs	button[kButton];			// radio preset button
	double	current_station;			// current frequency station
	char	frequency[kFrequency];		// current frequency
	int		volume;						// current volume
	bool	on;							// radio power configuration
	Freqs	beforeStation;				// user's previous configuration
	int		beforeVolume;				// user's previous volume
	bool	displayOut;					// radio output control

public:
	/* accessors */    
	double GetCurrent_Station(void);
	int GetCurrent_Volume(void);
	Freqs* GetRadioPresets(void);
	char* GetCurrent_Band(void);
	bool GetDisplayOut(void);
	bool IsRadioOn(void);

	/* constructors */
	AmFmRadio(bool def = false);
	AmFmRadio(bool def, Freqs* newButton);

	/* destructor */
	virtual ~AmFmRadio(void);

	/* mutators */
	void SetCurrentStation(double newStation);
	int SetVolume(int newVolume);
	void ToggleDisplayOutput(void);
	void PowerToggle(void);	
	int SetButton(int button_num);
	int SelectCurrentStation(int button_num);
	int SetVolume(void);
	virtual void ToggleFrequency(void);
	virtual void ScanUp(void);
	virtual void ScanDown(void);
	
	// output current radio settings
	void ShowCurrentSettings(void);
};
#endif
