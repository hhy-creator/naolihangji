#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>
using namespace std;
class player 
{
public:
	player(int);
	player();
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);
	void serializetxt(std::ostream& os) const;
	void deserializetxt(std::istream& is);
	void CheckMessage();
	player& SetName();
	string& GetName();
	void AddRight(vector<int>&, const int&);
	void AddWrong(vector<int>&, const int&);
	void CalAccuracy(const vector<int>&,const vector<int>&, vector<double>&);
	void CreatScore(vector<int>&, const int&, const bool& x,const vector<double>&time,const int&run);
	void ShowScore(const vector<int>&);
	void ShowAccuracy(const vector<double>&);
	vector<int>& Getscore();
	vector<int> returnGetscore()const;
	vector<double> returngettime()const;
	vector<double>& Getaccuracy();
	vector<int>& Getright();
	vector<int>& Getwrong();
	vector<double>& gettime();
	int& getnoendscore();
	int getnoend()const;
	double returntimeall();
	int returnscoreall();
private:
	string name;
	vector<double >time;
	vector<double>accuracy;
	vector<int>score;
	vector<int>right;
	vector<int>wrong;
	int noendscore=0;
	double timeall=0;
	int scoreall=0;



};
#endif // !PLAYER_H
