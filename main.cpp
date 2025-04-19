#include "game.h"
#include "mananger.h"
#include "player.h"
#include <iostream>
#include <random>
#include <easyx.h>
#include <vector>
using namespace std;

int main() 
{
	Mananger m1;
	srand(time(0));
	while (true) 
	{
		m1.RunChoose();
	}


}
//1、 同时实现记录时长函数

//2、 将mananger类完善展示玩家信息等。同时，将文件操作引入程序，实现将玩家信息等内容保存到文件中。
