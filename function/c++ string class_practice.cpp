/*
* DESCRIPTION		:
* 	This program is to calculate the cost of people checking in at the hotel according to the date of the meeting
*/

#include <iostream>
#include <string>

using namespace std;

// Constant
const int error = -1;

// Prototypes
int dayToIndex(string when);
double calculateRoomCost(const double arrRoomRate[], int checkInDay, int checkOutDay);

int main(void)
{
	const double roomRate[6] = { 127.50,128.25,130.50,150,150,162.50 };
	int inDay = 0;
	int outDay = 0;
	int peopleCount = 0;
	double cost = 0;
	double totalCost = 0;
	string checkInDay;
	string checkOutDay;
	string peopleName;

	/* Enter the information of 4 people attending the meeting */
	for (peopleCount; peopleCount < 4; peopleCount++)
	{
		cout << "Name: ";
		getline(cin, peopleName);

		/* If person doesn't have a name, skip that person */
		if (peopleName == "")
		{
			cout << "Error: name missing. Skipping this person." << endl << endl;
		}
		/* Receive people check-in date */
		else
		{
			cout << "When are they checking in: ";
			getline(cin, checkInDay);
			inDay = dayToIndex(checkInDay);

			/* If person enters the wrong date, skip that person */
			if (inDay == error)
			{
				cout << "Error: Invalid legth of stay. Skipping this person." << endl << endl;
			}
			/* If person check-in after Thursday, skip that person */
			else if (inDay > 4)
			{
				cout << "Error: this person is missing the meeting. Skipping this person." << endl << endl;
			}
			/* Receive people check-out date */
			else
			{
				cout << "When are they checking out: ";
				getline(cin, checkOutDay);
				outDay = dayToIndex(checkOutDay);

				/* If person enters the wrong date or the check-in date and check-out date are the same, skip that person */
				if (outDay == error || outDay == inDay)
				{
					cout << "Error: Invalid legth of stay. Skipping this person." << endl << endl;
				}
				/* If person check-out before Thursday, skip that person */
				else if (outDay < 4)
				{
					cout << "Error: this person is missing the meeting. Skipping this person." << endl << endl;
				}
				/* Calculate the hotel cost and settle the total cost */
				else
				{
					cost = calculateRoomCost(roomRate, inDay, outDay);					
					cout << "The room cost for " << peopleName << " is " << cost << "." << endl << endl;
					totalCost += cost;
				}				
			}			
		}		
	}	
	cout << "The total room cost for everyone is " << totalCost << "." << endl;

	return 0;
}

// Function		: dayToIndex()
// Description	: Divide the days into index numbers
// Parameters	: string when		: Distinguish the days
// Return Values: int dayIndex		: Return the index by day
int dayToIndex(string when)
{
	int dayIndex = 0;

	if (when == "sun")
	{
		dayIndex = 0;
	}
	else if (when == "mon")
	{
		dayIndex = 1;
	}
	else if (when == "tue")
	{
		dayIndex = 2;
	}
	else if (when == "wed")
	{
		dayIndex = 3;
	}
	else if (when == "thu")
	{
		dayIndex = 4;
	}
	else if (when == "fri")
	{
		dayIndex = 5;
	}
	else if (when == "sat")
	{
		dayIndex = 6;
	}
	else
	{
		dayIndex = error;
	}
	return dayIndex;
}

// Function		: calculateRoomCost()
// Description	: To calculate the fee according to the check-in date
// Parameters	: const double arrRommRate[]: This is the hotel fee for each day
//				  int checkInDay			: Check-in date	 
//				  int checkOutDay			: Check-out date
// Return Values: double total				: Return the calculated total cost
double calculateRoomCost(const double arrRoomRate[], int checkInDay, int checkOutDay)
{
	double total = 0;

	for (checkInDay; checkInDay < checkOutDay; checkInDay++)
	{
			total += arrRoomRate[checkInDay];
	}
	return total;		
}