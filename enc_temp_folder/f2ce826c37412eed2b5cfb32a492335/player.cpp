#include <iostream>
#include <iomanip>
using namespace std;
#include "player.h"
#include <algorithm>
#include "easyx.h"
player& player::SetName()
{
	string name="";
	char buffer[256] = { 0 };
	initgraph(640, 480);
	setbkmode(TRANSPARENT);
	IMAGE i1;
	loadimage(&i1, "C:/Users/pcuser/Desktop/ʵѵ/��ȡ���뱳��.jpg", 640, 480);
	putimage(0, 0, &i1);
	InputBox(buffer,256, _T("����������:"), _T("�봴���û�"), _T("ȷ��"));
	for (int i = 0; i <14; i++) 
	{
		name += buffer[i];
	}
	closegraph();
	this->name = name;
	return *this;
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
void player::serialize(std::ostream& os) const {
	// д�� name
	os.write(reinterpret_cast<const char*>(&this->name), sizeof(this->name));

	// д�� time ����
	for (int i = 0; i < this->time.size(); i++) 
	{
		double m = time[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(double));
	}



	// д�� score ����
	
	for (int i = 0; i < this->score.size(); i++)
	{
		int m = score[i];
		os.write(reinterpret_cast<const char*>(&m), sizeof(int));
	}
	// д�� noendscore
	os.write(reinterpret_cast<const char*>(&this->noendscore), sizeof(int));
}
void  player::deserialize(std::istream& is) {
	player p1(0);
    // ��ȡname
	string name;
	is.read(reinterpret_cast<char*>(&name),sizeof(name));
	p1.name = name;
    // ��ȡvector<double> time
	for (int i = 0; i < p1.gettime().size(); i++)
	{
		double m;
		is.read(reinterpret_cast<char*>(&m), sizeof(double));
		p1.gettime()[i] = m;
	}

	for (int i = 0; i < p1.score.size(); i++)
	{
		double m;
		is.read(reinterpret_cast<char*>(&m), sizeof(double));
		p1.gettime()[i] = m;
	}

    // ��ȡnoendscore
	int m;
	is.read(reinterpret_cast<char*>(&p1.noendscore), sizeof(int));
	
	p1.CheckMessage();
}
void player::serializetxt(std::ostream& os) const 
{
	// д�� name
	for (int i = 0; i < this->name.size(); i++) 
	{
		os << this->name[i];
	}
	os << endl;
	// д�� time ����
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
	// д�� score ����

	for (int i = 0; i < this->score.size(); i++)
	{
		os << score[i]<<" ";
	}
	// д�� noendscore
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

	p1.CheckMessage();
}
player::player(int) :name(""), noendscore(0)
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
	cout << "�޾���ս������" << this->getnoendscore() << endl;
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
	cout << "�ؿ�" <<setfill(' ') << setw(8) << "����" << endl;
	for (int i = 1; i <= 5; i++) 
	{
		cout << i <<setfill(' ') << setw(8) << array1[i] << endl;
	}
	cout << endl;
}
void player::ShowAccuracy(const vector<double>&array1)
{
	cout << "�ؿ�" <<setfill(' ') << setw(8) << "��ȷ��" << endl;
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
