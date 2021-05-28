#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "integration.h"


/*
integrates strings.
Input: first string, a middle sign between the strings, second string.
Output: pointer to the new string.(dynamic memory)
*/
char* integrateStrings(char* firstString, char* middleSign, char* secondString)
{
	char* finalString = NULL;
	unsigned int firstStringLen = strlen(firstString);//Not include the NULL at the end.
	unsigned int secondStringLen = strlen(secondString);//Not include the NULL at the end.
	unsigned int middleSignLen = strlen(middleSign); //Not include the NULL at the end.
	unsigned int finalStringLen = firstStringLen + secondStringLen + middleSignLen + 1; // Plus one to the null at the end.
	finalString = (char*)malloc(sizeof(char) * finalStringLen);
	strcpy(finalString, firstString);
	strncat(finalString, middleSign, middleSignLen);//Add the middle sign.
	strncat(finalString, secondString, secondStringLen);
	return finalString;
}