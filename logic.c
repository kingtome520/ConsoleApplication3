#include"interface.h"

//====================================================
//������int init(void)
//���ã���Ϸ��ʼ��
//====================================================
int init(void)
{
	//��ʼ��SDL��
	if (initSDL() != 0)
	{
		return -1;
	}

	/*font = TTF_OpenFont("path/to/font.ttf", 24);
	if (!font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return -1;
	}*/

	//����ͼƬ��Դ
	if (loadPicResources() != 0)
	{
		return -2;
	}
	
	return 0;
}

//====================================================
//������void gameFree(void) 
// ���ã���Ϸ��Դ�ͷ� 
void gameFree(void) 
{
	//	�ͷ�ͼƬ 
	freePicResources();

	/*TTF_CloseFont(font);
	TTF_Quit();*/
	
	//	�˳�SDL�⣬�ͷŴ��ڡ���Ⱦ��
	freeSDL();
}

//====================================================
//������Uint32 timerFun(Uint32 interval, void * param) 
//���ã���ʱ����Ӧ����
//====================================================
Uint32 timerFun(Uint32 interval, void* param) 
{
	//���ƴ��� 
	paint();
	return interval;
}

//====================================================
//������ void logicStart ��void��
//���ã���Ϸ��ʼ����Ӷ�ʱ�����Լ��¼�ѭ����
//====================================================
void start(void) 
{
	bool quit = false;
	paint();
	while (!quit) {
		handleEvents(&quit);

		// ���ö�ʱ����ÿ��1000�������һ��timerCallback
		/*SDL_TimerID timerID = SDL_AddTimer(1000, timerCallback, NULL);
		render();
		SDL_Delay(16); */// ����֡��
	}

	//SDL_RemoveTimer(timerID);


	SDL_Event event;	//�¼����ͱ���
	int nQuit = 0;		//�˳���ʶ��0ѭ������0�˳�ѭ��

	// ��Ӷ�ʱ������
	SDL_AddTimer(85, timerFun, NULL);

	// ����Ϣ������ѭ��ȡ���¼�
	while (nQuit == 0)		// �ж��Ƿ��˳��¼�ѭ��
	{
		while (SDL_PollEvent(&event))//��ȡ�¼�
		{
			switch (event.type)//�¼������
			{
				case SDL_QUIT:// �˳��¼�
					nQuit = 1; //�û������˳��¼�������ѭ��
					break;
				default:
					break;
			}
		}
	}
}