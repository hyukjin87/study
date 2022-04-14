/*
* NAME				: Circle
* PURPOSE			: The Circle class is set to the child class of the Shape class.
*					  Create a circle based on the set radius and color. 
*					  Calculates the circumference and area of a circle according to its radius and outputs it. 
*					  Added ability to combine, multiply, or compare circles.
*/

#include "Shape.h"

/**
* @class Circle
* @brief child class that generates circle
*/

class Circle : public Shape
{
private:
	float radius;				// Radius variable of circle

public:
	// constructors
	Circle(void);
	Circle(const char* whichColour, float newRadius);

	// destructor
	virtual ~Circle();

	// accessors
	float		GetRadius(void);
	char*		GetCircleColour(void);
	const char* GetCircleColour(void) const;

	// mutators
	void		 SetRadius(float newRadius);
	virtual void SetColour(char* newColour);

	// operators
	Circle		  operator+(const Circle& op2);
	Circle		  operator*(const Circle& op2);
	const Circle& operator=(const Circle& op2);
	bool		  operator==(const Circle& op2);
	
	// a virtual function that calculates and display a circle
	virtual float Perimeter(void);
	virtual float Area(void);
	virtual float OverallDimension(void);
	virtual void  Show(void);
};