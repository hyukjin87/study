/*
* NAME				: Square
* PURPOSE			: The Square class is set to the child class of the Shape class.
*					  Create a square based on the set side-length and color.
*					  Calculates the perimeter and area of a square according to its side length and outputs it. 
*					  Added ability to combine, multiply, or compare square.
*/
#include "Shape.h"

/**
* @class Square
* @brief child class that generates square
*/

class Square : public Shape
{
private:
	float sideLength;

public:
	// constructors
	Square(void);
	Square(const char* whichColour, float newSideLength);

	// destructor
	virtual ~Square();

	// accessors
	float		GetSideLength(void);
	char*		GetSquareColour(void);
	const char* GetSquareColour(void) const;

	// mutators
	void		 SetSideLength(float newSideLength);
	virtual void SetColour(char* newColour);

	// operators
	Square		  operator+(const Square& op2);
	Square		  operator*(const Square& op2);
	const Square& operator=(const Square& op2);
	bool		  operator==(const Square& op2);
	
	// a virtual function that calculates and display a square
	virtual float Perimeter(void);
	virtual float Area(void);
	virtual float OverallDimension(void);
	virtual void  Show(void);
};