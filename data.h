#ifndef _DATA_H_
#define _DATA_H_

//程序中会用到的外部头文件
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include"SDL.h"
#include"SDL_image.h"



//窗口大小
#define WINDOW_WIDTH 361
#define WINDOW_HEIGHT 380

//图片本地路径
//背景图片1
#define PATH_BACKGROUND_1 ".\\image\\background.png"
//背景图片2
#define PATH_BACKGROUND_2 ".\\image\\background_2.png"

//开始与结束按钮
#define PATH_START ".\\image\\start.png"
#define PATH_END ".\\image\\end.png"

//格子图案
#define PATH_BLANK_0 ".\\image\\blank.png"
#define PATH_BLANK_1 ".\\image\\1.png"
#define PATH_BLANK_2 ".\\image\\2.png"
#define PATH_BLANK_3 ".\\image\\3.png"
#define PATH_BLANK_4 ".\\image\\4.png"
#define PATH_BLANK_5 ".\\image\\5.png"
#define PATH_BLANK_6 ".\\image\\6.png"
#define PATH_BLANK_7 ".\\image\\7.png"
#define PATH_BLANK_8 ".\\image\\8.png"
#define PATH_BLANK_9 ".\\image\\blank_9.png"

//炸弹图片
#define PATH_BOMB_1 ".\\image\\bomb.png"
#define PATH_BOMB_2 ".\\image\\bomb_2.png"

//标记图案
#define PATH_SIGN_TAG ".\\image\\tag.png"
#define PATH_SIGN_UNKNOW ".\\image\\unknow.png"

//背景图片1位置
#define BACKGROUND_PIC1_W WINDOW_WIDTH 
#define BACKGROUND_PIC1_H WINDOW_HEIGHT
#define BACKGROUND_PIC1_X 0 
#define BACKGROUND_PIC1_Y 0
//背景图片2位置
#define BACKGROUND_PIC2_W WINDOW_WIDTH 
#define BACKGROUND_PIC2_H WINDOW_HEIGHT
#define BACKGROUND_PIC2_X 0 
#define BACKGROUND_PIC2_Y 0

//开始与结束按钮位置信息
#define BOX_W 150			//按钮宽度
#define BOX_H 40			//按钮高度
#define BOX_START_X 100		//开始按钮x坐标
#define BOX_START_Y 150		//开始按钮y坐标
#define BOX_END_X 143
#define BOX_END_Y 285

//格子图案位置信息
#define BLANK_W 37			//格子宽度
#define BLANK_H 37			//格子高度
#define BLANK_X 15			//第一格x坐标
#define BLANK_Y 45			//第一格y坐标

//时间显示的位置信息
#define STIME_X 142			//第一格x坐标
#define STIME_Y 16			//第一格y坐标

//定义格子和炸弹
#define GRID_SIZE 9
#define NUM_BOMBS 10

typedef struct {
	bool isBomb ;
	bool isRevealed;
	int nbomb;
	int change;
} Cell;

Cell grid[GRID_SIZE][GRID_SIZE];
extern bool firstClick;


//图片类型结构体
typedef struct picture
{
	SDL_Texture* pPic; //图片纹理指针
	SDL_Rect srcRect;  //源区域
	SDL_Rect dstRect;  //目标区域
} Picture;



#endif //_DATA_H_
