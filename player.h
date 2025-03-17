#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <array>
using namespace std;
class player 
{
public:
	player();
	player& SetName();
	string GetName();
	void AddRight(array<int, 10>&, const int&);
	void AddWrong(array<int, 10>&, const int&);
	void CalAccuracy(const array<int, 10>&,const array<int, 10>&, array<double, 10>&);
	void CreatScore(array<int, 10>&score,const int&, const bool& x);
	void ShowScore(const array<int, 10>&);
	void ShowAccuracy(const array<double, 10>&);
	array<int, 10>& Getscore();
	array<double, 10>& Getaccuracy();
	array<int, 10>& Getright();
	array<int, 10>& Getwrong();
private:
	string name;
	array<array<int, 10>, 10>time;
	array<double, 10>accuracy;
	array<int, 10>score;
	array<int, 10>right;
	array<int, 10>wrong;




};
#endif // !PLAYER_H
