#include"mananger.h"
#include"game.h"
#include <iostream>
#include <time.h>
using namespace std;
void Mananger::RunChoose() 
{
	ShowMenu();
	ChangeChoose();
	switch (choose) 
	{
	case 1:
		{
			system("cls");
			BeginGame();
			break;
		}
	case 2: 
	{
		system("cls");
		ShowRule();
		break;

	}
	case 0:
	{
		system("cls");
		Exitgame();
		break;
	}

	}
}
void Mananger::ChangeChoose() 
{
	int choose1;
	cin >> choose1;
	this->choose = choose1;
}
void Mananger::ShowMenu() 
{
	cout << "       ���������ѡ��" << endl;
	cout << "****************************" << endl;
	cout << "********1��ʼ��Ϸ***********" << endl;
	cout << "********2�˽���Ϸ����*******" << endl;
	cout << "*********0�˳���Ϸ**********" << endl;
	cout << "****************************" << endl;
};
void Mananger::ShowRule() 
{
	cout << "��������һ��ͨ��ĳһĿ�ĵصĺ���·�ߣ�ͬʱ������Ϊ��������ܻ����һ�˵����·�������������һ�˵�ʵ��·����" << endl;
}
void Mananger::Exitgame() 
{
	cout << "��Ϸ���˳�" << endl;
	exit(0);
}
void Mananger::BeginGame() 
{
	ChooseGame();

}
int Mananger::getlevel() 
{
	return level;
}
void creatgame1()
{
	game g1;
	g1.setrun(5);
	g1.setzihzhen();
	g1.getp1().SetPeopleBeginPos(30, 34);
	g1.getp1array()[0] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[1] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[2] = g1.getp1();
	g1.getp1().Movepeople(UP);
	g1.getp1array()[3] = g1.getp1();
	g1.getp1().Movepeople(RIGHT);
	g1.getp1array()[4] = g1.getp1();
	g1.getp2().SetPeopleBeginPos(35, 31);
	g1.getp2array()[0] = g1.getp2();
	g1.getp2().Movepeople(LEFT);
	g1.getp2array()[1] = g1.getp2();
	g1.getp2().Movepeople(LEFT);
	g1.getp2array()[2] = g1.getp2();
	g1.getp2().Movepeople(DOWN);
	g1.getp2array()[3] = g1.getp2();
	g1.getp2().Movepeople(DOWN);
	g1.getp2array()[4] = g1.getp2();
	g1.setp2relative(g1.getp2relative(), g1.getp2array(), g1.getp1array(), g1.getrun());
	bool x = 1;
	while (x) {
		g1.DisplayRelativeMove(g1.getp1array(), g1.getp2relative());
		bool a = g1.IfYes(g1.getrun(), g1.getp2array());
		if (a)
		{
			x = 0;
			cout << "��Ϸ��ս�ɹ��������ġ�" << endl;
			break;
		}
		else
		{
			cout << "��սʧ��" << endl;
			cout << "�Ƿ��ٴ���ս��(1��ʾ�ǣ�0��ʾ��)" << endl;
			bool aga;
			cin >> aga;
			if (!aga) { cout << "������ս" << endl; break; }
			else { system("cls"); }
		}
	}
}
void Mananger::ChooseGame() 
{
	cout << "��������Ҫ��ս�Ĺؿ�:" << endl;
	int num;
	cin >> num;
	this->level = num;
	switch (getlevel()) 
	{
	case 1: 
	{
		creatgame1();
		break;
	}
	}
}