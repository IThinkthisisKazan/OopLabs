#pragma once
#include "CBody.h"

class CSphere final : public CBody
{
public:
	CSphere(double radius, double density);
	double GetRadius() const;
	double GetVolume() const override;
private:
	virtual void OtherParameters(ostream& output) const override;
	double radius;
};