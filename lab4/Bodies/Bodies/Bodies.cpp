#include <iostream>
#include <vector>
#include "CBody.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	vector<shared_ptr<CBody>> bodies;
	UserInterface UI = UserInterface();
	UI.UserMenu(bodies, cin, cout);
	UI.PrintAllBodies(bodies, cout);
	if (bodies.size() != 0) {
		cout << "Body with biggest weight: " << endl;
		UI.PrintBody(UI.FindMaxMass(bodies), cout);
		cout << "Lightest body in water: " << endl;
		UI.PrintBody(UI.FindMinMassInWater(bodies), cout);
	}
	return 0;
}