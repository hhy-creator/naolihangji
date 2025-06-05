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
#include <graphics.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
const clock_t FPS = 1000/60;
int starttime = 0;
int freamtime = 0;
int	GQbuttonbeginlength = 170;
int	GQbuttonbeginwidth = 60;
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
	while (x) 
	{
		int number2 = rand() % 4;
		for (int i = this->run - 2; i >= 0;)
		{
			number2 = rand() % 4;
			/*if (i == 1) 
			{
				switch (number2)
				{
				case 0:
				{
					number2 = 3;
					break;
				}
				case 1:
				{
					number2 = 2;
					break;
				}
				case 2:
				{
					number2 = 1;

					break;
				}
				case 3:
				{
					number2 = 0;
					break;
				}
				}
			}
			if ( i == change)
			{
				switch (number2)
				{
				case 0:
				{
					number2 = 2;
					break;
				}
				case 1:
				{
					number2 = 3;
					break;
				}
				case 2:
				{
					number2 = 0;

					break;
				}
				case 3:
				{
					number2 = 1;
					break;
				}
				}
			}*/
			switch (number2)
			{
			case 0:
			{
				p1.Movepeople(UP);
				this->path[i] = p1;
				if (this->ifpass(this->path, i, this->run))
				{
					i--;
				}
				else { p1.Movepeople(DOWN); }
				break;
			}
			case 1:
			{
				p1.Movepeople(DOWN);
				this->path[i] = p1;
				if (this->ifpass(this->path, i, this->run))
				{
			
					i--;
				}
				else { p1.Movepeople(UP); }
				break;
			}
			case 2:
			{
				p1.Movepeople(LEFT);
				this->path[i] = p1;
				if (this->ifpass(this->path, i, this->run))
				{
				
					i--;
				}
				else { p1.Movepeople(RIGHT); }
				break;
			}
			case 3:
			{
				p1.Movepeople(RIGHT);
				this->path[i] = p1;
				if (this->ifpass(this->path, i, this->run))
				{
				
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
	ofstream ofs("playermessage.txt",ios::out);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	bool ifnoadd = 0;
	for (int i = 0; i < this->rank.size(); i++)
	{
		if (this->p1 == rank[i])
		{
			this->rank[i] =this-> p1;
			ifnoadd = 1;
		}
	}
	if (!ifnoadd) 
	{
		this->rank.push_back(this->p1);
	}
	for (int i = 0; i < this->rank.size(); i++) 
	{
		this->rank[i].serializetxt(ofs);
	}
	ofs.close();
}
void Mananger::dlOrZc() 
{
	readplayermessagetxt();
	for (int i = 0; i < this->rank.size(); i++) 
	{
		if (this->p1 == rank[i]) 
		{
			this->p1.gettime() = rank[i].gettime();
			this->p1.getnoendscore() = rank[i].getnoendscore();
			this->p1.Getaccuracy() = rank[i].Getaccuracy();
			this->p1.Getscore() = rank[i].Getscore();
			this->p1.Getright() = rank[i].Getright();
			this->p1.Getwrong() = rank[i].Getwrong();
			this->p1.revisetimeall() = rank[i].returntimeall();
			this->p1.revisescoreall() = rank[i].returnscoreall();
			break;
		}
	}
}
vector<player>& Mananger::readplayermessagetxt(){
	if (this->rank.size() != 0) 
	{
		this->rank.resize(0);
	}
	ifstream is("playermessage.txt");
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
			string passw;
			is >> passw;
			p1.revisepassword() = passw;
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
	ifstream is("game.txt");
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
			this->gameall.push_back(g2);
		}
	}
	is.close();
	return this->gameall;
}
Mananger::~Mananger() 
{
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
	cout << "**********************" << endl;
	cout << "******游戏已退出******" << endl;
	cout << "**********************" << endl;
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
bool& button::reviseCreateModeifpass() 
{
	return this->CreateModeIfpass;
}
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
	settextstyle(txtsh, txtsw, "黑体");
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
	settextstyle(35, 20, "黑体");
	settextcolor(RGB(252, 169, 97));
	int hspace = (this->width - textwidth("查看规则")) / 2;
	int vspace = (this->height - textheight("查看规则")) / 2;
	outtextxy(this->x + hspace - 5, this->y + vspace, this->text.c_str());
}
void button::drawbutton()
{
	setfillcolor(this->color);
	settextstyle(35, 20, "黑体");
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
	settextstyle(20, 20, "黑体");
	settextcolor(RGB(202,177,180));
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
		PlaySound(TEXT("脑力航迹/实训/按钮点击音效.wav"), NULL, SND_FILENAME | SND_ASYNC);
		pb.drawbutton();
		return 1;

	}
	return 0;
}
bool Mananger::ifinimage(ExMessage m, IMAGE&pb,const int& wb,const int& hb) 
{
	if (wb < m.x && wb + pb.getwidth() > m.x && hb< m.y && hb + pb.getheight() > m.y)
	{
		PlaySound(TEXT("脑力航迹/实训/按钮点击音效.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return true;

	}
	return false;
}
void Mananger::PlayerGreatgame()
{
	game playergame;
	int number1 = 0;
	char buffer[256] = { '0'};
	buffer[0] = '0';
	buffer[2] = '0';

	while (1) {
		initgraph(640, 480);
		setbkmode(TRANSPARENT);
		IMAGE i1;
		loadimage(&i1, "脑力航迹/实训/获取输入背景.jpg", 640, 480);
		putimage(0, 0, &i1);
		InputBox(buffer, 256, _T("请输入步数大小（不包括起点）:"), _T("欢迎创建游戏"), _T("10"));
		if ((buffer[1] >= '0' && buffer[1] <= '9' && buffer[0] >= '0' && buffer[0] <= '9')|| (buffer[1] == '\0' && buffer[0] >= '0' && buffer[0] <= '9'))
		{
			break;
		}
	}
	if (buffer[1] > '0'||(buffer[0] <= '9'&&buffer[0]>'0'&&buffer[1]=='0'))
	{
		for (int i = 0; i < 2; i++)
		{
			number1 *= 10;
			number1 += buffer[i] - 48;
		}
	}
	else 
	{
		number1 = buffer[0] - 48;
	}
	closegraph();

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
				int k = (msg.x - GQbuttonbeginlength) / 25;
				int j = (msg.y - GQbuttonbeginwidth) / 25;
				if (msg.message == WM_LBUTTONDOWN&&!b1[k][j].reviseCreateModeifpass())
				{

					if (j >= 0 && j <= 25 && k >= 0 && k <= 25)
					{
						playergame.getp1array()[i].getx() = k;
						playergame.getp1array()[i].gety() = j;
						if (i == 0||( i!=0&& (abs(k - playergame.getp1array()[i - 1].getx()) + abs(j - playergame.getp1array()[i - 1].gety()) == 1))) {
							b1[k][j].reviseCreateModeifpass() = 1;
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
	}
	bool a[25][25]{ 0 };
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
					if (j >= 0 && j <= 25 && k >= 0 && k <= 25&&!a[k][j])
					{
						playergame.getp2array()[i].getx() = k;
						playergame.getp2array()[i].gety() = j;
						if (i == 0 || (i != 0 && (abs(k - playergame.getp2array()[i - 1].getx()) + abs(j - playergame.getp2array()[i - 1].gety()) == 1))) {
							a[k][j] = 1;
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
							break;
						}
					}
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
void Mananger::loadgameP() 
{
	loadimage(&this->img[0], "脑力航迹/实训/开始界面.jpg", 900, 700);
	loadimage(&this->img[1], "脑力航迹/实训/规则介绍.jpg", 900, 600);
	loadimage(&this->img[3], "脑力航迹/实训/关卡背景图.jpg", 1000, 729);
	loadimage(&this->img[2], "脑力航迹/实训/关卡选择界面.jpg", 900, 600);
	loadimage(&this->img[4], "脑力航迹/实训/芙宁娜胜利.png", 800, 600);
	loadimage(&this->img[5], "脑力航迹/实训/芙宁娜失败.jpg", 800, 600);
	loadimage(&this->img[6], "脑力航迹/实训/提示图片.jpg",50,50);
	loadimage(&this->img[7], "脑力航迹/实训/撤回图片.jpg", 50, 50);
	loadimage(&this->img[8], "脑力航迹/实训/挑战模式.jpg", 400, 600);
	loadimage(&this->img[9], "脑力航迹/实训/创造模式背景.jpg", 600, 600);
	loadimage(&this->img[10], "脑力航迹/实训/自身消息.jpg", 800, 600);
	loadimage(&this->img[11], "脑力航迹/实训/查看信息背景.jpg", 600, 700);
	loadimage(&this->img[12], "脑力航迹/实训/排行榜.jpg", 600, 700);
	loadimage(&this->img[21], "脑力航迹/实训/普通排行图片.jpg", 600, 700);
	loadimage(&this->img[22], "脑力航迹/实训/无尽排行图片.jpg", 600, 700);
	loadimage(&this->img[24], "脑力航迹/实训/单关排行图片.jpg", 600, 700);
	loadimage(&this->img[25], "脑力航迹/实训/失败背景.jpg", 800, 600);
	loadimage(&this->img[13], "脑力航迹/实训/创意小船.jpg", 25, 25);
	loadimage(&this->img[14], "脑力航迹/实训/创意炸弹.jpg", 25, 25);
	loadimage(&this->img[15], "脑力航迹/实训/按钮背景.jpg", 200, 50);
	loadimage(&this->img[23], "脑力航迹/实训/创造模式按钮背景.jpg", 200, 50);
	loadimage(&this->img[16], "脑力航迹/实训/返回背景.jpg", 100, 50);
	loadimage(&this->img[17], "脑力航迹/实训/芙宁娜名片.jpg", 800, 600);
	loadimage(&this->img[18], "脑力航迹/实训/选择关卡按钮背景.jpg", 100, 100);
	loadimage(&this->img[19], "脑力航迹/实训/下一关按钮.jpg", 200, 100);
	loadimage(&this->img[20], "脑力航迹/实训/保存按钮图片.jpg", 50, 50);
	loadimage(&this->img[26], "脑力航迹/实训/返回主界面图片.jpg", 80, 80);
	loadimage(&this->img[27], "脑力航迹/实训/返回图片.jpg", 100, 100);
	loadimage(&this->img[28], "脑力航迹/实训/计时器.jpg", 70, 70);
	loadimage(&this->img[29], "脑力航迹/实训/查看答案.jpg", 50, 50);
	loadimage(&this->Move[0], "脑力航迹/实训/创下.jpg", 50, 50);
	loadimage(&this->Move[1], "脑力航迹/实训/创左.jpg", 50, 50);
	loadimage(&this->Move[2], "脑力航迹/实训/创右.jpg", 50, 50);
	loadimage(&this->Move[3], "脑力航迹/实训/创上.jpg", 50, 50);
	loadimage(&this->ymimg[0], "脑力航迹/实训/撤回图片掩码.jpg", 50, 50);
	loadimage(&this->ymimg[1], "脑力航迹/实训/芙宁娜胜利ym.png", 800, 600);
	loadimage(&this->ymimg[2], "脑力航迹/实训/下一关按钮掩码.jpg", 200, 100);
	loadimage(&this->ymimg[3], "脑力航迹/实训/保存按钮图片掩码.jpg", 50, 50);
	loadimage(&this->ymimg[4], "脑力航迹/实训/芙宁娜失败掩码.jpg", 800, 600);
	loadimage(&this->ymimg[5], "脑力航迹/实训/返回主界面图片掩码图.jpg", 80, 80);
	loadimage(&this->ymimg[6], "脑力航迹/实训/返回图片掩码.jpg", 100, 100);
	loadimage(&this->ymimg[7], "脑力航迹/实训/计时器掩码.jpg", 70, 70);
	loadimage(&this->ymimg[8], "脑力航迹/实训/创上掩码.jpg", 50, 50);
	loadimage(&this->ymimg[9], "脑力航迹/实训/创下掩码.jpg", 50, 50);
	loadimage(&this->ymimg[10], "脑力航迹/实训/创左掩码.jpg", 50, 50);
	loadimage(&this->ymimg[11], "脑力航迹/实训/创右掩码.jpg", 50, 50);
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
	PlaySound(TEXT("脑力航迹/实训/流水.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
	putimage(830, -10, &this->ymimg[5], NOTSRCERASE);
	putimage(830, -10, &this->img[26],SRCINVERT);
	putimage(575, 100, &this->img[18]);
	putimage(375, 100, &this->img[18]);
	putimage(175, 100, &this->img[18]);
	putimage(175, 250, &this->img[18]);
	putimage(375, 250, &this->img[18]);
	putimage(575, 250, &this->img[18]);
	putimage(175, 400, &this->img[18]);
	putimage(375, 400, &this->img[18]);
	putimage(575, 400, &this->img[18]);
	while (1)
	{
		settextstyle(50, 50, "黑体",0,0,FW_BOLD,false,false,false);
		settextcolor(BROWN);
		outtextxy(200, 125,to_string(1).c_str());
		outtextxy(400, 125, to_string(2).c_str());
		outtextxy(600, 125, to_string(3).c_str());
		outtextxy(200, 275, to_string(4).c_str());
		outtextxy(400, 275, to_string(5).c_str());
		outtextxy(600, 275, to_string(6).c_str());
		outtextxy(200, 425, to_string(7).c_str());
		outtextxy(400, 425, to_string(8).c_str());
		outtextxy(600, 425, to_string(9).c_str());
		ExMessage msg = getmousemessage();
		BeginBatchDraw();
		if (ifinimage(msg,this->img[26],830,-10))
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
		else if (ifinimage(msg, this->img[18], 175, 400))
		{
			this->level = 7;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 375, 400))
		{
			this->level = 8;
			EndBatchDraw();
			closegraph();
			break;
		}
		else if (ifinimage(msg, this->img[18], 575, 400))
		{
			this->level = 9;
			EndBatchDraw();
			closegraph();
			break;
		}
	}
	if (x)
	{
		RunChoose();
	}
	readgamekutxt();
	switch (getlevel())
	{
	case 1:
	{
		getfromgameku("关卡1", 0);
		break;
	}
	case 2:
	{
		getfromgameku("关卡2", 1);
		break;
	}
	case 3:
	{
		getfromgameku("关卡3", 2);
		break;
	}
	case 4:
	{
		getfromgameku("关卡4", 3);
		break;
	}
	case 5:
	{
		getfromgameku("关卡5", 4);
		break;
	}
	case 6:
	{
		getfromgameku("关卡6", 5);
		break;
	}
	case 7:
	{
		getfromgameku("关卡7", 6);
		break;
	}
	case 8:
	{
		getfromgameku("关卡8", 7);
		break;
	}
	case 9:
	{
		getfromgameku("关卡9", 8);
		break;
	}
	default:
		ChooseGame();
	}
}
void Mananger::getfromgameku(const string& name,const int& GQnumber) 
{
	for (int i = 0; i < this->gameall.size(); i++)
	{
			if (name == this->gameall[i].name)
			{
				createGameP(this->gameall[i].g1, GQnumber);
				break;
			}

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
void Mananger::drawanswerroad(people*&p2, const int& run, button**& b1, bool& x) 
{
	BeginBatchDraw();
	b1[p2[0].returnx()][p2[0].returny()].revisecolor() = RED;
	b1[p2[0].returnx()][p2[0].returny()].drawgamebutton(1, BLACK);
	for (int i = 1; i < run; i++)
	{

		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = RED;
		if (i == run - 1) {
			b1[p2[i].returnx()][p2[i].returny()].drawgamebutton(i + 1, BLACK);
		}
		else { b1[p2[i].returnx()][p2[i].returny()].drawbutton(); }
		b1[p2[i].returnx()][p2[i].returny()].reviseredifpass();
	}
	EndBatchDraw();
}
void Mananger::drawanswerroad(people*& p2, const int& run, button**& b1)
{
	for (int i = 0; i < run; i++)
	{

		b1[p2[i].returnx()][p2[i].returny()].revisecolor() = RED;
		b1[p2[i].returnx()][p2[i].returny()].drawgamebutton(i + 1, BLACK);
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
	putimage(50, 679, &this->ymimg[0], NOTSRCERASE);
	putimage(50, 679, &this->img[7],SRCINVERT);
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
			getplayer().CreatScore(getplayer().Getscore(), getlevel()-1, a, this->p1.gettime(), g1.getrun());
			getplayer().AddRight(getplayer().Getright(), getlevel()-1);
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			closegraph();
			recordmessagetxt();
			drawYesP(i);
			break;
		}
		else
		{
			closegraph();
			getplayer().AddWrong(getplayer().Getwrong(), getlevel()-1);
			getplayer().CalAccuracy(getplayer().Getright(), getplayer().Getwrong(), getplayer().Getaccuracy());
			getplayer().CreatScore(getplayer().Getscore(), getlevel()-1, a, this->p1.gettime(), g1.getrun());
			recordmessagetxt();
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
			this->p1.getnoendscore() =max((g1.getrun()-1)* 100,this->p1.getnoendscore());
			recordmessagetxt();
			drawYesP(g1);
			bool a = 1;
			break;
		}
		else
		{
			closegraph();
			bool a = 0;
			recordmessagetxt();
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
			drawNoPlayergame(g1);
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
			drawNoPlayergame(g1);
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
	PlaySound(TEXT("脑力航迹/实训/胜利.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->ymimg[1], NOTSRCERASE);
		putimage(0, 0, &this->img[4],SRCINVERT);
		putimage(600, 500, &this->ymimg[2], NOTSRCERASE);
		putimage(600, 500, &this->img[19],SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27],SRCINVERT);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg,this->img[27],0,0))
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
	PlaySound(TEXT("脑力航迹/实训/胜利.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->ymimg[1], NOTSRCERASE);
		putimage(0, 0, &this->img[4],SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27],SRCINVERT);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[27], 0, 0))
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
	bool x = 0;
	PlaySound(TEXT("脑力航迹/实训/胜利.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->ymimg[1], NOTSRCERASE);
		putimage(0, 0, &this->img[4], SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27], SRCINVERT);
		putimage(0, 550, &this->ymimg[3], NOTSRCERASE);
		putimage(0, 550, &this->img[20],SRCINVERT);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[27], 0, 0))
		{
			closegraph();
			RunChoose();
			x = 1;
		}
		else if (ifinimage(msg,this->img[20],0,550))
		{
			closegraph();
			readgamekutxt();
			string name = "";
			char buffer[256] = { 0 };
			while (1) {
				initgraph(640, 480);
				setbkmode(TRANSPARENT);
				IMAGE i1;
				loadimage(&i1, "脑力航迹/实训/获取输入背景.jpg", 640, 480);
				putimage(0, 0, &i1);
				InputBox(buffer, 256, _T("请给关卡起名(重名会要求重新输入):"), _T("创建关卡中..."), _T("******"));
				int i = 0;
				while (buffer[i] != '\0') {
					name += buffer[i];
					i++;
				}
				bool x = 1;
				for (int i = 0; i < this->gameall.size(); i++) {
					if (name == this->gameall[i].name) 
					{
						x = 0;
					}
				}
				if (x) 
				{
					closegraph();
					break;
				}
				closegraph();
			}
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
	string s = "";
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

	bool x = 0;
	PlaySound(TEXT("脑力航迹/实训/胜利.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		BeginBatchDraw();
		putimage(0, 0, &this->img[17]);
		putimage(0, 0, &this->ymimg[1], NOTSRCERASE);
		putimage(0, 0, &this->img[4], SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27], SRCINVERT);
		putimage(230, 180, &this->ymimg[7], NOTSRCERASE);
		putimage(230, 180, &this->img[28], SRCINVERT);
		settextstyle(30, 30, "黑体");
		settextcolor(RGB(250, 240, 202));
		outtextxy(310, 210, s.c_str());
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[27], 0, 0))
		{
			closegraph();
			ChooseGame();
			x = 1;
		}

	}

}
void Mananger::drawNoMyCreate(game& g1, int& number1, people*& Pall)
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	bool x = 0;
	PlaySound(TEXT("脑力航迹/实训/失败.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[25]);
		putimage(0, 0, &this->ymimg[4], NOTSRCERASE);
		putimage(0, 0, &this->img[5],SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27], SRCINVERT);
		putimage(0, 550, &this->ymimg[0], NOTSRCERASE);
		putimage(0, 550, &this->img[7], SRCINVERT);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[27], 0, 0))
		{
			closegraph();
			x = 1;
			RunChoose();
		}
		else if (ifinimage( msg,this->img[7],0,550))
		{
			closegraph();
			x = 1;
			createchallenge(g1, number1,  Pall);
		}
	}
}
void Mananger::drawNoPlayergame(game& g1) 
{
	cleardevice();
	initgraph(800, 600);
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	cleardevice();
	button b4(280, 520, 200, 50, "再次挑战");
	bool x = 0;
	PlaySound(TEXT("脑力航迹/实训/失败.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[25]);
		putimage(0, 0, &this->ymimg[4], NOTSRCERASE);
		putimage(0, 0, &this->img[5], SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27], SRCINVERT);
		putimage(0, 550, &this->img[29]);
		b4.drawbuttonwithPic(&this->img[15]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[27], 0, 0))
		{
			closegraph();
			x = 1;
			CreateMode();
		}
		else if (ifinbutoon(b4, msg))
		{
			closegraph();
			x = 1;
			PlayercreatrGame(g1);
		}
		else if (ifinimage(msg, this->img[29], 0, 550))
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
				putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
				putimage(0, 0, &this->img[27], SRCINVERT);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinimage(msg, this->img[27], 0, 0))
				{
					closegraph();
					for (int i = 0; i < 25; i++)
					{
						delete[]b1[i];
					}
					delete[] b1;
					m = 0;
					PlayercreatrGame(g1);
				}
			}
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
	button b4(280, 520, 200, 50, "再次挑战");
	bool x = 0;
	PlaySound(TEXT("脑力航迹/实训/失败.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[25]);
		putimage(0, 0, &this->ymimg[4], NOTSRCERASE);
		putimage(0, 0, &this->img[5], SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27], SRCINVERT);
		putimage(0, 550, &this->img[29]);
		b4.drawbuttonwithPic(&this->img[15]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg,this->img[27],0,0))
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
		else if (ifinimage(msg,this->img[29],0,550))
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
				putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
				putimage(0, 0, &this->img[27], SRCINVERT);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinimage(msg,this->img[27],0,0))
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
	string s = "";
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
	button b4(280, 520, 200, 50, "再次挑战");
	bool x = 0;
	PlaySound(TEXT("脑力航迹/实训/失败.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!x)
	{
		int number = 0;
		BeginBatchDraw();
		putimage(0, 0, &this->img[25]);
		putimage(0, 0, &this->ymimg[4], NOTSRCERASE);
		putimage(0, 0, &this->img[5], SRCINVERT);
		putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
		putimage(0, 0, &this->img[27], SRCINVERT);
		putimage(250, 227, &this->ymimg[7], NOTSRCERASE);
		putimage(250, 227, &this->img[28], SRCINVERT);
		putimage(0, 550, &this->img[29]);
		settextstyle(30, 30, "黑体");
		settextcolor(RGB(250, 240, 202));
		outtextxy(324, 250, s.c_str());
		b4.drawbuttonwithPic(&this->img[15]);
		EndBatchDraw();
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[27], 0, 0))
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
			case 0: { getfromgameku("关卡1",i); break; }
			case 1: { getfromgameku("关卡2", i); break; }
			case 2: { getfromgameku("关卡3", i); break; }
			case 3: { getfromgameku("关卡4", i); break; }
			case 4: { getfromgameku("关卡5", i); break; }
			case 5: { getfromgameku("关卡6", i); break; }
			case 6: { getfromgameku("关卡7", i); break; }
			case 7: { getfromgameku("关卡8", i); break; }
			case 8: { getfromgameku("关卡9", i); break; }
			}
		}
		else if (ifinimage(msg,this->img[29],0,550))
		{
			closegraph();
			cleardevice();
			initgraph(1000, 729);
			setbkmode(TRANSPARENT);
			
			bool m = 1;
			while (m) {
				BeginBatchDraw();
				putimage(0, 0, &this->img[3]);
				putimage(0, 0, &this->ymimg[6], NOTSRCERASE);
				putimage(0, 0, &this->img[27], SRCINVERT);
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 25; j++) { b1[i][j].drawGQbutton(); }
				}
				drawanswerroad(g1.getp2array(), g1.getrun(), b1);
				
				EndBatchDraw();
				ExMessage msg = getmousemessage();
				setbutton();
				if (ifinimage(msg,this->img[27],0,0))
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
	putimage(0, 0, &this->ymimg[0], NOTSRCERASE);
	putimage(0, 0, &this->img[7], SRCINVERT);
	string text;
	settextcolor(RGB(7,56,132));
	settextstyle(15, 15, "黑体");
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
	putimage(0, 0, &this->ymimg[0], NOTSRCERASE);
	putimage(0, 0, &this->img[7], SRCINVERT);
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
void Mananger::createchallenge(game& randomgame, int&number1,people*& Pall)
{
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
	putimage(860, 500, &this->ymimg[9], NOTSRCERASE);
	putimage(860, 500, &this->Move[0], SRCINVERT);
	putimage(810, 500, &this->ymimg[10], NOTSRCERASE);
	putimage(810, 500, &this->Move[1], SRCINVERT);
	putimage(910, 500, &this->ymimg[11], NOTSRCERASE);
	putimage(910, 500, &this->Move[2], SRCINVERT);
	putimage(860, 450, &this->ymimg[8],NOTSRCERASE);
	putimage(860, 450, &this->Move[3],SRCINVERT);
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
		putimage(shipx, shipy, &this->img[13]);
		putimage(s1Px, s1Py, &this->img[14]);
		putimage(s2Px, s2Py, &this->img[14]);
		b1[k][j].reviseMycreateifpass() = true;
		if (b1[k][j].reviseMycreateifpass() != b1[k][j].revisecreateifpass() || (s1Px == shipx && s1Py == shipy) || (s2Px == shipx && s2Py == shipy))
		{

			drawNoMyCreate(randomgame,  number1, Pall);
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
				if (ifinimage(msg, this->Move[0], 860, 500))
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
				else if (ifinimage(msg, this->Move[1], 810, 500))
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
				else if (ifinimage(msg, this->Move[2], 910, 500))
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
				else if (ifinimage(msg, this->Move[3], 860, 450))
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
		int a[25][25]{0};
		a[xfinal][yfinal] = 1;
		for (int i = number1 - 2; i >= 0;)
		{
			int number1 = rand() % 4;
			switch (number1)
			{
			case 0:
			{
				randomgame.getp1().Movepeople(UP);
				randomgame.getp1array()[i] = randomgame.getp1();
				if (randomgame.ifpass(randomgame.getp1array(), i)&&a[randomgame.getp1().returnx()][randomgame.getp1().returny()==0])
				{
					i--;
					a[randomgame.getp1().returnx()][randomgame.getp1().returny()] = 1;
				}
				else randomgame.getp1().Movepeople(DOWN);
				break;
			}
			case 1:
			{
				randomgame.getp1().Movepeople(DOWN);
				randomgame.getp1array()[i] = randomgame.getp1();
				if (randomgame.ifpass(randomgame.getp1array(), i)&& a[randomgame.getp1().returnx()][randomgame.getp1().returny()] ==0)
				{
					i--;
					a[randomgame.getp1().returnx()][randomgame.getp1().returny()] = 1;
				}
				else randomgame.getp1().Movepeople(UP);
				break;
			}
			case 2:
			{
				randomgame.getp1().Movepeople(LEFT);
				randomgame.getp1array()[i] = randomgame.getp1();
				if (randomgame.ifpass(randomgame.getp1array(), i)&& a[randomgame.getp1().returnx()][randomgame.getp1().returny()] ==0)
				{
					i--;
					a[randomgame.getp1().returnx()][randomgame.getp1().returny()] = 1;
				}
				else randomgame.getp1().Movepeople(RIGHT);
				break;
			}
			case 3:
			{
				randomgame.getp1().Movepeople(RIGHT);
				randomgame.getp1array()[i] = randomgame.getp1();
				if (randomgame.ifpass(randomgame.getp1array(), i)&& a[randomgame.getp1().returnx()][randomgame.getp1().returny()] ==0)
				{
					i--;
					a[randomgame.getp1().returnx()][randomgame.getp1().returny()] = 1;
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
		randomgame.setp2relative(randomgame.getp2relative(), randomgame.getp2array(), randomgame.getp1array(), randomgame.getrun());
		bool x = 1;
		for (int i = 0; i < randomgame.getrun()-1; i++) 
		{
			if (randomgame.getp2relative()[i].returnx() == randomgame.getp2relative()[i + 1].returnx() && randomgame.getp2relative()[i].returny() == randomgame.getp2relative()[i + 1].returny()) 
			{
				x = 0; 
				break;
			}
		}
		if (ifOKCreat(randomgame)&&x)
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
	createchallenge(randomgame, number1, Pall);

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
	BeginBatchDraw();
	putimage(0, 0, &this->img[3]);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++) { this->GQbutton[i][j].drawGQbutton(); }
	}
	EndBatchDraw();
	bool x = 1;
	drawanswerroad(p1, 11, b1,x);
	putimage(800, 629, &this->ymimg[2], NOTSRCERASE);
	putimage(800, 629, &this->img[19], SRCINVERT);
	//button con(800, 679, 200, 50, "下一步");
	//con.drawbuttonwithPic(&this->img[15]);
	while (1)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (ifinimage(msg,this->img[19],800,629))
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
	putimage(0, 0, &this->ymimg[5], NOTSRCERASE);
	putimage(0, 0, &this->img[26], SRCINVERT);
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
			cleardevice();
			initgraph(600, 700);
			setbkmode(TRANSPARENT);
			putimage(0, 0, &this->img[12]);
			putimage(0, -10, &this->ymimg[6], NOTSRCERASE);
			putimage(0, -10, &this->img[27], SRCINVERT);
			putimage(430, 620, &this->ymimg[2], NOTSRCERASE);
			putimage(430,620, &this->img[19], SRCINVERT);
			string text;
			settextstyle(22, 22, "黑体");
			settextcolor(RGB(130,170,230));
			text = "已有自建关卡:";
			outtextxy(150, 90 , text.c_str());
			settextstyle(15, 15, "黑体");
			for (int i = 0; i < this->gameall.size(); i++)
			{
				text =gameall[i].name;
				outtextxy(150, 120+20*i, text.c_str());
			}
			while (1)
			{
				ExMessage msg = getmousemessage();
				if (ifinimage(msg, this->img[19], 500, 600)) 
				{
					bool x = 1;
					while (x) {
						string name = "";
						char buffer[256] = { 0 };
						initgraph(640, 480);
						setbkmode(TRANSPARENT);
						IMAGE i1;
						loadimage(&i1, "脑力航迹/实训/获取输入背景.jpg", 640, 480);
						putimage(0, 0, &i1);
						InputBox(buffer, 256, _T("请输入关卡名字:"), _T("请选择关卡"), _T("******"));
						int i = 0;
						while(buffer[i]!='\0'){
							name += buffer[i];
							i++;
						}
						for (int i = 0; i < gameall.size(); i++)
						{
							if (gameall[i].name == name)
							{
								creatrGameChallenge(gameall[i].g1);
								x = 0;
								break;
							}
						}
					}
					closegraph();
				}
				else if (ifinimage(msg, this->img[27], 0, -10))
				{
					closegraph();
					CreateMode();
					break;
				}
			}
			closegraph();
			
		}
		else if (ifinimage(msg, this->img[26], 0, 0))
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
	putimage(0, 0, &this->ymimg[0], NOTSRCERASE);
	putimage(0, 0, &this->img[7], SRCINVERT);
	string text;
	settextstyle(15, 15, "黑体");
	settextcolor(RGB(7, 56, 132));
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
	putimage(0, 0, &this->ymimg[0], NOTSRCERASE);
	putimage(0, 0, &this->img[7], SRCINVERT);
	string text;
	settextcolor(RGB(7, 56, 132));
	settextstyle(15, 15, "黑体");
	for (int i = 0; i < 9; i++)
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
	settextstyle(40, 40, "黑体");
	settextcolor(RGB(202,81,0));
	string text;
	text = this->p1.GetName();
	outtextxy(150, 150, text.c_str());
	settextstyle(20, 20, "黑体");
	for (int i = 0; i < 9; i++)
	{
		outtextxy(170 + i * 70, 223, to_string(i + 1).c_str());
	}
	settextstyle(17, 17, "黑体");
	for (int i = 0; i < this->p1.Getaccuracy().size(); i++)
	{
		int num = this->p1.Getaccuracy()[i] * 100;
		text = to_string(num) + "%";
		outtextxy(170 + i * 70, 300, text.c_str());
	}
	for (int i = 0; i < this->p1.Getscore().size(); i++)
	{
		text = to_string(this->p1.Getscore()[i]);
		outtextxy(170 + i * 70, 378, text.c_str());
	}
	text = to_string(this->p1.getnoendscore());
	settextstyle(40, 40, "黑体");
	outtextxy(300, 467, text.c_str());
	putimage(0, 0, &this->ymimg[5], NOTSRCERASE);
	putimage(0, 0, &this->img[26], SRCINVERT);
	while (1)
	{
		ExMessage msg = getmousemessage();
		if (ifinimage(msg, this->img[26], 0, 0))
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
	button b0(150, 170, 100, 50, "简单");
	button b1(150, 220, 100, 50, "普通");
	button b2(150, 270, 100, 50, "困难");
	button b3(150, 320, 100, 50, "史诗");
	button b4(150, 370, 100, 50, "传说");
	b0.drawbutton1();
	b1.drawbutton1();
	b2.drawbutton1();
	b3.drawbutton1();
	b4.drawbutton1();
	int number;
	putimage(0, 0, &this->ymimg[5], NOTSRCERASE);
	putimage(0, 0, &this->img[26], SRCINVERT);
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
		else if (ifinimage(msg, this->img[26], 0, 0))
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
	button b0(335, 175, 200, 50, "开始游戏");
	button b1(335, 225, 200, 50, "查看规则");
	button b2(335, 275, 200, 50, "查看信息");
	button b3(335, 325, 200, 50, "创造模式");
	button b4(335, 375, 200, 50, "挑战模式");
	button b5(335, 425, 200, 50, "无尽模式");
	button b6(335, 475, 200, 50, "退出游戏");
	button b8(335, 525, 200, 50, " 排行榜");
	button b9(335, 575, 200, 50, "创意模式");
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
	loadgameP();
	setbutton();
	dlOrZc();

}