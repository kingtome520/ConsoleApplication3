#define SDL_MAIN_HANDLED
#include"interface.h"

int main(void) 
{
	srand(time(NULL));// 使用当前时间作为种子值初始化随机数生成器
	//初始化
	init();
	
	//运行
	start();
	
	//释放
	gameFree();

   
	return 0;
}