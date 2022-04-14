/*
* DESCRIPTION		:
* 	Get information about the movie and sort the genre and rate in the linked list to be displayed
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

// Data Type
struct MovieInfo {
	char* pGenre = NULL;
	char* pTitle = NULL;
	int rate = 0;
	struct MovieInfo* next;
	struct MovieInfo* prev;
};

// Prototypes
int getMovieInfo(MovieInfo* node, MovieInfo* sortNode);
void printMovieInfo(MovieInfo* head, MovieInfo* sortGenre);
void updatePrintMovieInfo(MovieInfo* head, MovieInfo* sortGenre);
void clearCR(char* buf);
MovieInfo* MovieNode(MovieInfo** head, MovieInfo** tail, MovieInfo** sortHead, MovieInfo** sortTail);
MovieInfo* AddMovieNode(MovieInfo** head, MovieInfo** tail, MovieInfo** sortHead, MovieInfo** sortTail, char *newGenre, char *newTitle);
MovieInfo* findMovie(MovieInfo* head, char* newGenre, char* newTitle);
int deleteNode(MovieInfo* node, MovieInfo** head, MovieInfo** tail);
int getNum(void);

// Constants
#define kSize 30

int main(void)
{
	MovieInfo* head = NULL;
	MovieInfo* tail = NULL;
	MovieInfo* sortHead = NULL;
	MovieInfo* sortTail = NULL;
	MovieInfo* nodeCount = NULL;
	MovieInfo* findNode = NULL;
	MovieInfo* findSortNode = NULL;
	char findGenre[kSize] = { 0 };
	char findTitle[kSize] = { 0 };

	int loop = 0;
	int loopCount = 0;
	int count = 0;

	while (loop == 0)
	{
		// Check the number of loops
		loopCount++;

		MovieNode(&head, &tail, &sortHead, &sortTail);

		// Check the number of nodes
		nodeCount = head;
		while (nodeCount != NULL)
		{
			nodeCount = nodeCount->next;
			count++;
		}
		// Compare the number of nodes and the number of loops
		if (loopCount != count)
		{
			break;
		}
		// Initialize the number of nodes
		count = 0;
	}

	printMovieInfo(head, sortHead);
	
	// Search for the node the user wants to find
	printf("Please input the name of the genre of the movie you selected: ");
	fgets(findGenre, kSize, stdin);
	clearCR(findGenre);

	printf("Please input the title of the movie you selected: ");
	fgets(findTitle, kSize, stdin);
	clearCR(findTitle);
	findNode = findMovie(head, findGenre, findTitle);
	findSortNode = findMovie(sortHead, findGenre, findTitle);

	// If there is a node you are looking for, delete it and add a new node
	if (findNode != NULL)
	{
		deleteNode(findNode, &head, &tail);
		deleteNode(findSortNode, &sortHead, &sortTail);
		AddMovieNode(&head, &tail, &sortHead, &sortTail, findGenre, findTitle);
	}

	updatePrintMovieInfo(head, sortHead);

	return 0;
}

// Function		: MovieNode()
// Description	: Create a node with a linked list and sort node
// Parameters	: MovieInfo **head		: Deliver the node of the structure (sorting rate)
//				  MovieInfo **tail		: Deliver the tail node of the structure (sorting rate)
//				  MovieInfo **sortHead  : Deliver the node of the structure (sorting genre)
//				  MovieInfo **sortTail  : Deliver the tail node of the structure (soring genre)
// Return Values: MovieInfo			    : Corrected node delivery
MovieInfo* MovieNode(MovieInfo** head, MovieInfo** tail, MovieInfo** sortHead, MovieInfo** sortTail)
{
	MovieInfo* newNode = NULL;
	MovieInfo* sortNewNode = NULL;
	MovieInfo* nextNode = NULL;
	MovieInfo* prevNode = NULL;
	MovieInfo* sortNextNode = NULL;
	MovieInfo* sortPrevNode = NULL;

	// Dynamic assignment to pointer
	newNode = (MovieInfo*)malloc(sizeof(MovieInfo));
	if (newNode == NULL)
	{
		printf("Error! No more memory!\n");
		return *head;
	}
	sortNewNode = (MovieInfo*)malloc(sizeof(MovieInfo));
	if (sortNewNode == NULL)
	{
		printf("Error! No more memory!\n");
		return *sortHead;
	}
	// Add data to the node
	getMovieInfo(newNode, sortNewNode);
	// Create a head node
	if (*head == NULL)
	{
		*head = newNode;
		*tail = newNode;
		*sortHead = sortNewNode;
		*sortTail = sortNewNode;
	}
	// Node creation termination conditions
	else if (strcmp(newNode->pGenre, ".") == 0 || strcmp(newNode->pTitle, ".") == 0 || newNode->rate < 1 || newNode->rate >5)
	{
		newNode->next = NULL;
	}
	else
	{
		/* Sorting conditions according to rate */
		// Inserting at the front of the list
		if ((*head)->rate > newNode->rate)
		{
			newNode->next = *head;
			(*head)->prev = newNode;
			*head = newNode;
		}
		else
		{
			prevNode = *head;
			nextNode = (*head)->next;
			// Explore nodes that fit the sorting position
			while (nextNode != NULL)
			{
				if (nextNode->rate > newNode->rate)
				{
					break;
				}
				prevNode = nextNode;
				nextNode = nextNode->next;
			}
			// Add a new node
			newNode->prev = prevNode;
			newNode->next = nextNode;
			prevNode->next = newNode;
			// Tail node check
			if (nextNode == NULL)
			{
				*tail = newNode;
			}
			else
			{
				nextNode->prev = newNode;
			}
		}
		/* Sorting conditions according to genre */
		// Inserting at the front of the list
		if (strcmp((*sortHead)->pGenre, sortNewNode->pGenre) >= 0)
		{
			sortNewNode->next = *sortHead;
			(*sortHead)->prev = sortNewNode;
			*sortHead = sortNewNode;
		}
		else
		{
			sortPrevNode = *sortHead;
			sortNextNode = (*sortHead)->next;
			// Explore nodes that fit the sorting position
			while (sortNextNode != NULL)
			{
				if (strcmp(sortNextNode->pGenre, sortNewNode->pGenre) >= 0)
				{
					break;
				}
				sortPrevNode = sortNextNode;
				sortNextNode = sortNextNode->next;
			}
			// Add a new node			
			sortNewNode->prev = sortPrevNode;
			sortNewNode->next = sortNextNode;
			sortPrevNode->next = sortNewNode;
			// Tail node check
			if (sortNextNode == NULL)
			{
				*sortTail = sortNewNode;
			}
			else
			{
				sortNextNode->prev = sortNewNode;
			}
		}
	}

	return *head;
}

// Function		: getMovieInfo()
// Description	: Save the input value about movie information
// Parameters	: MovieInfo *node		: Node information delivery (sorting rate)
//				: MovieInfo *sortNode	: Node information delivery (sorting genre)
// Return Values: int				    : Check the program's normal operation
int getMovieInfo(MovieInfo* node, MovieInfo* sortNode)
{
	char genre[kSize] = { 0 };
	char title[kSize] = { 0 };
	char sortGenre[kSize] = { 0 };
	char sortTitle[kSize] = { 0 };

	// Receive genre information from the user
	printf("Enter genre: ");
	fgets(genre, sizeof genre, stdin);
	clearCR(genre);
	strcpy(sortGenre, genre);

	// Dynamic memory allocation for storing user information
	node->pGenre = (char*)malloc(sizeof genre);
	if (node->pGenre == NULL)
	{
		printf("Out of memory\n");
		return -1;
	}
	strcpy(node->pGenre, genre);

	sortNode->pGenre = (char*)malloc(sizeof sortGenre);
	if (sortNode->pGenre == NULL)
	{
		printf("Out of memory\n");
		return -2;
	}
	strcpy(sortNode->pGenre, sortGenre);

	// Check the termination conditions
	if (strcmp(node->pGenre, ".") == 0)
	{
		return -3;
	}
	else
	{
		// Receive title information from the user
		printf("Enter title: ");
		fgets(title, sizeof title, stdin);
		clearCR(title);
		strcpy(sortTitle, title);

		// Dynamic memory allocation for storing user information
		node->pTitle = (char*)malloc(sizeof title);
		if (node->pTitle == NULL)
		{
			printf("Out of memory\n");
			return -4;
		}
		strcpy(node->pTitle, title);

		sortNode->pTitle = (char*)malloc(sizeof sortTitle);
		if (sortNode->pTitle == NULL)
		{
			printf("Out of memory\n");
			return -5;
		}
		strcpy(sortNode->pTitle, sortTitle);

		// Check the termination conditions
		if (strcmp(node->pTitle, ".") == 0)
		{
			return -6;
		}

		// Receive rate information from the user
		printf("Enter rating of 1-5: ");
		node->rate = getNum();
		sortNode->rate = node->rate;

		if (node->rate < 0 || node->rate>5)
		{
			printf("Error reading rating input\n");
			return -7;
		}
	}
	// Processing the end of the node
	node->prev = NULL;
	node->next = NULL;
	sortNode->prev = NULL;
	sortNode->next = NULL;

	return 1;
}

// Function		: findMovie()
// Description	: A function for node location search
// Parameters	: MovieInfo *head		: Node information delivery
//				: MovieInfo *newGenre	: User input value needed for search
//				: MovieInfo *newTitle	: User input value needed for search
// Return Values: MovieInfo			    : Forward the location of the node you found
MovieInfo* findMovie(MovieInfo* head, char* newGenre, char* newTitle)
{
	MovieInfo* currNode = NULL;

	if (head == NULL)
	{
		return head;
	}
	currNode = head->next;
	// Search for node location corresponding to conditions
	while (currNode != NULL)
	{
		if (strcmp(currNode->pGenre, newGenre) == 0 && strcmp(currNode->pTitle, newTitle) == 0)
		{
			return currNode;
		}
		currNode = currNode->next;
	}
	printf("The movie is not found.\n");
	return NULL;
}

// Function		: deleteNode()
// Description	: A function for node location search
// Parameters	: MovieInfo *node		: The node you want to delete
//				: MovieInfo **head		: Head node of node to delete
//				: MovieInfo **tail		: Tail node of node to delete
// Return Values: int				    : Check the program's normal operation
int deleteNode(MovieInfo* node, MovieInfo** head, MovieInfo** tail)
{
	MovieInfo* currNode = NULL;
	MovieInfo* nextNode = NULL;
	MovieInfo* deleteNode = NULL;
	MovieInfo* secondNode = NULL;
	MovieInfo* lastNode = NULL;
	MovieInfo* precedingNode = NULL;
	MovieInfo* followingNode = NULL;

	currNode = *head;
	deleteNode = node;

	// Search for the node you want to delete
	while (currNode != NULL)
	{
		if (strcmp(deleteNode->pGenre, currNode->pGenre) == 0 && strcmp(deleteNode->pTitle, currNode->pTitle) == 0)
		{
			// Condition when there is only one node
			if ((currNode == *head) && (currNode == *tail))
			{
				*head = NULL;
				*tail = NULL;
				free(currNode);
				return 1;
			}
			// If the node you want to delete is the first one
			if (currNode == *head)
			{
				secondNode = currNode->next;
				*head = currNode->next;
				secondNode->prev = NULL;
			}
			else
			{
				// If the node you want to delete is the last one
				if (currNode == *tail)
				{
					lastNode = currNode->prev;
					*tail = currNode->prev;
					lastNode->next = NULL;
				}
				else
				{
					// Reconnect except for nodes to delete
					precedingNode = currNode->prev;
					followingNode = currNode->next;

					followingNode->prev = precedingNode;
					precedingNode->next = followingNode;
				}
			}
			// free the desired node
			free(currNode);
			return 1;
		}
		currNode = currNode->next;
	}
	return 0;
}

// Function		: AddMovieNode()
// Description	: A function that receives values from nodes and rearranges them
// Parameters	: MovieInfo **head		: Deliver the node of the structure (sorting rate)
//				  MovieInfo **tail		: Deliver the tail node of the structure (sorting rate)
//				  MovieInfo **sortHead  : Deliver the node of the structure (sorting genre)
//				  MovieInfo **sortTail  : Deliver the tail node of the structure (soring genre)
//				  char *newGenre		: The input value of the user to be rearranged
//				  char *newTitle		: The input value of the user to be rearranged.
// Return Values: MovieInfo			    : Corrected node delivery
MovieInfo* AddMovieNode(MovieInfo** head, MovieInfo** tail, MovieInfo** sortHead, MovieInfo** sortTail, char *newGenre, char *newTitle)
{
	MovieInfo* newNode = NULL;
	MovieInfo* sortNewNode = NULL;
	MovieInfo* nextNode = NULL;
	MovieInfo* prevNode = NULL;
	MovieInfo* sortNextNode = NULL;
	MovieInfo* sortPrevNode = NULL;
	
	// Dynamic assignment to pointer
	newNode = (MovieInfo*)malloc(sizeof(MovieInfo));
	if (newNode == NULL)
	{
		printf("Error! No more memory!\n");
		return *head;
	}
	sortNewNode = (MovieInfo*)malloc(sizeof(MovieInfo));
	if (sortNewNode == NULL)
	{
		printf("Error! No more memory!\n");
		return *sortHead;
	}
	// Dynamic assignment to user input
	newNode->pGenre = (char*)malloc(sizeof newGenre);
	if (newNode->pGenre == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}
	strcpy(newNode->pGenre, newGenre);

	newNode->pTitle = (char*)malloc(sizeof newTitle);
	if (newNode->pTitle == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}
	strcpy(newNode->pTitle, newTitle);

	sortNewNode->pGenre = (char*)malloc(sizeof newGenre);
	if (sortNewNode->pGenre == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}
	strcpy(sortNewNode->pGenre, newGenre);

	sortNewNode->pTitle = (char*)malloc(sizeof newTitle);
	if (sortNewNode->pTitle == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}
	strcpy(sortNewNode->pTitle, newTitle);

	// rate to be updated
	printf("Enter update rating of 1-5: ");
	newNode->rate = getNum();
	sortNewNode->rate = newNode->rate;
	newNode->next, newNode->prev, sortNewNode->next, sortNewNode->next = NULL;

	// Create a head node
	if (*head == NULL)
	{
		*head = newNode;
		*tail = newNode;
		*sortHead = *sortTail = sortNewNode;
	}
	else
	{
		/* Sorting conditions according to rate */
		// Inserting at the front of the list
		if ((*head)->rate > newNode->rate)
		{
			newNode->next = *head;
			(*head)->prev = newNode;
			*head = newNode;
		}
		else
		{
			prevNode = *head;
			nextNode = (*head)->next;
			// Explore nodes that fit the sorting position
			while (nextNode != NULL)
			{
				if (nextNode->rate > newNode->rate)
				{
					break;
				}
				prevNode = nextNode;
				nextNode = nextNode->next;
			}
			// Add a new node
			newNode->prev = prevNode;
			newNode->next = nextNode;
			prevNode->next = newNode;
			// Tail node check
			if (nextNode == NULL)
			{
				*tail = newNode;
			}
			else
			{
				nextNode->prev = newNode;
			}
		}
		/* Sorting conditions according to genre */
		// Inserting at the front of the list
		if (strcmp((*sortHead)->pGenre, sortNewNode->pGenre) >= 0)
		{
			sortNewNode->next = *sortHead;
			(*sortHead)->prev = sortNewNode;
			*sortHead = sortNewNode;
		}
		else
		{
			sortPrevNode = *sortHead;
			sortNextNode = (*sortHead)->next;
			// Explore nodes that fit the sorting position
			while (sortNextNode != NULL)
			{
				if (strcmp(sortNextNode->pGenre, sortNewNode->pGenre) >= 0)
				{					
					break;
				}			
				sortPrevNode = sortNextNode;
				sortNextNode = sortNextNode->next;
			}
			// Add a new node			
			sortNewNode->prev = sortPrevNode;
			sortNewNode->next = sortNextNode;
			sortPrevNode->next = sortNewNode;
			// Tail node check
			if (sortNextNode == NULL)
			{
				*sortTail = sortNewNode;
			}
			else
			{
				sortNextNode->prev = sortNewNode;
			}
		}
	}

	return *head;
}


// Function		: printMovieInfo()
// Description	: Output information stored in the node
// Parameters	: MovieInfo *head	  : A set of nodes sorted by rate
//				  MovieInfo *sortGenre: A set of nodes sorted by genre
// Return Values: None
void printMovieInfo(MovieInfo* head, MovieInfo* sortGenre)
{
	MovieInfo* node = NULL;
	MovieInfo* curNode = NULL;
	MovieInfo* sortNode = NULL;
	MovieInfo* sortCurNode = NULL;

	node = head;
	sortNode = sortGenre;
	// Node output sorted by rate
	printf("\nSorted by Rating:\n");
	while (node != NULL)
	{
		curNode = node;
		printf("%-35s", node->pGenre);
		printf("%-35s", node->pTitle);
		printf("%-35d\n", node->rate);
		node = node->next;
	}
	// Node output sorted by genre
	printf("\nSorted by Genre:\n");
	while (sortNode != NULL)
	{
		sortCurNode = sortNode;
		printf("%-35s", sortNode->pGenre);
		printf("%-35s", sortNode->pTitle);
		printf("%-35d\n", sortNode->rate);
		sortNode = sortNode->next;
	}
}

// Function		: updatePrintMovieInfo()
// Description	: Output information stored in the node and release the dynamic memory
// Parameters	: MovieInfo *head	  : A set of nodes sorted by rate
//				  MovieInfo *sortGenre: A set of nodes sorted by genre
// Return Values: None
void updatePrintMovieInfo(MovieInfo* head, MovieInfo* sortGenre)
{
	MovieInfo* node = NULL;
	MovieInfo* curNode = NULL;
	MovieInfo* sortNode, * sortCurNode = NULL;

	node = head;
	sortNode = sortGenre;
	// Node output sorted by rate
	printf("\nSorted by Rating:\n");
	while (node != NULL)
	{
		curNode = node;
		printf("%-35s", node->pGenre);
		printf("%-35s", node->pTitle);
		printf("%-35d\n", node->rate);
		node = node->next;
		// Release the memory
		free(curNode);
	}
	// Node output sorted by genre
	printf("\nSorted by Genre:\n");
	while (sortNode != NULL)
	{
		sortCurNode = sortNode;
		printf("%-35s", sortNode->pGenre);
		printf("%-35s", sortNode->pTitle);
		printf("%-35d\n", sortNode->rate);
		sortNode = sortNode->next;
		// Release the memory
		free(sortCurNode);
	}
}

// Function		: clearCR()
// Description	: Remove the null value at the end of the string (made in Carlo)
// Parameters	: char *buf: String value
// Return Values: None
void clearCR(char* buf)
{
	char* whereCR = strchr(buf, '\n');
	if (whereCR != NULL)
	{
		*whereCR = '\0';
	}
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
