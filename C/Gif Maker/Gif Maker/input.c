#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
/*
Reclaims a frame's name.
Inptu: pointer to a gif, new frame node.
Output: none.
*/
void reclaimName(gif* pGif, FrameNode* newNode)
{
	int unique = FALSE; //Is unique name.
	int counter = 0; //Counts the number of the creating new frame's name.
	char* newName = NULL;

	//'Do-While loop' that rensponses on the unique of each frame's name.
	do
	{
		if (counter > 0)//If the names has not unique at least one time.
		{
			printf("\nYou have to enter an unique name for each frame, type new name\n");
			free(newName);
			newNode->frame->name = receiveString(stdin); //Receive a safe string as dynamic memory.
		}
		newName = newNode->frame->name;
		unique = isUniqueName(pGif, newName); //Checks if the frame has an unique name
		counter++;
	} while (!unique);
}
/*
Get a string from the user in a safety and memory efficient way.
Input: stream to input from.
Output: pointer to a dynamic string.
*/
char* receiveString(FILE* stream)
{
	int stringLen = 0;
	char* efficientStr = NULL;
	char str[STR_LEN] = { 0 }; //Default str.
	myFgets(str, STR_LEN, stream);
	stringLen = strlen(str) + 1;//Include the NULL at the end.
	efficientStr = (char*)malloc(sizeof(char) * stringLen);
	strcpy(efficientStr, str); //Doing copy for all the content, include the NULL at the end.

	return efficientStr;
}
/*
Fix of fgets function.
Input: a string, max len to input, stream to input from.
Output: none.
*/
void myFgets(char* str, int maxLen, FILE* stream)
{
	fgets(str, maxLen, stream);
	str[strcspn(str, NEW_LINE_AS_STRING)] = 0;
}
/*
Checks if a frame's name is unique or not.
Input: pointer to a gif, frame name.
Output: answer of the question - is the names is unique or not?.
*/
int isUniqueName(gif* pGif, char* newName)
{
	FrameNode* curr = pGif->firstNode;
	int isUniqueName = TRUE;
	char* currName = NULL;

	while (curr && isUniqueName)
	{
		currName = curr->frame->name;
		if (strcmp(currName, newName) == 0)//If the new name in the gif already.
		{
			isUniqueName = FALSE;
		}
		curr = curr->next;//Paas to the next node.
	}

	return isUniqueName;
}
/*
Scan an unsigned integer in a safe way - refers to a char additionally to a number.
Makes sure that the number that scaned is in the required range.

Input: pointer to an unsigned int, min value to scan, max value to scan.
The range includes the limits.

Output: none.
*/
void safeUnsignedIntScan(unsigned int* pNumber, const unsigned int MIN_VALUE, const unsigned int MAX_VALUE)
{
	int didSucceed = 1; //Did the scan succeed - a number was scan, not a char.
	int isInRange = 1; //Is the number in the values range.

	do
	{
		!didSucceed ? printf("\nInvalid input, try again...\n") : printf(""); //When the number is invalid - a char was scan.
		!isInRange && didSucceed ? printf("\nThe number is not in the values' range...\nTry Again.\n") : printf(""); //When the number an int and the number is not in the range.

		didSucceed = scanf("%u", pNumber);

		//Cleans the buffer - even if the buffer contains more than one char.
		cleanBuffer();
		
		isInRange = (*pNumber >= MIN_VALUE && *pNumber <= MAX_VALUE);
		
	} 
	while (!didSucceed || !isInRange);
}
/*
Cleans the buffer.
Input: none.
Output: none.
*/
void cleanBuffer()
{
	char ch = '0';
	while (ch != NEW_LINE_AS_CHAR)
	{
		ch = (char)getchar();
	}
}