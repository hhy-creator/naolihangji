#ifndef GAME_H
#define GAME_H
#include <iostream>
enum Direction{UP,DOWN,LEFT,RIGHT};
class people 
{
public:
	people() :x(0), y(0) {}
	void DisplayMessage(people&);
	void SetPeopleBeginPos(int,int);
	void Movepeople(Direction heading);
	int& getx();
	int& gety();
	int returnx()const;
	int returny()const;
private:
	int x; 
	int y;
};
class game 
{

public:
	~game();
	void DisplayRelativeMove( people*, people*);
	bool IfYes(int, people*);
	void setrun(int);
	int getrun();
	people& getp1();
	people& getp2();
	people*& getp1array();
	people*& getp2array();
	people*& getp2relative();
	void setp2relative(people*&,people*,people*,int run);
	void setzihzhen();
	void getanswer(people *);
	bool ifpass( people*&, const int&);
	void gettip(int &,people*);
private:
	people p1, p2;
	int run;
	people* p1array;
	people* p2array;
	people* p2relative;
};

#endif // !GAME_H
