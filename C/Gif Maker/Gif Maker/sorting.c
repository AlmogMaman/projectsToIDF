#include <stdio.h>
#include <string.h>
#include "sorting.h"
#include "linkedList.h"

/*
Sorting a gif.
The method of the sorting is sorting by name.
The key of sorting is: we sort the gif from the lowest name to
the highest name.

Input: pointer to a gif.
Output: none.
*/
void sortGif(gif *pGif)
{
	FrameNode* bigenNode = pGif->firstNode; //The node that we start sorting every single iteration.
	FrameNode* nodeToReplace = NULL;//The node with the lowest name each iteration.
	unsigned int s = 0;
}