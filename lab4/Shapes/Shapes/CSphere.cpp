#include "CSphere.h"

CSphere::CSphere(double radius, double density) : CBody("Sphere", density), radius(radius)
{
}

double CSphere::GetRadius() const
{
	return CSphere::radius;
}

double CSphere::GetVolume() const
{
	return round((4 / 3 * 3.14 * radius * radius * radius) * 1000) / 1000;
}

void CSphere::OtherParameters(ostream& output) const
{
	output << "Radius: " << GetRadius() << endl;
}