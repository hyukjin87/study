/*
* DESCRIPTION		:
* 	Functions and prototypes used for the assign1
*/

// Constant
#define kSuccess 1
#define kFailure -1
#define kSize 80

// Prototypes
void parseUserInput(char* userInput);
int assessGrade(int num[]);
void assessGrade(double num);
void assessGrade(char* str);
void showGrade(double result);
void clearCR(char* buf);