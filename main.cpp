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
#include <algorithm>
#include <conio.h>
#include <graphics.h>
#include <set>
#include <time.h>
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
