/*
* DESCRIPTION		:
* 	A set of functions that set and output conditions suitable for the input value.
*/

#include "Circle.h"

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

/**
* @brief Circle class constructor
* @details initialize a circle class data member
* @param const char* whichColour user-input color
* @param float newRadius user-input radius
* @return none
*/
Circle::Circle(const char* whichColour, float newRadius) : Shape("Circle", whichColour)
{
	// Check that the radius is not negative
	if (newRadius >= 0)
	{
		radius = newRadius;
	}
	else
	{
		radius = 0;
	}
}

/**
* @brief Circle class constructor
* @details define the default value for Circle class
* @param none
* @return none
*/
Circle::Circle(void) : Shape("Circle","undefined")
{
	radius = 0;
}

/**
* @brief Circle class destructor
* @details Display output message when object is destroyed
* @param none
* @return none
*/
Circle::~Circle()
{
	printf("The circle is broken ...\n");
}

/**
* @brief Circle class accessor
* @details indicate an access to a radius data member
* @param none
* @return float radius return a radius data member
*/
float Circle::GetRadius(void)
{
	return radius;
}

/**
* @brief Circle class accessor
* @details indicate an access to a colour data member
* @param none
* @return this object colour
*/
char* Circle::GetCircleColour(void)
{
	return this->colour;
}

/**
* @brief Circle class const accessor
* @details indicate an access to a colour data member
* @param none
* @return this object colour
*/
const char* Circle::GetCircleColour(void) const
{
	return this->colour;
}

/**
* @brief Circle class mutator
* @details determine the scope of radius data member
* @param float newRadius received radius value
* @return none
*/
void Circle::SetRadius(float newRadius)
{
	// negative value of 0
	if (newRadius < 0)
	{
		radius = 0;
	}
	else
	{
		radius = newRadius;
	}
}

/**
* @brief Circle class mutator
* @details determine the scope of colour data member
* @param char* newColour received colour value
* @return none
*/
void Circle::SetColour(char* newColour)
{
	Shape::SetColour(newColour);
}

/**
* @brief Circle class operator
* @details Circular class plus operator. The color will use the color of the LHS.
* @param const Circle& op2 received Circle object
* @return Circle object
*/
Circle Circle::operator+(const Circle& op2)
{
	Circle temp;
	// Follow the LHS colour
	temp.SetColour(GetColour());
	temp.radius = radius + op2.radius;

	return temp;
}

/**
* @brief Circle class operator
* @details Circular class multiplication operator. The color will use the color of the RHS.
* @param const Circle& op2 received Circle object
* @return Circle object
*/
Circle Circle::operator*(const Circle& op2)
{
	Circle temp;
	// Follow the RHS colour
	temp.SetColour(strcpy(this->colour,op2.colour));
	temp.radius = radius * op2.radius;

	return temp;
}

/**
* @brief Circle class operator
* @details Circular class Comparative operator. If the values of the two objects are not the same, substitute the RHS value
* @param const Circle& op2 received Circle object
* @return Circle object
*/
const Circle& Circle::operator=(const Circle& op2)
{
	if (this != &op2)
	{
		strcpy(this->colour, op2.colour);
		this->radius = op2.radius;
	}
	return *this;
}

/**
* @brief Circle class operator
* @details Circular class Comparative operator. Returns True if two objects have equal values, False if not equal
* @param const Circle& op2 received Circle object
* @return bool
*/
bool Circle::operator==(const Circle& op2)
{
	// Compare the color and radius values of two objects
	if (strcmp(this->GetColour(), op2.GetCircleColour())==0 
		&& (radius == op2.radius))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief Circle class virtual function
* @details formula for determining the circumference of a circle
* @param none
* @return float circlePerimeter calculated circle circumference
*/
float Circle::Perimeter(void)
{
	float circlePerimeter = 0;
	circlePerimeter = 2 * (float)kPi * radius;
	
	return circlePerimeter;
}

/**
* @brief Circle class virtual function
* @details formula for determining the area of a circle
* @param none
* @return float circleArea calculated circle area
*/
float Circle::Area(void)
{
	float circleArea = 0;
	circleArea = (float)kPi * radius * radius;

	return circleArea;
}

/**
* @brief Circle class virtual function
* @details formula for determining the size of a circle
* @param none
* @return float circleDimension calculated circle dimension
*/
float Circle::OverallDimension(void)
{
	float circleDimension = 0;
	circleDimension = 2 * radius;

	return circleDimension;
}

/**
* @brief Display function
* @details function of outputting values stored in a calculated circle
* @param none
* @return none
*/
void Circle::Show(void)
{
	printf("\nShape Information\n");
	printf("Name           : %s\n",GetName());
	printf("Colour         : %s\n",GetColour());
	printf("Radius         : %.2f cm\n", GetRadius());
	printf("Circumference  : %.2f cm\n", Perimeter());
	printf("Area           : %.2f square cm\n", Area());
}
#endif