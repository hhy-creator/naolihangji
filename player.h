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
	bool operator==(const player&p1);
	player();
	void serializetxt(std::ostream& os) const;
	void deserializetxt(std::istream& is);
	player& SetName();
	string& GetName();
	string& revisepassword();
	void AddRight(vector<int>&, const int&);
	void AddWrong(vector<int>&, const int&);
	void CalAccuracy(const vector<int>&,const vector<int>&, vector<double>&);
	void CreatScore(vector<int>&, const int&, const bool& x,const vector<double>&time,const int&run);
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
	double& revisetimeall();
	int& revisescoreall();
private:
	string name;
	string password;
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
