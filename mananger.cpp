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
#include <conio.h>
#include <graphics.h>
using namespace std;
const clock_t FPS = 1000/60;
int starttime = 0;
int freamtime = 0;
int	GQbuttonbeginlength = 150;
int	GQbuttonbeginwidth = 40;
int ship::getrun() 
{
	return this->run;
}
people*& ship::revisepath()
{
	return this->path;
}
ship::ship(const int& bx,const int&by):Myx(0),Myy(0)
{
	createMypath(bx, by);
}
int& ship::reviseMyx() 
{
	return this->Myx;
}
int& ship::reviseMyy() 
{
	return this->Myy;
}
bool ship::ifpass(people*& p1, const int& num,const int& run)const
{
	for (int i = run - 1; i > num; i--)
	{
		if ((p1[i].returnx() == p1[num].returnx()) && p1[i].returny() == p1[num].returny())
		{
			return false;
		}
	}
	return true;
}
void ship::createMypath(const int&bx,const int& by) 
{
	this->run= rand() % 2 + 6;
	this->path = new people[this->run];
	people p1;
	int xfinal = 0, yfinal = 0;
	xfinal = bx;
	yfinal = by;
	p1.SetPeopleBeginPos(xfinal, yfinal);
	this->path[this->run - 1].SetPeopleBeginPos(xfinal, yfinal);
	bool x = 1;
	int number2 = rand() % 4;
	while (x) 
	{
		for (int i = this->run - 2; i >= 0;)
		{
			switch (number2)
			{
			case 0:
			{
				p1.Movepeople(UP);
				if (this->ifpass(this->path, i, this->run))
				{
					this->path[i] = p1;
					i--;
				}
				else { p1.Movepeople(DOWN); }
				break;
			}
			case 1:
			{
				p1.Movepeople(DOWN);
				if (this->ifpass(this->path, i, this->run))
				{
					this->path[i] = p1;
					i--;
				}
				else { p1.Movepeople(UP); }
				break;
			}
			case 2:
			{
				p1.Movepeople(LEFT);
				
				if (this->ifpass(this->path, i, this->run))
				{
					this->path[i] = p1;
					i--;
				}
				else { p1.Movepeople(RIGHT); }
				break;
			}
			case 3:
			{
				p1.Movepeople(RIGHT);
				
				if (this->ifpass(this->path, i, this->run))
				{
					this->path[i] = p1;
					i--;
				}
				else { p1.Movepeople(LEFT); }
				break;
			}
			}

		}
		if (ifOKPath()) 
		{
			break;
		}
	}
}
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
	sort(p1.begin(), p1.end(), wujinRankcmp);
}
void Mananger::PuTongRank(vector<player>& p1)
{
	sort(p1.begin(), p1.end(), putongRankcmp);
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
vector<gameku>& Mananger::readgamekutxt() 
{
	if (this->gameall.size() != 0)
	{
		this->gameall.resize(0);
	}
	ifstream is("D:/脑力航迹/game.txt");
	if (!is.is_open())
	{
		cout << "文件打开失败" << endl;
		return this->gameall;
	}
	string line;
	int gamenumber = 1;
	while (getline(is, line) && !is.eof())
	{
		gameku g2;
		string  id;
		is >> id;
		int number1;
		if (id != "") {
			g2.name = id;
			is >> number1;
			g2.g1.setrun(number1);
			g2.g1.setzihzhen();
			for (int i = 0; i <number1; i++)
			{
				is >>g2.g1.getp1array()[i].getx() >> g2.g1.getp1array()[i].gety();
			}
			for (int i = 0; i < number1; i++)
			{
				is >> g2.g1.getp2array()[i].getx() >> g2.g1.getp2array()[i].gety();
			}
			this->gameall.resize(gamenumber);
			this->gameall[gamenumber - 1] = g2;
			gamenumber++;
		}
	}
	is.close();
	return this->gameall;
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
	ChangeChoose();
	switch (choose) 
	{
	case 1:
	{
		system("cls");
		ChooseGame();
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
		checkmessageP();
		break;
	}
	case 4:
	{
		system("cls");
		CreateMode();
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
		rankP();
		break;
	}
	case 8:
	{
		system("cls");
		Mycreate();
		break;
	}

	}
}
bool& button::revisebombpass() 
{
	return this->bombpass;
}
void Mananger::Exitgame() 
{
	recordmessagetxt();
	cout << "游戏已退出" << endl;
	exit(0);
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
void Mananger::randomcreatgame(int number1,bool x)
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
		creatrGameChallenge(randomgame);
	}
	else
	{
		randomcreatgame(number1,1);
	}
}
button::button(const int& x, const int& y, const int& width, const int& height, const string& text1):text(text1), x(x), y(y), width(width), height(height), color(YELLOW)
{

}
button::~button() {}
button::button(const int& x, const int& y, const int& width, const int& height, const string& text1, const IMAGE& img) :text(text1), x(x), y(y), width(width), height(height), color(YELLOW)
{
	
}
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
bool& button::revisecreateifpass()
{
	return this->createifpass;
}
bool& button::reviseMycreateifpass()
{
	return this->Mycreateifpass;
}
bool button::returngreenifpass()
{
	return this->greenifpass;
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
button::button() {}
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
bool ship::ifOKPath()
{
	for (int i = 0; i < this->getrun(); i++)
	{
		if (this->path[i].getx() > 25 || this->path[i].getx() < 0 || this->path[i].gety() > 25 || this->path[i].gety() < 0)
		{
			return false;
		}
	}
	return true;
}
void button::drawbuttontxtBig(const int& txtsh, const int& txtsw, const int& txth, const int& txtw, const COLORREF& CL)
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
void button::drawbuttonwithPic(IMAGE* m1)
{
	putimage(this->x, this->y, m1);
	settextstyle(35, 20, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("查看规则")) / 2;
	int vspace = (this->height - textheight("查看规则")) / 2;
	outtextxy(this->x + hspace - 5, this->y + vspace, this->text.c_str());
}
void button::drawbutton()
{
	setfillcolor(this->color);
	settextstyle(35, 20, "宋体");
	settextcolor(BLACK);
	int hspace = (this->width - textwidth("查看规则")) / 2;
	int vspace = (this->height - textheight("查看规则")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x + hspace - 5, this->y + vspace, this->text.c_str());
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
void button::drawgamebutton(const int& i, const COLORREF& textcolor)
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
void button::drawgamerepetebutton()
{
	setfillcolor(this->color);
	settextstyle(10, 10, "宋体");
	int hspace = (this->width - textwidth("1")) / 2;
	int vspace = (this->height - textheight("1")) / 2;
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	settextcolor(BLACK);
	this->revisetext() = to_string(this->repeterun1);
	outtextxy(this->x + hspace, this->y + vspace - 8, this->text.c_str());
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
	outtextxy(this->x + hspace - 3, this->y + vspace - 8, this->text.c_str());
	this->revisetext() = "";
	settextstyle(9, 9, "宋体");
	for (int i = 0; i < this->repeter1.size(); i++)
	{
		this->revisetext() += to_string(this->repeter1[i]);
	}
	settextcolor(DARKGRAY);
	outtextxy(this->x + hspace - 7, this->y + vspace + 3, this->text.c_str());
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
bool& button::reviseifokclick() 
{
	return this->ifokclick;
}
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
	this->ifokclick = b1.ifokclick;
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
void Mananger::PlayerGreatgame()
{
	game playergame;
	int number1 = 0;
	cout << "请输入行动步数（不包括起点）:" << endl;
	cin >> number1;
	playergame.setrun(number1 + 1);
	playergame.setzihzhen();
	cleardevice();
	initgraph(1000, 729);
	setbkmode(TRANSPARENT);
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
	BeginBatchDraw();
	putimage(0, 0, &this->img[3]);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
	}
	EndBatchDraw();
	for (int i = 0; i < playergame.getrun(); i++)
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
					if (j >= 0 && j <= 25 && k >= 0 && k <= 25)
					{
						playergame.getp1array()[i].getx() = k;
						playergame.getp1array()[i].gety() = j;
						b1[k][j].revisecolor() = YELLOW;
						b1[k][j].drawgamebutton(i + 1, BLACK);
						b1[k][j].reviseyellowifpass();
						b1[k][j].returnrepeterun1() = i + 1;
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < playergame.getrun(); i++)
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
					if (j >= 0 && j <= 25 && k >= 0 && k <= 25)
					{
						playergame.getp2array()[i].getx() = k;
						playergame.getp2array()[i].gety() = j;
						b1[k][j].repeter1.push_back(i + 1);
						b1[k][j].revisecolor() = GREEN;
						b1[k][j].revisegreenifpass();
						b1[k][j].returnrepeterun2() = i + 1;
						if (b1[k][j].repeter1.size() == 1 && b1[k][j].returnyellowifpass() != true)
						{
							b1[k][j].drawgamebutton(b1[k][j].repeter1[0], BLACK);
						}
						else
						{

							b1[k][j].drawmyrepete(BLACK);
						}
					}
					break;
				}
			}
		}
	}
	closegraph();
	if (ifOKCreat(playergame))
	{
		PlayercreatrGame(playergame);
	}
	else
	{
		cout << "您创造的游戏因技术有限越界了，请重新创建，两路径坐标差不要太大" << endl;
		PlayerGreatgame();
	}
}
void button::changecolor()
{
	this->color = RED;
}
string& button::revisetext() 
{
	return this->text;
}
int& button::returnbushu() 
{
	return this->bushu;
};
int& button::returnrepeterun1() 
{
	return this->repeterun1;
}
int& button::returnrepeterun2() 
{
	return this->repeterun2;
}
void Mananger::noendchallenge()
{
	int i = 1;
	bool x = 1;
	randomcreatgame(i + 1);
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
	createGameP(g1, 0);
}
void Mananger::loadwindow()
{

	loadimage(&this->img[0], "C:/Users/pcuser/Desktop/实训/开始界面.jpg", 900, 700);
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
	loadimage(&this->img[4], "C:/Users/pcuser/Desktop/实训/芙宁娜胜利.png", 800, 600);
	loadimage(&this->img[5], "C:/Users/pcuser/Desktop/实训/芙宁娜失败.jpg", 800, 600);
	loadimage(&this->img[6], "C:/Users/pcuser/Desktop/实训/提示图片.jpg",50,50);
	loadimage(&this->img[7], "C:/Users/pcuser/Desktop/实训/撤回图片.jpg", 50, 50);
	loadimage(&this->img[8], "C:/Users/pcuser/Desktop/实训/挑战模式.jpg", 400, 600);
	loadimage(&this->img[9], "C:/Users/pcuser/Desktop/实训/创造模式背景.jpg", 600, 600);
	loadimage(&this->img[10], "C:/Users/pcuser/Desktop/实训/自身消息.jpg", 800, 600);
	loadimage(&this->img[11], "C:/Users/pcuser/Desktop/实训/查看信息背景.jpg", 600, 700);
	loadimage(&this->img[12], "C:/Users/pcuser/Desktop/实训/排行榜.jpg", 600, 700);
	loadimage(&this->img[21], "C:/Users/pcuser/Desktop/实训/普通排行图片.jpg", 600, 700);
	loadimage(&this->img[22], "C:/Users/pcuser/Desktop/实训/无尽排行图片.jpg", 600, 700);
	loadimage(&this->img[24], "C:/Users/pcuser/Desktop/实训/单关排行图片.jpg", 600, 700);
	loadimage(&this->img[13], "C:/Users/pcuser/Desktop/实训/创意小船.jpg", 25, 25);
	loadimage(&this->img[14], "C:/Users/pcuser/Desktop/实训/创意炸弹.jpg", 25, 25);
	loadimage(&this->img[15], "C:/Users/pcuser/Desktop/实训/按钮背景.jpg", 200, 50);
	loadimage(&this->img[23], "C:/Users/pcuser/Desktop/实训/创造模式按钮背景.jpg", 200, 50);
	loadimage(&this->img[16], "C:/Users/pcuser/Desktop/实训/返回背景.jpg", 100, 50);
	loadimage(&this->img[17], "C:/Users/pcuser/Desktop/实训/芙宁娜名片.jpg", 800, 600);
	loadimage(&this->img[18], "C:/Users/pcuser/Desktop/实训/选择关卡按钮背景.jpg", 100, 100);
	loadimage(&this->img[19], "C:/Users/pcuser/Desktop/实训/下一关按钮.jpg", 200, 100);
	loadimage(&this->img[20], "C:/Users/pcuser/Desktop/实训/保存按钮图片.jpg", 50, 50);
	loadimage(&this->Move[0], "C:/Users/pcuser/Desktop/实训/创下.jpg", 50, 50);
	loadimage(&this->Move[1], "C:/Users/pcuser/Desktop/实训/创左.jpg", 50, 50);
	loadimage(&this->Move[2], "C:/Users/pcuser/Desktop/实训/创右.jpg", 50, 50);
	loadimage(&this->Move[3], "C:/Users/pcuser/Desktop/实训/创上.jpg", 50, 50);
}
void Mananger::loadChooseGQmenu()
{
	loadimage(&this->img[2], "C:/Users/pcuser/Desktop/实训/关卡选择界面.jpg", 900, 600);


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
	initgraph(900, 700);
	setbkmode(TRANSPARENT);
	while (1) {
		cleardevice();
		putimage(0, 0, &this->img[0]);
		for (int i = 0; i <= 6; i++)
		{
			this->buttonarr[i].drawbuttonwithPic(&this->img[15]);
		}
		this->buttonarr[8].drawbuttonwithPic(&this->img[15]);
		this->buttonarr[9].drawbuttonwithPic(&this->img[15]);
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(this->buttonarr[0], msg))
		{
			this->choose = 1;
			break;
		}
		else if (ifinbutoon(this->buttonarr[1], msg))
		{
			 this->choose = 2; break;
		}
		else if (ifinbutoon(this->buttonarr[2], msg)) {
			 this->choose = 3; break;
		}
		else if (ifinbutoon(this->buttonarr[3], msg)) {
			 this->choose = 4; break;
		}
		else if (ifinbutoon(this->buttonarr[4], msg)) {
			 this->choose = 5; break;
		}
		else if (ifinbutoon(this->buttonarr[5], msg)) {
			 this->choose = 6; break;
		}
		else if (ifinbutoon(this->buttonarr[8], msg)) {
		    this->choose = 7; break;
		}
		else if (ifinbutoon(this->buttonarr[9], msg)) {
			 this->choose = 8; break;
		}
		else if (ifinbutoon(this->buttonarr[6], msg)) {
			 this->choose = 0; break;
		}
	}
	EndBatchDraw();
	closegraph();
}
void Mananger::ShowRule()
{
	cleardevice();
	initgraph(900, 600);
	setbkmode(TRANSPARENT);
	while (1) {
		putimage(0, 0, &this->img[1]);
		putimage(0, 0, &this->img[16]);
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinimage(msg, this->img[16], 0, 0))
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
	putimage(0, 0, &this->img[2]);
	putimage(0, 0, &this->img[7]);
	putimage(575, 100, &this->img[18]);
	putimage(375, 100, &this->img[18]);
	putimage(175, 100, &this->img[18]);
	putimage(175, 250, &this->img[18]);
	putimage(375, 250, &this->img[18]);
	putimage(575, 250, &this->img[18]);
	while (1)
	{
		settextstyle(50, 50, "宋体");
		settextcolor(BLACK);
		outtextxy(200, 125,to_string(1).c_str());
		outtextxy(400, 125, to_string(2).c_str());
		outtextxy(600, 125, to_string(3).c_str());
		outtextxy(200, 275, to_string(4).c_str());
		outtextxy(400, 275, to_string(5).c_str());
		outtextxy(600, 275, to_string(6).c_str());
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinimage(msg,this->img[7],0,0))
		{
			EndBatchDraw();
			closegraph();
			x = 1;
			break;
		}
		else if (ifinimage(msg,this->img[18],175,100))
		{
			this->level = 1;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 375, 100))
		{
			this->level = 2;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 575, 100))
		{
			this->level = 3;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 175, 250))
		{
			this->level = 4;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 375, 250))
		{
			this->level = 5;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 575, 250))
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
button**& Mananger::drawMyCreate(people*&p2, const int& run, button**&b1) 
{
	for (int i = 0; i < run; i++)
	{
		b1[p2[i].returnx()][p2[i].returny()].revisecreateifpass() = true;
	}
	return b1;
}
button**& Mananger::drawOtherPath(people*& p2, const int& run, button**& b1)
{
	for (int i = 0; i < run; i++)
	{
		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = BLUE;
		b1[p2[i].returnx()][p2[i].returny()].drawbutton();
		b1[p2[i].returnx()][p2[i].returny()].revisebombpass() = true;
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
void Mananger::drawcreate(people*& p2, const int& run, button**& b1)
{
	for (int i = 0; i < run; i++)
	{
		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = RED;
		b1[p2[i].returnx()][p2[i].returny()].drawbutton();
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
					if (j >= 0 && j <= 25 && k >= 0 && k <= 25 && b1[k][j].reviseifokclick())
					{
						p3array[i].getx() = k;
						p3array[i].gety() = j;
						b1[k][j].revisecolor() = CYAN;
						b1[k][j].drawgamebutton(i + 1, BLACK,1);
						b1[k][j].reviseifokclick() = false;
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
						b1[p3array[i].returnx()][p3array[i].returny()].reviseifokclick() = true;
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
			for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
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
void Mananger::creatrGameChallenge(game& g1) 
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
			drawYesPChallenge(g1);
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
void Mananger::PlayercreatrGame(game& g1)
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
			drawYesPPlayerCreate(g1);
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
	bool x = 0;
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->img[4]);
		putimage(600, 500, &this->img[19]);
		putimage(0, 0, &this->img[7]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg,this->img[7],0,0))
		{
			closegraph();
			RunChoose();
			x = 1;
		}
		else if(ifinimage(msg,this->img[19],600, 500 ))
		{
			closegraph();
			randomcreatgame(g1.getrun() + 1);
		}

	}

}
void Mananger::drawYesPChallenge(game& g1) 
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	bool x = 0;
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->img[4]);
		putimage(0, 0, &this->img[7]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			closegraph();
			RunChoose();
			x = 1;
		}

	}
}
void Mananger::drawYesPPlayerCreate(game& g1)
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	button b2(250, 50, 300, 50, "保存");
	bool x = 0;
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->img[4]);
		putimage(0, 0, &this->img[7]);
		putimage(0, 50, &this->img[20]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			closegraph();
			RunChoose();
			x = 1;
		}
		else if (ifinimage(msg,this->img[20],0,50))
		{
			closegraph();
			string name;
			cout << "请为游戏取个名字:" << endl;
			cin >> name;
			g1.writegame(name);
			RunChoose();
		}
	}
}
void Mananger::drawYesP(const int& i)
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
	button b2(230, 200, 300, 50, s);
	bool x = 0;
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->img[4]);
		//putimage(600, 500, &this->img[19]);
		putimage(0, 0, &this->img[7]);
		b2.drawbutton();
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			closegraph();
			RunChoose();
			x = 1;
		}

	}

}
void Mananger::drawNoMyCreate() 
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	bool x = 0;
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[5]);
		putimage(0, 0, &this->img[7]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			closegraph();
			x = 1;
			RunChoose();
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
	button b4(280, 20, 200, 50, "再次挑战");
	button b5(280, 220, 200, 50, "查看答案");
	bool x = 0;
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[5]);
		putimage(0, 0, &this->img[7]);
		b4.drawbuttonwithPic(&this->img[15]);
		b5.drawbuttonwithPic(&this->img[15]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg,this->img[7],0,0))
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
				putimage(0, 0, &this->img[7]);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinimage(msg,this->img[7],0,0))
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
	button b2(250, 540, 300, 50, s);
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
	button b4(280, 20, 200, 50, "再次挑战");
	button b5(280, 220, 200, 50, "查看答案");
	bool x = 0;
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[5]);
		putimage(0, 0, &this->img[7]);
		b4.drawbuttonwithPic(&this->img[15]);
		b5.drawbuttonwithPic(&this->img[15]);
		b2.drawbutton();
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[7], 0, 0))
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
			
			bool m = 1;
			while (m) {
				BeginBatchDraw();
				putimage(0, 0, &this->img[3]);
				putimage(0, 0, &this->img[7]);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinimage(msg,this->img[7],0,0))
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
void Mananger::PTrankP()
{
	cleardevice();
	initgraph(600, 700);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &this->img[21]);
	putimage(0, 0, &this->img[7]);
	string text;
	settextcolor(BLACK);
	settextstyle(15, 15, "宋体");
	for (int i = 0; i<min(20,rank.size()); i++)
	{
		text = to_string(i + 1);
		outtextxy(50, 100 + i * 25, text.c_str());
		text = rank[i].GetName();
		outtextxy(150, 100 + i * 25, text.c_str());
		text = to_string(rank[i].returnscoreall());
		outtextxy(320, 100 + i * 25, text.c_str());
		text = to_string(int(rank[i].returntimeall()));
		outtextxy(475, 100 + i * 25, text.c_str());
	}
	while (1)
	{
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			EndBatchDraw();
			closegraph();
			rankP();
			break;
		}
	}
}
void Mananger::rankP()
{
	cleardevice();
	initgraph(600, 700);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &this->img[11]);
	putimage(0, 0, &this->img[7]);
	button b1(200, 250, 200, 50, "普通排行");
	button b2(200, 300, 200, 50, "无尽排行");
	button b3(200, 350, 200, 50, "单关排行");
	b1.drawbuttonwithPic(&this->img[15]);
	b2.drawbuttonwithPic(&this->img[15]);
	b3.drawbuttonwithPic(&this->img[15]);
	while (1)
	{
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(b1, msg))
		{
			EndBatchDraw();
			PuTongRank(readplayermessagetxt());
			PTrankP();
			break;
		}
		else if (ifinbutoon(b2, msg))
		{
			EndBatchDraw();
			wujinRank(readplayermessagetxt());
			WJrankP();
			break;
		}
		else if (ifinbutoon(b3, msg))
		{
			EndBatchDraw();
			wujinRank(readplayermessagetxt());
			DGrankP();
			break;
		}
		else if (ifinimage(msg, this->img[7], 0, 0))
		{
			EndBatchDraw();
			closegraph();
			RunChoose();
			break;
		}
	}
	closegraph();
}
void Mananger::Mycreate()
{

	game randomgame;
	int number1 = 6;
	randomgame.setrun(number1);
	randomgame.setzihzhen();
	while (1) {
		int xfinal = 0, yfinal = 0;
		xfinal = rand() % 10 + 8;
		yfinal = rand() % 10 + 8;
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
			break;
		}

	}
	people* Pall = new people[2 * number1 - 1];
	for (int i = 0; i < number1; i++)
	{
		Pall[i].getx() = randomgame.getp1array()[i].returnx();
		Pall[i].gety() = randomgame.getp1array()[i].returny();
	}
	for (int i = number1; i < 2 * number1 - 1; i++)
	{
		Pall[i].getx() = randomgame.getp2array()[2 * number1 - 2 - i].returnx();
		Pall[i].gety() = randomgame.getp2array()[2 * number1 - 2 - i].returny();
	}
	MyCreateGameP(randomgame, Pall);
	cleardevice();
	initgraph(1000, 729);
	setbkmode(TRANSPARENT);
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
	ship s1(Pall[3].returnx(), Pall[3].returny());
	ship s2(Pall[8].returnx(), Pall[8].returny());
	BeginBatchDraw();
	putimage(0, 0, &this->img[3]);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++) { this->GQbutton[i][j].drawGQbutton(); }
	}
	drawMyCreate(Pall, 2 * number1 - 1, b1);
	drawOtherPath(s1.revisepath(), s1.getrun(), b1);
	drawOtherPath(s2.revisepath(), s2.getrun(), b1);
	int shipx = b1[Pall[0].returnx()][Pall[0].returny()].returnx();
	int shipy = b1[Pall[0].returnx()][Pall[0].returny()].returny();
	putimage(800, 500, &this->Move[0]);
	putimage(750, 500, &this->Move[1]);
	putimage(850, 500, &this->Move[2]);
	putimage(800, 450, &this->Move[3]);
	EndBatchDraw();
	int k = Pall[0].returnx();
	int j = Pall[0].returny();
	int s1Px = b1[Pall[3].returnx()][Pall[3].returny()].returnx();
	int s1Py = b1[Pall[3].returnx()][Pall[3].returny()].returny();
	int s1x = (s1Px - GQbuttonbeginlength) / 25;
	int s1y = (s1Py - GQbuttonbeginwidth) / 25;
	int s1index = s1.getrun() - 1;
	bool s1AD = 0;
	int s2Px = b1[Pall[8].returnx()][Pall[8].returny()].returnx();
	int s2Py = b1[Pall[8].returnx()][Pall[8].returny()].returny();
	int s2x = (s2Px - GQbuttonbeginlength) / 25;
	int s2y = (s2Py - GQbuttonbeginwidth) / 25;
	int s2index = s2.getrun() - 1;
	bool s2AD = 0;
	while (1)
	{
		starttime = clock();
		putimage(shipx, shipy, &this->img[13]);
		putimage(s1Px, s1Py, &this->img[14]);
		putimage(s2Px, s2Py, &this->img[14]);
		b1[k][j].reviseMycreateifpass() = true;
		if (b1[k][j].reviseMycreateifpass() != b1[k][j].revisecreateifpass() || (s1Px == shipx && s1Py == shipy) || (s2Px == shipx && s2Py == shipy))
		{

			drawNoMyCreate();
			break;
		}
		bool x = 1;
		for (int k = 0; k < 25; k++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (b1[k][j].reviseMycreateifpass() != b1[k][j].revisecreateifpass())
				{
					x = 0;
				}
			}
		}
		if (x && k == Pall[2 * number1 - 2].returnx() && j == Pall[2 * number1 - 2].returny())
		{
			drawYesPChallenge(randomgame);
			break;
		}
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				freamtime = clock() - starttime;
				if (ifinimage(msg, this->Move[0], 800, 500))
				{
					BeginBatchDraw();
					if (b1[k][j].revisecreateifpass()) { b1[k][j].drawbutton(); }
					else { this->GQbutton[k][j].drawGQbutton(); }
					b1[s1x][s1y].drawbutton();
					if (!s1AD)
					{
						if (s1index == 0)
						{
							s1index = 1;
							s1AD = 1;
						}
						else s1index -= 1;
					}
					else
					{
						if (s1index == s1.getrun() - 1)
						{
							s1index -= 1;
							s1AD = 0;
						}
						else { s1index += 1; }
					}
					s1x = s1.revisepath()[s1index].returnx();
					s1y = s1.revisepath()[s1index].returny();
					s1Px = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returnx();
					s1Py = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returny();
					b1[s2x][s2y].drawbutton();
					if (!s2AD)
					{
						if (s2index == 0)
						{
							s2index = 1;
							s2AD = 1;
						}
						else s2index -= 1;
					}
					else
					{
						if (s2index == s2.getrun() - 1)
						{
							s2index -= 1;
							s2AD = 0;
						}
						else { s2index += 1; }
					}
					s2x = s2.revisepath()[s2index].returnx();
					s2y = s2.revisepath()[s2index].returny();
					s2Px = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returnx();
					s2Py = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returny();
					putimage(s2Px, s2Py, &this->img[14]);
					j += 1;
					shipy += 25;
					putimage(shipx, shipy, &this->img[13]);
					putimage(s1Px, s1Py, &this->img[14]);
					EndBatchDraw();
				}
				else if (ifinimage(msg, this->Move[1], 750, 500))
				{
					BeginBatchDraw();
					if (b1[k][j].revisecreateifpass()) { b1[k][j].drawbutton(); }
					else { this->GQbutton[k][j].drawGQbutton(); }
					b1[s1x][s1y].drawbutton();
					if (!s1AD)
					{
						if (s1index == 0)
						{
							s1index = 1;
							s1AD = 1;
						}
						else s1index -= 1;
					}
					else
					{
						if (s1index == s1.getrun() - 1)
						{
							s1index -= 1;
							s1AD = 0;
						}
						else { s1index += 1; }
					}
					s1x = s1.revisepath()[s1index].returnx();
					s1y = s1.revisepath()[s1index].returny();
					s1Px = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returnx();
					s1Py = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returny();
					b1[s2x][s2y].drawbutton();
					if (!s2AD)
					{
						if (s2index == 0)
						{
							s2index = 1;
							s2AD = 1;
						}
						else s2index -= 1;
					}
					else
					{
						if (s2index == s2.getrun() - 1)
						{
							s2index -= 1;
							s2AD = 0;
						}
						else { s2index += 1; }
					}
					s2x = s2.revisepath()[s2index].returnx();
					s2y = s2.revisepath()[s2index].returny();
					s2Px = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returnx();
					s2Py = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returny();
					putimage(s2Px, s2Py, &this->img[14]);
					k -= 1;
					shipx -= 25;
					putimage(shipx, shipy, &this->img[13]);
					putimage(s1Px, s1Py, &this->img[14]);
					EndBatchDraw();
				}
				else if (ifinimage(msg, this->Move[2], 850, 500))
				{
					BeginBatchDraw();
					if (b1[k][j].revisecreateifpass()) { b1[k][j].drawbutton(); }
					else { this->GQbutton[k][j].drawGQbutton(); }
					b1[s1x][s1y].drawbutton();
					if (!s1AD)
					{
						if (s1index == 0)
						{
							s1index = 1;
							s1AD = 1;
						}
						else s1index -= 1;
					}
					else
					{
						if (s1index == s1.getrun() - 1)
						{
							s1index -= 1;
							s1AD = 0;
						}
						else { s1index += 1; }
					}
					s1x = s1.revisepath()[s1index].returnx();
					s1y = s1.revisepath()[s1index].returny();
					s1Px = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returnx();
					s1Py = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returny();
					b1[s2x][s2y].drawbutton();
					if (!s2AD)
					{
						if (s2index == 0)
						{
							s2index = 1;
							s2AD = 1;
						}
						else s2index -= 1;
					}
					else
					{
						if (s2index == s2.getrun() - 1)
						{
							s2index -= 1;
							s2AD = 0;
						}
						else { s2index += 1; }
					}
					s2x = s2.revisepath()[s2index].returnx();
					s2y = s2.revisepath()[s2index].returny();
					s2Px = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returnx();
					s2Py = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returny();
					putimage(s2Px, s2Py, &this->img[14]);
					k += 1;
					shipx += 25;
					putimage(shipx, shipy, &this->img[13]);
					putimage(s1Px, s1Py, &this->img[14]);
					EndBatchDraw();
				}
				else if (ifinimage(msg, this->Move[3], 800, 450))
				{
					BeginBatchDraw();
					if (b1[k][j].revisecreateifpass()) { b1[k][j].drawbutton(); }
					else { this->GQbutton[k][j].drawGQbutton(); }
					b1[s1x][s1y].drawbutton();
					if (!s1AD)
					{
						if (s1index == 0)
						{
							s1index = 1;
							s1AD = 1;
						}
						else s1index -= 1;
					}
					else
					{
						if (s1index == s1.getrun() - 1)
						{
							s1index -= 1;
							s1AD = 0;
						}
						else { s1index += 1; }
					}
					s1x = s1.revisepath()[s1index].returnx();
					s1y = s1.revisepath()[s1index].returny();
					s1Px = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returnx();
					s1Py = b1[s1.revisepath()[s1index].returnx()][s1.revisepath()[s1index].returny()].returny();
					b1[s2x][s2y].drawbutton();
					if (!s2AD)
					{
						if (s2index == 0)
						{
							s2index = 1;
							s2AD = 1;
						}
						else s2index -= 1;
					}
					else
					{
						if (s2index == s2.getrun() - 1)
						{
							s2index -= 1;
							s2AD = 0;
						}
						else { s2index += 1; }
					}
					s2x = s2.revisepath()[s2index].returnx();
					s2y = s2.revisepath()[s2index].returny();
					s2Px = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returnx();
					s2Py = b1[s2.revisepath()[s2index].returnx()][s2.revisepath()[s2index].returny()].returny();
					putimage(s2Px, s2Py, &this->img[14]);
					j -= 1;
					shipy -= 25;
					putimage(shipx, shipy, &this->img[13]);
					putimage(s1Px, s1Py, &this->img[14]);
					EndBatchDraw();
				}
				if (freamtime > 0)
				{
					Sleep(FPS - freamtime);
				}
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		delete[]b1[i];
	}
	delete[] b1;
	setbutton();

}
void Mananger::createmiddle(people*& p1, game& g1)
{
	cleardevice();
	initgraph(1000, 729);
	setbkmode(TRANSPARENT);
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
	putimage(0, 0, &this->img[3]);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++) { this->GQbutton[i][j].drawGQbutton(); }
	}
	drawanswerroad(p1, 11, b1);
	button con(800, 679, 200, 50, "下一步");
	con.drawbuttonwithPic(&this->img[15]);
	while (1)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (ifinbutoon(con, msg))
				{
					break;
				}
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		delete[]b1[i];
	}
	delete[] b1;
	closegraph();
}
void Mananger::MyCreateGameP(game& g1, people*& p1)
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
			createmiddle(p1, g1);
			break;
		}
		else
		{
			closegraph();
			drawNoP(g1);
			break;
		}
	}
}
void Mananger::CreateMode() 
{
	cleardevice();
	initgraph(600, 600);
	setbkmode(TRANSPARENT);
	button b1(200, 200, 200, 50, "自建关卡");
	button b2(200, 250, 200, 50, "创意总站");
	putimage(0, 0, &this->img[9]);
	putimage(0, 0, &this->img[7]);
	b1.drawbuttonwithPic(&this->img[23]);
	b2.drawbuttonwithPic(&this->img[23]);
	while (1) {
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(b1, msg))
		{
			EndBatchDraw();
			PlayerGreatgame();
			break;
		}
		else if (ifinbutoon(b2, msg))
		{
			EndBatchDraw();
			readgamekutxt();
			cout << "请输入想要玩的关卡的名字：" << endl;
			cout << "已有自建关卡:" << "  ";
			for (int i = 0; i < this->gameall.size(); i++)
			{
				cout << gameall[i].name << " ";
			}
			cout << endl;
			bool x = 1;
			while (x)
			{
				string name1;
				cin >> name1;
				for (int i = 0; i < gameall.size(); i++)
				{
					if (gameall[i].name == name1)
					{
						PlayercreatrGame(gameall[i].g1);
						x = 0;
						break;
					}
				}
				cout << "名字不正确，请再次输入" << endl;
			}

			break;
		}
		else if (ifinimage(msg, this->img[7], 0, 0))
		{
			EndBatchDraw();
			closegraph();
			RunChoose();
			break;
		}
	}
	closegraph();
}
void Mananger::WJrankP()
{
	cleardevice();
	initgraph(600, 700);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &this->img[22]);
	putimage(0, 0, &this->img[7]);
	string text;
	settextstyle(15, 15, "宋体");
	settextcolor(BLACK);
	for (int i = 0; i < min(20,rank.size()); i++)
	{
		text = to_string(i + 1);
		outtextxy(120, 125 + i * 25, text.c_str());
		text = rank[i].GetName();
		outtextxy(250, 125 + i * 25, text.c_str());
		text = to_string(rank[i].getnoendscore());
		outtextxy(450, 125 + i * 25, text.c_str());
	}
	while (1)
	{
		ExMessage msg = getmousemessage();
		
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			
			closegraph();
			rankP();
			break;
		}
	}
}
void Mananger::DGrankP()
{
	cleardevice();
	initgraph(600, 700);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &this->img[24]);
	putimage(0, 0, &this->img[7]);
	string text;
	settextcolor(BLACK);
	settextstyle(15, 15, "宋体");
	for (int i = 0; i < 6; i++)
	{
		sort(this->rank.begin(), this->rank.end(), [i](const player& p1, const player& p2)
			{
				if (p1.returnGetscore()[i] == p2.returnGetscore()[i])return p1.returngettime()[i] < p2.returngettime()[i];
				else return p1.returnGetscore()[i] > p2.returnGetscore()[i];
			}
		);
		text = to_string(i + 1);
		outtextxy(100, 125 + i * 25, text.c_str());
		text = rank[0].GetName();
		outtextxy(275, 125 + i * 25, text.c_str());
		text = to_string(rank[0].Getscore()[i]);
		outtextxy(400, 125 + i * 25, text.c_str());
		text = to_string(int(rank[0].gettime()[i]));
		outtextxy(500, 125 + i * 25, text.c_str());
	}
	while (1)
	{
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			EndBatchDraw();
			closegraph();
			rankP();
			break;
		}
	}
}
void Mananger::checkmessageP()
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &this->img[10]);
	settextstyle(40, 40, "宋体");
	settextcolor(BLUE);
	string text;
	text = this->p1.GetName();
	outtextxy(150, 150, text.c_str());
	settextstyle(30, 30, "宋体");
	for (int i = 0; i < 10; i++)
	{
		outtextxy(160 + i * 60, 220, to_string(i + 1).c_str());
	}
	for (int i = 0; i < this->p1.Getaccuracy().size(); i++)
	{
		int num = this->p1.Getaccuracy()[i] * 100;
		text = to_string(num) + "%";
		outtextxy(160 + i * 60, 300, text.c_str());
	}
	for (int i = 0; i < this->p1.Getscore().size(); i++)
	{
		text = to_string(this->p1.Getscore()[i]);
		outtextxy(160 + i * 60, 378, text.c_str());
	}
	text = to_string(this->p1.getnoendscore());
	settextstyle(40, 40, "宋体");
	outtextxy(300, 467, text.c_str());
	putimage(0, 0, &this->img[7]);
	while (1)
	{
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[7], 0, 0))
		{
			closegraph();
			RunChoose();
			break;
		}
	}
}
void Mananger::challengegame()
{
	cleardevice();
	initgraph(400, 600);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &this->img[8]);
	button b0(150, 120, 100, 50, "简单");
	button b1(150, 170, 100, 50, "普通");
	button b2(150, 220, 100, 50, "困难");
	button b3(150, 270, 100, 50, "史诗");
	button b4(150, 320, 100, 50, "传说");
	COLORREF c1 = RGB(242, 217, 151);
	b0.revisecolor() = c1;
	b1.revisecolor() = c1;
	b2.revisecolor() = c1;
	b3.revisecolor() = c1;
	b4.revisecolor() = c1;
	b4.drawbutton1();
	b1.drawbutton1();
	b2.drawbutton1();
	b3.drawbutton1();
	b4.drawbutton1();
	int number;
	putimage(0, 0, &this->img[7]);
	while (1) {
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinbutoon(b0, msg))
		{
			EndBatchDraw();
			number = 1;
			break;
		}
		else if (ifinbutoon(b1, msg))
		{
			EndBatchDraw();
			number = 2;
			break;
		}
		else if (ifinbutoon(b2, msg)) {
			EndBatchDraw();
			number = 3;
			break;
		}
		else if (ifinbutoon(b3, msg)) {
			EndBatchDraw();
			number = 4;
			break;
		}
		else if (ifinbutoon(b4, msg)) {
			EndBatchDraw();
			number = 5;
			break;
		}
		else if (ifinimage(msg, this->img[7], 0, 0))
		{
			EndBatchDraw();
			RunChoose();
			break;
		}
	}
	closegraph();
	switch (number)
	{
	case 1:
	{
		randomcreatgame(6, 1);
		break;
	}
	case 2:
	{
		randomcreatgame(9, 1);
		break;
	}
	case 3:
	{

		randomcreatgame(12, 1);
		break;
	}
	case 4:
	{
		randomcreatgame(18, 1);
		break;
	}
	case 5:
	{
		randomcreatgame(25, 1);
		break;
	}
	default:
	{
		cout << "输入不符合要求，请重新输入:" << endl;
		challengegame();
	}
	}

}
Mananger::Mananger()
{
	button b0(320, 175, 200, 50, "开始游戏");
	button b1(320, 225, 200, 50, "查看规则");
	button b2(320, 275, 200, 50, "查看信息");
	button b3(320, 325, 200, 50, "创造模式");
	button b4(320, 375, 200, 50, "挑战模式");
	button b5(320, 425, 200, 50, "无尽模式");
	button b6(320, 475, 200, 50, "退出游戏");
	button b8(320, 525, 200, 50, " 排行榜");
	button b9(320, 575, 200, 50, "创意模式");
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
	this->buttonarr[9] = b9;
	loadwindow();
	loadrule();
	loadChooseGQmenu();
	loadGamebk();
	loadgameP();
	setbutton();

}