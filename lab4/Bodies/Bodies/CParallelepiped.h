#pragma once
#include "CBody.h"

class CParallelepiped final : public CBody
{
public:
	CParallelepiped(double width, double height, double depth, double density);
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;
private:
	double width;
	double height;
	double depth;
};