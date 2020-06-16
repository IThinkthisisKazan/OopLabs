#pragma once
#include <string>
#include <fstream>
using namespace std;

class CBody
{
public:
	CBody(string type, double density);
	virtual ~CBody();
	double GetDensity();
	virtual double GetVolume() const = 0;
	double GetMass();
	void PrintInfo(ostream& output);//string ToString();
private:
	virtual void OtherParameters(ostream& output) const = 0;
	double density;
	string type;
};
