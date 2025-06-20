#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <iomanip>
#include <fstream>
enum Direction { UP, DOWN, LEFT, RIGHT };
class people
{
public:
	people() :x(0), y(0) {}
	void SetPeopleBeginPos(const int&, const int&);
	void Movepeople(const Direction& heading);
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

	game(const game& g1);
	game();
	game& operator=(const game&g1);
	void setrun(const int&);
	int getrun()const;
	people& getp1();
	people& getp2();
	people*& getp1array();
	people*& getp2array();
	people*& getp2relative();
	void setp2relative(people*&, people*&, people*&, const int& run);
	void setzihzhen();
	bool ifpass(people*&, const int&)const;
	bool ifpass1(people*&, const int&)const;
	people* returnp1arr()const;
	people* returnp2arr()const;
	people* returnp2rearr()const;
	void writegame(const std::string&);
	bool& reviselookanswer();
	bool returnlookanswer();
private:
	people p1, p2;
	int run;
	people* p1array = nullptr;
	people* p2array = nullptr;
	people* p2relative = nullptr;
	bool iflookanswer = 0;
};

#endif // !GAME_H
