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
#include <conio.h>
#include <set>
#include<time.h>
#include <graphics.h>
struct gameku 
{
	game g1;
	std::string name;
};
class ship 
{
public:
	ship(const int& bx, const int& by);
	int& reviseMyx();
	int& reviseMyy();
	people*& revisepath();
	void createMypath(const int& bx, const int& by);
	bool ifOKPath();
	bool ifpass(people*& p1, const int& num,const int& run)const;
	int getrun();
private:
	int Myx;
	int Myy;
	people* path;
	int run;
};
class button
{
public:
	button();
	void drawbuttonwithPic( IMAGE*);
	button(const int& x, const int& y, const int& width, const int& height, const std::string& text);
	button(const int& x, const int& y, const int& width, const int& height, const std::string& text, const IMAGE& img);
	void drawbutton();
	void drawbutton1();
	void drawbuttontxtBig(const int& txtsh,const int& txtsw,const int&txth,const int&txtw,const  COLORREF&);
	void drawgamebutton(const int&,const COLORREF&);
	void drawgamebutton(const int&, const COLORREF&,const bool& x);
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
	bool returngreenifpass();
	bool ifrepete();
	int& returnrepeterun1();
	int& returnrepeterun2();
	vector<int>repeter1;
	int drawnumber = 0;
	button& operator=(const button&b1);
	int& returnbushu();
	bool& reviseifokclick();
	bool& revisecreateifpass();
	bool& reviseMycreateifpass();
	bool& revisebombpass();
	bool& reviseCreateModeifpass();
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
	int bushu;
	bool ifokclick=1;
	bool createifpass=0;
	bool CreateModeIfpass = 0;
	bool Mycreateifpass = 0;
	bool bombpass = 0;
};
class Mananger
{
public:
	Mananger();
	bool ifOKCreat(const game&g1);
	~Mananger();
	void rankP();
	void getfromgameku(const string& name, const int& GQnumber);
	void ChangeChoose();
	void ShowRule();
	void Exitgame();
	void ChooseGame();
	void RunChoose();
	void CreateMode();
	int getlevel()const;
	player& getplayer();
	void Mycreate();
	void randomcreatgame();
	void PlayerGreatgame();
	void drawYesPPlayerCreate(game& g1);
	void drawNoPlayergame(game& g1);
	void PlayercreatrGame(game& g1);
	void challengegame();
	void randomcreatgame(int number1);//无尽挑战
	void randomcreatgame(int number1, bool x);//挑战模式
	void noendchallenge();
	int ifinbutoon(button&,ExMessage );
	void loadgameP();
	ExMessage getmousemessage();
	void createGameP( game& g1, const int& i);
	void createGameP(game& g1);
	void MyCreateGameP(game& g1, people*& p1);
	void creatrGameChallenge(game& g1);
	void recordmessagetxt();
	vector<player> &readplayermessagetxt();
	void wujinRank(vector<player>& p1);
	void PuTongRank(vector<player>& p1);
	button**& drawMyroad( people*&,const int&run,  button**&);
	button**& drawMyCreate(people*&, const int& run, button**&);
	button**& drawYourroad( people*&, const int& run, button**& b1);
	button**& drawOtherPath(people*& p2, const int& run, button**& b1);
	void drawanswerroad( people*&, const int& run, button**& b1);
	void drawanswerroad(people*&, const int& run, button**& b1,bool& x);
	button**& drawrepetebutton(button**& b1);
	bool clickanswer( game&, button**& b1);
	void drawYesP(const int& i);
	void drawNoP(game& g1, const int& i);
	void drawYesP(game&g1);
	void drawYesPChallenge(game& g1);
	void drawNoP(game& g1);
	void createmiddle(people*& p1,game& g1);
	void drawcreate(people*& p2, const int& run, button**& b1);
	void drawNoMyCreate();
	void setbutton();
	bool ifinimage(ExMessage,IMAGE&, const int& wb, const int& hb);
	vector<gameku>& readgamekutxt();
	void checkmessageP();
	void PTrankP();
	void WJrankP();
	void DGrankP();
	void dlOrZc();
private:
	int choose;
	int level;
	player p1;
	array<button, 15>buttonarr;
	IMAGE img[35];
	IMAGE ymimg[20];
	IMAGE Move[4];
	array<array<button,25>,25>GQbutton;
	vector<player>rank;
	vector<gameku>gameall;

};
#endif // !MANANGER_H