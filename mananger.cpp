#include"mananger.h"
#include"game.h"
#include "player.h"
#include <iostream>
#include <time.h>
#include <random>
#include <iomanip>
#include <easyx.h>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;
void Mananger::recordmessage()
{
	ofstream ofs("D:/脑力航迹/playermessgae.txt", ios::binary|ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	this->p1.serialize(ofs);
	ofs.close();

}
void Mananger::readplayermessage() 
{
	ifstream ifs("D:/脑力航迹/playermessgae.txt", ios::binary);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	while (!ifs.eof()) {
		player p1(0);
		p1=p1.deserialize(ifs);
		p1.CheckMessage();
	}
	return;

}
Mananger::~Mananger() 
{
}
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
	case 4:
	{
		system("cls");
		PlayerGreatgame();
		break;
	}
	case 5:
	{
		system("cls");
		challengegame();
		break;
	}
	case 6:
	{
		system("cls");
		noendchallenge();
		break;
	}
	default:
		cout << "输入的选择不符合要求，请重新输入：" << endl;

	}
}
void Mananger::ShowMenu() 
{

	cout << "       请输入你的选择：" << endl;
	cout << "****************************" << endl;
	cout << "********1开始游戏***********" << endl;
	cout << "********2查看规则*******" << endl;
	cout << "********3查看消息*******" << endl;
	cout << "********4创造模式**********"<<endl;
	cout << "********5挑战模式**********" << endl;
	cout << "********6无尽模式**********" << endl;
	cout << "********0退出游戏**********" << endl;
	cout << "****************************" << endl;
};
void Mananger::Exitgame() 
{
	recordmessage();
	readplayermessage();
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
	p1.CheckMessage();
}
void Mananger::GameShowmess(game& g1)
{
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	bool x = 1;
	while (x) {
		g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative());
		int gamestarttime = 0;
		int gameduration = 0;
		gamestarttime = clock();
		bool a = g1.IfYes(g1.getrun(), g1.getp2array());
		gameduration = clock() - gamestarttime;
		int secondall = gameduration / 1000;
		int seconds = secondall % 60;
		int minute = secondall / 60;
		cout << "用时：" << setfill('0') << setw(2) << minute << ":" << setw(2) << seconds << endl;
		if (a)
		{
			x = 0;
			cout << "游戏挑战成功，棒棒的。" << endl;
			bool a = 1;
			getplayer().CreatScore(getplayer().Getscore(), getlevel(), a, this->p1.gettime(), g1.getrun());
			getplayer().AddRight(getplayer().Getright(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			break;
		}
		else
		{
			getplayer().AddWrong(getplayer().Getwrong(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			bool a = 0;
			getplayer().CreatScore(getplayer().Getscore(), getlevel(), a, this->p1.gettime(), g1.getrun());
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
void Mananger::GameShowmess(game& g1,const int &i) 
{
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	bool x = 1;
	while (x) {
		g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative());
		int gamestarttime = 0;
		int gameduration = 0;
		gamestarttime = clock();
		bool a = g1.IfYes(g1.getrun(), g1.getp2array());
		gameduration = clock() - gamestarttime;
		int secondall = gameduration / 1000;
		int seconds = secondall % 60;
		int minute = secondall / 60;
		this->p1.gettime()[i] = secondall;
		cout << "用时：" << setfill('0') << setw(2) << minute << ":" << setw(2) << seconds<<endl;
		if (a)
		{
			x = 0;
			cout << "游戏挑战成功，棒棒的。" << endl;
			bool a = 1;
			getplayer().CreatScore(getplayer().Getscore(),getlevel(), a,this->p1.gettime(),g1.getrun());
			getplayer().AddRight(getplayer().Getright(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(),getplayer().Getaccuracy());
			break;
		}
		else
		{
			getplayer().AddWrong(getplayer().Getwrong(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			bool a = 0;
			getplayer().CreatScore(getplayer().Getscore(), getlevel(), a, this->p1.gettime(), g1.getrun());
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
void Mananger::PlayerGameShowmess(game& g1)
{
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	cout << "请输入玩家作答还是系统作答：(1玩家0系统)" << endl;
	bool aa;
	cin >> aa;
	if (aa)
	{
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
	else { g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative()); g1.getanswer(g1.getp2array()); }
}
void Mananger::GameShowmess1(game& g1)
{
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative());
	bool a = g1.IfYes(g1.getrun(), g1.getp2array());
	if (a)
	{
		
		cout << "游戏挑战成功，棒棒的。" << endl;

	}
	else{
				cout << "挑战结束" << endl;

		}

	
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
	GameShowmess(g2,1);
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

	GameShowmess(g3,2);
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
	GameShowmess(g4,3);
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
	GameShowmess(g5,4);
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
void Mananger::randomcreatgame(int number1)
{

	game randomgame;
	randomgame.setrun(number1);
	randomgame.setzihzhen();
	int xfinal = 0, yfinal = 0;
	xfinal = rand() % 5 + 19;
	yfinal = rand() % 5 + 10;
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
	GameShowmess1(randomgame);
}
void Mananger::PlayerGreatgame() 
{
	game playergame;
	int number1 = 0;
	cout << "请输入移动步数：" << endl;
	cin >> number1;
	playergame.setrun(number1+1);
	playergame.setzihzhen();
	int xstart1 = 0, ystart1 = 0;
	cout << "请输入您的起始坐标：" << endl;
	cin >> xstart1 >> ystart1;
	playergame.getp1().SetPeopleBeginPos(xstart1, ystart1);
	playergame.getp1array()[0].SetPeopleBeginPos(xstart1, ystart1);
	cout << "请输入您的移动(0上1下2左3右):" << endl;
	int number2 = 0;
	for (int i = 1; i<playergame.getrun();)
	{
		cin >> number2;
		switch (number2)
		{
		case 0:
		{
			playergame.getp1().Movepeople(UP);
			playergame.getp1array()[i] = playergame.getp1();
			if (playergame.ifpass1(playergame.getp1array(), i))
			{
				i++;
			}
			else
			{
				cout << "该地方已经经过，请重新输入：" << endl;
				playergame.getp1().Movepeople(DOWN);

			}
			break;
		}
		case 1:
		{
			playergame.getp1().Movepeople(DOWN);
			playergame.getp1array()[i] = playergame.getp1();
			if (playergame.ifpass1(playergame.getp1array(), i))
			{
				i++;
			}
			else
			{
				cout << "该地方已经经过，请重新输入：" << endl; playergame.getp1().Movepeople(UP);

			}
			break;
		}
		case 2:
		{
			playergame.getp1().Movepeople(LEFT);
			playergame.getp1array()[i] = playergame.getp1();
			if (playergame.ifpass1(playergame.getp1array(), i))
			{
				i++;
			}
			else {
				cout << "该地方已经经过，请重新输入：" << endl; playergame.getp1().Movepeople(RIGHT);
			}
			break;
		}
		case 3:
		{
			playergame.getp1().Movepeople(RIGHT);
			playergame.getp1array()[i] = playergame.getp1();
			if (playergame.ifpass1(playergame.getp1array(), i))
			{
				i++;
			}
			else
			{
				cout << "该地方已经经过，请重新输入：" << endl; playergame.getp1().Movepeople(LEFT);
			}
			break;
		}
		}

	}
	int xstart2, ystart2 = 0;
	cout << "请输入别人的起始坐标：" << endl;
	cin >> xstart2 >> ystart2;
	playergame.getp2().SetPeopleBeginPos(xstart2, ystart2);
	playergame.getp2array()[0].SetPeopleBeginPos(xstart2, ystart2);
	cout << "请输入别人的移动(0上1下2左3右):" << endl;
	for (int i = 1; i < playergame.getrun();)
	{
		int number2 = 0;
		cin >> number2;
		switch (number2)
		{
		case 0:
		{
			playergame.getp2().Movepeople(UP);
			playergame.getp2array()[i] = playergame.getp2();
			if (playergame.ifpass1(playergame.getp2array(), i))
			{
				i++;
			}
			else
			{
				cout << "该地方已经经过，请重新输入：" << endl;
				playergame.getp2().Movepeople(DOWN);

			}
			break;
		}
		case 1:
		{
			playergame.getp2().Movepeople(DOWN);
			playergame.getp2array()[i] = playergame.getp2();
			if (playergame.ifpass1(playergame.getp2array(), i))
			{
				i++;
			}
			else
			{
				cout << "该地方已经经过，请重新输入：" << endl; playergame.getp2().Movepeople(UP);

			}
			break;
		}
		case 2:
		{
			playergame.getp2().Movepeople(LEFT);
			playergame.getp2array()[i] = playergame.getp2();
			if (playergame.ifpass1(playergame.getp2array(), i))
			{
				i++;
			}
			else {
				cout << "该地方已经经过，请重新输入：" << endl; playergame.getp2().Movepeople(RIGHT);
			}
			break;
		}
		case 3:
		{
			playergame.getp2().Movepeople(RIGHT);
			playergame.getp2array()[i] = playergame.getp2();
			if (playergame.ifpass1(playergame.getp2array(), i))
			{
				i++;
			}
			else
			{
				cout << "该地方已经经过，请重新输入：" << endl; playergame.getp2().Movepeople(LEFT);
			}
			break;
		}
		}

	}
	PlayerGameShowmess(playergame);
}
void Mananger::challengegame() 
{
	cout << "请输入您要挑战的难度(1简单2中等3困难4专家5传奇)：" << endl;
	int number;
	cin >> number;
	switch (number) 
	{
	case 1: 
	{
		randomcreatgame(6);
		break;
	}
	case 2:
	{
		randomcreatgame(9);
		break;
	}
	case 3: 
	{

		randomcreatgame(12);
		break;
	}
	case 4:
	{
		randomcreatgame(18);
		break;
	}
	case 5: 
	{
		randomcreatgame(25);
		break;
	}
	default:
	{
		cout << "输入不符合要求，请重新输入:" << endl;
		challengegame();
	}
	}

}
void Mananger::noendchallenge() 
{
	int i = 1;
	bool x = 1;
	while (x)
	{
		cout << "第" << i << "关" << endl;
		randomcreatgame(i+1);
		cout << "是否继续挑战？(退出请输入0继续请按1)" << endl;
		bool a;
		cin >> a;
		if (a) 
		{
			this->p1.getnoendscore() = 100 * i;
			i++;
			
		}
		else 
		{
			this->p1.getnoendscore() = 100 * i;
			break;
		}

	}
}
button::button(const int& x, const int& y, const int& width, const int& height, const string& text1)
	:text(text1), x(x), y(y), width(width), height(height), color(YELLOW)
{

}
button::~button() {}
int button::returnx()
{
	return this->x;

}
int button::returny() 
{
	return this->y;
}
int button::returnwidth() 
{
	return this->width;
}
int button::returnheight() 
{
	return this->height;
}
button::button() {}
ExMessage Mananger::getmousemessage()
{
	ExMessage msg;
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				return msg;
			}
		}
	}
}
int Mananger::ifinbutoon(button& pb, ExMessage m)
{
	if (pb.returnx() < m.x && pb.returnx() + pb.returnwidth() > m.x && pb.returny() < m.y && pb.returny() + pb.returnheight() > m.y)
	{
		pb.changecolor();
		pb.drawbutton();
		return 1;

	}
	return 0;
}
void button::changecolor()
{
	this->color = RED;
}
void button::drawbutton()
{
	setfillcolor(this->color);
	settextstyle(35, 20, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("查看规则")) / 2;
	int vspace = (this->height - textheight("查看规则")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x+hspace, this->y+vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void button::drawbutton1()
{
	setfillcolor(this->color);
	settextstyle(20, 20, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("返回")) / 2;
	int vspace = (this->height - textheight("返回")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace, this->y + vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void button::drawGQbutton() 
{
	setfillcolor(WHITE);
	settextstyle(10, 10, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("10")) / 2;
	int vspace = (this->height - textheight("10")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace, this->y + vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void button::drawchoosebutton()
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("10")) / 2;
	int vspace = (this->height - textheight("10")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace, this->y + vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void Mananger::loadwindow()
{

	loadimage(&this->img[0], "C:/Users/pcuser/Desktop/实训/开始界面.jpg", 900, 600);
}
void Mananger::loadrule()
{
	loadimage(&this->img[1], "C:/Users/pcuser/Desktop/实训/规则介绍.jpg", 900, 600);
}
void Mananger::loadGamebk()
{
	loadimage(&this->img[3], "C:/Users/pcuser/Desktop/实训/关卡背景图.jpg", 1000, 729);

}
void Mananger::loadChooseGQmenu()
{
	loadimage(&this->img[2], "C:/Users/pcuser/Desktop/实训/关卡选择界面.jpg", 900, 600);


}
void Mananger::createGameP()
{
	cleardevice();
	initgraph(1000, 729);
	setbkmode(TRANSPARENT);
	while (1) 
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[3]);
		for (int i = 0; i < 625; i++) 
		{
			this->GQbutton[i].drawGQbutton();
		}
		EndBatchDraw();
	}
}
Mananger::Mananger()
{
	button b0(320, 120, 200, 50, "开始游戏");
	button b1(320, 170, 200, 50, "查看规则");
	button b2(320, 220, 200, 50, "查看信息");
	button b3(320, 270, 200, 50, "创造模式");
	button b4(320, 320, 200, 50, "挑战模式");
	button b5(320, 370, 200, 50, "无尽模式");
	button b6(320, 420, 200, 50, "退出游戏");
	button b7(0, 0, 125, 50, "返回");
	button choose0(100, 100, 30, 30, "1");
	button choose1(150, 100, 30, 30, "2");
	button choose2(200, 100, 30, 30, "3");
	button choose3(250, 100, 30, 30, "4");
	button choose4(300, 100, 30, 30, "5");
	button choose5(350, 100, 30, 30, "6");

	this->buttonarr[0] = b0;
	this->buttonarr[1] = b1;
	this->buttonarr[2] = b2;
	this->buttonarr[3] = b3;
	this->buttonarr[4] = b4;
	this->buttonarr[5] = b5;
	this->buttonarr[6] = b6;
	this->buttonarr[7] = b7;
	this->GQChoosebutton[0] = choose0;
	this->GQChoosebutton[1] = choose1;
	this->GQChoosebutton[2] = choose2;
	this->GQChoosebutton[3] = choose3;
	this->GQChoosebutton[4] = choose4;
	this->GQChoosebutton[5] = choose5;
	loadwindow();
	loadrule();
	loadChooseGQmenu();
	loadGamebk();
	for (int i = 0; i < 25; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			button b0(i*25+100,j*25+30,25,25,"");
			this->GQbutton[i*25 + j] = b0;
		}
	}

}
void Mananger::ChangeChoose()
{
	initgraph(900, 600);
	setbkmode(TRANSPARENT);
	while (1) {
		cleardevice();
		putimage(0, 0, &this->img[0]);
		for (int i = 0; i <= 6; i++)
		{
			this->buttonarr[i].drawbutton();
		}
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(this->buttonarr[0], msg))
		{
			EndBatchDraw();
			this->choose = 1;
			break;
		}
		else if (ifinbutoon(this->buttonarr[1], msg))
		{
			EndBatchDraw(); this->choose = 2; break;
		}
		else if (ifinbutoon(this->buttonarr[2], msg)) {
			EndBatchDraw(); this->choose = 3; break;
		}
		else if (ifinbutoon(this->buttonarr[3], msg)) {
			EndBatchDraw(); this->choose = 4; break;
		}
		else if (ifinbutoon(this->buttonarr[4], msg)) {
			EndBatchDraw(); this->choose = 5; break;
		}
		else if (ifinbutoon(this->buttonarr[5], msg)) {
			EndBatchDraw(); this->choose = 6; break;
		}
		else if (ifinbutoon(this->buttonarr[6], msg)) {
			EndBatchDraw(); this->choose = 0; break;
		}
	}
	closegraph();
}
void Mananger::ShowRule()
{
	cleardevice();
	initgraph(900, 600);
	setbkmode(TRANSPARENT);
	while (1) {
		putimage(0, 0, &this->img[1]);
		this->buttonarr[7].drawbutton1();
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(this->buttonarr[7], msg))
		{
			EndBatchDraw();
			cleardevice();
			break;
		}
	}
	closegraph();
	RunChoose();
}
void Mananger::ChooseGame()
{

	cleardevice();
	initgraph(900, 600);
	setbkmode(TRANSPARENT);
	bool x = 0;
	while (1)
	{
		putimage(0, 0, &this->img[2]);
		this->buttonarr[7].drawbutton();
		for (int i = 0; i < 6; i++)
		{
			this->GQChoosebutton[i].drawchoosebutton();
		}
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(this->buttonarr[7], msg))
		{
			EndBatchDraw();
			closegraph();
			x = 1;
			break;
		}
		else if (ifinbutoon(this->GQChoosebutton[0], msg)) 
		{
			this->level = 1;
			EndBatchDraw();
			closegraph();
			break;
		}
	}
	if (x)
	{
		RunChoose();
	}
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
		cout << "当前关卡不存在，请重新输入!" << endl;
		ChooseGame();
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
	//createGameP();
	GameShowmess(g1,0);
}