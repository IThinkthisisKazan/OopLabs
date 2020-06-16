#include "CCone.h"


CCone::CCone(double baseRad, double height, double density)
	:CBody("Cone", density),
	baseRadius(baseRad),
	height(height)
{
}

double CCone::GetBaseRadius() const
{
	return CCone::baseRadius;
}

double CCone::GetHeight() const
{
	return CCone::height;
}

double CCone::GetVolume() const
{
	return round((3.14 * baseRadius * baseRadius * height) / 3 * 1000) / 1000;
}

void CCone::OtherParameters(ostream& output) const
{
	output << "Height: " << GetHeight() << endl;
	output << "Base radius:" << GetBaseRadius() << endl;
}