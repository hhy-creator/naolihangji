#include"mananger.h"
#include"game.h"
#include "player.h"
#include <iostream>
#include <time.h>
#include <random>
#include <ctime>
using namespace std;
bool again() 
{
	int num1 = 0;
	cin >> num1;
	if (num1 == 1) { return true; }
	else if (num1 == 0) { return false; }
	else
	{
		cout << "输入不符合要求，请重新输入:" << endl; 
		again();
	}
}
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
	case 3:
	{
		system("cls");
		CheckMessage(p1);
		break;
	}
	default:
		cout << "输入的选择不符合要求，请重新输入：" << endl;
		break;

	}
}
void Mananger::ChangeChoose() 
{
	int choose1;
	cin >> choose1;
	this->choose = choose1;
}
void Mananger::ShowMenu()const 
{
	cout << "       请输入你的选择：" << endl;
	cout << "****************************" << endl;
	cout << "********1开始游戏***********" << endl;
	cout << "********2了解游戏规则*******" << endl;
	cout << "********3展示用户消息*******" << endl;
	cout << "********0退出游戏**********" << endl;
	cout << "****************************" << endl;
};
void Mananger::ShowRule()const 
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
int Mananger::getlevel()const 
{
	return level;
}
player& Mananger::getplayer() 
{
	return this->p1;
}
void Mananger::CheckMessage( player&p1) 
{
	cout << p1.GetName() << ":"<<endl;
	p1.ShowAccuracy(p1.Getaccuracy());
	p1.ShowScore(p1.Getscore());
}
void Mananger::GameShowmess(game& g1) 
{
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	bool x = 1;
	while (x) {
		g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative());
		bool a = g1.IfYes(g1.getrun(), g1.getp2array());
		if (a)
		{
			x = 0;
			cout << "游戏挑战成功，棒棒的。" << endl;
			bool a = 1;
			getplayer().CreatScore(getplayer().Getscore(),getlevel(), a);
			getplayer().AddRight(getplayer().Getright(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(),getplayer().Getaccuracy());
			break;
		}
		else
		{
			getplayer().AddWrong(getplayer().Getwrong(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			bool a = 0;
			getplayer().CreatScore(getplayer().Getscore(), getlevel(), a);
			cout << "挑战失败" << endl;
			cout << "是否再次挑战？(1表示是，0表示否)" << endl;


			
			if (!again()) 
			{ 
				cout << "放弃挑战" << endl;
				cout << "是否查看答案（1表示是，0表示否）" << endl;
				if (again()) { g1.getanswer(g1.getp2array()); }
			    break; 
			}
			else { system("cls"); }
		}
	}
}
void Mananger::creatgame1()
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
	GameShowmess(g1);
}
void Mananger::creatgame2()
{
	game g2;
	g2.setrun(11);
	g2.setzihzhen();
	g2.getp1().SetPeopleBeginPos(19,17);
	g2.getp1array()[0] = g2.getp1();
	g2.getp1().Movepeople(LEFT);
	g2.getp1array()[1] = g2.getp1();
	g2.getp1().Movepeople(LEFT);
	g2.getp1array()[2] = g2.getp1();
	g2.getp1().Movepeople(LEFT);
	g2.getp1array()[3] = g2.getp1();
	g2.getp1().Movepeople(DOWN);
	g2.getp1array()[4] = g2.getp1();
	g2.getp1().Movepeople(DOWN);
	g2.getp1array()[5] = g2.getp1();
	g2.getp1().Movepeople(RIGHT);
	g2.getp1array()[6] = g2.getp1();
	g2.getp1().Movepeople(RIGHT);
	g2.getp1array()[7] = g2.getp1();
	g2.getp1().Movepeople(DOWN);
	g2.getp1array()[8] = g2.getp1();
	g2.getp1().Movepeople(RIGHT);
	g2.getp1array()[9] = g2.getp1();
	g2.getp1().Movepeople(RIGHT);
	g2.getp1array()[10] = g2.getp1();
	g2.getp2().SetPeopleBeginPos(22, 22);
	g2.getp2array()[0] = g2.getp2();
	g2.getp2().Movepeople(UP);
	g2.getp2array()[1] = g2.getp2();
	g2.getp2().Movepeople(UP);
	g2.getp2array()[2] = g2.getp2();
	g2.getp2().Movepeople(RIGHT);
	g2.getp2array()[3] = g2.getp2();
	g2.getp2().Movepeople(UP);
	g2.getp2array()[4] = g2.getp2();
	g2.getp2().Movepeople(UP);
	g2.getp2array()[5] = g2.getp2();
	g2.getp2().Movepeople(LEFT);
	g2.getp2array()[6] = g2.getp2();
	g2.getp2().Movepeople(DOWN);
	g2.getp2array()[7] = g2.getp2();
	g2.getp2().Movepeople(LEFT);
	g2.getp2array()[8] = g2.getp2();
	g2.getp2().Movepeople(LEFT);
	g2.getp2array()[9] = g2.getp2();
	g2.getp2().Movepeople(DOWN);
	g2.getp2array()[10] = g2.getp2();
	GameShowmess(g2);
}
void Mananger::creatgame3()
{
	game g3;
	g3.setrun(16);
	g3.setzihzhen();
	g3.getp1().SetPeopleBeginPos(70, 62);
	g3.getp1array()[0] = g3.getp1();
	g3.getp1().Movepeople(UP);
	g3.getp1array()[1] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[2] = g3.getp1();
	g3.getp1().Movepeople(DOWN);
	g3.getp1array()[3] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[4] = g3.getp1();
	g3.getp1().Movepeople(UP);
	g3.getp1array()[5] = g3.getp1();
	g3.getp1().Movepeople(UP);
	g3.getp1array()[6] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[7] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[8] = g3.getp1();
	g3.getp1().Movepeople(DOWN);
	g3.getp1array()[9] = g3.getp1();
	g3.getp1().Movepeople(DOWN);
	g3.getp1array()[10] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[11] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[12] = g3.getp1();
	g3.getp1().Movepeople(UP);
	g3.getp1array()[13] = g3.getp1();
	g3.getp1().Movepeople(UP);
	g3.getp1array()[14] = g3.getp1();
	g3.getp1().Movepeople(LEFT);
	g3.getp1array()[15] = g3.getp1();
	g3.getp2().SetPeopleBeginPos(57, 59);
	g3.getp2array()[0] = g3.getp2();
	g3.getp2().Movepeople(RIGHT);
	g3.getp2array()[1] = g3.getp2();
	g3.getp2().Movepeople(DOWN);
	g3.getp2array()[2] = g3.getp2();
	g3.getp2().Movepeople(DOWN);
	g3.getp2array()[3] = g3.getp2();
	g3.getp2().Movepeople(RIGHT);
	g3.getp2array()[4] = g3.getp2();
	g3.getp2().Movepeople(UP);
	g3.getp2array()[5] = g3.getp2();
	g3.getp2().Movepeople(UP);
	g3.getp2array()[6] = g3.getp2();
	g3.getp2().Movepeople(RIGHT);
	g3.getp2array()[7] = g3.getp2();
	g3.getp2().Movepeople(DOWN);
	g3.getp2array()[8] = g3.getp2();
	g3.getp2().Movepeople(DOWN);
	g3.getp2array()[9] = g3.getp2();
	g3.getp2().Movepeople(RIGHT);
	g3.getp2array()[10] = g3.getp2();
	g3.getp2().Movepeople(UP);
	g3.getp2array()[11] = g3.getp2();
	g3.getp2().Movepeople(UP);
	g3.getp2array()[12] = g3.getp2();
	g3.getp2().Movepeople(RIGHT);
	g3.getp2array()[13] = g3.getp2();
	g3.getp2().Movepeople(RIGHT);
	g3.getp2array()[14] = g3.getp2();
	g3.getp2().Movepeople(DOWN);
	g3.getp2array()[15] = g3.getp2();

	GameShowmess(g3);
}
void Mananger::creatgame4()
{
	cout << "我两爱方形" << endl;
	game g4;
	g4.setrun(16);
	g4.setzihzhen();
	g4.getp1().SetPeopleBeginPos(10, 14);
	g4.getp1array()[0] = g4.getp1();
	g4.getp1().Movepeople(DOWN);
	g4.getp1array()[1] = g4.getp1();
	g4.getp1().Movepeople(DOWN);
	g4.getp1array()[2] = g4.getp1();
	g4.getp1().Movepeople(DOWN);
	g4.getp1array()[3] = g4.getp1();
	g4.getp1().Movepeople(LEFT);
	g4.getp1array()[4] = g4.getp1();
	g4.getp1().Movepeople(LEFT);
	g4.getp1array()[5] = g4.getp1();
	g4.getp1().Movepeople(LEFT);
	g4.getp1array()[6] = g4.getp1();
	g4.getp1().Movepeople(UP);
	g4.getp1array()[7] = g4.getp1();
	g4.getp1().Movepeople(UP);
	g4.getp1array()[8] = g4.getp1();
	g4.getp1().Movepeople(UP);
	g4.getp1array()[9] = g4.getp1();
	g4.getp1().Movepeople(RIGHT);
	g4.getp1array()[10] = g4.getp1();
	g4.getp1().Movepeople(RIGHT);
	g4.getp1array()[11] = g4.getp1();
	g4.getp1().Movepeople(DOWN);
	g4.getp1array()[12] = g4.getp1();
	g4.getp1().Movepeople(DOWN);
	g4.getp1array()[13] = g4.getp1();
	g4.getp1().Movepeople(LEFT);
	g4.getp1array()[14] = g4.getp1();
	g4.getp1().Movepeople(UP);
	g4.getp1array()[15] = g4.getp1();
	g4.getp2().SetPeopleBeginPos(6, 16);
	g4.getp2array()[0] = g4.getp2();
	g4.getp2().Movepeople(UP);
	g4.getp2array()[1] = g4.getp2();
	g4.getp2().Movepeople(UP);
	g4.getp2array()[2] = g4.getp2();
	g4.getp2().Movepeople(UP);
	g4.getp2array()[3] = g4.getp2();
	g4.getp2().Movepeople(RIGHT);
	g4.getp2array()[4] = g4.getp2();
	g4.getp2().Movepeople(RIGHT);
	g4.getp2array()[5] = g4.getp2();
	g4.getp2().Movepeople(RIGHT);
	g4.getp2array()[6] = g4.getp2();
	g4.getp2().Movepeople(DOWN);
	g4.getp2array()[7] = g4.getp2();
	g4.getp2().Movepeople(DOWN);
	g4.getp2array()[8] = g4.getp2();
	g4.getp2().Movepeople(DOWN);
	g4.getp2array()[9] = g4.getp2();
	g4.getp2().Movepeople(LEFT);
	g4.getp2array()[10] = g4.getp2();
	g4.getp2().Movepeople(LEFT);
	g4.getp2array()[11] = g4.getp2();
	g4.getp2().Movepeople(UP);
	g4.getp2array()[12] = g4.getp2();
	g4.getp2().Movepeople(UP);
	g4.getp2array()[13] = g4.getp2();
	g4.getp2().Movepeople(RIGHT);
	g4.getp2array()[14] = g4.getp2();
	g4.getp2().Movepeople(DOWN);
	g4.getp2array()[15] = g4.getp2();
	GameShowmess(g4);
}
void Mananger::creatgame5()
{
	cout << "耿直的他" << endl;
	game g5;
	g5.setrun(21);
	g5.setzihzhen();
	g5.getp1().SetPeopleBeginPos(8,54);
	g5.getp1array()[0] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[1] = g5.getp1();
	g5.getp1().Movepeople(LEFT);
	g5.getp1array()[2] = g5.getp1();
	g5.getp1().Movepeople(DOWN);
	g5.getp1array()[3] = g5.getp1();
	g5.getp1().Movepeople(DOWN);
	g5.getp1array()[4] = g5.getp1();
	g5.getp1().Movepeople(RIGHT);
	g5.getp1array()[5] = g5.getp1();
	g5.getp1().Movepeople(RIGHT);
	g5.getp1array()[6] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[7] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[8] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[9] = g5.getp1();
	g5.getp1().Movepeople(LEFT);
	g5.getp1array()[10] = g5.getp1();
	g5.getp1().Movepeople(LEFT);
	g5.getp1array()[11] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[12] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[13] = g5.getp1();
	g5.getp1().Movepeople(RIGHT);
	g5.getp1array()[14] = g5.getp1();
	g5.getp1().Movepeople(DOWN);
	g5.getp1array()[15] = g5.getp1();
	g5.getp1().Movepeople(RIGHT);
	g5.getp1array()[16] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[17] = g5.getp1();
	g5.getp1().Movepeople(UP);
	g5.getp1array()[18] = g5.getp1();
	g5.getp1().Movepeople(RIGHT);
	g5.getp1array()[19] = g5.getp1();
	g5.getp1().Movepeople(DOWN);
	g5.getp1array()[20] = g5.getp1();
	g5.getp2().SetPeopleBeginPos(10, 30);
	g5.getp2array()[0] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[1] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[2] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[3] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[4] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[5] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[6] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[7] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[8] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[9] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[10] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[11] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[12] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[13] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[14] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[15] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[16] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[17] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[18] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[19] = g5.getp2();
	g5.getp2().Movepeople(DOWN);
	g5.getp2array()[20] = g5.getp2();
	GameShowmess(g5);
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
	case 2:
	{
		creatgame2();
		break;
	}
	case 3:
	{
		creatgame3();
		break;
	}
	case 4:
	{
		creatgame4();
		break;
	}
	case 5:
	{
		creatgame5();
		break;
	}
	case 6:
	{
		randomcreatgame();
		break;
	}
	default:
		cout << "当前关卡不存在，请重新输入!"<<endl;
		ChooseGame();
	}
}
void Mananger::randomcreatgame() 
{
	game randomgame;
	int number1 = rand() % 7 + 10;
	randomgame.setrun(number1);
	randomgame.setzihzhen();
	int xfinal = 0, yfinal = 0;
	xfinal = rand() % 100 + 1;
	yfinal = rand() % 100 + 1;
	randomgame.getp1().SetPeopleBeginPos(xfinal, yfinal);
	randomgame.getp2().SetPeopleBeginPos(xfinal, yfinal);
	randomgame.getp1array()[number1 - 1].SetPeopleBeginPos(xfinal, yfinal);
	randomgame.getp2array()[number1 - 1].SetPeopleBeginPos(xfinal, yfinal);
	for (int i = number1 - 2; i >= 0;) 
	{
		int number1 = rand() % 4;
		switch (number1) 
		{
		case 0: 
		{
			randomgame.getp1().Movepeople(UP);
			randomgame.getp1array()[i] = randomgame.getp1();
			if (randomgame.ifpass(randomgame.getp1array(), i))
			{
				i--;
			}
			else randomgame.getp1().Movepeople(DOWN);
			break;
		}
		case 1:
		{
			randomgame.getp1().Movepeople(DOWN);
			randomgame.getp1array()[i] = randomgame.getp1();
			if (randomgame.ifpass(randomgame.getp1array(), i))
			{
				i--;
			}
			else randomgame.getp1().Movepeople(UP);
			break;
		}
		case 2:
		{
			randomgame.getp1().Movepeople(LEFT);
			randomgame.getp1array()[i] = randomgame.getp1();
			if (randomgame.ifpass(randomgame.getp1array(), i))
			{
				i--;
			}
			else randomgame.getp1().Movepeople(RIGHT);
			break;
		}
		case 3:
		{
			randomgame.getp1().Movepeople(RIGHT);
			randomgame.getp1array()[i] = randomgame.getp1();
			if (randomgame.ifpass(randomgame.getp1array(), i))
			{
				i--;
			}
			else randomgame.getp1().Movepeople(LEFT);
			break;
		}
		}
		
	}
	for (int i = number1 - 2; i >= 0;)
	{
		int number1 = rand() % 4;
		bool c2 = 0;
		switch (number1)
		{
		case 0:
		{
			randomgame.getp2().Movepeople(UP);
			randomgame.getp2array()[i] = randomgame.getp2();
			if (randomgame.ifpass(randomgame.getp2array(), i))
			{
				i--;
			}
			else randomgame.getp2().Movepeople(DOWN);
			break;
		}
		case 1:
		{
			randomgame.getp2().Movepeople(DOWN);
			randomgame.getp2array()[i] = randomgame.getp2();
			if (randomgame.ifpass(randomgame.getp2array(), i))
			{
				i--;
			}
			else randomgame.getp2().Movepeople(UP);
			break;
		}
		case 2:
		{
			randomgame.getp2().Movepeople(LEFT);
			randomgame.getp2array()[i] = randomgame.getp2();
			if (randomgame.ifpass(randomgame.getp2array(), i))
			{
				i--;
			}
			else randomgame.getp2().Movepeople(RIGHT);
			break;
		}
		case 3:
		{
			randomgame.getp2().Movepeople(RIGHT);
			randomgame.getp2array()[i] = randomgame.getp2();
			if (randomgame.ifpass(randomgame.getp2array(), i))
			{
				i--;
			}
			else randomgame.getp2().Movepeople(LEFT);
			break;
		}
		}
	}
	GameShowmess(randomgame);
}