/*
* Description: It is a content that uses the getNum() function to receive numbers and 
*			   check the input numbers within a designated range through 
*			   the rangeChecker() function to raise two values using the powerCalculator() function.
*/

#include <stdio.h>
#pragma warning(disable: 4996) 

// prototypes
int powerCalculator(int base, int exponent);
int rangeChecker(int check, int min, int max);
int getNum(void);

int main(void)
{
	int userOption = 0;			//	Check the user's options.
	int base = 1;				//	Save the input value.
	int baseBefore = 1;			//	The purpose of checking the range of input values.
	int exponent = 1;			//	Save the input value.
	int exponentBefore = 1;		//	The purpose of checking the range of input values.
	int checker = 1;			//	To check the scope.
	int power = 0;				//	The purpose of storing the calculated value.
		
	// If the user's option is an integer, continue with the program.
	while (userOption > -1)
	{
		// Basic menu
		if (userOption == 0)
		{
		printf("\n\n");
		printf("Power Menu :\n\n");
		printf("      1. Charge base\n");
		printf("      2. Charge exponent\n");
		printf("      3. Display base raise to exponent\n");
		printf("      4. Exit program\n");
		printf("\nOption? ");

		userOption = getNum();	//	Receive user's options
			
			// Check the user's options (move base)
			if (userOption == 1)
			{
				printf("\ncharge base:  ");
				baseBefore = getNum();						//	Receive a user's value.
				checker = rangeChecker(baseBefore, 1, 25);	//	Check the range of input values.
				//	Notification that it's out of range.
				if (checker == 0)
				{
					printf("Base value is out of range!\n");
				}
				else
				{
					base = baseBefore;	//	Save the value if it's included in the range.
				}
				userOption = 0;	//	move on to the main menu.
			}
			//	Check the user's options (move the exponent)
			else if (userOption == 2)
			{
				printf("\ncharge exponent:  ");
				exponentBefore = getNum();						//	Receive a user's value.
				checker = rangeChecker(exponentBefore, 1, 5);	//	Check the range of input values.
				//	Notification that it's out of range.
				if (checker == 0)
				{
					printf("Exponent value is out of range!\n");
				}
				else
				{
					exponent = exponentBefore;	//	Save the value if it's included in the range.
				}
				userOption = 0;	//	move on to the main menu.
			}
			//	Check the user's options (calculation)
			else if (userOption == 3)
			{
				power = powerCalculator(base, exponent);	//	Calculate the two stored values.
				printf("\n%d to the power of %d is %d\n", base, exponent, power);
				userOption = 0;	//	move on to the main menu.
			}
			//	Check the user's options (exit).
			else if (userOption == 4)
			{
				userOption = -1;	//	End of the program.
			}
			//	It indicates that the input value is wrong.
			else
			{
				printf("invalid entry\n");
				userOption = 0;	//	move on to the main menu.
			}
		}		
	}
	return 0;
}

// Function		:powerCalculator()
// Description	:A function that raise the two values received.
// Parameter	:int base		:value to increase
//				:int exponent	:number of times to increase
// Return		:int power		:return calculated value
int powerCalculator(int base, int exponent)
{
	int power = 1;	//	Save the power value.
	int count = 1;	//	The number of calculations.

	//	Repeat as many times as the input value.
	while (count <= exponent)
	{
		power *= base;	//	Multiply the power by the number of times.
		count++;		//	Increase the number by 1.
	}
	return power;
}

// Function		:rangeChecker()
// Description	:A function that checks conditions by specifying a range.
// Parameter	:int check		:value to check
//				:int min		:minimum value of range
//				:int max		:maximum value of range
// Return		:int range		:return checked value
int rangeChecker(int check, int min, int max)
{
	int range = 0;	//	The value to check the range and return it.

	//	If the base value falls within the range, True
	if (check >= min && check <= max)
	{
		range = 1;		
	}		
	return range;
}

// Function	   : getNum()
// Description : Sample number input function received from Carlo.
// Parameter   : None
// Return	   : int number		:returns the number of value entered by the user
int getNum(void) 
{
	/* we will see in a later lecture how we can improve this code */ 
	char record[121] = { 0 }; 
	/* record stores the string */ 
	
	int number = 0;
	/* NOTE to student: indent and brace this function consistent with your others */

	/* use fgets() to get a string from the keyboard */     
	fgets(record, 121, stdin);
	/* extract the number from the string; sscanf() returns a number       
		* corresponding with the number of items it found in the string */     
	if (sscanf(record, "%d", &number) != 1)
	{
		/* if the user did not enter a number recognizable by
			 * the system, set number to -1 */         
		number = -1;
	}
	return number;
}
