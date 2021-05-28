#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "input.h"
#include "Technical constants.h"
#include "linkedList.h"

/*
Checks if a path is a valid picture path according to the ending that supported by the openCv lib.
Input: a path.
Output: the answer of the question.
*/
int isPicturePath(char* path)
{
	FILE* file = fopen(path, "rb");
	int isPicturePath = 0;

	if (file) //If the path is existed.
	{
		
		//Checks of the file is a supported picture. (supported for the openCv lib).
		if (strstr(path, PICTURE_ENDING1)  || strstr(path, PICTURE_ENDING2)  ||
			strstr(path, PICTURE_ENDING3)  || strstr(path, PICTURE_ENDING4)  ||
			strstr(path, PICTURE_ENDING5)  || strstr(path, PICTURE_ENDING6)  ||
			strstr(path, PICTURE_ENDING7)  || strstr(path, PICTURE_ENDING8)  ||
			strstr(path, PICTURE_ENDING9)  || strstr(path, PICTURE_ENDING10) ||
			strstr(path, PICTURE_ENDING11) || strstr(path, PICTURE_ENDING12) ||
			strstr(path, PICTURE_ENDING13) || strstr(path, PICTURE_ENDING14) ||
			strstr(path, PICTURE_ENDING15) || strstr(path, PICTURE_ENDING16) ||
			strstr(path, PICTURE_ENDING17) || strstr(path, PICTURE_ENDING18) ||
			strstr(path, PICTURE_ENDING19) || strstr(path, PICTURE_ENDING20) ||
			strstr(path, PICTURE_ENDING21) || strstr(path, PICTURE_ENDING22) ||
			strstr(path, PICTURE_ENDING23) || strstr(path, PICTURE_ENDING24) ||
			strstr(path, PICTURE_ENDING25) || strstr(path, PICTURE_ENDING26))
		{
			isPicturePath = 1;
		}
		fclose(file);
	}
	


	return isPicturePath;
	
}
/*
Saves a gif in a file.
Input: pointer to a gif.
Output: none.
*/
void saveGif(gif* pGif)
{
	FILE* file = NULL; //The user's file.
	char* path = NULL; //The user's path.
	FrameNode* curr = pGif->firstNode; //Current frame node.
	char durationAsString[MAX_UNSIGNED_INT_LEN + 1] = { 0 }; //This buffer contains the duration of each frame (not together) as string.

	printf("\nEnter a file's path for save the gif\n");
	path = receiveString(stdin);
	file = fopen(path, "wb");

	if (file) //If the file is not in another process and we have permissions to write to this file.
	{
		//Write the gif maker file's signature to the file.
		fprintf(file, GIF_MAKER_FILE_SIGNATURE);
		if (curr) //If the gif contains at least 1 frame, we will print a newline, else - we won't write a newline.
		{
			fprintf(file, "%c\n", CRTL_AS_ASSCI); //For the format.
		}

		//Saves the gif to the user's file.
		while (curr)
		{
			fprintf(file, curr->frame->name); //Saves the names.
			fprintf(file, "%c\n", CRTL_AS_ASSCI); //For the format.
			fprintf(file, curr->frame->path);//Saves the paths.
			fprintf(file, "%c\n", CRTL_AS_ASSCI); //For the format.
			//Converting the duration to a string and saves the duration as a string:
			sprintf(durationAsString, "%u", curr->frame->duration);//The converting.
			fprintf(file, durationAsString); //Prints the duration as string to the file.
			
			if (curr->next) //If the node is not the last node - print a new line.
			{
				fprintf(file, "%c\n", CRTL_AS_ASSCI); //For the format.
			}

			curr = curr->next;
		}
		printf("\nThe gif has saved successfully\n");
		fclose(file);
	}
	else
	{
		printf("\nCan not save the gif.\n");
		printf("Check if the file in another process, and you have permissions to the file.\n");
	}
	free(path);
}
/*
Loads a gif from a 'Gif maker file' (file with the gif maker signature).
Input: pointer to a gif.
Output: none.
*/
void loadGifProject(gif* pGif)
{
	FILE* file = NULL;
	char* path = NULL;
	char signatureLine[SIGNATURE_LEN] = { 0 }; //The signature' line of the gif maker file.

	printf("\nEnter full path for loading\n");
	path = receiveString(stdin);
	file = fopen(path, "rb"); //Open the file to reading.

	if (file) //If the file has opened successfully.
	{
		myFgets(signatureLine, SIGNATURE_LEN, file); //Reads the first file's line.
		if (strcmp(signatureLine, GIF_MAKER_FILE_SIGNATURE) == 0)//If the first line of the file is the gif maker file's signature, so the file is a gif maker file.
		{
			//Moves the cursor two steps, for do not relate to the ' \n' and '\r' chars at the end of the signature when we are loading the file.
			//If do not have thees chars at the end, the cursor will be in the end of file, thats mean that to the file has saeved an empty gif project.
			fgetc(file);
			fgetc(file);

			//Doing the main loading.
			mainGifProjectLoading(file, pGif);
			printf("\nThe file has loaded successfuly\n");
		}
		else
		{
			printf("\nThe file is not suitable...\n");
			printf("Creating new project...\n");
		}
		fclose(file);
	}
	else
	{
		printf("\nCan not open the file...\n");
		printf("Creating new project\n");
	}

	free(path);
}
/*
Doing the main of the loading.
Input: gif maker's file, pointer to a gif.
Output: none.
*/
void mainGifProjectLoading(FILE* file, gif* pGif)
{
	char durationAsString[MAX_UNSIGNED_INT_LEN + THREE] = { 0 }; //The duration of each fram as string.Plus three for '\r', '\n' at the end of each line, and for the null at the end of each string.
	FrameNode* newNode = NULL;

	while (feof(file) == 0)//If the file's end does not have reched.
	{
		//Creates a new frame node.
		newNode = createFrameNode();
		newNode->next = NULL; //For default next.

		newNode->frame->name = receiveString(file); //Reads the frame's name for each frame.
		newNode->frame->name[strlen(newNode->frame->name) - 1] = 0; //Removes the crtl from the name - the end of the name.


		newNode->frame->path = receiveString(file); //Reads the frame's path for each frame.
		newNode->frame->path[strlen(newNode->frame->path) - 1] = 0; //Removes the crtl from the path - the end of the path.

		myFgets(durationAsString, MAX_UNSIGNED_INT_LEN + THREE, file); //Reads the duration as string.
		durationAsString[strcspn(durationAsString, "\r")] = 0; //Removes the crtl from the durations string - the end of the duration string.
		newNode->frame->duration = (unsigned int)atoll(durationAsString);

		mainAddFrameNodeToGif(pGif, newNode);
	}
}