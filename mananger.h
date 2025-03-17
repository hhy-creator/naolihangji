#ifndef MANANGER_H
#define MANANGER_H
#include <iostream>
#include "player.h"
#include"game.h"
class Mananger
{
public:
	void ChangeChoose();
	void ShowMenu();
	void ShowRule();
	void Exitgame();
	void BeginGame();
	void ChooseGame();
	void RunChoose();
	int getlevel();
	void CheckMessage(player&);
	void GameShowmess(game& g1);
	player& getplayer();
	void creatgame1();
	void creatgame2();
	void creatgame3();
	void creatgame4();
	void creatgame5();
private:
	int choose;
	int level;
	player p1;
};

#endif // !MANANGER_H