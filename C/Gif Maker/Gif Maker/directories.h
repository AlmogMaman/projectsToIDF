#ifndef DIRECTORIES_H
#define DIRECTORIES_H
#include "linkedList.h"
#include "dirent.h"



void createGifByDir(gif* pGif);
void mainAddFramesNodesByDir(DIR* dir, char* dirPath, gif* pGif, unsigned int framesDuration);

#endif
