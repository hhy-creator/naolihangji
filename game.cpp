#include "game.h"
#include <iostream>
using namespace std;
void people::DisplayMessage() 
{
	cout << this->x << " " << this->y<<endl;
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
int people::getx() 
{
	return x;

}
int people::gety()
{
	return y;

}
void game::setrun(int num1)
{
	this->run = num1;
	
}
void game::DisplayRelativeMove(people p1,people p2, people* p1array, people*p2array)
{
	for (int i = 0; i < run; i++) 
	{
		if (i == 0) 
		{
			p1array[i].DisplayMessage(); p2array[i].DisplayMessage();
		}
		else 
		{
			cout << p2array[i - 1].getx() + p2array[i].getx() - p1array[i].getx()<<" "<<p2array[i - 1].gety() + p2array[i].gety() - p1array[i].gety();
		}
	}
}
void game::DisplayPath() 
{
	for(int i=0;i<this->run;i++)
	{
        this->getp1array()[i].DisplayMessage();
	}
}
people game::getp1() 
{
	return p1;
}
people game::getp2() 
{
	return p2;
}
people* game::getp1array() 
{
	return p1array;
}
people* game::getp2array() 
{
	return p2array;
}











