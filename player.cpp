#include <iostream>
#include <iomanip>
using namespace std;
#include "player.h"
player& player::SetName()
{
	string name;
	cout << "欢迎来到游戏，请创建您的名字：" << endl;
	cin >> name;
	this->name = name;
	return *this;
}
string player::GetName() 
{
	return this->name;
}
player::player() : time{ 0 }, accuracy{ 0 }, score{ 0 }, right{ 0 }, wrong{0},noendscore(0)
{
	SetName();
}
void player::AddRight(array<int, 10>&right,const int&i)
{
	right[i]++;
}
void player::AddWrong(array<int, 10>&wrong,const int&i) 
{
	wrong[i]++;
}
void player::CalAccuracy(const array<int, 10>&right, const array<int, 10>&wrong, array<double, 10>&) 
{
	for (int i = 0; i < 10; i++) 
	{
		if(right[i]+wrong[i]!=0)accuracy[i] = double(right[i]) / (right[i] + wrong[i]);
	}
}
void player::CreatScore(array<int, 10>& score, const int&i,const bool&x ) 
{
	if (x) 
	{
		score[i] = 100;
	}
	else 
	{
		score[i] = 0;
	}
}
void player::ShowScore(const array<int, 10>&array1) 
{
	cout << "关卡" << setw(8) << "分数" << endl;
	for (int i = 1; i <= 5; i++) 
	{
		cout << i << setw(8)<< array1[i]<<endl;
	}
	cout << endl;
}
void player::ShowAccuracy(const array<double, 10>&array1)
{
	cout << "关卡" << setw(8) << "正确率" << endl;
	for (int i = 1; i <=5; i++)
	{
		cout << i <<setw(8)<< array1[i]*100 << "% "<<endl;
	}
	cout << endl;
}
array<int, 10>& player::Getscore() 
{
	return this->score;
}
array<int, 10>& player::Getright()
{
	return this->right;
}
array<int, 10>& player::Getwrong()
{
	return this->wrong;
}
array<double, 10>& player::Getaccuracy()
{
	return this->accuracy;
}