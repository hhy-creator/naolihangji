#ifndef GAME_H
#define GAME_H
#include <iostream>
enum Direction{UP,DOWN,LEFT,RIGHT};
class people 
{
public:
	void DisplayMessage();
	void SetPeopleBeginPos(int,int);
	void Movepeople(Direction heading);
	int getx();
	int gety();
private:
	int x; 
	int y;
};
class game 
{
public:
	void DisplayRelativeMove(people p1, people p2, people*, people*);
	void DisplayPath();
	void setrun(int);
	people getp1();
	people getp2();
	people* getp1array();
	people* getp2array();
private:
	people p1, p2;
	int run;
	people* p1array=new people[run];
	people* p2array=new people[run];
	
};
#endif // !GAME_H
