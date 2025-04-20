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
void player::serialize(std::ostream& os) const {
	// 写入 name
	size_t name_len = name.size();
	os.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
	os.write(name.c_str(), name_len);

	// 写入 time 向量
	size_t time_size = time.size();
	os.write(reinterpret_cast<const char*>(&time_size), sizeof(time_size));
	os.write(reinterpret_cast<const char*>(time.data()), time_size * sizeof(double));

	// 写入 accuracy 向量
	size_t accuracy_size = accuracy.size();
	os.write(reinterpret_cast<const char*>(&accuracy_size), sizeof(accuracy_size));
	os.write(reinterpret_cast<const char*>(accuracy.data()), accuracy_size * sizeof(double));

	// 写入 score 向量
	size_t score_size = score.size();
	os.write(reinterpret_cast<const char*>(&score_size), sizeof(score_size));
	os.write(reinterpret_cast<const char*>(score.data()), score_size * sizeof(int));

	// 写入 right 向量
	size_t right_size = right.size();
	os.write(reinterpret_cast<const char*>(&right_size), sizeof(right_size));
	os.write(reinterpret_cast<const char*>(right.data()), right_size * sizeof(int));

	// 写入 wrong 向量
	size_t wrong_size = wrong.size();
	os.write(reinterpret_cast<const char*>(&wrong_size), sizeof(wrong_size));
	os.write(reinterpret_cast<const char*>(wrong.data()), wrong_size * sizeof(int));

	// 写入 noendscore
	os.write(reinterpret_cast<const char*>(&noendscore), sizeof(noendscore));
}

// 新增反序列化方法
void player::deserialize(std::istream& is) {
	// 读取 name
	size_t name_len;
	is.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
	name.resize(name_len);
	is.read(&name[0], name_len);

	// 读取 time 向量
	size_t time_size;
	is.read(reinterpret_cast<char*>(&time_size), sizeof(time_size));
	time.resize(time_size);
	is.read(reinterpret_cast<char*>(time.data()), time_size * sizeof(double));

	// 读取 accuracy 向量
	size_t accuracy_size;
	is.read(reinterpret_cast<char*>(&accuracy_size), sizeof(accuracy_size));
	accuracy.resize(accuracy_size);
	is.read(reinterpret_cast<char*>(accuracy.data()), accuracy_size * sizeof(double));

	// 读取 score 向量
	size_t score_size;
	is.read(reinterpret_cast<char*>(&score_size), sizeof(score_size));
	score.resize(score_size);
	is.read(reinterpret_cast<char*>(score.data()), score_size * sizeof(int));

	// 读取 right 向量
	size_t right_size;
	is.read(reinterpret_cast<char*>(&right_size), sizeof(right_size));
	right.resize(right_size);
	is.read(reinterpret_cast<char*>(right.data()), right_size * sizeof(int));

	// 读取 wrong 向量
	size_t wrong_size;
	is.read(reinterpret_cast<char*>(&wrong_size), sizeof(wrong_size));
	wrong.resize(wrong_size);
	is.read(reinterpret_cast<char*>(wrong.data()), wrong_size * sizeof(int));

	// 读取 noendscore
	is.read(reinterpret_cast<char*>(&noendscore), sizeof(noendscore));
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