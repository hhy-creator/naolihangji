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
player::player() : noendscore(0)
{
	for (int i = 0; i < 10; i++) 
	{
		time.push_back(0);
		accuracy.push_back(0);
		score.push_back(0);
		right.push_back(0);
		wrong.push_back(0);
	}
	SetName();
}
void player::AddRight(vector<int>&right,const int&i)
{
	right[i]++;
}
void player::AddWrong(vector<int>&wrong,const int&i)
{
	wrong[i]++;
}
void player::CalAccuracy(const vector<int>&right, const vector<int>&wrong, vector<double>&accurary)
{
	for (int i = 0; i < 10; i++) 
	{
		if(right[i]+wrong[i]!=0)accuracy[i] = double(right[i]) / (right[i] + wrong[i]);
	}
}
int& player::getnoendscore() 
{
	return this->noendscore;
}
vector <double>&player:: gettime() 
{
	return this->time;
}
void player::CreatScore(vector<int>& score, const int&i,const bool&x,const vector<double>&time, const int& run)
{
	if (x) 
	{
		if (time[i] < run * 5) { score[i] = 100; }
		else { score[i] = 100 * ((time[i] / run) / 5); }
	}
	else 
	{
		score[i] = 0;
	}
}
void player::ShowScore(const vector<int>&array1)
{
	cout << "关卡" << setw(8) << "分数" << endl;
	for (int i = 1; i <= 5; i++) 
	{
		cout << i << setw(8)<< array1[i]<<endl;
	}
	cout << endl;
}
void player::ShowAccuracy(const vector<double>&array1)
{
	cout << "关卡" << setw(8) << "正确率" << endl;
	for (int i = 1; i <=5; i++)
	{
		cout << i <<setw(8)<< array1[i]*100 << "% "<<endl;
	}
	cout << endl;
}
vector<int>& player::Getscore()
{
	return this->score;
}
vector<int>& player::Getright()
{
	return this->right;
}
vector<int>& player::Getwrong()
{
	return this->wrong;
}
vector<double>& player::Getaccuracy()
{
	return this->accuracy;
}