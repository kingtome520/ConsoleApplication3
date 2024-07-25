#include"interface.h"

//====================================================
//函数：int init(void)
//作用：游戏初始化
//====================================================
int init(void)
{
	//初始化SDL库
	if (initSDL() != 0)
	{
		return -1;
	}

	/*font = TTF_OpenFont("path/to/font.ttf", 24);
	if (!font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return -1;
	}*/

	//加载图片资源
	if (loadPicResources() != 0)
	{
		return -2;
	}
	
	return 0;
}

//====================================================
//函数：void gameFree(void) 
// 作用：游戏资源释放 
void gameFree(void) 
{
	//	释放图片 
	freePicResources();

	/*TTF_CloseFont(font);
	TTF_Quit();*/
	
	//	退出SDL库，释放窗口、渲染器
	freeSDL();
}

//====================================================
//函数：Uint32 timerFun(Uint32 interval, void * param) 
//作用：定时器响应函数
//====================================================
Uint32 timerFun(Uint32 interval, void* param) 
{
	//绘制窗口 
	paint();
	return interval;
}

//====================================================
//函数： void logicStart （void）
//作用：游戏开始（添加定时器，以及事件循环）
//====================================================
void start(void) 
{
	bool quit = false;
	paint();
	while (!quit) {
		handleEvents(&quit);

		// 设置定时器，每隔1000毫秒调用一次timerCallback
		/*SDL_TimerID timerID = SDL_AddTimer(1000, timerCallback, NULL);
		render();
		SDL_Delay(16); */// 控制帧率
	}

	//SDL_RemoveTimer(timerID);


	SDL_Event event;	//事件类型变量
	int nQuit = 0;		//退出标识，0循环，非0退出循环

	// 添加定时器函数
	SDL_AddTimer(85, timerFun, NULL);

	// 从消息队列中循环取得事件
	while (nQuit == 0)		// 判断是否退出事件循环
	{
		while (SDL_PollEvent(&event))//获取事件
		{
			switch (event.type)//事件的类别
			{
				case SDL_QUIT:// 退出事件
					nQuit = 1; //用户激活退出事件，跳出循环
					break;
				default:
					break;
			}
		}
	}
}