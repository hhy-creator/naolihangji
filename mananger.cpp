#include"mananger.h"
#include <iostream>
using namespace std;
void Mananger::RunChoose() 
{
	ShowMenu();
	ChangeChoose();
	switch (choose) 
	{
	case 1:
		{
			system("cls");
			BeginGame();
			break;
		}
	case 2: 
	{
		system("cls");
		ShowRule();
		break;

	}
	case 0:
	{
		system("cls");
		Exitgame();
		break;
	}

	}
}
void Mananger::ChangeChoose() 
{
	int choose1;
	cin >> choose1;
	this->choose = choose1;
}
void Mananger::ShowMenu() 
{
	cout << "       请输入你的选择：" << endl;
	cout << "****************************" << endl;
	cout << "********1开始游戏***********" << endl;
	cout << "********2了解游戏规则*******" << endl;
	cout << "*********0退出游戏**********" << endl;
	cout << "****************************" << endl;
};
void Mananger::ShowRule() 
{
	cout << "您将会获得一条通往某一目的地的航行路线，同时，以你为参照物，您能获得另一人的相对路径，请推理出另一人的实际路径。" << endl;
		cout << "你与好朋友在星期六天下午相约在某一地点相聚，双方均规划好了前进路线，你好奇地问对方将怎么到达那里，可对方却笑着回答道，不告诉你，要求" << endl;
}
void Mananger::Exitgame() 
{
	exit(0);
}
void Mananger::BeginGame() 
{
	ChooseGame();

}
void Mananger::ChooseGame() 
{
	cout << "请输入您要挑战的关卡" << endl;
	int num;
	cin >> num;
	this->level = num;

}