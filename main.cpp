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
#include <graphics.h>
#include <string>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
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
