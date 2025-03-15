#include"mananger.h"
#include"game.h"
#include <iostream>
#include <time.h>
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
}
void Mananger::Exitgame() 
{
	cout << "游戏已退出" << endl;
	exit(0);
}
void Mananger::BeginGame() 
{
	ChooseGame();

}
int Mananger::getlevel() 
{
	return level;
}
void creatgame1()
{
	game g1;
	g1.setrun(5);
	g1.setzihzhen();
	g1.getp1().SetPeopleBeginPos(30, 34);
	g1.getp1array()[0] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[1] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[2] = g1.getp1();
	g1.getp1().Movepeople(UP);
	g1.getp1array()[3] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[4] = g1.getp1();
	g1.getp2().SetPeopleBeginPos(35, 31);
	g1.getp2array()[0] = g1.getp2();
	g1.getp2().Movepeople(LEFT);
	g1.getp2array()[1] = g1.getp2();
	g1.getp2().Movepeople(LEFT);
	g1.getp2array()[2] = g1.getp2();
	g1.getp2().Movepeople(DOWN);
	g1.getp2array()[3] = g1.getp2();
	g1.getp2().Movepeople(DOWN);
	g1.getp2array()[4] = g1.getp2();
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	bool x = 1;
	while (x) {
		g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative());
		bool a = g1.IfYes(g1.getrun(), g1.getp2array());
		if (a)
		{
			x = 0;
			cout << "游戏挑战成功，棒棒的。" << endl;
			break;
		}
		else
		{
			cout << "挑战失败" << endl;
			cout << "是否再次挑战？(1表示是，0表示否)" << endl;
			bool aga;
			cin >> aga;
			if (!aga) { cout << "放弃挑战" << endl; break; }
			else { system("cls"); }
		}
	}
}
void Mananger::ChooseGame() 
{
	cout << "请输入您要挑战的关卡:" << endl;
	int num;
	cin >> num;
	this->level = num;
	switch (getlevel()) 
	{
	case 1: 
	{
		creatgame1();
		break;
	}
	}
}