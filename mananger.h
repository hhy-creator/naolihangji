#ifndef MANANGER_H
#define MANANGER_H
#include <iostream>
#include "player.h"
#include"game.h"

class Mananger
{
public:
	Mananger();
	void ChangeChoose();
	void ShowMenu()const;
	void ShowRule()const;
	void Exitgame();
	void BeginGame();
	void ChooseGame();
	void RunChoose();
	int getlevel()const;
	void CheckMessage(player&);
	void GameShowmess(game& g1);
	void GameShowmess1(game& g1);
	player& getplayer();
	void creatgame1();
	void creatgame2();
	void creatgame3();
	void creatgame4();
	void creatgame5();
	void randomcreatgame();
	void PlayerGreatgame();
	void challengegame();
	void randomcreatgame(int number1);
	void PlayerGameShowmess(game& g1);
	void noendchallenge();

private:
	int choose;
	int level;
	player p1;

};

#endif // !MANANGER_H