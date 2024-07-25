#ifndef _DATA_H_
#define _DATA_H_

//�����л��õ����ⲿͷ�ļ�
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include"SDL.h"
#include"SDL_image.h"



//���ڴ�С
#define WINDOW_WIDTH 361
#define WINDOW_HEIGHT 380

//ͼƬ����·��
//����ͼƬ1
#define PATH_BACKGROUND_1 ".\\image\\background.png"
//����ͼƬ2
#define PATH_BACKGROUND_2 ".\\image\\background_2.png"

//��ʼ�������ť
#define PATH_START ".\\image\\start.png"
#define PATH_END ".\\image\\end.png"

//����ͼ��
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

//ը��ͼƬ
#define PATH_BOMB_1 ".\\image\\bomb.png"
#define PATH_BOMB_2 ".\\image\\bomb_2.png"

//���ͼ��
#define PATH_SIGN_TAG ".\\image\\tag.png"
#define PATH_SIGN_UNKNOW ".\\image\\unknow.png"

//����ͼƬ1λ��
#define BACKGROUND_PIC1_W WINDOW_WIDTH 
#define BACKGROUND_PIC1_H WINDOW_HEIGHT
#define BACKGROUND_PIC1_X 0 
#define BACKGROUND_PIC1_Y 0
//����ͼƬ2λ��
#define BACKGROUND_PIC2_W WINDOW_WIDTH 
#define BACKGROUND_PIC2_H WINDOW_HEIGHT
#define BACKGROUND_PIC2_X 0 
#define BACKGROUND_PIC2_Y 0

//��ʼ�������ťλ����Ϣ
#define BOX_W 150			//��ť���
#define BOX_H 40			//��ť�߶�
#define BOX_START_X 100		//��ʼ��ťx����
#define BOX_START_Y 150		//��ʼ��ťy����
#define BOX_END_X 143
#define BOX_END_Y 285

//����ͼ��λ����Ϣ
#define BLANK_W 37			//���ӿ��
#define BLANK_H 37			//���Ӹ߶�
#define BLANK_X 15			//��һ��x����
#define BLANK_Y 45			//��һ��y����

//ʱ����ʾ��λ����Ϣ
#define STIME_X 142			//��һ��x����
#define STIME_Y 16			//��һ��y����

//������Ӻ�ը��
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


//ͼƬ���ͽṹ��
typedef struct picture
{
	SDL_Texture* pPic; //ͼƬ����ָ��
	SDL_Rect srcRect;  //Դ����
	SDL_Rect dstRect;  //Ŀ������
} Picture;



#endif //_DATA_H_
