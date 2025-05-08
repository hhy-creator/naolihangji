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
#include <algorithm>
using namespace std;
int	GQbuttonbeginlength = 100;
int	GQbuttonbeginwidth = 30;
bool wujinRankcmp(const player& p3, const player& p2)
{
	return p3.getnoend() > p2.getnoend();
}
bool putongRankcmp( player& p3,  player& p2)
{
	if (p3.returnscoreall()==p2.returnscoreall())return p3.returntimeall() < p2.returntimeall();
	else return p3.returnscoreall() > p2.returnscoreall();
}
void Mananger::wujinRank(vector<player>& p1)
{
	cout << "***************无尽挑战排行榜*************" << endl;
	sort(p1.begin(), p1.end(), wujinRankcmp);
	for (int i = 0; i < p1.size(); i++)
	{
		cout << i + 1 << " " << p1[i].GetName() << " " << p1[i].getnoend()<<endl;
	}
}
void Mananger::recordmessagetxt() 
{
	ofstream ofs("D:/脑力航迹/playermessgae.txt", ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	this->p1.serializetxt(ofs);
	ofs.close();
}
void Mananger::PuTongRank(vector<player>& p1)
{
	cout << "***************普通挑战排行榜*************" << endl;
	sort(p1.begin(), p1.end(), putongRankcmp);
	for (int i = 0; i < 5; i++) 
	{
		cout << i + 1 << " " << p1[i].GetName() << " " << p1[i].returnscoreall() << " " << p1[i].returntimeall() << endl;
	}
}
vector<player>& Mananger::readplayermessagetxt(){
	if (this->rank.size() != 0) 
	{
		this->rank.resize(0);
	}
	ifstream is("D:/脑力航迹/playermessgae.txt");
	if (!is.is_open())
	{
		cout << "文件打开失败" << endl;
		return this->rank;
	}
	string line;
	while (getline(is, line) && !is.eof())
	{
		player p1(0);
		string  id;
		is >> id;
		if (id != "") {
			p1.GetName() = id;
			for (int i = 0; i < p1.gettime().size(); i++)
			{
				is >> p1.gettime()[i];
			}
			for (int i = 0; i < p1.Getaccuracy().size(); i++)
			{
				is >> p1.Getaccuracy()[i];
			}
			for (int i = 0; i < p1.Getright().size(); i++)
			{
				is >> p1.Getright()[i];
			}
			for (int i = 0; i < p1.Getwrong().size(); i++)
			{
				is >> p1.Getwrong()[i];
			}


			for (int i = 0; i < p1.Getscore().size(); i++)
			{
				is >> p1.Getscore()[i];
			}

			is >> p1.getnoendscore();

			this->rank.push_back(p1);
		}
	}
	is.close();
	return this->rank;
}
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
	while (ifs) {
		p1.deserialize(ifs);
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
	case 7: 
	{
		system("cls");

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
	recordmessagetxt();
	wujinRank(readplayermessagetxt());
	PuTongRank(readplayermessagetxt());
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
	g2.getp1().SetPeopleBeginPos(10,8);
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
	g2.getp2().SetPeopleBeginPos(13, 13);
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
	createGameP(g2,1);
}
void Mananger::creatgame3()
{
	game g3;
	g3.setrun(16);
	g3.setzihzhen();
	g3.getp1().SetPeopleBeginPos(20, 12);
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
	g3.getp2().SetPeopleBeginPos(7, 9);
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
	createGameP(g3,2);
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
	createGameP(g4,3);
}
void Mananger::creatgame5()
{
	cout << "耿直的他" << endl;
	game g5;
	g5.setrun(21);
	g5.setzihzhen();
	g5.getp1().SetPeopleBeginPos(8,14);
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
	g5.getp2().SetPeopleBeginPos(10, 0);
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
	createGameP(g5,4);
}
void Mananger::randomcreatgame() 
{
	game randomgame;
	int number1 = rand() % 7 + 10;
	randomgame.setrun(number1);
	randomgame.setzihzhen();
	int xfinal = 0, yfinal = 0;
	xfinal = rand() % 10 + 1;
	yfinal = rand() % 10 + 1;
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
	if (ifOKCreat(randomgame))
	{
		createGameP(randomgame);
	}
	else
	{
		randomcreatgame();
	}
}
void Mananger::randomcreatgame(int number1)
{

	game randomgame;
	randomgame.setrun(number1);
	randomgame.setzihzhen();
	int xfinal = 0, yfinal = 0;
	xfinal = rand() % 5 + 9;
	yfinal = rand() % 5 + 9;
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
	if (ifOKCreat(randomgame)) 
	{
		createGameP(randomgame);
	}
	else 
	{
		randomcreatgame(number1);
	}
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
	randomcreatgame(i+1);
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
button& button::operator=(const button& b1)
{
	this->color = b1.color;
	this->yellowifpass = b1.yellowifpass;
	this->y = b1.y;
	this->x = b1.x;
	this-> repeterun1=b1.repeterun1;
	this-> repeterun2=b1.repeterun2;
	this-> width=b1.width;
	this-> height=b1.height;
	this-> text=b1.text;
	this-> passnumber = b1.passnumber;
	this-> greenifpass = b1.greenifpass;
	this-> redifpass = b1.redifpass;
	this->repeter1 = b1.repeter1;
	this->bushu = b1.bushu;
	this->drawnumber = b1.drawnumber;
	return *this;
}
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
		pb.drawbutton();
		return 1;

	}
	return 0;
}
bool Mananger::ifinimage(ExMessage m, IMAGE&pb,const int& wb,const int& hb) 
{
	if (wb < m.x && wb + pb.getwidth() > m.x && hb< m.y && hb + pb.getheight() > m.y)
	{
		return true;

	}
	return false;
}
void button::changecolor()
{
	this->color = RED;
}
void button::drawbuttontxtBig(const int& txtsh, const int& txtsw, const int& txth, const int& txtw, const COLORREF&CL)
{
	setfillcolor(this->color);
	settextstyle(txtsh, txtsw, "宋体");
	settextcolor(CL);
	int hspace = (this->width - txtw) / 2;
	int vspace = (this->height - txth) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace, this->y + vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void button::drawbutton()
{
	setfillcolor(this->color);
	settextstyle(35, 20, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("查看规则")) / 2;
	int vspace = (this->height - textheight("查看规则")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x+hspace-5, this->y+vspace, this->text.c_str());
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
string& button::revisetext() 
{
	return this->text;
}
int& button::returnbushu() 
{
	return this->bushu;
};
void button::drawgamebutton(const int& i, const COLORREF& textcolor, const bool& x)
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	settextcolor(textcolor);
	this->text = to_string(i);
	int hspace = (this->width - textwidth("10")) / 2;
	int vspace = (this->height - textheight("10")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace, this->y + vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void button::drawgamebutton(const int &i, const COLORREF&textcolor)
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	settextcolor(textcolor);
	this->text = "";
	this->text = to_string(i);
	int hspace = (this->width - textwidth("10")) / 2;
	int vspace = (this->height - textheight("10")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace, this->y + vspace, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	this->bushu = i;
}
int& button::returnrepeterun1() 
{
	return this->repeterun1;
}
int& button::returnrepeterun2() 
{
	return this->repeterun2;
}
void button::drawgamerepetebutton()
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	int hspace = (this->width - textwidth("1")) / 2;
	int vspace = (this->height - textheight("1")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	settextcolor(BLACK);
	this->revisetext() = to_string(this->repeterun1);
	outtextxy(this->x + hspace , this->y + vspace - 8, this->text.c_str());
	this->revisetext() = "";
	for (int i = 0; i < this->repeter1.size(); i++)
	{
		this->revisetext() += to_string(this->repeter1[i]);
	}
	settextcolor(DARKGRAY);
	outtextxy(this->x + hspace, this->y + vspace + 3, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
void button::drawgamerepetebutton1() 
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	int hspace = (this->width - textwidth("1")) / 2;
	int vspace = (this->height - textheight("1")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
		settextcolor(BLACK);
	this->revisetext() = to_string(this->repeterun1);
	outtextxy(this->x + hspace-3, this->y + vspace-8, this->text.c_str());
	this->revisetext() = "";
	settextstyle(9, 9, "宋体");
	for (int i = 0; i < this->repeter1.size(); i++)
	{
		this->revisetext() += to_string(this->repeter1[i]);
	}
	settextcolor(DARKGRAY);
	outtextxy(this->x + hspace-7, this->y + vspace+3, this->text.c_str());
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
void Mananger::loadgameP() 
{
	loadimage(&this->img[4], "C:/Users/pcuser/Desktop/实训/芙宁娜胜利.jpg", 400, 400);
	loadimage(&this->img[5], "C:/Users/pcuser/Desktop/实训/芙宁娜失败.jpg", 400, 400);
	loadimage(&this->img[6], "C:/Users/pcuser/Desktop/实训/提示图片.jpg",50,50);
	loadimage(&this->img[7], "C:/Users/pcuser/Desktop/实训/撤回图片.jpg", 50, 50);
}
void Mananger::loadChooseGQmenu()
{
	loadimage(&this->img[2], "C:/Users/pcuser/Desktop/实训/关卡选择界面.jpg", 900, 600);


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
	button b8(320, 470, 200, 50, "关卡排行");
	button b7(0, 0, 150, 75, "返回");
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
	this->buttonarr[8] = b8;
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
	loadgameP();
	setbutton();

}
void Mananger::setbutton() 
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			button b0(i * 25 + GQbuttonbeginlength, j * 25 + GQbuttonbeginwidth, 25, 25, "");
			this->GQbutton[i][j] = b0;
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
		this->buttonarr[7].drawbutton1();
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
		else if (ifinbutoon(this->GQChoosebutton[1], msg)) 
		{
			this->level = 2;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinbutoon(this->GQChoosebutton[2], msg))
		{
			this->level = 3;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinbutoon(this->GQChoosebutton[3], msg))
		{
			this->level = 4;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinbutoon(this->GQChoosebutton[4], msg))
		{
			this->level = 5;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinbutoon(this->GQChoosebutton[5], msg))
		{
			this->level = 6;
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
	g1.getp1().SetPeopleBeginPos(10, 14);
	g1.getp1array()[0] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[1] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[2] = g1.getp1();
	g1.getp1().Movepeople(UP);
	g1.getp1array()[3] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[4] = g1.getp1();
	g1.getp2().SetPeopleBeginPos(15, 11);
	g1.getp2array()[0] = g1.getp2();
	g1.getp2().Movepeople(LEFT);
	g1.getp2array()[1] = g1.getp2();
	g1.getp2().Movepeople(LEFT);
	g1.getp2array()[2] = g1.getp2();
	g1.getp2().Movepeople(DOWN);
	g1.getp2array()[3] = g1.getp2();
	g1.getp2().Movepeople(DOWN);
	g1.getp2array()[4] = g1.getp2();
	createGameP(g1,0);
}
void button::revisegreenifpass() 
{
	this->greenifpass = true;
}
void button::reviseyellowifpass() 
{
	this->yellowifpass = true;
}
void button::reviseredifpass() 
{
	this->redifpass = true;
}
button**& Mananger::drawMyroad(people*&p2, const int& run, button**&b1)
{
	for (int i = 0; i < run; i++) 
	{
		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = YELLOW;
		b1[p2[i].returnx()][p2[i].returny()].drawgamebutton(i + 1, BLACK);
		b1[p2[i].returnx()][p2[i].returny()].reviseyellowifpass();
		b1[p2[i].returnx()][p2[i].returny()].returnrepeterun1() = i+1;
	}
	return b1;
}
button**& Mananger::drawYourroad(people*& p2, const int& run, button**& b1)
{
	for (int i = 0; i < run; i++)
	{
		b1[p2[i].returnx()][p2[i].returny()].repeter1.push_back(i+ 1);
	}
	for (int i = 0; i < run; i++)
	{
		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = GREEN;
		if (b1[p2[i].returnx()][p2[i].returny()].repeter1.size() == 1 && b1[p2[i].returnx()][p2[i].returny()].returnyellowifpass() != true)
		{
			b1[p2[i].returnx()][p2[i].returny()].drawgamebutton(b1[p2[i].returnx()][p2[i].returny()].repeter1[0], BLACK);
		}
		else
		{

				b1[p2[i].returnx()][p2[i].returny()].drawmyrepete(BLACK);
		}
		b1[p2[i].returnx()][p2[i].returny()].revisegreenifpass();
		b1[p2[i].returnx()][p2[i].returny()].returnrepeterun2() = i + 1;
	}
	return b1;
}
void button::drawmyrepete( const COLORREF& textcolor)
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	settextcolor(textcolor);
	this->text = "";
	for (int i = 0; i < repeter1.size()/2; i++)
	{
		this->text += to_string(repeter1[i]);
	}
	int hspace = (this->width - textwidth("10")) / 2;
	int vspace = (this->height - textheight("10")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace-1, this->y + vspace-6, this->text.c_str());
	this->text = "";
	for (int i = repeter1.size() / 2; i < repeter1.size(); i++)
	{
		this->text += to_string(repeter1[i]);
	}
	outtextxy(this->x + hspace-3 , this->y + vspace - -3, this->text.c_str());
	setlinecolor(BLACK);
	rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}
bool button::returnyellowifpass() 
{
	return this->yellowifpass;
}
void Mananger::drawanswerroad(people*& p2, const int& run, button**& b1)
{
	for (int i = 0; i < run; i++)
	{
		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = RED;
		b1[p2[i].returnx()][p2[i].returny()].drawgamebutton(i+1,BLACK);
		b1[p2[i].returnx()][p2[i].returny()].reviseredifpass();
	}
}
button**& Mananger::drawrepetebutton(button**& b1)
{
	for (int i = 0; i < 25; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			if (b1[i][j].ifrepete()) 
			{
				b1[i][j].revisecolor() = BROWN;
				if (b1[i][j].repeter1.size() == 1) { b1[i][j].drawgamerepetebutton(); }
				else { b1[i][j].drawgamerepetebutton1(); }
			}
		}
	}
	return b1;
}
bool Mananger::clickanswer( game&g1, button**& b1)
{

	putimage(0, 679, &this->img[6]);
	putimage(50, 679, &this->img[7]);
	people* p3array = new people[g1.getrun()];
	button** b2 = new button * [25];
	for (int i = 0; i < 25; i++)
	{
		b2[i] = new button[25];
	
	}
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			b2[i][j] = b1[i][j];
	
		}
	}

	for (int i = 0; i < g1.getrun();) 
	{
		ExMessage msg;
		while (true) 
		{
			if (peekmessage(&msg, EX_MOUSE)) 
			{
				if (msg.message == WM_LBUTTONDOWN) 
				{
					int k = (msg.x - GQbuttonbeginlength) / 25;
					int j = (msg.y - GQbuttonbeginwidth) / 25;
					if (j >= 0 && j <= 25 && k >= 0 && k <= 25 && b1[k][j].revisecolor() != CYAN) 
					{
						p3array[i].getx() = k;
						p3array[i].gety() = j;
						b1[k][j].revisecolor() = CYAN;
						b1[k][j].drawgamebutton(i + 1, BLACK,1);

						i++;
						break;
					}
					else if (ifinimage(msg, this->img[6], 0, 679))
					{
						b1[g1.getp2array()[i].returnx()][g1.getp2array()[i].returny()].revisecolor() = CYAN;
						b1[g1.getp2array()[i].returnx()][g1.getp2array()[i].returny()].drawgamebutton(i + 1, BLACK,1);
						p3array[i].getx() = g1.getp2array()[i].returnx();
						p3array[i].gety() = g1.getp2array()[i].returny();
						i++;
						break;
					}
					else if (ifinimage(msg, this->img[7], 50, 679)&&i>=1) 
					{
						i--;
						if (b2[p3array[i].returnx()][p3array[i].returny()].returnyellowifpass() == true && b2[p3array[i].returnx()][p3array[i].returny()].returngreenifpass() == false)
						{
							b2[p3array[i].returnx()][p3array[i].returny()].drawgamebutton(b2[p3array[i].returnx()][p3array[i].returny()].returnrepeterun1(), BLACK, 1);
						}
						else if (b2[p3array[i].returnx()][p3array[i].returny()].returngreenifpass() == true && b2[p3array[i].returnx()][p3array[i].returny()].returnyellowifpass() == false)
						{
							if (b2[p3array[i].returnx()][p3array[i].returny()].repeter1.size() == 1) 
							{
								b2[p3array[i].returnx()][p3array[i].returny()].drawgamebutton(b2[p3array[i].returnx()][p3array[i].returny()].repeter1[0], BLACK, 1);
							}
							else { b2[p3array[i].returnx()][p3array[i].returny()].drawmyrepete(BLACK); }
						}
						else if(b2[p3array[i].returnx()][p3array[i].returny()].returngreenifpass()==true&& b2[p3array[i].returnx()][p3array[i].returny()].returnyellowifpass()==true)
						{
							if (b2[p3array[i].returnx()][p3array[i].returny()].repeter1.size() == 1) { b2[p3array[i].returnx()][p3array[i].returny()].drawgamerepetebutton(); }
							else { b2[p3array[i].returnx()][p3array[i ].returny()].drawgamerepetebutton1(); }
						}
						else
						{
							this->GQbutton[p3array[i].returnx()][p3array[i].returny()].drawGQbutton();
						}
						b1[p3array[i].returnx()][p3array[i].returny()] = b2[p3array[i].returnx()][p3array[i].returny()];
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < g1.getrun(); i++)
	{
		if (g1.getp2array()[i].returnx() != p3array[i].returnx() || g1.getp2array()[i].returny() != p3array[i].returny())
		{
			system("cls");
			for (int i = 0; i < 25; i++)
			{
				delete[]b2[i];
			}
			delete[]b2;
			delete[]p3array;

			return false;
		}
	}
	system("cls");
	delete[]p3array;
	for (int i = 0; i < 25; i++) 
	{
		delete[]b2[i];
	}
	delete[]b2;
	return true;

}
bool button::ifrepete() 
{
	if (this->greenifpass == true && this->yellowifpass == true) { return true; }
	else { return false; }
}
COLORREF& button::revisecolor() 
{
	return this->color;
}
void Mananger::gameprogress() 
{

}
void Mananger::GameShowmess(game& g1, const int& i)
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
bool button::returngreenifpass() 
{
	return this->greenifpass;
}
void Mananger::createGameP(game& g1, const int& i)
{
	cleardevice();
	initgraph(1000, 729);
	setbkmode(TRANSPARENT);
	bool x = 1;
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	button** b1 = new button * [25];
	for (int i = 0; i < 25; i++)
	{
		b1[i] = new button[25];
	}
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			b1[i][j] = this->GQbutton[i][j];
		}
	}
	while (x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[3]);
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++) {b1[i][j].drawGQbutton(); }
		}
		drawMyroad(g1.getp1array(), g1.getrun(), b1);
		drawYourroad(g1.getp2relative(), g1.getrun(), b1);
		drawrepetebutton(b1);
		EndBatchDraw();
		int gamestarttime = 0;
		int gameduration = 0;
		gamestarttime = clock();
		bool a = clickanswer(g1, b1);
		for (int i = 0; i < 25; i++) 
		{
			delete[]b1[i];
		}
		delete[] b1;
		gameduration = clock() - gamestarttime;
		setbutton();
		int secondall = gameduration / 1000;
		int seconds = secondall % 60;
		int minute = secondall / 60;
		this->p1.gettime()[i] = secondall;
		if (a)
		{
			x = 0;
			closegraph();
			drawYesP(i);
			bool a = 1;
			getplayer().CreatScore(getplayer().Getscore(), getlevel(), a, this->p1.gettime(), g1.getrun());
			getplayer().AddRight(getplayer().Getright(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			ChooseGame();
			break;
		}
		else
		{
			closegraph();
			getplayer().AddWrong(getplayer().Getwrong(), getlevel());
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			bool a = 0;
			getplayer().CreatScore(getplayer().Getscore(), getlevel(), a, this->p1.gettime(), g1.getrun());
			drawNoP(g1, i);
			break;
		}
	}
}
void Mananger::createGameP(game& g1)
{
	cleardevice();
	initgraph(1000, 729);
	setbkmode(TRANSPARENT);
	bool x = 1;
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	button** b1 = new button * [25];
	for (int i = 0; i < 25; i++)
	{
		b1[i] = new button[25];
	}
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			b1[i][j] = this->GQbutton[i][j];
		}
	}
	while (x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[3]);
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++) { this->GQbutton[i][j].drawGQbutton(); }
		}
		b1 = drawMyroad(g1.getp1array(), g1.getrun(), b1);
		b1 = drawYourroad(g1.getp2relative(), g1.getrun(), b1);
		b1 = drawrepetebutton(b1);
		EndBatchDraw();
		bool a = clickanswer(g1, b1);
		for (int i = 0; i < 25; i++)
		{
			delete[]b1[i];
		}
		delete[] b1;
		setbutton();

		if (a)
		{
			x = 0;
			closegraph();
			this->p1.getnoendscore() += 100;
			drawYesP(g1);
			bool a = 1;
			break;
		}
		else
		{
			closegraph();
			bool a = 0;
			drawNoP(g1);
			break;
		}
	}
}
void Mananger::drawYesP(game& g1)
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	button b1(250, 0, 300, 50, "VICTORY");
	button b2(250, 50, 300, 50, "下一关");
	button b3(0, 0, 75, 75, "返回");
	bool x = 0;
	while (!x)
	{
		BeginBatchDraw();
		putimage(200, 200, &this->img[4]);
		b1.drawbutton();
		b2.drawbutton();
		b3.drawbuttontxtBig(10, 10, 10, 10, GREEN);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinbutoon(b3, msg))
		{
			closegraph();
			RunChoose();
			x = 1;
		}
		else if(ifinbutoon(b2, msg))
		{
			closegraph();
			randomcreatgame(g1.getrun() + 1);
		}

	}

}
void Mananger::drawNoP(game& g1) 
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	button b1(250, 0, 300, 50, "DEFEAT");
	button b3(0, 0, 75, 75, "返回");
	button b4(250, 50, 300, 50, "再次挑战");
	button b5(250, 100, 300, 50, "查看答案");
	bool x = 0;
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(200, 200, &this->img[5]);
		b1.drawbutton();
		b3.drawbuttontxtBig(10, 10, 10, 10, GREEN);
		b4.drawbutton();
		b5.drawbutton();
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinbutoon(b3, msg))
		{
			closegraph();
			x = 1;
			RunChoose();
		}
		else if (ifinbutoon(b4, msg))
		{
			closegraph();
			x = 1;
			createGameP(g1);
		}
		else if (ifinbutoon(b5, msg))
		{
			closegraph();
			cleardevice();
			initgraph(1000, 729);
			setbkmode(TRANSPARENT);
			button b3(0, 0, 75, 75, "返回");
			button** b1 = new button * [25];
			for (int i = 0; i < 25; i++)
			{
				b1[i] = new button[25];
			}
			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					b1[i][j] = this->GQbutton[i][j];
				}
			}
			bool m = 1;
			while (m) {
				BeginBatchDraw();
				putimage(0, 0, &this->img[3]);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				b3.drawbuttontxtBig(10, 10, 10, 10, GREEN);
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinbutoon(b3, msg))
				{
					closegraph();
					for (int i = 0; i < 25; i++)
					{
						delete[]b1[i];
					}
					delete[] b1;
					m = 0;
					createGameP(g1);
				}
			}
		}
	}
}
void Mananger::drawYesP(const int&i) 
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	string s = "用时：";
	int timeall = p1.gettime()[i];
	if (timeall < 10)
	{
		s += to_string(0);
		s += to_string(timeall / 60);
	}
	else 
	{
		s += to_string(timeall / 60);
	}
	s += ":";
	if (timeall % 60 < 10)
	{
		s += to_string(0);
		s += to_string(timeall % 60);
	}
	else
	{
		s += to_string(timeall % 60);
	}
	button b1(250, 0, 300, 50, "VICTORY");
	button b2 (250, 50, 300, 50, s);
	button b3(0, 0, 75, 75, "返回");
	bool x = 0;
	while (!x) 
	{
		BeginBatchDraw();
		putimage(200, 200, &this->img[4]);
		b1.drawbutton();
		b2.drawbutton();
		b3.drawbuttontxtBig(10,10,10,10,GREEN);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinbutoon(b3, msg)) 
		{
			closegraph();
			x = 1;
		}
		
	}

}
void Mananger::drawNoP(game& g1, const int& i)
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	string s = "用时：";
	int timeall = p1.gettime()[i];
	if (timeall < 10)
	{
		s += to_string(0);
		s += to_string(timeall / 60);
	}
	else
	{
		s += to_string(timeall / 60);
	}
	s += ":";
	if (timeall % 60 < 10)
	{
		s += to_string(0);
		s += to_string(timeall % 60);
	}
	else
	{
		s += to_string(timeall % 60);
	}
	button b11(250, 0, 300, 50, "DEFEAT");
	button b2(250, 50, 300, 50, s);
	button b3(0, 0, 75, 75, "返回");
	button b4(250, 100, 300, 50, "再次挑战");
	button b5(250, 150, 300, 50, "查看答案");
	button** b1 = new button * [25];
	for (int i = 0; i < 25; i++)
	{
		b1[i] = new button[25];
	}
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			b1[i][j] = this->GQbutton[i][j];
		}
	}
	bool x = 0;
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(200, 200, &this->img[5]);
		b11.drawbutton();
		b2.drawbutton();
		b3.drawbuttontxtBig(10, 10, 10, 10, GREEN);
		b4.drawbutton();
		b5.drawbutton();
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinbutoon(b3, msg))
		{
			closegraph();
			x = 1;
			ChooseGame();
		}
		else if (ifinbutoon(b4, msg)) 
		{
			closegraph();
			x = 1;
			switch (i) 
			{
			case 0: { creatgame1(); break; }
			case 1: { creatgame2(); break; }
			case 2: { creatgame3(); break; }
			case 3: { creatgame4(); break; }
			case 4: { creatgame5(); break; }
			}
		}
		else if (ifinbutoon(b5, msg)) 
		{
			closegraph();
			cleardevice();
			initgraph(1000, 729);
			setbkmode(TRANSPARENT);
			button b3(0, 0, 75, 75, "返回");
			bool m = 1;
			while (m) {
				BeginBatchDraw();
				putimage(0, 0, &this->img[3]);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				b3.drawbuttontxtBig(10, 10, 10, 10, GREEN);
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinbutoon(b3, msg)) 
				{
					closegraph();
					for (int i = 0; i < 25; i++)
					{
						delete[]b1[i];
					}
					delete[] b1;
					m = 0;
					ChooseGame();
				}
			}
		}
	}
}
bool Mananger::ifOKCreat(const game& g1) 
{
	for (int i = 0; i < g1.getrun(); i++) 
	{
		if (g1.returnp1arr()[i].getx() > 25 || g1.returnp1arr()[i].getx() < 0 || g1.returnp1arr()[i].gety() > 25 || g1.returnp1arr()[i].gety() < 0) 
		{
			return false;
		}
		if (g1.returnp2arr()[i].getx() > 25 || g1.returnp2arr()[i].getx() < 0 || g1.returnp2arr()[i].gety() > 25 || g1.returnp2arr()[i].gety() < 0)
		{
			return false;
		}
		if (g1.returnp2rearr()[i].getx() > 25 || g1.returnp2rearr()[i].getx() < 0 || g1.returnp2rearr()[i].gety() > 25 || g1.returnp2rearr()[i].gety() < 0)
		{
			return false;
		}
	}
	return true;
}