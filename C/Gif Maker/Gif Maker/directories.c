#include <stdio.h>

#include "directories.h"
#include "dirent.h"
#include "input.h"
#include "files.h"
#include "integration.h"
#include "Technical constants.h"
#include "linkedList.h"
#include "sorting.h"

/*
Creates a gif by a directory.
If have some frames in the gif already, they will be deleted.

Input: pointer to a gif.
Output: none.
*/
void createGifByDir(gif* pGif)
{
	char* dirPath = NULL; //The dir's path.
	DIR* dir = NULL;
	unsigned int framesDurations = 0;

	printf("\nEnter a pictures' directory\n");
	dirPath = receiveString(stdin);
	dir = opendir(dirPath);

	if (dir) //If the dir's path is a real dir's path, if the dir has opened.
	{
		freeGif(pGif); //Free the frames that were in the gif untill now (if were frames).
		resetGif(pGif); //reset the gif to be new gif.

		//Gets a duration for each frame together.
		printf("\nEnter the duration for each frame\n");
		safeUnsignedIntScan(&framesDurations, 1, MAX_UNSIGNED_INT_VALUE);

		mainAddFramesNodesByDir(dir, dirPath, pGif, framesDurations); //The main creation by directory exist here, adds frames nodes by dir.
		//sortGif(pGif);

		printf("\nThe add has successful\n");
		free(dir);
	}
	else
	{
		printf("\nThe directory that you have entered is not valid...\n");
		printf("The gif will be like it was before...\n");
	}

	free(dirPath);

}
/*
Comply the main add frames nodes by a directory.
Input: a dir, dir's path, pointer to a gif, the duration for each frame.
Output: none.
*/
void mainAddFramesNodesByDir(DIR* dir, char* dirPath, gif* pGif, unsigned int framesDurations)
{
	struct dirent* dirent = readdir(dir);
	char* filePath = NULL; //The path for each file in the directory.
	char* fileName = NULL; //The name for each file in the directory.
	FrameNode* newNode = NULL; //New node to add to the gif.

	while (dirent != NULL) //Runs on all the items in the user's dir.
	{
		fileName = dirent->d_name;
		filePath = integrateStrings(dirPath, SLASH_AS_STRING, fileName);

		if (isPicturePath(filePath)) //Checks if each file's path is a picture's path. 
		{
			newNode = createFrameNode();
			newNode->next = NULL; //For default next.
			newNode->frame->name = integrateStrings(fileName, "", ""); //Integrates the file name with nothing for place in the frame's name a dynamic string.
			newNode->frame->path = filePath;
			newNode->frame->duration = framesDurations;

			mainAddFrameNodeToGif(pGif, newNode);
		}
		dirent = readdir(dir);
	}
}
