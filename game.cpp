#include "game.h"
#include <iostream>
using namespace std;
void people::DisplayMessage( people& p1) 
{
	cout <<"("<< p1.returnx() << "," << p1.returny()<<")" << "   ";
}
void people::SetPeopleBeginPos(int x1, int y1)
{
	this->x = x1;
	this->y = y1;
	
}
void people::Movepeople(Direction heading) 
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
void game::setrun(int num1)
{
	this->run = num1;

}
void game::setzihzhen()
{
	p1array = new people[run];
	p2array = new people[run];
	p2relative = new people[run];
}
void game::setp2relative(people*& p1, people*p2, people*p3,int run)
{
	p1[0].getx() = p2->getx();
	p1[0].gety() = p2->gety();
	for (int i = 1; i < run; i++) 
	{
		p1[i].getx() = p1[i - 1].getx() + p2[i].getx()-p2[i-1].getx()- p3[i].getx() + p3[i - 1].getx();
		p1[i].gety() = p1[i - 1].gety() + p2[i].gety() - p2[i - 1].gety() - p3[i].gety() + p3[i - 1].gety();
	}

}
void game::DisplayRelativeMove(people* p1array, people*p2relative)
{
	

	for (int i = 0; i < run; i++) 
	{
		if (i == 0) 
		{
			cout << "��ʼ�㼰���˵����꣺" << endl;
			p1array[i].DisplayMessage(p1array[i]); 
			p2relative[i].DisplayMessage(p2relative[i]);
			cout << endl;
		}
		else 
		{
			cout << "��" << i << "��������꼰���˵��������:" << endl;
			p1array[i].DisplayMessage(p1array[i]);
			p2relative[i].DisplayMessage(p2relative[i]);
			cout << endl;

		}
	}
}
void game::getanswer(people *p2array) 
{
	for (int i = 0; i < this->getrun(); i++) 
	{
		p2array[i].DisplayMessage(p2array[i]);
	}
}
bool game::IfYes(int number, people* p2array) 
{
	cout << "��Ҫ��ʾ������250 250" << endl;
	people* p3array = new people[number];
	for (int i = 0; i < number; i++) 
	{
		if (i == 0) 
		{
			cout << "����һ��ʼ�����꣺" << endl;
			int x1, y1;
			cin >> x1 >> y1;
			if (x1 == 250 && y1 == 250) 
			{
				gettip(i, p2array);
				cin >> x1 >> y1;
			}
			p3array[i].SetPeopleBeginPos(x1, y1);
		}
		else {
			cout << "�������" << i << "�����˵�ʵ�����꣺" << endl;
			int x1, y1;
			cin >> x1 >> y1;
			if (x1 == 250 && y1 == 250)
			{
				gettip(i, p2array);
				cin >> x1 >> y1;
			}
			p3array[i].SetPeopleBeginPos(x1, y1);
		}

	}
	for (int i = 0; i < number; i++)
	{
		if (p2array[i].getx() != p3array[i].getx() || p2array[i].gety() != p3array[i].gety())
		{
			system("cls");
			return false;
		}
	}
	system("cls");
	delete[]p3array;
	return true;
}
bool game::ifpass(people*& p1, const int& num) 
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
void game::gettip(int &i, people* p2array)
{

		cout << "��ʾ��"; p2array[i].DisplayMessage(p2array[i]);
}
int game::getrun() 
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











