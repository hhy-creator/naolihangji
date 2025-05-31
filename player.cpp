#include <iostream>
#include <iomanip>
using namespace std;
#include "player.h"
#include <algorithm>
#include "easyx.h"
player& player::SetName()
{
		string name = "";
		string password = "";
		char buffer[256] = { 0 };
		char buffer1[256] = { 0 };
		initgraph(640, 480);
		setbkmode(TRANSPARENT);
		IMAGE i1;
		loadimage(&i1, "脑力航迹/实训/获取输入背景.jpg", 640, 480);
		putimage(0, 0, &i1);
		InputBox(buffer, 256, _T("请输入名字（长度不超过10超过将取前10个字节）:"), _T("请创建or登陆用户"), _T("确定"));
		for (int i = 0; i < 10; i++)
		{
			name += buffer[i];
		}
		InputBox(buffer1, 256, _T("请输入密码:"), _T("下一步"), _T("确定"));

		for (int i = 0; i < 14; i++)
		{
			password += buffer1[i];
		}
	closegraph();
	this->name = name;
	this->password = password;
	return *this;
}
bool player::operator==(const player& p1) 
{
	if (this->name == p1.name && this->password == p1.password) 
	{
		return true;
	}
	return false;
}
double& player::revisetimeall()
{
	return this->timeall;
}
int& player::revisescoreall()
{
	return this->scoreall;
}
double player::returntimeall() 
{
	this->timeall = 0;
	for (int i = 0; i < this->time.size(); i++) 
	{
		this->timeall += this->time[i];
	}
	return this->timeall;
}
int player::returnscoreall() 
{
	this->scoreall = 0;
	for (int i = 0; i < this->score.size(); i++) 
	{
		this->scoreall += this->score[i];
	}
	return this->scoreall;
}
string& player::revisepassword() 
{
	return this->password;
}
string& player::GetName() 
{
	return this->name;
}
vector<int> player::returnGetscore() const
{
	return this->score;
}
vector<double> player::returngettime() const
{
	return this->time;
}
void player::serializetxt(std::ostream& os) const 
{
	// 写入 name
	os << endl;
	for (int i = 0; i < this->name.size(); i++) 
	{
		os << this->name[i];
	}
	os << endl;
	for (int i = 0; i < this->password.size(); i++)
	{
		os << this->password[i];
	}
	os << endl;
	// 写入 time 向量
	for (int i = 0; i < this->time.size(); i++)
	{
		os << time[i]<<" ";
	}

	for (int i = 0; i < this->accuracy.size(); i++)
	{
		os << accuracy[i]<<" ";
	}
	for (int i = 0; i < this->right.size(); i++)
	{
		os << right[i]<<" ";
	}
	for (int i = 0; i < this->wrong.size(); i++)
	{
		os << wrong[i]<<" ";
	}
	// 写入 score 向量

	for (int i = 0; i < this->score.size(); i++)
	{
		os << score[i]<<" ";
	}
	// 写入 noendscore
	os << noendscore << endl;
}
int player::getnoend() const
{
	return this->noendscore;
}
void player::deserializetxt(std::istream& is) 
{
	player p1(0);
	for (int i = 0; i < 32; i++)
	{
		is >>p1.name[i];
	}
	for (int i = 0; i < this->time.size(); i++)
	{
		is>>p1.time[i];
	}
	for (int i = 0; i < this->accuracy.size(); i++)
	{
		is >> p1.accuracy[i];
	}
	for (int i = 0; i < this->right.size(); i++)
	{
		is >> right[i];
	}
	for (int i = 0; i < this->wrong.size(); i++)
	{
		is>> p1.wrong[i];
	}


	for (int i = 0; i < this->score.size(); i++)
	{
		is>>p1.score[i];
	}

	is >> p1.noendscore;

}
player::player(int) :name(""), noendscore(0),password("0")
{
	name.resize(32);
	for (int i = 0; i < 9; i++)
	{
		time.push_back(0);
		accuracy.push_back(0);
		score.push_back(0);
		right.push_back(0);
		wrong.push_back(0);
	}
}
player::player() : noendscore(0)
{
	name.resize(32);
	for (int i = 0; i < 9; i++) 
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
	for (int i = 0; i < 9; i++) 
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
		if (time[i] < run * 5) { score[i] =max( 100,score[i]); }
		else { score[i] = max((100 / (time[i] / run)) * 5,score[i]); }
	}
	else 
	{
		score[i] = score[i] > 0 ? score[i] = score[i] : score[i] = 0;
	}
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
