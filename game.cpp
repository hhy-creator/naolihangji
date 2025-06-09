#include "game.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;
void people::SetPeopleBeginPos(const int& x1, const int& y1)
{
	this->x = x1;
	this->y = y1;
	
}
void people::Movepeople(const Direction& heading) 
{
	switch (heading) 
	{
	case UP:
		this->y--;
		break;
	case DOWN:
		this->y++;
		break;
	case LEFT:
		this->x--;
		break;
	case RIGHT:
		this->x++;
		break;
	}
}
int& people::getx() 
{
	return x;

}
int& people::gety()
{
	return y;

}
int people::returnx() const
{
	return x;
}
int people::returny()const
{
	return y;
}
game::~game()
{
	delete[]p1array;
	delete[]p2array;
	delete[]p2relative;
	p1array = nullptr;
	p2array = nullptr;
	p2relative = nullptr;
}
void game::setrun(const int& num1)
{
	this->run = num1;

}
void game::setzihzhen()
{
	p1array = new people[run];
	p2array = new people[run];
	p2relative = new people[run];
}
void game::setp2relative(people*& p1, people*&p2, people*&p3,const int& run)
{
	p1[0].getx() = p2->returnx();
	p1[0].gety() = p2->returny();
	for (int i = 1; i < run; i++) 
	{
		p1[i].getx() = p1[i - 1].getx() + p2[i].returnx()-p2[i-1].returnx()- p3[i].returnx() + p3[i - 1].returnx();
		p1[i].gety() = p1[i - 1].gety() + p2[i].returny() - p2[i - 1].returny() - p3[i].returny() + p3[i - 1].returny();
	}

}
bool& game::reviselookanswer() 
{
	return this->iflookanswer;
}
bool game::returnlookanswer() 
{
	return this->iflookanswer;
}
bool game::ifpass(people*& p1, const int& num)const 
{
	for (int i = this->getrun() - 1; i > num; i--) 
	{
		if ((p1[i].returnx() == p1[num].returnx()) && p1[i].returny() == p1[num].returny()) 
		{
			return false;
		}
	}
	return true;
}
bool game::ifpass1(people*& p1, const int& num)const
{
	for (int i = 0; i<num-1; i++)
	{
		if ((p1[i].returnx() == p1[num].returnx()) && p1[i].returny() == p1[num].returny())
		{
			return false;
		}
	}
	return true;
}
int game::getrun() const
{
	return run;
}
people& game::getp1() 
{
	return this->p1;
}
people& game::getp2() 
{
	return this->p2;
}
people*&game::getp1array() 
{
	return this->p1array;
}
people*& game::getp2array() 
{
	return this->p2array;
}
people*& game::getp2relative()
{
	return this->p2relative;
}
people* game::returnp1arr() const
{
	
	return this->p1array;
}
people* game::returnp2arr() const
{
	return this->p2array;
}
people* game::returnp2rearr() const
{
	return this->p2relative;
};
void game::writegame(const std::string&name) 
{
	ofstream os("game.txt",ios::app);
	if (!os.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	os << endl;
	for (int i = 0; i < name.size(); i++)
	{
		os <<name[i];
	}
	os << endl;
	os << this->run<<" ";
	for (int i = 0; i < this->run; i++)
	{
		os << this->p1array[i].getx() << " " << this->p1array[i].gety()<<" ";
	}
	for (int i = 0; i < this->run; i++)
	{
		os << this->p2array[i].getx() << " " << this->p2array[i].gety() << " ";
	}
	os.close();
}
game::game() 
{

}
game::game(const game& g1) 
{
	this->run = g1.run;
	this->setzihzhen();
	for (int i = 0; i < this->run; i++)
	{
		this->p1array[i].getx() = g1.returnp1arr()[i].returnx();
		this->p1array[i].gety() = g1.returnp1arr()[i].returny();
		this->p2array[i].getx() = g1.returnp2arr()[i].returnx();
		this->p2array[i].gety() = g1.returnp2arr()[i].returny();
		this->p2relative[i].getx() = g1.returnp2rearr()[i].returnx();
		this->p2relative[i].gety() = g1.returnp2rearr()[i].returny();
	}
	this->p1 = g1.p1;
	this->p2 = g1.p2;
	
}
game& game::operator=(const game& g1) 
{
	this->run = g1.run;
	this->setzihzhen();
	for (int i = 0; i < this->run; i++) 
	{
		this->p1array[i].getx() = g1.returnp1arr()[i].returnx();
		this->p1array[i].gety() = g1.returnp1arr()[i].returny();
		this->p2array[i].getx() = g1.returnp2arr()[i].returnx();
		this->p2array[i].gety() = g1.returnp2arr()[i].returny();
		this->p2relative[i].getx() = g1.returnp2rearr()[i].returnx();
		this->p2relative[i].gety() = g1.returnp2rearr()[i].returny();
	}
	return *this;
}








