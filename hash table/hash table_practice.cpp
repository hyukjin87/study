/*
* DESCRIPTION		:
* 	A program that reads data files and searches for values entered by users
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define kHashSize 127
#define kNameSize 30

// Data Type
struct LinkedList {
	char* pName = NULL;
	struct LinkedList* next;
};

// Prototypes
LinkedList* createNode(char* input);
LinkedList* nodeFunction(char* input, LinkedList** node);
unsigned long djb2(char* str);
void clearCR(char* buf);
LinkedList* searchLinkedList(char* searchName, LinkedList* linkedList, int* comparisonCount);
void searchForNameTwice(char* searchName, LinkedList* linkedList, LinkedList* hashTable[], int comparisonCount[2]);
void freeAll(LinkedList* linkedList, LinkedList* hashTable[]);


int main(void)
{
	char nameList[kNameSize] = { 0 };
	LinkedList* sortedLinkedList = NULL;
	LinkedList* hashTable[kHashSize] = { 0 };
	FILE* fpName = NULL;
	char userInput[kNameSize] = { 0 };
	int hashIndex = 0;
	int comparisonCount[2] = { 0 };
	int searchCount = 0;
	int totalComparisonCount = 0;
	int totalComparisonHashCount = 0;
	
	// Open names.txt for reading
	fpName = fopen("names.txt", "r");

	// Error check: Check for error upon opening
	if (fpName == NULL)
	{
		printf("Error: File not openable\n");		
		return -1;
	}

	// Get each of the lines from the file
	while (!feof(fpName))
	{
		if (fgets(nameList, sizeof nameList, fpName) > 0)
		{
			// If there's an empty line, skip it
			if (strcmp(nameList, "\n") == 0)
			{
				continue;
			}
			// Create long aligned nodes and hashtable nodes
			else
			{
				clearCR(nameList);
				nodeFunction(nameList, &sortedLinkedList);
				hashIndex = djb2(nameList);
				nodeFunction(nameList, &hashTable[hashIndex]);
			}
		}
	}
	// Error check: Close the file we are reading from 
	if (fclose(fpName) != 0)
	{
		printf("Error: File not closeable\n");
		return -1;
	}

	printf("Search for name.  Input '.' to exit the loop.\n");

	while (1)
	{
		// User received a value to search for
		fgets(userInput, kNameSize, stdin);
		clearCR(userInput);
		// Conditions for ending the loop
		if (strcmp(userInput, ".") == 0)
		{
			break;
		}
		else
		{
			searchForNameTwice(userInput, sortedLinkedList, hashTable, comparisonCount);
			searchCount++;										// The number of searches
			totalComparisonCount += comparisonCount[0];			// The number of long sorting nodes compared
			totalComparisonHashCount += comparisonCount[1];		// The number of hash tables compared to each other
		}
	}

	printf("\tTotal Number of Searches: %d\n", searchCount);
	printf("\tTotal Number of Comparisons in Linked List: %d\n", totalComparisonCount);
	printf("\tTotal Number of Comparisons in Hash Table: %d\n", totalComparisonHashCount);	
	
	// Release the memory
	freeAll(sortedLinkedList, hashTable);

	return 0;
}

// Function		: nodeFunction()
// Description	: Sort node generation function according to input value
// Parameters	: char *input			: The value entered by the user
//				  LinkedList **node		: Node values to be stored in the linked lists
// Return Values: LinkedList newNode	: Corrected node delivery
LinkedList* nodeFunction(char* input, LinkedList** node)
{
	LinkedList* newNode = NULL;
	LinkedList* nextNode = NULL;
	LinkedList* prevNode = NULL;

	// Nodes of data input from users
	newNode = createNode(input);
	
	// Create a head node
	if (*node == NULL)
	{
		*node = newNode;
	}
	else
	{
		// If the node has a value, apply the sorting node
		if (strcmp((*node)->pName, newNode->pName) >= 0)
		{
			newNode->next = *node;
			*node = newNode;
		}
		// If the node has more than one value, apply node sorting
		else
		{
			prevNode = *node;
			nextNode = (*node)->next;

			while (nextNode != NULL)
			{
				if (strcmp(nextNode->pName, newNode->pName) >= 0)
				{
					break;
				}
				prevNode = nextNode;
				nextNode = nextNode->next;
			}
			// Add a new node
			newNode->next = nextNode;
			prevNode->next = newNode;
		}
	}
	return newNode;
}

// Function		: createNode()
// Description	: A function of creating a node with the value input by the user
// Parameters	: char *input			: The value entered by the user
// Return Values: LinkedList newNode    : Corrected node delivery
LinkedList* createNode(char* input)
{
	LinkedList* newNode = NULL;
	
	// Error check: Dynamic assignment to pointer
	newNode = (LinkedList*)malloc(sizeof(LinkedList) * 2);
	if (newNode == NULL)
	{
		printf("Error! No more memory!\n");
		return 0;
	}
	// Error check: Dynamic memory allocation for storing user information
	newNode->pName = (char*)malloc(sizeof(kNameSize) * 2);
	if (newNode->pName == NULL)
	{
		printf("Error! No more memory!\n");
		return 0;
	}
	// Apply the value input from the user to the node
	strcpy(newNode->pName, input);
	newNode->next = NULL;

	return newNode;
}

// Function		: searchLinkedList()
// Description	: A function of comparing and searching the values of the linked lists
// Parameters	: char *searchName			: The value entered by the user
//				: LinkedList *linkedList	: The linked list to search for
//				: int *comparisonCouunt		: The number of comparisons
// Return Values: LinkedList NULL			: Check the function
LinkedList* searchLinkedList(char* searchName, LinkedList* linkedList, int* comparisonCount)
{
	LinkedList* curNode = NULL;
	int count = 1;

	curNode = linkedList;

	// Error check: Check the existence of a node
	if (curNode == NULL)
	{
		printf("Not there!\n");
	}
	else
	{
		// Find the search value of the node
		while (curNode != NULL)
		{
			// found the search value
			if (strcmp(curNode->pName, searchName) == 0)
			{
				printf("\t%s was found in the hash table bucket in %d comparisons.\n", searchName, count);
				break;
			}
			// Search value not found
			else if (strcmp(curNode->pName, searchName) > 0)
			{
				printf("\t%s was NOT found in the linked list in %d comparisons.\n", searchName, count);
				break;
			}
			else if (curNode->next == NULL)
			{
				printf("\t%s was NOT found in the linked list in %d comparisons.\n", searchName, count);
				break;
			}
			else
			{
				count++;
				curNode = curNode->next;
			}			
		}
	}
	// deliver the comparison
	*comparisonCount = count;

	return NULL;
}	

// Function		: searchForNameTwice()
// Description	: A function of comparing and searching the values of the hashtable linked list
// Parameters	: char *searchName			: The value entered by the user
//				: LinkedList *linkedList	: The value of linked list
//				: LinkedList *hashTable[]	: The value of hash table linked list
//				: int comparisonCouunt[2]	: The number of comparisons
// Return Values: None
void searchForNameTwice(char* searchName, LinkedList* linkedList, LinkedList* hashTable[], int comparisonCount[2])
{
	LinkedList* curNode = NULL;
	LinkedList* curHashNode[kHashSize] = { 0 };
	int hashIndex = 0;
	int count = 1;
	int count2 = 1;

	curNode = linkedList;
	searchLinkedList(searchName, curNode, &count);		// Search linked list
	
	hashIndex = djb2(searchName);
	curHashNode[hashIndex] = hashTable[hashIndex];		// Search hashtable linked list

	// Error check: Check the existence of a node
	if (curHashNode[hashIndex] == NULL)
	{
		printf("Not there!\n");
	}
	else
	{
		// Find the search value of the hash index node
		while (curHashNode[hashIndex] != NULL)
		{
			// found the search value
			if (strcmp(curHashNode[hashIndex]->pName, searchName) == 0)
			{
				printf("\t%s was found in the hash table bucket in %d comparisons.\n", searchName, count2);
				break;
			}
			// Search value not found
			else if (strcmp(curHashNode[hashIndex]->pName, searchName) > 0)
			{
				printf("\t%s was NOT found in the hash table bucket in %d comparisons.\n", searchName, count2);
				break;
			}
			else if (curHashNode[hashIndex]->next == NULL)
			{
				printf("\t%s was NOT found in the hash table bucket in %d comparisons.\n", searchName, count2);
				break;
			}
			else
			{
				count2++;
				curHashNode[hashIndex] = curHashNode[hashIndex]->next;
			}		
		}
	}
	// deliver the comparison
	comparisonCount[0] = count;
	comparisonCount[1] = count2;	
}

// Function		: freeAll()
// Description	: A function that releases dynamic memory allocated to a node
// Parameters	: LinkedList *linkedList		: Node values stored in the linked list
//				: LinkedList *hashTable[]		: Node values stored in the hash table
// Return Values: None
void freeAll(LinkedList* linkedList, LinkedList* hashTable[])
{
	LinkedList* curNode = NULL;
	LinkedList* nextNode = NULL;
	LinkedList* curHashNode[kHashSize] = { 0 };
	LinkedList* nextHashNode[kHashSize] = { 0 };
	int i = 0;	
	
	// Release the memory of linked list
	nextNode = linkedList;
	while (nextNode != NULL)
	{
		curNode = nextNode;
		nextNode = nextNode->next;
		free(curNode);
	}
	
	// Release the memory of hash table
	for (i; i < kHashSize; i++)
	{
		nextHashNode[i] = hashTable[i];
		while (nextHashNode[i] != NULL)
		{
			curHashNode[i] = nextHashNode[i];
			nextHashNode[i] = nextHashNode[i]->next;
			free(curHashNode[i]);
		}
	}
}

// Function		: djb2()
// Author		: Dan Bernstein
// Description	: String Hash Function
// Availability : DS_HashTables.pdf p95 (from week5 data structure lecture)
// Parameters	: char *str				: The value entered by the user
// Return Values: int hash			    : Hash index return
unsigned long djb2(char* str)
{
	unsigned long hash = 5381;
	int c = 0;

	while ((c = *str++) != '\0')
	{
		hash = ((hash << 5) + hash) + c;
	}
	// Delivery of hash values that fit the table size
	return hash % kHashSize;
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