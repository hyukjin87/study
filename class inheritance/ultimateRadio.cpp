/*
* DESCRIPTION		:
* 	Run a program and run a radio that matches the user's input options. 
*	After running the radio, re-run the radio or terminate the program according to the user's input key
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <new>
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include "PioneerAM.h"
#include "PioneerWorld.h"
#pragma warning(disable:4996)

// Constants
#define kPioneerCarRadio "-car"
#define kPioneerAM		 "-am"
#define kPioneerWorld	 "-world"

// Prototypes
void createRadio(PioneerCarRadio** newRadio, char* newChoice);
const char* switchingRadio(void);

int main(int argc, char *argv[])
{
	PioneerCarRadio* pRadio = NULL;					// PioneerCarRadio class variable
	char inputArgv[10] = { 0 };						// variable to store user execution options

	strcpy(inputArgv, argv[1]);						// store user-entered values
	
	try
	{
		createRadio(&pRadio, inputArgv);			// allocate dynamic memory based on user input and generate objects
		pRadio->SetInputKeyPresses();				// receive input from the user and execute appropriate options
		delete pRadio;								// deallocate memory

		while (1)
		{
			system("cls");
			strcpy(inputArgv, switchingRadio());	// change the radio or shut down the program according to the user's input value

			createRadio(&pRadio, inputArgv);		// allocate dynamic memory based on user input and generate objects
			pRadio->SetInputKeyPresses();			// receive input from the user and execute appropriate options
			delete pRadio;							// deallocate memory
		}		
	}
	
	/* print out messages thrown when exceptions occur */
	catch (const char* msg)
	{
		printf("%s\n", msg);
	}
	/* Output message when errors other than specified exceptions occur */
	catch (...)
	{
		printf("Unknown error\n");
	}

	return 0;
}

// FUNCTION		: createRadio()
// DESCRIPTION	: allocate radio pointers to memory appropriate for options
// PARAMETERS	: PioneerCarRadio** newRadio : dereferencing pointer variables
//				: char* newChoice			 : specified option value required for memory allocation selection
// RETURN		: None
void createRadio(PioneerCarRadio** newRadio, char* newChoice)
{
	/* If the user's input value is equal to '-car', allocate dynamic memory to PioneerCarRadio */
	if (strcmp(newChoice, kPioneerCarRadio) == 0)
	{
		*newRadio = (PioneerCarRadio*)new PioneerCarRadio;
		// cause exceptions if memory is not allocated
		if (*newRadio == NULL)
		{
			throw "Not enough memory";
		}
	}
	/* If the user's input value is equal to '-am', allocate dynamic memory to PioneerCarRadio */
	else if (strcmp(newChoice, kPioneerAM) == 0)
	{
		*newRadio = (PioneerAM*)new PioneerAM;
		// cause exceptions if memory is not allocated
		if (*newRadio == NULL)
		{
			throw "Not enough memory";
		}
	}
	/* If the user's input value is equal to '-world', allocate dynamic memory to PioneerCarRadio */
	else if (strcmp(newChoice, kPioneerWorld) == 0)
	{
		*newRadio = (PioneerWorld*)new PioneerWorld;
		// cause exceptions if memory is not allocated
		if (*newRadio == NULL)
		{
			throw "Not enough memory";
		}
	}
	/* exceptions that occur when a value other than the specified value is delivered */
	else
	{
		throw "This character is not allowed to run the radio";
	}
}

// FUNCTION		: switchingRadio()
// DESCRIPTION	: A function that receives a user input of whether to create a new radio after destroying the object
// PARAMETERS	: None
// RETURN		: const char* : return a string corresponding to the input value option
const char* switchingRadio(void)
{
	char input;
	while (1)
	{
		input = getch();
		switch (input)
		{
		case 'c':							// Return '-car' when the user enters 'c'
			return kPioneerCarRadio;
		case 'a':							// Return '-am' when the user enters 'a'
			return kPioneerAM;			
		case 'w':							// Return '-world' when the user enters 'w'
			return kPioneerWorld;			
		case 'x':							// throw an exception to the end of a program
			throw "Quit the program";
		default:
			break;
		}
	}
}