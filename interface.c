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

//int timerValue = 0; // 计时器变量


//====================================================
//函数：int initSDL(void)
//作用：初始化SDL库及窗口、渲染器
//返回：0表示初始化成功，非0表示初始化失败
//====================================================
int initSDL(void)
{
	//初始化SDL2.0开发库
	if (0 != SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("SDL2.0初始化失败：%s\n", SDL_GetError());
		return -1;
	}
	printf("SDL2.0初始化成功!\n");

	//创建窗口
	g_pWindow = SDL_CreateWindow(u8"扫雷",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);
	if (NULL == g_pWindow)
	{
		printf("窗口创建失败: %s\n", SDL_GetError());
		return -2;
	}
	else
	{
		printf("窗口创建成功！\n");
	}
	//创建渲染器
	g_pRenderer = SDL_CreateRenderer(g_pWindow,
		-1, SDL_RENDERER_ACCELERATED);
	if (NULL == g_pRenderer)
	{
		printf("渲染器创建失败：%s\n", SDL_GetError());
		return -3;
	}
	else
	{
		printf("创建渲染器成功!\n");
	}

	return 0;
}

//====================================================
//函数：void freeSDL(void)
//作用:释放SDL库及窗口、渲染器
//====================================================
void freeSDL(void)
{
	//释放渲染器
	SDL_DestroyRenderer(g_pRenderer);
	printf("渲染器释放！\n");

	//释放窗口
	SDL_DestroyWindow(g_pWindow);
	printf("窗口释放！\n");

	//退出SDL2.0库
	SDL_Quit();
	printf("SDL库已退出！\n");
}


//====================================================
//函数：Picture loadPic(const char *path)
//作用：加载一张图片
//参数：path本地图片路径
//返回：图片结构体
//====================================================
Picture loadPic(const char* path)
{
	Picture pic;
	//加载一张图片
	pic.pPic = IMG_LoadTexture(g_pRenderer, path);
	if (NULL == pic.pPic)
	{
		printf("图片创建失败：%s\n", SDL_GetError());
	}
	else
	{
		printf("图片加载成功：%s\n", path);
	}
	return pic;
}
 
//====================================================
//名称：void setPicDstRect(Picture * picture, int x, int y, 	int w, int h) 
//说明：设置一幅图片的目标显示区域
//参数：picture图片结构体指针
//	x, y	目标区域坐标
//	w, h	目标区域大小 
//====================================================
void setPicDstRect(Picture *picture, int x, int y, int w, int h) {
	picture->dstRect.x = x; 
	picture->dstRect.y = y;
	picture->dstRect.w = w;
	picture->dstRect.h = h;
}
	
//====================================================
//名称：void setPicSrcRect(Picture *picture, int x, int y,int w, int h)
//说明：设置一幅图片的源读取区域
//参数：picture图片结构体指针
//	х, y
//	目标区域坐标
//  w, h
//	目标区域大小
//====================================================
void setPicSrcRect(Picture *picture, int x, int y,
			       int w, int h)
{
	picture->srcRect.x = x;
	picture->srcRect.y = y;
	if (picture->pPic == NULL) 
	{
		printf("纹理未正确加载：%s\n", SDL_GetError());
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
//名称：int loadPicResources(void) 
// 说明：加载程序所需的图片资源
//返回：0表示加载成功，非0表示加载失败
//====================================================
int loadPicResources(void)
{
	// 加载背景图片1

	g_picBackGround_1 = loadPic(PATH_BACKGROUND_1);
	if (g_picBackGround_1.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBackGround_1, 0, 0, 0, 0);
	setPicDstRect(&g_picBackGround_1,
		BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y,
		BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);
	
	//加载背景图片2
	g_picBackGround_2 = loadPic(PATH_BACKGROUND_2);
	if (g_picBackGround_2.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBackGround_2, 0, 0, 0, 0);
	setPicDstRect(&g_picBackGround_2,
		BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y,
		BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);

	//加载游戏胜利与失败图片
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


	//加载游戏开始按钮图片 
	g_picStartButton = loadPic(PATH_START);
	if (g_picStartButton.pPic == NULL) {
		return -1;
	}
	setPicSrcRect(&g_picStartButton, 0, 0, 0, 0);
	setPicDstRect(&g_picStartButton, BOX_START_X, BOX_START_Y, BOX_W, BOX_H);

	//加载点击前的格子
	g_picBlank_0 = loadPic(PATH_BLANK_0);
	if (g_picBlank_0.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_0, 0, 0, 0, 0);
	setPicDstRect(&g_picBlank_0, BLANK_X, BLANK_Y, BLANK_W, BLANK_H);

	//加载点击后的格子
	g_picBlank_9 = loadPic(PATH_BLANK_9);
	if (g_picBlank_9.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_9, 0, 0, 0, 0);

	//加载显示雷的格子图片
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
	
	
	//加载炸弹图片
	g_picBomb = loadPic(PATH_BOMB_1);
	if (g_picBomb.pPic ==NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picBlank_0, 0, 0, 0, 0);

	//加载标记1
	g_picsign_tag = loadPic(PATH_SIGN_TAG);
	if (g_picsign_tag.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picsign_tag, 0, 0, 0, 0);

	//加载标记2
	g_picsign_unknow = loadPic(PATH_SIGN_UNKNOW);
	if (g_picsign_unknow.pPic == NULL)
	{
		return -1;
	}
	setPicSrcRect(&g_picsign_unknow, 0, 0, 0, 0);

	return 0;
}
//====================================================
//名称：void freePicResources(void) 
// 说明：释放程序加载的图片资源		
//====================================================
void freePicResources(void) 
{
	SDL_DestroyTexture(g_picBackGround_1.pPic);
	SDL_DestroyTexture(g_picBackGround_2.pPic);
	SDL_DestroyTexture(g_picStartButton.pPic);

}

//====================================================
//名称：void paintPic(Picture* picture) 
//说明：往渲染器绘制一幅图片
//参数：picture图片结构体指针
//====================================================
void paintPic(Picture* picture)
{
	SDL_RenderCopy(g_pRenderer, picture->pPic,
		&(picture->srcRect), &(picture->dstRect));
}

//====================================================
//名称：void paint(void)
//说明：绘制窗口
//====================================================
void paint() 
{
	SDL_RenderClear(g_pRenderer);
	if (gameStarted){
		paintPic(&g_picBackGround_2);//游戏开始后的背景
		if (!place)
		{
			int n = 37;//加载点击前的格子
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

//格子被点击后的变化
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
			// 根据周围炸弹的数量显示相应的图片
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



//游戏开始按钮点击
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
								printf("游戏结束！你点击了一个雷！\n");
								gameover = true;
								gameStarted = false;
								// 显示所有炸弹
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
									printf("你赢了！所有雷都被标记了！\n");
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
							
							printf("你赢了！所有雷都被标记了！\n");
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


//右键标记
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

//检查胜利条件
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


//初始化格子
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

//布置炸弹,对炸弹检测
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
				grid[i][j].nbomb = 9; // 用于表示炸弹
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
