#define SDL_MAIN_HANDLED
#include"interface.h"

int main(void) 
{
	srand(time(NULL));// ʹ�õ�ǰʱ����Ϊ����ֵ��ʼ�������������
	//��ʼ��
	init();
	
	//����
	start();
	
	//�ͷ�
	gameFree();

   
	return 0;
}