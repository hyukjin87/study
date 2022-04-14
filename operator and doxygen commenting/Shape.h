/*
* NAME				: Shape
* PURPOSE			: The Shape class is responsible for creating shapes.
*					  Determines the name and color of the shape.
*/

/**
* @mainpage Shape Project
* @author Hyuk-Jin Kwon
*/

#include <stdio.h>
#include <string.h>
#pragma warning(disable: 4996)

// Constants
#define kNameSize 50
#define kColourSize 10
#define kPi 3.1415926

/**
* @class Shape
* @brief parent class that generates shapes
*/

#ifndef __SHAPE_H__
#define __SHAPE_H__
class Shape
{
private:
	char name[kNameSize];			// Name variables in shapes

protected:
	char colour[kColourSize];		// Color Variables for Shape

public:
	// constructors
	Shape(void);
	Shape(const char* whichName, const char* whichColour);	

	// accessors
	char* GetName(void);
	char* GetColour(void);

	// mutators
	void		 SetName(char* newName);
	virtual void SetColour(char* newColour);

	// pure virtual functions
	virtual float Perimeter(void) = 0;
	virtual float Area(void) = 0;
	virtual float OverallDimension(void) = 0;
	virtual void  Show(void) = 0;
};
#endif