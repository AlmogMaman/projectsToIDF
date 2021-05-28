/*
All teh things that related to the menu.
Print the menu, and do the menu. 
*/

#ifndef MENUH
#define MENUH
//Headers:
#include "linkedList.h"

//Constants:

//The pre gif menu:
#define NEW_PROJECT_OPTION 1
#define EXISTED_PROJECT_OPTION 2

//The actions menu:
#define FIRST_ACTION 0 //The first action (exit).
#define LAST_ACTION 9 //The last action (the bonus).

//The options constants:
#define EXIT 0
#define ADD_FRAME_NODE 1
#define REMOVE_FRAME_NODE 2
#define CHANGE_FRAME_POSITION 3
#define CHANGE_FRAME_DURATION 4
#define CHANGE_ALL_FRAMES_DURATION 5
#define PRINT_FRAMES_LIST 6
#define PLAY_GIF 7
#define SAVE_GIF 8
#define CREATE_GIF_BY_DIR 9 //The bonus - create a gif by directory.


//Functions:
void printGifPreMenu();
void printGifMenuActions();
void doGifActions(gif* pGif, int option);

#endif
