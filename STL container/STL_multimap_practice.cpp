/*
* DESCRIPTION		:
* 	Get information about the movie and sort the genre and rate in the multimap to be displayed
*/

#include <iostream>
#include <map>
#include <string>
#pragma warning(disable:4996)
using namespace std;

// Prototypes
int getMovieInfo(string* newGenre, string* newTitle, int* newRate);
void printMovieInfo(multimap<pair<int, string>, string> multi2, multimap<pair<string, string>, int> multi);
int findMovie(multimap<pair<int, string>, string> *multi2, multimap<pair<string, string>, int>* multi);
int getNum(void);

// Constants
#define kSize 30

int main(void)
{
	string genre = { 0 };
	string title = { 0 };
	int rate = 0;
	multimap<pair<int, string>, string> rateSortMultimap;
	multimap<pair<string, string>, int> genreSortMultimap;

	while (1)
	{
		if (getMovieInfo(&genre, &title, &rate) < 0)							// receive movie information from users
		{
			break;																// loop termination in case of error
		}
		rateSortMultimap.insert(make_pair(make_pair(rate, genre), title));		// configuring multimap on a rate sort basis
		genreSortMultimap.insert(make_pair(make_pair(genre, title), rate));		// configuring multimap on a genre sort basis
	}
	
	printMovieInfo(rateSortMultimap, genreSortMultimap);						// output sorted multimap

	/* If the multimap is not empty, search and re-output the updated multimap */
	if (rateSortMultimap.empty() != 1)
	{
		findMovie(&rateSortMultimap, &genreSortMultimap);
		printMovieInfo(rateSortMultimap, genreSortMultimap);
	}	
	return 0;
}

// Function		: getMovieInfo()
// Description	: A function of receiving genre, title, and rate from the user
// Parameters	: string *newGenre	: user input genre
//				  string *newTitle	: user input title
//				  int *newRate		: user input rate
// Return Values: int				: function normal operation check
int getMovieInfo(string *newGenre, string *newTitle, int *newRate)
{
	string genre = { 0 };
	string title = { 0 };
	int rate = 0;

	cout << "Enter genre: ";
	getline(cin, genre);		// receive genre value
	/* If the input value exceeds the limited size or is an exit command */
	if (genre.length() > kSize || genre == ".")
	{
		return -1;
	}
	*newGenre = genre;

	cout << "Enter title: ";
	getline(cin, title);		// receive title value
	/* If the input value exceeds the limited size or is an exit command */
	if (title.length() > kSize || title == ".")
	{
		return -2;
	}
	*newTitle = title;

	cout << "Enter rating of 1-5: ";
	rate = getNum();			// receive rate value
	/* If the input value exceeds the limited size */
	if (rate <= 0 || rate > 5)
	{
		cout << "Error reading rating input" << endl;
		return -3;
	}
	*newRate = rate;

	return 1;
}

// Function		: printMovieInfo()
// Description	: function of outputting sorted multimap
// Parameters	: multimap<pair<int, string>, string> newRateMultimap  : multimap container sorted by rate
//				  multimap<pair<string, string>, int> newGenreMultimap : multimap container sorted by genre
// Return Values: none
void printMovieInfo(multimap<pair<int, string>, string> newRateMultimap, multimap<pair<string, string>, int> newGenreMultimap)
{
	multimap<pair<int, string>, string>::iterator iterRate;
	multimap<pair<string, string>, int>::iterator iterGenre;

	cout << endl;
	cout << "Sorted by Rating:" << endl;
	for (iterRate = newRateMultimap.begin(); iterRate != newRateMultimap.end(); ++iterRate)
	{
		cout.flags(ios::left);					// left-justified with a width of 35 characters
		cout.width(35);
		cout << iterRate->first.second;
		cout.flags(ios::left);					// left-justified with a width of 35 characters
		cout.width(35);
		cout << iterRate->second;
		cout << iterRate->first.first << endl;
	}
	cout << endl;
	cout << "Sorted by Genre:" << endl;
	for (iterGenre = newGenreMultimap.begin(); iterGenre != newGenreMultimap.end(); ++iterGenre)
	{
		cout.flags(ios::left);					// left-justified with a width of 35 characters
		cout.width(35);
		cout << iterGenre->first.first;
		cout.flags(ios::left);					// left-justified with a width of 35 characters
		cout.width(35);
		cout << iterGenre->first.second;
		cout << iterGenre->second << endl;
	}
}

// Function		: findMovie()
// Description	: function to retrieve the value entered by the user from the container and update the rate
// Parameters	: multimap<pair<int, string>, string> newRateMultimap  : multimap container sorted by rate
//				  multimap<pair<string, string>, int> newGenreMultimap : multimap container sorted by genre
// Return Values: int												   : function normal operation check
int findMovie(multimap<pair<int, string>, string> *newRateMultimap, multimap<pair<string, string>, int>* newGenreMultimap)
{
	multimap<pair<int, string>, string>::iterator iterRate;
	multimap<pair<string, string>, int>::iterator iterGenre;
	string genre = { 0 };
	string title = { 0 };
	int rate = 0;

	multimap<pair<int, string>, string> newRate(*newRateMultimap);
	multimap<pair<string, string>, int> newGenre(*newGenreMultimap);

	cout << "Please input the name of the genre of the movie you selected: ";
	getline(cin, genre);		// User enters the genre value to search for
	/* If the input value exceeds the limited size or is an exit command */
	if (genre.length() > kSize || genre == ".")
	{
		return -1;
	}
	cout << "Please input the title of the movie you selected: ";
	getline(cin, title);		// User enters the title value to search for
	/* If the input value exceeds the limited size or is an exit command */
	if (title.length() > kSize || title == ".")
	{
		return -2;
	}
	/* search for sorted containers */
	for (iterRate = newRate.begin(); iterRate != newRate.end(); ++iterRate)
	{
		if (iterRate->first.second == genre)
		{			
			if (iterRate->second == title)
			{
				newRate.erase(iterRate);	// Delete the value if it matches the value entered by the user
				cout << "Enter updated rating of 1-5: ";
				rate = getNum();
				/* If the input value exceeds the limited size */
				if (rate <= 0 || rate > 5)
				{
					cout << "Error reading rating input";
					return -3;
				}
				else
				{
					newRate.insert(make_pair(make_pair(rate, genre), title));		// add the updated rate value to the container
					/* search for sorted containers */
					for (iterGenre = newGenre.begin(); iterGenre != newGenre.end(); ++iterGenre)
					{
						if (iterGenre->first.first == genre)
						{
							if (iterGenre->first.second == title)
							{
								newGenre.erase(iterGenre);		// Delete the value if it matches the value entered by the user						
								newGenre.insert(make_pair(make_pair(genre, title), rate));		// add the updated rate value to the container
								/* Returning used temporary containers */
								*newRateMultimap = newRate;
								*newGenreMultimap = newGenre;
								return 1;
							}
						}
					}					
				}
			}
		}
	}
	return 1;
}

// Function		: getNum()
// Description	: A function of receiving numbers from the user
// Parameters	: None
// Return Values: int		: The number you received
int getNum(void)
{
	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[121] = { 0 }; /* record stores the string */
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
