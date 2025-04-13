#ifndef MANANGER_H
#define MANANGER_H
#include <iostream>
#include "player.h"
#include"game.h"
#include <easyx.h>
#include <array>
class button
{
public:
	button();
	button(const int& x, const int& y, const int& width, const int& height, const std::string& text);
	void drawbutton();
	void drawbutton1();
	int returnx();
	int returny();
	int returnwidth();
	int returnheight();
	void changecolor();
	void drawchoosebutton();
	void drawGQbutton();
	~button();
private:
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	std::string text;
	int passnumber = 0;
};
class Mananger
{
public:
	Mananger();
	void ChangeChoose();
	void ShowMenu();
	void ShowRule();
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
	void loadwindow();
	int ifinbutoon(button&,ExMessage );
	void loadrule();
	ExMessage getmousemessage();
	void loadChooseGQmenu();
	void createGameP();
	void loadGamebk();

private:
	int choose;
	int level;
	player p1;
	array<button, 10>buttonarr;
	array<button, 10>GQChoosebutton;
	IMAGE img[10];
	array<button, 625>GQbutton;
};
#endif // !MANANGER_H