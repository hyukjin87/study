/*
* DESCRIPTION		:
* 	A set of functions that set and output conditions suitable for the input value.
*/

#include "Square.h"

#ifndef __SQUARE_H__
#define __SQUARE_H__

/**
* @brief Square class constructor
* @details initialize a square class data member
* @param const char* whichColour user-input color
* @param float newSideLength user-input side length
* @return none
*/
Square::Square(const char* whichColour, float newSideLength) : Shape("Square",whichColour)
{
	// Check that the sideLength is not negative
	if (newSideLength >= 0)
	{
		sideLength = newSideLength;
	}
	else
	{
		sideLength = 0;
	}
}

/**
* @brief Square class constructor
* @details define the default value for Square class
* @param none
* @return none
*/
Square::Square(void) : Shape("Square", "undefined")
{
	sideLength = 0;
}

/**
* @brief Square class destructor
* @details Display output message when object is destroyed
* @param none
* @return none
*/
Square::~Square()
{
	printf("The square is squished ...\n");
}

/**
* @brief Square class accessor
* @details indicate an access to a side length data member
* @param none
* @return float sideLength return a sideLength data member
*/
float Square::GetSideLength(void)
{
	return sideLength;
}

/**
* @brief Square class accessor
* @details indicate an access to a colour data member
* @param none
* @return this object colour
*/
char* Square::GetSquareColour(void)
{
	return this->colour;
}

/**
* @brief Square class const accessor
* @details indicate an access to a colour data member
* @param none
* @return this object colour
*/
const char* Square::GetSquareColour(void) const
{
	return this->colour;
}

/**
* @brief Square class name mutator
* @details determine the scope of sideLength data member
* @param float newSideLength received side length value
* @return none
*/
void Square::SetSideLength(float newSideLength)
{
	// negative value of 0
	if (newSideLength < 0)
	{
		sideLength = 0;
	}
	else
	{
		sideLength = newSideLength;
	}
}

/**
* @brief Square class mutator
* @details determine the scope of colour data member
* @param char* newColour received colour value
* @return none
*/
void Square::SetColour(char* newColour)
{
	Shape::SetColour(newColour);
}

/**
* @brief Square class operator
* @details Square class plus operator. The color will use the color of the LHS.
* @param const Square& op2 received Square object
* @return Square object
*/
Square Square::operator+(const Square& op2)
{
	Square temp;
	// Follow the LHS colour
	temp.SetColour(GetColour());
	temp.sideLength = sideLength + op2.sideLength;

	return temp;
}

/**
* @brief Square class operator
* @details Square class multiplication operator. The color will use the color of the RHS.
* @param const Square& op2 received Square object
* @return Square object
*/
Square Square::operator*(const Square& op2)
{
	Square temp;
	// Follow the RHS colour
	temp.SetColour(strcpy(this->colour,op2.colour));
	temp.sideLength = sideLength * op2.sideLength;

	return temp;
}

/**
* @brief Square class operator
* @details Square class Comparative operator. If the values of the two objects are not the same, substitute the RHS value
* @param const Square& op2 received Square object
* @return Square object
*/
const Square& Square::operator=(const Square& op2)
{
	if (this != &op2)
	{
		strcpy(this->colour, op2.colour);
		this->sideLength = op2.sideLength;
	}
	return *this;
}

/**
* @brief Square class operator
* @details Square class Comparative operator. Returns True if two objects have equal values, False if not equal
* @param const Square& op2 received Square object
* @return bool
*/
bool Square::operator==(const Square& op2)
{
	if ((this->GetColour() == op2.GetSquareColour()) && (sideLength == op2.sideLength))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief Square class virtual function
* @details formula for determining the circumference of a square
* @param none
* @return float squarePerimeter calculated square circumference
*/
float Square::Perimeter(void)
{
	float squarePerimeter = 0;
	squarePerimeter = 4 * sideLength;

	return squarePerimeter;
}

/**
* @brief Square class virtual function
* @details formula for determining the area of a square
* @param none
* @return float squareArea calculated square area
*/
float Square::Area(void)
{
	float squareArea = 0;
	squareArea = sideLength * sideLength;

	return squareArea;
}

/**
* @brief Square class virtual function
* @details formula for determining the size of a square
* @param none
* @return float squareDimension calculated square dimension
*/
float Square::OverallDimension(void)
{
	float squareDimension = 0;
	squareDimension = sideLength;

	return squareDimension;
}

/**
* @brief Display function
* @details function of outputting values stored in a calculated square
* @param none
* @return none
*/
void Square::Show(void)
{
	printf("\nShape Information\n");
	printf("Name           : %s\n",GetName());
	printf("Colour         : %s\n",GetColour());
	printf("Side-Length    : %.2f cm\n",GetSideLength());
	printf("Perimeter      : %.2f cm\n",Perimeter());
	printf("Area           : %.2f square cm\n",Area());
}
#endif