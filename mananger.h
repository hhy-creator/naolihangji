#ifndef MANANGER_H
#define MANANGER_H
#include <iostream>
#include "player.h"
#include"game.h"
#include <easyx.h>
#include <array>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <set>
class button
{
public:
	button();
	button(const int& x, const int& y, const int& width, const int& height, const std::string& text);
	void drawbutton();
	void drawbutton1();
	void drawbuttontxtBig(const int& txtsh,const int& txtsw,const int&txth,const int&txtw,const  COLORREF&);
	void drawgamebutton(const int&,const COLORREF&);
	std::string& revisetext();
	void drawgamerepetebutton();
	void drawgamerepetebutton1();
	void drawmyrepete( const COLORREF& textcolor);
	int returnx();
	int returny();
	int returnwidth();
	int returnheight();
	void changecolor();
	void drawchoosebutton();
	void drawGQbutton();
	~button();
	COLORREF &revisecolor();
	void reviseyellowifpass();
	void revisegreenifpass ();
	void reviseredifpass() ;
	bool returnyellowifpass();
	bool ifrepete();
	int& returnrepeterun1();
	int& returnrepeterun2();
	vector<int>repeter1;
	int drawnumber = 0;
private:
	int x;
	int y;
	int repeterun1;
	int repeterun2;
	int width;
	int height;
	COLORREF color;
	std::string text;
	int passnumber = 0;
	bool yellowifpass=0;
	bool greenifpass=0;
	bool redifpass = 0;
};
class Mananger
{
public:
	Mananger();
	~Mananger();
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
	void GameShowmess(game& g1,const int&i);
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
	void loadgameP();
	ExMessage getmousemessage();
	void loadChooseGQmenu();
	void createGameP( game& g1, const int& i);
	void loadGamebk();
	void readplayermessage();
	void recordmessage();
	void recordmessagetxt();
	vector<player> &readplayermessagetxt();
	void wujinRank(vector<player>& p1);
	void PuTongRank(vector<player>& p1);
	void drawMyroad( people*&,const int&run, array<array<button, 25>, 25>&b1);
	void drawYourroad( people*&, const int& run, array<array<button, 25>, 25>&b1);
	void drawanswerroad( people*&, const int& run, array<array<button, 25>, 25>&b1);
	void drawrepetebutton(array<array<button, 25>, 25>& b1);
	bool clickanswer( game&, array<array<button, 25>, 25>& b1);
	void drawYesP(const int& i);
	void drawNoP(game& g1, const int& i);
	void gameprogress();
	void setbutton();
private:
	int choose;
	int level;
	player p1;
	array<button, 10>buttonarr;
	array<button, 10>GQChoosebutton;
	IMAGE img[10];
	array<array<button,25>,25>GQbutton;
	vector<player>rank;

};
#endif // !MANANGER_H