#include "CCylinder.h"

CCylinder::CCylinder(double baseRad, double height, double density)
	:CBody("Cylinder", density),
	height(height),
	baseRadius(baseRad)
{
}

double CCylinder::GetBaseRadius() const
{
	return CCylinder::baseRadius;
}

double CCylinder::GetHeight() const
{
	return CCylinder::height;
}

double CCylinder::GetVolume() const
{
	return round(3.14 * baseRadius * baseRadius * height * 1000) / 1000;
}

void CCylinder::OtherParameters(ostream& output) const
{
	output << "Height: " << GetHeight() << endl;
	output << "Base radius:" << GetBaseRadius() << endl;
}