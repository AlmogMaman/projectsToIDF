/*
Comply some linked list functions.
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "files.h"
#include "input.h" //Function that relates to an input.
#include "Technical constants.h"


/*
Free a gif.
Input: pointer to a gif.
output: none.
*/
void freeGif(gif* pGif)
{
	FrameNode* curr = pGif->firstNode;
	FrameNode* next = NULL;
	while (curr)
	{
		next = curr->next;
		freeFrameNode(curr);
		curr = next;
	}
}
/*
Reset the gif's fields.
Input: pointer to a gif.
Output: none.
*/
void resetGif(gif* pGif)
{
	//Place the gif like a new one.
	pGif->firstNode = NULL;
	pGif->framesNodesSum = 0;
	pGif->lastNode = NULL;
}
/*
Adds a frame node to gif's tail.
Input: pointer to a gif.
Output: none.
*/
void addFrameNodeToGif(gif* pGif)
{
	FrameNode* newNode = createFrameNode();
	char* newPath = NULL;

	newNode->next = NULL; //Default next.
	initFrameNodeByUser(newNode); //Init the node by the user.
	reclaimName(pGif, newNode); //Checks that the name of each frame is a valid, if not - reclaim the name to be a valid name. (in the input.c\h file)
	newPath = newNode->frame->path;

	//Checks that the path is a picture's path, and according to that, add or not add the file to the gif:

	if (isPicturePath(newPath)) //Checks if the path that the user has entered, was a picture's path. (in the files.c\h file)
	{
		//Adds the picture to the gif.
		mainAddFrameNodeToGif(pGif, newNode);
	}
	else //If the path is not a picture's path or not real or with different language than English or not supported by openCv lib.
	{
		printf("\nThe path is not a picture's path\nOr not a real path\nOr has different language than English in the path\nOr the picture is not supported in the openCv lib.\n\nThe file won't be added\n");
		freeFrameNode(newNode);
	}
}
/*
Doing the main of the frame node's adding.
Input: pointer to a gif, new node.
Outptu: none.
*/
void mainAddFrameNodeToGif(gif* pGif, FrameNode* newNode)
{
	if (pGif->firstNode != NULL) //If the frame is not the first frame that added.
	{
		pGif->lastNode->next = newNode;
		pGif->lastNode = newNode;
	}
	else //If the frame is the first frame that added.
	{
		pGif->firstNode = newNode;
		pGif->lastNode = newNode;
	}
	pGif->framesNodesSum++;
}
/*
Creates a frame node.
Input: none.
Output: pointer to a frame node (dynamic memeory).
*/
FrameNode* createFrameNode()
{
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
	newNode->frame = (Frame*)malloc(sizeof(Frame));

	return newNode;
}
/*
Inits a frame node by the user.
Input: pointer to a frame node.
Output: none.
*/
void initFrameNodeByUser(FrameNode* newNode)
{
	unsigned int* pDuration = &newNode->frame->duration;

	printf("\nEnter the frame's name please\n");
	newNode->frame->name = receiveString(stdin);

	printf("\nEnter the frame's path please\n");
	newNode->frame->path = receiveString(stdin);

	printf("\nEnter the frame's duration in 1 - %u range (in milli seconds)\n", MAX_UNSIGNED_INT_VALUE);
	safeUnsignedIntScan(pDuration, 1, MAX_UNSIGNED_INT_VALUE); //Scans the duration in safe way (if the user will enter a char the user will be ask one more time to scan)

}
/*
Removes a frame node from the gif.
Input: pointer to a gif.
Output: none.
*/
void removalFrameNodeFromGif(gif* pGif)
{
	char* frameName = NULL;
	int successfulRemoval = FALSE;

	printf("\nEnter a frame's name to remove\n");
	frameName = receiveString(stdin);

	if (pGif->firstNode != NULL) //If the gif is not empty.
	{
		successfulRemoval = mainRemovalFrameFromGif(pGif, frameName);

		if (successfulRemoval)
		{
			printf("%s removed from the gif\n", frameName);
			pGif->framesNodesSum--;
		}
		else
		{
			printf("%s not in the gif\n", frameName);
		}
	}
	else
	{
		printf("The gif is empty, %s not in the gif\n", frameName);
	}
	free(frameName);
}
/*
The main removal frame from a gif.
Input: pointer to a gif, the name of the frame that we want to remove.
Output: flag for success.
*/
int mainRemovalFrameFromGif(gif* pGif, char* frameName)
{
	FrameNode* temp = NULL;
	FrameNode* curr = pGif->firstNode;
	int successfulRemoval = FALSE;

	//LIMIT SITUATION: IF WE WANT REMOVE THE FIRST ONE.
	if (strcmp(pGif->firstNode->frame->name, frameName) == 0) //The first frame node contains the name.
	{
		temp = pGif->firstNode; //The temp is the node that we want to remove, its the first node.
		pGif->firstNode = temp->next; //pass the first node to the seconde node. 
		if (pGif->framesNodesSum == 1) //If the gif contains just the node that we want to remove.
		{
			pGif->lastNode = pGif->firstNode; //So, first = last = NULL;
		}
		freeFrameNode(temp); //We are deleting the first node. 
		successfulRemoval = 1; //Turn on the flag.
	}
	else //If the first node is not the node that we want to remove.
	{
		while (!successfulRemoval && curr->next) //Runs on the gif apatr from the last node, or until the node that we want to remove find. 
		{
			if (strcmp(curr->next->frame->name, frameName) == 0) //If the name of the next curr is the node.
			{
				temp = curr->next; //The node that we want to remove.
				curr->next = temp->next; //'Tear' the node that we want to remove. 
				freeFrameNode(temp); //Remove the node.
				successfulRemoval = 1; //Turn on the flag.
				if (curr->next == NULL) //After the removing,if the next of the curr is NUUL thats mean that we have removed the last node.So in this case we need to change the last.
				{
					pGif->lastNode = curr;
				}
			}
			curr = curr->next;
		}
	}

	return successfulRemoval;
}
/*
Free a frame node.
Input: pointer to a frame node.
Output: none.
*/
void freeFrameNode(FrameNode* frameNode)
{
	free(frameNode->frame->name);
	free(frameNode->frame->path);
	free(frameNode->frame);
	free(frameNode);
}
/*
Change frame position.
Input: pointer to a gif.
Output: none.
*/
void changeFramePosition(gif* pGif)
{
	char* movedNodeName = NULL;
	unsigned int futureIndex = 0, nodesSum = (unsigned int)pGif->framesNodesSum;
	FrameNode *movedNode = NULL, *preNode = NULL; // The previous node of the node that we want to move. 

	printf("\nEnter a frame's name\n");
	movedNodeName = receiveString(stdin);

	preNode = findPreNodeByName(pGif, movedNodeName); //in this case the pre node is the pre of the node that the user entered its name.
	movedNode = findNodeByPreNode(preNode, movedNodeName);

	if (NULL != preNode) //If the frame name in the gif.
	{
		printf("\nEnter a future index of the frame\n");
		printf("The index could be in the 1 - %d range\n", nodesSum);
		safeUnsignedIntScan(&futureIndex, MIN_FRAME_NODE_INDEX, nodesSum);

		if (!isSuitable(pGif, movedNode, futureIndex)) //Is the moved node is suitable to the futuer index.
		{
			mainChangingFramePosition(pGif, preNode, movedNode, movedNodeName, futureIndex);
			printf("\nThe change has successed\n");
		}
		else
		{
			printf("\nThe future index is the frame's index...\n");
		}
	}
	else
	{
		printf("\nThe frame with this name is not in the gif.\n");
	}
	free(movedNodeName);
}
/*
The main of the changinf frame position.

Input: pointer to a gif, pointer to the previous node that we want to replace, pointer to the node that we want to replace,
the name of the node that we want to replace, the index that we want to move the node to.

Output: none.
*/
void mainChangingFramePosition(gif* pGif, FrameNode* preNode, FrameNode* movedNode, char* movedNodeName, unsigned int futureIndex)
{
	FrameNode *temp = NULL;
	FrameNode* futurePreNode = NULL; //The previous node of the node that we want to 'take' its place (affter the tearing). 

	tearNode(pGif, preNode, movedNodeName); //Tears a node from the gif, tear node is like remove a node, but without the free.
	//Changes the frame posiotion:
	if (futureIndex == (unsigned int)pGif->framesNodesSum) //Moves the frame to the last frame.
	{
		pGif->lastNode->next = movedNode;
		movedNode->next = NULL;
		pGif->lastNode = movedNode;
	}
	else if (futureIndex == MIN_FRAME_NODE_INDEX) //The frame node is gonna be the first node.
	{
		movedNode->next = pGif->firstNode;
		pGif->firstNode = movedNode;
	}
	else //If we want replace a frame to the middle of the gif (all the frames that not the first/last frame)
	{
		//Finding the future previous node by index.
		findPreNodeByIndex(pGif, futureIndex, &futurePreNode);

		//Doing the change position from a position to the middle.
		temp = futurePreNode->next;
		futurePreNode->next = movedNode;
		movedNode->next = temp;
	}
}
/*
Finds a previous node of a node, by an index of a node.

Input: pointer to a gif, index of a node, pointer to pointer to a previous node.
Notes: 1.the index start from 1, not from 0.
2.If the node that we send is the first node, the previous node of this node is itself.

Output: none.
*/
void findPreNodeByIndex(gif* pGif, unsigned int index, FrameNode** pPPreNode)
{
	unsigned int i = 1;
	*pPPreNode = pGif->firstNode;
	
	for (i = 1; i < index - 1; i++)
	{
		*pPPreNode = (*pPPreNode)->next;
	}
}
/*
Finds a previous frame node by name.

Input: pointer to a gif.

Output: pointer of the previous frame node that we are looking for.
If the frame node is not exist, the pointer will be a NULL
If the frame node that we looking for is the first node, the pointer to the first node will
be passed.
*/
FrameNode* findPreNodeByName(gif* pGif, char* frameName)
{
	FrameNode* preNode = NULL;
	int found = FALSE;
	char* nextName = NULL; //The name of the curr frame node.
	FrameNode* curr = pGif->firstNode;

	if (curr) //If the gif is not empty.
	{
		if (strcmp(curr->frame->name, frameName) == 0) //If the node that we looking for is the first node.
		{
			preNode = curr; //The previous is not the rael previous, but the head itself.
		}
		else
		{
			while (!found && curr->next) //Runs untill we find the previous node, or untill we check all of the nodes (we check all the names apart from the head of the gif). 
			{
				nextName = curr->next->frame->name;

				if (strcmp(nextName, frameName) == 0)
				{
					found = TRUE;
					preNode = curr;
				}

				curr = curr->next;
				
			}
		}

	}
	
	return preNode;
}
/*
Tears a node from the gif, tear node is like remove a node, but without the free.
Input: pointer to a gif, pointer to the previous node that we want to tear, the frame's name that we are looking for.
Output: none.
*/
void tearNode(gif* pGif, FrameNode* preNode, char* frameName)
{
	FrameNode* pre = pGif->firstNode; //the previous node of each node that we run on.
	int teared = FALSE; //Flag for - is the node has teared. 

	
	if (preNode) //If the previous node has found.
	{
		if (pGif->firstNode == preNode && strcmp(preNode->frame->name, frameName) == 0) //If the previous node is the first node, it could be two things, or the second item is the required frame node, or the first is the required node. So we need the name of the node to decise.
		{
			pGif->firstNode = pGif->firstNode->next;
		}
		else if (preNode->next == pGif->lastNode) //If the node that we want to tear is the last node.
		{
			pGif->lastNode = preNode;
			preNode->next = NULL;
		}
		else
		{
			while (!teared && pre->next) //Runs on the gif (apart from the last node).
			{
				if (pre == preNode) //If the current previous node is the previous node of the node that we want to tear.
				{
					pre->next = pre->next->next; //Tears the node, the node replace to the next node of the node that we want to tear.
					teared = TRUE;
				}

				pre = pre->next;
			}
		}
	}
}
/*
Finds a node by previous node, and the frame name.
Input: previous node of the moved node, name of the moved node.
Output: the moved node.
*/
FrameNode* findNodeByPreNode(FrameNode* preNode, char* frameName)
{
	FrameNode* movedNode = NULL;
	//Init the moved node - the node that we want to replace.
	if (preNode)
	{
		if (strcmp(frameName, preNode->frame->name) == 0) //If the node that we want to replace is the first node.
		{
			movedNode = preNode;
		}
		else
		{
			movedNode = preNode->next;
		}
	}

	return movedNode;
}
/*
Checks if a node is suitable to an index - the function a subsidiary of the 'changeFramePosition'.
Input: pointer to a gif, frame node, an index.
Output: anwer to the quistion - is the frame node and the index are suitable.
*/
int isSuitable(gif* pGif, FrameNode* frameNode, unsigned int index)
{
	unsigned int isSuitable = FALSE;
	unsigned int found = FALSE; //Flag for finding the node that we are looking for, in the gif.
	FrameNode* curr = pGif->firstNode;
	unsigned int currIndex = 1;

	while (!found && curr)
	{
		if (curr == frameNode) //We find the node that we check the match.
		{
			found = TRUE;
			isSuitable = (currIndex == index);
		}
		currIndex++;
		curr = curr->next;
	}
	return isSuitable;
}
/*
Changes a frame duration.
Input: pointer to a gif.
Output: none.
*/
void changeFrameDuration(gif* pGif)
{
	char* frameName = NULL;
	FrameNode* theNode = NULL;
	FrameNode* preNode = NULL;
	unsigned int* pDuration = NULL;

	printf("\nEnter a frame name\n");
	frameName = receiveString(stdin);

	preNode = findPreNodeByName(pGif, frameName);
	theNode = findNodeByPreNode(preNode, frameName);

	if (theNode) //If the node has found.
	{
		pDuration = &theNode->frame->duration; //For more readability.
		printf("\nEnter new time\n");
		safeUnsignedIntScan(pDuration, 1, MAX_UNSIGNED_INT_VALUE);
		printf("\nThe time has changed successfuly\n");
	}
	else
	{
		printf("\nThe fram has not found...\n");
	}

	free(frameName);
}
/*
Changes the duration of all the frames.
Input: pointer to a gif.
Output: none.
*/
void changeAllFramesDuration(gif* pGif)
{
	unsigned int newDuration = 0;
	FrameNode* curr = pGif->firstNode;
	int counter = 0; //Counts the changes time.

	printf("\nEnter new time for each frame\n");
	safeUnsignedIntScan(&newDuration, 1, MAX_UNSIGNED_INT_VALUE);

	while (curr)
	{
		curr->frame->duration = newDuration;
		counter++;

		curr = curr->next;
	}
	counter ? printf("\nThe changes have succeed\n") : printf("\nThe gif is empty...\n");
}
/*
Prints the gif's frames.
Input: pointer to a gif.
Output: none.
*/
void printFramesList(gif* pGif)
{
	FrameNode* curr = pGif->firstNode;


	if (curr)
	{
		while (curr)
		{
			printf("\n");
			printf("Frame's name: %s\n", curr->frame->name);
			printf("Frame's path: %s\n", curr->frame->path);
			printf("Frame's duration: %u milli seconds\n", curr->frame->duration);

			curr = curr->next;
		}
	}
	else
	{
		printf("\nDoes not have a frame in the gif.\n");
	}
}