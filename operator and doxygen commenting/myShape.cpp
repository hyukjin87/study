/*
* DESCRIPTION		:
* 	Run shape programs and provide appropriate prompts for users
*/

/**
* @mainpage Adding Operators Project
* 
* @section intro Program Instroduction
* myShape is intended to test and simulate an example of an operator overload.
* 
* <hr>
* @section version Current version of project:
* <ul>
* <li>@author Hyuk Jin Kwon</li>
* <li>@version 1.00.00</li>
* <li>@date 2022-04-08</li>
* <li>@details Run shape programs and provide appropriate prompts for users\n
* The main function of this program is to instantiate three circular and three rectangular objects first.\n
* The round objects of each class are added and multiplied for simulation.\n
* The above progressed results are stored in the play object.\n
* The output result values are then compared between objects and determined by the '=' and '==' operators.\n
* Displays the output for each course, and the final result value is output after all the courses are finished.\n
* </li>
* </ul>
*/

#include "Circle.h"
#include "Shape.h"
#include "Square.h"

int main(void)
{	
	// instantiate 3 Circle objects, 3 Square objects
	Circle round1("red", 5.5);
	Circle round2("blue", 10.5);
	Circle playARound;
	Square square1("orange", 5);
	Square square2("purple", 12);
	Square playASquare;

	// print out current status of every instantiated object
	round1.Show();
	round2.Show();
	playARound.Show();
	square1.Show();
	square2.Show();
	playASquare.Show();
		
	playARound = round1 + round2;		// perform overloaded addition for Circle objects
	playASquare = square2 + square1;	// perform overloaded addition for Square objects

	// print out current status of play object
	playARound.Show();
	playASquare.Show();

	playARound = round1 * round2;		// perform overloaded multiplication for Circle objects
	playASquare = square2 * square1;	// perform overloaded multiplication for Square objects
	
	// print out current status of play object
	playARound.Show();
	playASquare.Show();

	// perform overloaded direct assignment
	playARound = round1;
	// perform overloaded equal comparison
	if (playARound == round1)
	{
		printf("\nHurray !!\n");
	}
	else
	{
		printf("\nAwww !!\n");
	}

	return 0;
}
