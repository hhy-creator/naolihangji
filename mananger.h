#ifndef MANANGER_H
#define MANANGER_H
#include <iostream>
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

private:
	int choose;
	int level;

};

#endif // !MANANGER_H