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
//void player::operator=(player&) 
//{}
string player::GetName() 
{
	return this->name;
}
void player::serialize(std::ostream& os) const {
	// 写入 name
	os.write(reinterpret_cast<const char*>(&this->name), sizeof(this->name));
	os.write(name.c_str(), 32);

	// 写入 time 向量
	for (int i = 0; i < this->time.size(); i++) 
	{
		double m = time[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(double));
	}

	// 写入 accuracy 向量
	for (int i = 0; i < this->accuracy.size(); i++)
	{
		double m = accuracy[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(double));
	}

	// 写入 score 向量
	
	for (int i = 0; i < this->score.size(); i++)
	{
		int m = score[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(int));
	}
	// 写入 right 向量
	
	for (int i = 0; i < this->right.size(); i++)
	{
		int m = right[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(int));
	}
	// 写入 wrong 向量
	for (int i = 0; i < this->wrong.size(); i++)
	{
		int m = wrong[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(int));
	}
	// 写入 noendscore
	os.write(reinterpret_cast<const char*>(&this->noendscore), sizeof(int));
}

// 新增反序列化方法
player player::deserialize(std::istream& is) {
	player p1(0);
    // 读取name
	string name;
	is.read(reinterpret_cast<char*>(&name), 32);
	p1.GetName() = name;

    // 读取vector<double> time
	for (int i = 0; i < p1.gettime().size(); i++)
	{
		double m;
		is.read(reinterpret_cast<char*>(&m), sizeof(double));
		p1.gettime()[i] = m;
	}

    // 读取vector<double> accuracy
	for (int i = 0; i < p1.Getaccuracy().size(); i++)
	{
		double m;
		is.read(reinterpret_cast<char*>(&m), sizeof(double));
		p1.Getaccuracy()[i] = m;
	}

    // 读取vector<int> score
	for (int i = 0; i < p1.Getscore().size(); i++)
	{
		int m;
		is.read(reinterpret_cast<char*>(&m), sizeof(int));
		p1.Getscore()[i] = m;
	}

    // 读取vector<int> right
	for (int i = 0; i < p1.Getright().size(); i++)
	{
		int m;
		is.read(reinterpret_cast<char*>(&m), sizeof(int));
		p1.Getright()[i] = m;
	}

    // 读取vector<int> wrong
	for (int i = 0; i < p1.Getwrong().size(); i++)
	{
		int m;
		is.read(reinterpret_cast<char*>(&m), sizeof(int));
		p1.Getwrong()[i] = m;
	}

    // 读取noendscore
	int m;
	is.read(reinterpret_cast<char*>(&p1.noendscore), sizeof(int));
	return p1;
}

player::player(int) :name("11"), noendscore(0)
{
	name.resize(32);
	for (int i = 0; i < 10; i++)
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
void player::CheckMessage()
{
	cout << this->GetName() << ":" << endl;
	this->ShowAccuracy(this->Getaccuracy());
	this->ShowScore(this->Getscore());
	cout << "无尽挑战分数：" << this->getnoendscore() << endl;
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
	cout << "关卡" <<setfill(' ') << setw(8) << "分数" << endl;
	for (int i = 1; i <= 5; i++) 
	{
		cout << i <<setfill(' ') << setw(8) << array1[i] << endl;
	}
	cout << endl;
}
void player::ShowAccuracy(const vector<double>&array1)
{
	cout << "关卡" <<setfill(' ') << setw(8) << "正确率" << endl;
	for (int i = 0; i <5; i++)
	{
		cout << i+1 << setfill(' ') << setw(8) << array1[i] * 100 << "% " << endl;
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