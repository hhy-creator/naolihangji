#include"mananger.h"
#include <iostream>
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
		cout << "�������������������������Լ��ĳһ�ص���ۣ�˫�����滮����ǰ��·�ߣ��������ʶԷ�����ô��������ɶԷ�ȴЦ�Żش�����������㣬Ҫ��" << endl;
}
void Mananger::Exitgame() 
{
	exit(0);
}
void Mananger::BeginGame() 
{
	ChooseGame();

}
void Mananger::ChooseGame() 
{
	cout << "��������Ҫ��ս�Ĺؿ�" << endl;
	int num;
	cin >> num;
	this->level = num;

}