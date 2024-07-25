#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "data.h"

int initSDL(void);

void freeSDL(void);

Picture loadPic(const char* path);

void setPicDstRect(Picture picture, int x, 
				   int y, int w, int h);

void setPicSrcRect(Picture picture, int x,
				   int y, int w, int h);

int loadPicResources(void);

void freePicResources(void);

void paintPic(Picture* picture);

void paint(void);

void handleEvents(bool* quit);

void initGrid();

void placeBombs(int firstClickX, int firstClickY);

void change(int x, int y);
#endif // !_INTERFACE_H_



