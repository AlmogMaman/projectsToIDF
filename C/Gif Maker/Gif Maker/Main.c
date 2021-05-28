/*
Gif makar.
Copyrights - Almog Maman.

Final project - Gif maker.
Almog Maman - class 10th 6 (yud 6).
*/

//Headers:

//Build in headers:
#include <stdio.h>

//My headers:
#include "linkedList.h"
#include "input.h"
#include "menu.h"
#include "files.h"

int main(void)
{
	gif gif = {NULL, NULL, 0};
	unsigned int preOption = 0;
	unsigned int actionOption = 0;

	printf("Copyrights - Almog Maman\n\n");

	printGifPreMenu(); //The menu that ask the user if load an existed project or create a new one.
	safeUnsignedIntScan(&preOption, NEW_PROJECT_OPTION, EXISTED_PROJECT_OPTION);
	
	if (EXISTED_PROJECT_OPTION == preOption)
	{
		loadGifProject(&gif); //PART 2.
	}
	
	do
	{
		printGifMenuActions();
		safeUnsignedIntScan(&actionOption, FIRST_ACTION, LAST_ACTION);

		doGifActions(&gif, actionOption);
	} 
	while (actionOption != EXIT);

	getchar();
	return 0;
}