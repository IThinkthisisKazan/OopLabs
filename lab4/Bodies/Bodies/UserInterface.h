#pragma once
#include <memory>
#include <vector>
#include "CBody.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"

class UserInterface {
public:
	shared_ptr<CBody> FindMaxMass(const vector<shared_ptr<CBody>>& bodies);
	shared_ptr<CBody> FindMinMassInWater(const vector<shared_ptr<CBody>>& bodies);

	void UserMenu(vector<shared_ptr<CBody>>& bodies, istream& input, ostream& output);
	void PrintBody(const shared_ptr<CBody>& body, ostream& output);
	void PrintAllBodies(const vector<shared_ptr<CBody>>& bodies, ostream& output);
};