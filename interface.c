#include "interface.h"

SDL_Window * g_pWindow = NULL;
SDL_Renderer* g_pRenderer = NULL;

Picture g_picBackGround_1;
Picture g_picBackGround_2;
Picture g_picStartButton;
Picture g_picBlank_0;
Picture g_picBlank_1;
Picture g_picBlank_2;
Picture g_picBlank_3;
Picture g_picBlank_4;
Picture g_picBlank_5;
Picture g_picBlank_6;
Picture g_picBlank_7;
Picture g_picBlank_8;
Picture g_picBlank_9;
Picture g_picBomb;
Picture g_picsign_tag;
Picture g_picsign_unknow;
Picture g_picgamewin;
Picture g_picgameover;



bool gameStarted = false;
bool firstClick = true;
bool place = false;
bool gamewin = false;
bool gameover = false;

//int timerValue = 0; // ��ʱ������


//====================================================
//������int initSDL(void)
//���ã���ʼ��SDL�⼰���ڡ���Ⱦ��
//���أ�0��ʾ��ʼ���ɹ�����0��ʾ��ʼ��ʧ��
//====================================================
int initSDL(void)
{
	//��ʼ��SDL2.0������
	if (0 != SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("SDL2.0��ʼ��ʧ�ܣ�%s\n", SDL_GetError());
		return -1;
	}
	printf("SDL2.0��ʼ���ɹ�!\n");

	//��������
	g_pWindow = SDL_CreateWindow(u8"ɨ��",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);
	if (NULL == g_pWindow)
	{
		printf("���ڴ���ʧ��: %s\n", SDL_GetError());
		return -2;
	}
	else
	{
		printf("���ڴ����ɹ���\n");
	}
	//������Ⱦ��
	g_pRenderer = SDL_CreateRenderer(g_pWindow,
		-1, SDL_RENDERER_ACCELERATED);
	if (NULL == g_pRenderer)
	{
		printf("��Ⱦ������ʧ�ܣ�%s\n", SDL_GetError());
		return -3;
	}
	else
	{
		printf("������Ⱦ���ɹ�!\n");
	}

	return 0;
}

//====================================================
//������void freeSDL(void)
//����:�ͷ�SDL�⼰���ڡ���Ⱦ��
//====================================================
void freeSDL(void)
{
	//�ͷ���Ⱦ��
	SDL_DestroyRenderer(g_pRenderer);
	printf("��Ⱦ���ͷţ�\n");

	//�ͷŴ���
	SDL_DestroyWindow(g_pWindow);
	printf("�����ͷţ�\n");

	//�˳�SDL2.0��
	SDL_Quit();
	printf("SDL�����˳���\n");
}


//====================================================
//������Picture loadPic(const char *path)
//���ã�����һ��ͼƬ
//������path����ͼƬ·��
//���أ�ͼƬ�ṹ��
//====================================================
Picture loadPic(const char* path)
{
	Picture pic;
	//����һ��ͼƬ
	pic.pPic = IMG_LoadTexture(g_pRenderer, path);
	if (NULL == pic.pPic)
	{
		printf("ͼƬ����ʧ�ܣ�%s\n", SDL_GetError());
	}
	else
	{
		printf("ͼƬ���سɹ���%s\n", path);
	}
	return pic;
}
 
//====================================================
//���ƣ�void setPicDstRect(Picture * picture, int x, int y, 	int w, int h) 
//˵��������һ��ͼƬ��Ŀ����ʾ����
//������pictureͼƬ�ṹ��ָ��
//	x, y	Ŀ����������
//	w, h	Ŀ�������С 
//====================================================
void setPicDstRect(Picture *picture, int x, int y, int w, int h) {
	picture->dstRect.x = x; 
	picture->dstRect.y = y;
	picture->dstRect.w = w;
	picture->dstRect.h = h;
}
	
//====================================================
//���ƣ�void setPicSrcRect(Picture *picture, int x, int y,int w, int h)
//˵��������һ��ͼƬ��Դ��ȡ����
//������pictureͼƬ�ṹ��ָ��
//	��, y
//	Ŀ����������
//  w, h
//	Ŀ�������С
//====================================================
void setPicSrcRect(Picture *picture, int x, int y,
			       int w, int h)
{
	picture->srcRect.x = x;
	picture->srcRect.y = y;
	if (picture->pPic == NULL) 
	{
		printf("����δ��ȷ���أ�%s\n", SDL_GetError());
	}

	if (0 == w || 0 == h) {
		if (SDL_QueryTexture(picture->pPic, NULL, NULL, &(picture->srcRect.w), &(picture->srcRect.h)) != 0)
		{
			printf("SDL_QueryTexture Error: %s\n", SDL_GetError());
		}
		else 
		{
			printf("Texture width: %d, height: %d\n", picture->srcRect.w, picture->srcRect.h);
		}
	}
	else
	{
		picture->srcRect.w = w;
		picture->srcRect.h = h;
	}
	if (SDL_QueryTexture(picture->pPic, NULL, NULL, &(picture->srcRect.w), &(picture->srcRect.h)) != 0) 
	{
		printf("SDL_QueryTexture Error: %s\n", SDL_GetError());
	}

}
//====================================================
//���ƣ�int loadPicResources(void) 
// ˵�������س��������ͼƬ��Դ
//���أ�0��ʾ���سɹ�����0��ʾ����ʧ��
//====================================================
int loadPicResources(void)
{
	// ���ر���ͼƬ1

	g_picBackGround_1 = loadPic(PATH_BACKGROUND_1);
	if (g_picBackGround_1.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBackGround_1, 0, 0, 0, 0);
	setPicDstRect(&g_picBackGround_1,
		BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y,
		BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);
	
	//���ر���ͼƬ2
	g_picBackGround_2 = loadPic(PATH_BACKGROUND_2);
	if (g_picBackGround_2.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBackGround_2, 0, 0, 0, 0);
	setPicDstRect(&g_picBackGround_2,
		BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y,
		BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);

	//������Ϸʤ����ʧ��ͼƬ
	g_picgamewin = loadPic(PATH_GAMEWIN);
	if (g_picgamewin.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picgamewin, 0, 0, 0, 0);
	setPicDstRect(&g_picgamewin,
		BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y,
		BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);

	g_picgameover = loadPic(PATH_GAMEOVER);
	if (g_picgameover.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picgameover, 0, 0, 0, 0);
	setPicDstRect(&g_picgameover,
		BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y,
		BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);


	//������Ϸ��ʼ��ťͼƬ 
	g_picStartButton = loadPic(PATH_START);
	if (g_picStartButton.pPic == NULL) {
		return -1;
	}
	setPicSrcRect(&g_picStartButton, 0, 0, 0, 0);
	setPicDstRect(&g_picStartButton, BOX_START_X, BOX_START_Y, BOX_W, BOX_H);

	//���ص��ǰ�ĸ���
	g_picBlank_0 = loadPic(PATH_BLANK_0);
	if (g_picBlank_0.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_0, 0, 0, 0, 0);
	setPicDstRect(&g_picBlank_0, BLANK_X, BLANK_Y, BLANK_W, BLANK_H);

	//���ص����ĸ���
	g_picBlank_9 = loadPic(PATH_BLANK_9);
	if (g_picBlank_9.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_9, 0, 0, 0, 0);

	//������ʾ�׵ĸ���ͼƬ
	g_picBlank_1 = loadPic(PATH_BLANK_1);
	if (g_picBlank_1.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_1, 0, 0, 0, 0);

	g_picBlank_2 = loadPic(PATH_BLANK_2);
	if (g_picBlank_2.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_2, 0, 0, 0, 0);

	g_picBlank_3 = loadPic(PATH_BLANK_3);
	if (g_picBlank_3.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_3, 0, 0, 0, 0);

	g_picBlank_4 = loadPic(PATH_BLANK_4);
	if (g_picBlank_4.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_4, 0, 0, 0, 0);

	g_picBlank_5 = loadPic(PATH_BLANK_5);
	if (g_picBlank_5.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_5, 0, 0, 0, 0);

	g_picBlank_6 = loadPic(PATH_BLANK_6);
	if (g_picBlank_6.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_6, 0, 0, 0, 0);

	g_picBlank_7 = loadPic(PATH_BLANK_7);
	if (g_picBlank_7.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_7, 0, 0, 0, 0);

	g_picBlank_8 = loadPic(PATH_BLANK_8);
	if (g_picBlank_8.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_8, 0, 0, 0, 0);
	
	
	//����ը��ͼƬ
	g_picBomb = loadPic(PATH_BOMB_1);
	if (g_picBomb.pPic ==NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_0, 0, 0, 0, 0);

	//���ر��1
	g_picsign_tag = loadPic(PATH_SIGN_TAG);
	if (g_picsign_tag.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picsign_tag, 0, 0, 0, 0);

	//���ر��2
	g_picsign_unknow = loadPic(PATH_SIGN_UNKNOW);
	if (g_picsign_unknow.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picsign_unknow, 0, 0, 0, 0);

	return 0;
}
//====================================================
//���ƣ�void freePicResources(void) 
// ˵�����ͷų�����ص�ͼƬ��Դ		
//====================================================
void freePicResources(void) 
{
	SDL_DestroyTexture(g_picBackGround_1.pPic);
	SDL_DestroyTexture(g_picBackGround_2.pPic);
	SDL_DestroyTexture(g_picStartButton.pPic);

}

//====================================================
//���ƣ�void paintPic(Picture* picture) 
//˵��������Ⱦ������һ��ͼƬ
//������pictureͼƬ�ṹ��ָ��
//====================================================
void paintPic(Picture* picture)
{
	SDL_RenderCopy(g_pRenderer, picture->pPic,
		&(picture->srcRect), &(picture->dstRect));
}

//====================================================
//���ƣ�void paint(void)
//˵�������ƴ���
//====================================================
void paint() 
{
	SDL_RenderClear(g_pRenderer);
	if (gameStarted){
		paintPic(&g_picBackGround_2);//��Ϸ��ʼ��ı���
		if (!place)
		{
			int n = 37;//���ص��ǰ�ĸ���
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					setPicDstRect(&g_picBlank_0, BLANK_X + BLANK_W * j, 
						BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
					paintPic(&g_picBlank_0);
					
				}
			}
		}
		else
		{
			for (int i = 0; i < GRID_SIZE; i++)
			{
				for (int j = 0; j < GRID_SIZE; j++)
				{
					if (grid[i][j].change==1&& grid[i][j].Mark==0)
					{
						setPicDstRect(&g_picBlank_0, BLANK_X + BLANK_W * j,
							BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
						paintPic(&g_picBlank_0);
						switch (grid[i][j].nbomb)
						{
						case 0:
							setPicDstRect(&g_picBlank_9, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_9);
							break;
						case 1:
							setPicDstRect(&g_picBlank_1, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_1);
							break;
						case 2:
							setPicDstRect(&g_picBlank_2, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_2);
							break;
						case 3:
							setPicDstRect(&g_picBlank_3, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_3);
							break;
						case 4:
							setPicDstRect(&g_picBlank_4, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_4);
							break;
						case 5:
							setPicDstRect(&g_picBlank_5, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_5);
							break;
						case 6:
							setPicDstRect(&g_picBlank_6, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_6);
							break;
						case 7:
							setPicDstRect(&g_picBlank_7, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_7);
							break;
						case 8:
							setPicDstRect(&g_picBlank_8, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
							paintPic(&g_picBlank_8);
							break;
						default:
							break;
						}
					}
					else if (grid[i][j].isBomb && grid[i][j].change == 1&& grid[i][j].Mark == 0)
					{
						setPicDstRect(&g_picBomb, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
						paintPic(&g_picBomb);
					}
					else if (grid[i][j].change==0&& grid[i][j].Mark == 0) {
						setPicDstRect(&g_picBlank_0, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
						paintPic(&g_picBlank_0);
					}
					if (grid[i][j].Mark==1)
					{
						setPicDstRect(&g_picsign_tag, BLANK_X + BLANK_W * j,
							BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
						paintPic(&g_picsign_tag);
					}
					if (grid[i][j].Mark == 2)
					{
						setPicDstRect(&g_picsign_unknow, BLANK_X + BLANK_W * j,
							BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
						paintPic(&g_picsign_unknow);
					}
				}
			}
		}
		
	}
	else {
		paintPic(&g_picBackGround_1);
		paintPic(&g_picStartButton);
	}
	if (gameover)
	{
		paintPic(&g_picgameover);
	}
	if (gamewin)
	{
		paintPic(&g_picgamewin);

	}


	SDL_RenderPresent(g_pRenderer);

}

//���ӱ������ı仯
void change(int x, int y)
{

	int i = (y - BLANK_Y) / BLANK_H;
	int j = (x - BLANK_X) / BLANK_W;
	printf("%d,%d,%d???\n" ,i+1, j+1, grid[i][j].nbomb);
	if (i>=0&&i<=8&& j >= 0 && j <= 8)
	{
		if (((grid[i][j].isRevealed == false) && (grid[i][j].change == 0)) 
			&& (grid[i][j].isBomb == false))
		{
			grid[i][j].change = 1;
			grid[i][j].isRevealed = true;
			// ������Χը����������ʾ��Ӧ��ͼƬ
			switch (grid[i][j].nbomb)
			{
			case 0:
				printf("     %d, %d???\n", i , j );
				setPicDstRect(&g_picBlank_9, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_9);
				/*change(x + 37, y);
				change(x, y + 37);
				change(x-37, y);
				change(x , y-37);*/
				change(x + 37, y);
				change(x + 37, y + 37);
				change(x, y + 37);
				change(x - 37, y + 37);
				change(x - 37, y);
				change(x - 37, y - 37);
				change(x, y - 37);
				change(x + 37, y - 37);
				break;
			case 1:
				SDL_RenderClear(g_pRenderer);
				setPicDstRect(&g_picBlank_1, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_1);
				break;
			case 2:
				setPicDstRect(&g_picBlank_2, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_2);
				break;
			case 3:
				setPicDstRect(&g_picBlank_3, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_3);
				break;
			case 4:
				setPicDstRect(&g_picBlank_4, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_4);
				break;
			case 5:
				setPicDstRect(&g_picBlank_5, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_5);
				break;
			case 6:
				setPicDstRect(&g_picBlank_5, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_6);
				break;
			case 7:
				setPicDstRect(&g_picBlank_7, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_7);
				break;
			case 8:
				setPicDstRect(&g_picBlank_8, BLANK_X + BLANK_W * j, 
					BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
				paintPic(&g_picBlank_8);
				break;
			default:
				break;
				
			}
			
		}
		else if (((grid[i][j].isRevealed == false) && (grid[i][j].change == 0)) && grid[i][j].isBomb == true)
		{
			grid[i][j].change = 1;
			grid[i][j].isRevealed = true;
			setPicDstRect(&g_picBlank_0, BLANK_X + BLANK_W * j, BLANK_Y + BLANK_H * i, BLANK_W, BLANK_H);
			paintPic(&g_picBomb);
		
		}
	}
	paint();
	
}



//��Ϸ��ʼ��ť���
void handleEvents(bool* quit)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			*quit = true;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (!gameStarted && x >= BOX_START_X && x <= BOX_START_X + BOX_W &&
				y >= BOX_START_Y && y <= BOX_START_Y + BOX_H)
			{
				gameStarted = true;
				paint();
			}
			else if (gameStarted)
			{
				int gridX = (x - BLANK_X) / BLANK_W;
				int gridY = (y - BLANK_Y) / BLANK_H;
				if (gridX >= 0 && gridX < GRID_SIZE && gridY >= 0 && gridY < GRID_SIZE)
				{
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						if (firstClick)
						{
							initGrid();
							placeBombs(gridX, gridY);
							place = true;
							firstClick = false;
						}
						if (!grid[gridY][gridX].isRevealed && grid[gridY][gridX].Mark == 0)
						{
							if (grid[gridY][gridX].isBomb)
							{
								printf("��Ϸ������������һ���ף�\n");
								gameover = true;
								gameStarted = false;
								// ��ʾ����ը��
								for (int i = 0; i < GRID_SIZE; i++) {
									for (int j = 0; j < GRID_SIZE; j++) {
										if (grid[i][j].isBomb) {
											grid[i][j].change = 1;
										}
									}
								}
								paint();
							}
							else {
								change(x, y);
								if (checkWin())
								{
									printf("��Ӯ�ˣ������׶�������ˣ�\n");
									gameStarted = false;
									paint();
								}
							}
						}
					}
					else if (e.button.button == SDL_BUTTON_RIGHT)
					{
						Mmark(x, y);
						if (checkWin())
						{
							
							printf("��Ӯ�ˣ������׶�������ˣ�\n");
							gamewin = true;

							gameStarted = false;
							paint();
						}
					}
				}
			}
		}
	}
}


//�Ҽ����
void Mmark(int x, int y)
{
	int i = (y - BLANK_Y) / BLANK_H;
	int j = (x - BLANK_X) / BLANK_W;
	if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE) {
		if (!grid[i][j].isRevealed && grid[i][j].change == 0) {
			grid[i][j].Mark = (grid[i][j].Mark + 1) % 3;
			paint();
		}
	}
}

//���ʤ������
bool checkWin() 
{
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (grid[i][j].isBomb && grid[i][j].Mark != 1) {
				return false;
			}
		}
	}
	return true;
}


//��ʼ������
void initGrid() 
{
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			grid[i][j].isBomb = false;
			grid[i][j].isRevealed = false;
			grid[i][j].Mark = 0;
			grid[i][j].change = 0;
		}
	}
}

//����ը��,��ը�����
void placeBombs(int firstClickX, int firstClickY) {
	int bombsPlaced = 0;
	while (bombsPlaced < NUM_BOMBS) {
		int x = rand() % GRID_SIZE;
		int y = rand() % GRID_SIZE;
		printf("%d,%d*********\n", x, y);
		if ((x != firstClickX || y != firstClickY) && !grid[y][x].isBomb) {
			grid[y][x].isBomb = true;
			bombsPlaced++;
		}
	}

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (!grid[i][j].isBomb) {
				grid[i][j].nbomb = 0;
				for (int dx = -1; dx <= 1; dx++) {
					for (int dy = -1; dy <= 1; dy++) {
						int ni = i + dy;
						int nj = j + dx;
						if (ni >= 0 && ni < GRID_SIZE && nj >= 0 && nj < GRID_SIZE && grid[ni][nj].isBomb)
						{
							grid[i][j].nbomb++;
						}
					}
				}
			}
			else {
				grid[i][j].nbomb = 9; // ���ڱ�ʾը��
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", grid[i][j].nbomb);
			if (j==8)
			{
				printf("\n");
			}
		}
	}

}
