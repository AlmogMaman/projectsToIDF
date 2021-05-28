#include <stdio.h>
#include "menu.h"
#include "linkedList.h"
#include "view.h"
#include "files.h"
#include "directories.h"

/*
Prints the gif's pre menu.
The menu that ask the user if load an existed project or create a new one.

Input: none.
Output: none.
*/
void printGifPreMenu()
{
	printf("Welcome to Almog's Movie Maker! what would you like to do?\n");
	printf("1 - Create a new project\n");
	printf("2 - Load existing project\n");
}
/*
Prints the gif menu's actions.
Input: none.
Output: none.
*/
void printGifMenuActions()
{
	printf("\n0 - Exit\n");
	printf("1 - Add new Frame\n");
	printf("2 - Remove a Frame\n");
	printf("3 - Change frame index\n");
	printf("4 - Change frame duration\n");
	printf("5 - Change duration of all frames\n");
	printf("6 - List frames\n");
	printf("7 - Play movie!\n");
	printf("8 - Save project\n");
	printf("9 - Create a gif by a directory\n");
}
/*
Comply the actions menu.
Input: pointer to a gif, action's option from the user.
Output: none.
*/
void doGifActions(gif* pGif, int option)
{
	switch (option)
	{
		case EXIT:
			printf("\nGoodbye, I hope you enjoied (:\n");
			freeGif(pGif);
			resetGif(pGif);
			break;
		case ADD_FRAME_NODE:
			addFrameNodeToGif(pGif);
			break;
		case REMOVE_FRAME_NODE:
			removalFrameNodeFromGif(pGif);
			break;
		case CHANGE_FRAME_POSITION:
			changeFramePosition(pGif);
			break;
		case CHANGE_FRAME_DURATION:
			changeFrameDuration(pGif);
			break;
		case CHANGE_ALL_FRAMES_DURATION:
			changeAllFramesDuration(pGif);
			break;
		case PRINT_FRAMES_LIST:
			printFramesList(pGif);
			break;
		case PLAY_GIF:
			play(pGif->firstNode);
			break;
		case SAVE_GIF:
			saveGif(pGif);
			break;
		case CREATE_GIF_BY_DIR:
			createGifByDir(pGif);
			break;
		default:
			printf("\nI have a bag\n");
			break;
	}
}