#include "game.h"
#include "mananger.h"
#include "player.h"
#include <iostream>
#include <random>
#include <easyx.h>
class button
{
public:
	button();
	button(const int& x, const int& y, const int& width, const int& height, const std::string& text);
	void drawbutton();
	~button();
private:
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	std::string text;
};
using namespace std;
button::button(const int& x, const int& y, const int& width, const int& height, const string& text1)
	:text(text1), x(x), y(y), width(width), height(height), color(YELLOW)
{

}
button::~button() {}
void button::drawbutton()
{
	setfillcolor(this->color);
	settextstyle(35, 0, "楷体");
	fillrectangle(this->x, this->y, this->x + this->width, this->y + this->height);
	outtextxy(this->x, this->y, this->text.c_str());
}
button::button() {}
void createwindow()
{
	initgraph(900, 600);
	IMAGE beginimage;
	loadimage(&beginimage, "C:/Users/pcuser/Desktop/实训/开始界面.jpg", 900, 600);
	putimage(0, 0, &beginimage);
	button b0(300, 200, 200, 50, "查看规则");
	b0.drawbutton();
	while (1);
	closegraph();
}
using namespace std;

int main() 
{
	Mananger m1;
	//srand(time(0));
	//while (true) 
	//{
	//	m1.RunChoose();
	//}
	createwindow();
}
