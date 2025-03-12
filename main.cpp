#include "game.h"
#include "mananger.h"
#include <iostream>
using namespace std;
int main() 
{
	Mananger m1;
	game g1;
	g1.setrun(5);
	g1.getp1().SetPeopleBeginPos(30, 34);
	g1.getp1array()[0] = g1.getp1();
	/*g1.getp1array()->Movepeople()*/
	while (true) 
	{
		m1.RunChoose();
	}
}