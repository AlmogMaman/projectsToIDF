#ifndef INPUTH
#define INPUTH

//Headers:
#include "linkedList.h"

//Constants:
#define STR_LEN 301
#define NEW_LINE_AS_STRING "\n"
#define NEW_LINE_AS_CHAR '\n'

//Functions:
void reclaimName(gif* pGif, FrameNode* newNode);
char* receiveString(FILE* stream);
void myFgets(char* str, int maxLen, FILE* stream);
int isUniqueName(gif* pGif, char* newName);
void safeUnsignedIntScan(unsigned int* pNumber, const unsigned int MIN_VALUE, const unsigned int MAX_VALUE);
void cleanBuffer();


#endif
