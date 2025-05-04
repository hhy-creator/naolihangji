#include "game.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
void people::DisplayMessage(const people& p1)const 
{
	cout <<"("<< p1.returnx() << "," << p1.returny()<<")" << "   ";
}
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
void game::DisplayRelativeMove( people*& p1array,  people*&p2relative)const
{
	

	for (int i = 0; i < run; i++) 
	{
		if (i == 0) 
		{
			cout << "你与别人的起点：" << endl;
			p1array[i].DisplayMessage(p1array[i]); 
			p2relative[i].DisplayMessage(p2relative[i]);
			cout << endl;
			cout << "步数     你与别人的坐标" << endl;
		}
		else 
		{
			cout <<setw(3)<< i << setw(8);
			p1array[i].DisplayMessage(p1array[i]);
			p2relative[i].DisplayMessage(p2relative[i]);
			cout << endl;

		}
	}
}
void game::getanswer( people* &p2array)const 
{
	for (int i = 0; i < this->getrun(); i++) 
	{
		p2array[i].DisplayMessage(p2array[i]);
	}
	cout << endl;
}
bool game::IfYes(int number, people*& p2array)
{
	cout << "需要提示请输入250 250" << endl;
	people* p3array = new people[number];
	for (int i = 0; i < number; i++) 
	{
		if (i == 0) 
		{
			cout << "别人的起点：" << endl;
			int x1, y1;
			cin >> x1 >> y1;
			if (x1 == 250 && y1 == 250) 
			{
				gettip(i, p2array);
				cin >> x1 >> y1;
			}
			p3array[i].SetPeopleBeginPos(x1, y1);
			cout << "步数     别人的坐标" << endl;
		}
		else {
			cout << i <<"          ";
			int x1, y1;
			cin >> x1 >> y1;
			if (x1 == 250 && y1 == 250)
			{
				gettip(i, p2array);
				cout << "请继续输入当前别人的坐标：" << endl;
				cin >> x1 >> y1;
			}
			p3array[i].SetPeopleBeginPos(x1, y1);
		}

	}
	for (int i = 0; i < number; i++)
	{
		if (p2array[i].returnx() != p3array[i].returnx() || p2array[i].returny() != p3array[i].returny())
		{
			system("cls");
			delete[]p3array;
		
			return false;
		}
	}
	system("cls");
	delete[]p3array;
	return true;
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
void game::gettip( int &i, people*& p2array)const
{

		cout << "提示："; p2array[i].DisplayMessage(p2array[i]);
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










