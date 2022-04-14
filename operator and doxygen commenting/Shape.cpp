/*
* DESCRIPTION		:
* 	Settings for the Shape class function
*/

#include "Shape.h"

/**
* @brief Shape class constructor
* @details initialize a shape class data member
* @param const char* whichName indicate the name of the figure to be created
* @param const char* whichColour indicate the colour of the figure to be created
* @return none
*/
Shape::Shape(const char* whichName, const char* whichColour)
{
	strcpy(name, whichName);
	strcpy(colour, whichColour);
}

/**
* @brief Shape class constructor
* @details define the default value for Shape class
* @param none
* @return none
*/
Shape::Shape(void)
{
	strcpy(name, "Unknown");
	strcpy(colour, "undefined");
}

/**
* @brief Shape class accessor
* @details indicate an access to a name data member
* @param none
* @return char* name return a name data member
*/
char* Shape::GetName(void)
{
	return name;
}

/**
* @brief Shape class accessor
* @details indicate an access to a colour data member
* @param none
* @return char* name return a colour data member
*/
char* Shape::GetColour(void)
{
	return colour;
}


/**
* @brief Shape class name mutator
* @details determine the scope of name data member
* @param char* newName received name value
* @return none
*/
void Shape::SetName(char* newName)
{
	int inputSize = 0;

	inputSize = strlen(newName);
	// allowed name value check
	if (inputSize > kNameSize)
	{
		strcpy(name, "Unknown");
	}
	else if (strcmp(newName, "Circle") == 0)
	{
		strcpy(name, newName);
	}
	else if (strcmp(newName, "Square") == 0)
	{
		strcpy(name, newName);
	}
	else
	{
		strcpy(name, "Unknown");
	}
}

/**
* @brief Shape class colour mutator
* @details determine the scope of colour data member
* @param char* newColour received colour value
* @return none
*/
void Shape::SetColour(char* newColour)
{
	int inputSize = 0;

	inputSize = strlen(newColour);
	// allowed colour value check
	if (inputSize > kColourSize)
	{
		strcpy(colour, "undefined");
	}
	else if (strcmp(newColour, "red") == 0)
	{
		strcpy(colour, newColour);
	}
	else if (strcmp(newColour, "green") == 0)
	{
		strcpy(colour, newColour);
	}
	else if (strcmp(newColour, "blue") == 0)
	{
		strcpy(colour, newColour);
	}
	else if (strcmp(newColour, "yellow") == 0)
	{
		strcpy(colour, newColour);
	}
	else if (strcmp(newColour, "purple") == 0)
	{
		strcpy(colour, newColour);
	}
	else if (strcmp(newColour, "pink") == 0)
	{
		strcpy(colour, newColour);
	}
	else if (strcmp(newColour, "orange") == 0)
	{
		strcpy(colour, newColour);
	}
	else
	{
		strcpy(colour, "undefined");
	}
}
