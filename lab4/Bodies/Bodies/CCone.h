#pragma once
#include "CBody.h"

class CCone final : public CBody
{
public:
	CCone(double baseRad, double height, double density);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
private:
	virtual void OtherParameters(ostream& output) const override;
	double baseRadius;
	double height;
};