#include "game.h"
#include "mananger.h"
#include "player.h"
#include <iostream>
#include <random>
#include <easyx.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdexcept>
using namespace std;

int main() 
{
	Mananger m1;
	srand(time(0));
	while (true) 
	{
		m1.RunChoose();
	}


}
