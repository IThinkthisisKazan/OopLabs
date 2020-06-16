#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

#include "../../catch2/catch.hpp"
#include "../Bodies/Bodies/CSphere.h"
#include "../Bodies/Bodies/CBody.h"
#include "../Bodies/Bodies/CParallelepiped.h"
#include "../Bodies/Bodies/CCone.h"
#include "../Bodies/Bodies/CCylinder.h"
#include "../Bodies/Bodies/UserInterface.h"

using namespace std;

SCENARIO("Sphere Tests")
{
	CSphere* sphere = new CSphere(0.1, 1200);
	WHEN("Get radius") {
		THEN("Return correct radius")
		{
			CHECK(0.1 == sphere->GetRadius());
		}
	}
	WHEN("Get density")
	{
		THEN("Return correct density")
		{
			CHECK(1200 == static_cast<CBody*>(sphere)->GetDensity());
		}
	}
	WHEN("Get mass")
	{
		THEN("Return correct calculated mass")
		{
			CHECK(3.6 == static_cast<CBody*>(sphere)->GetMass());
		}
	}
	WHEN("Get volume")
	{
		THEN("Return correct calculated volume")
		{
			CHECK(0.003 == static_cast<CBody*>(sphere)->GetVolume());
		}
	}
}
SCENARIO("Cone Tests")
{
	CCone* cone = new CCone(0.1, 1, 1200);
	WHEN("Get base radius")
	{
		THEN("Return correct base radius")
		{
			CHECK(0.1 == cone->GetBaseRadius());
		}
	}
	WHEN("Get height")
	{
		THEN("Return correct height")
		{
			CHECK(1 == cone->GetHeight());
		}
	}

	WHEN("Get density")
	{
		THEN("Return correct density")
		{
			CHECK(1200 == static_cast<CBody*>(cone)->GetDensity());
		}
	}
	WHEN("Get mass")
	{
		THEN("Return correct calculated mass")
		{
			CHECK(12 == static_cast<CBody*>(cone)->GetMass());
		}
	}
	WHEN("Get volume")
	{
		THEN("Return correct calculated volume")
		{
			CHECK(0.01 == static_cast<CBody*>(cone)->GetVolume());
		}
	}
}
SCENARIO("Cylinder Tests")
{
	CCylinder* cylinder = new CCylinder(0.1, 1, 1200);
	WHEN("Get base radius")
	{
		THEN("Return correct base radius")
		{
			CHECK(0.1 == cylinder->GetBaseRadius());
		}
	}
	WHEN("Get height")
	{
		THEN("Return correct height")
		{
			CHECK(1 == cylinder->GetHeight());
		}
	}
	WHEN("Get density")
	{
		THEN("Return correct density")
		{
			CHECK(1200 == static_cast<CBody*>(cylinder)->GetDensity());
		}
	}
	WHEN("Get mass")
	{
		THEN("Return correct calculated mass")
		{
			CHECK(37.2 == static_cast<CBody*>(cylinder)->GetMass());
		}
	}
	WHEN("Get volume")
	{
		THEN("Return correct calculated volume")
		{
			CHECK(0.031 == static_cast<CBody*>(cylinder)->GetVolume());
		}
	}
}
SCENARIO("Parallelepiped Tests")
{
	CParallelepiped* parallelepiped = new CParallelepiped(1, 1, 1, 1200);
	WHEN("Get width")
	{
		THEN("Return correct width")
		{
			CHECK(1 == parallelepiped->GetWidth());
		}
	}
	WHEN("Get height")
	{
		THEN("Return correct height")
		{
			CHECK(1 == parallelepiped->GetHeight());
		}
	}
	WHEN("Get depth")
	{
		THEN("Return correct depth")
		{
			CHECK(1 == parallelepiped->GetDepth());
		}
	}
	WHEN("Get density")
	{
		THEN("Return correct density")
		{
			CHECK(1200 == static_cast<CBody*>(parallelepiped)->GetDensity());
		}
	}
	WHEN("Get mass")
	{
		THEN("Return correct calculated mass")
		{
			CHECK(1200 == static_cast<CBody*>(parallelepiped)->GetMass());
		}
	}
	WHEN("Get volume")
	{
		THEN("Return correct calculated volume")
		{
			CHECK(1 == static_cast<CBody*>(parallelepiped)->GetVolume());
		}
	}
}
SCENARIO("Find max mass body tests")
{
	vector<shared_ptr<CBody>> bodies;
	UserInterface UI = UserInterface();
	WHEN("One body in vector")
	{
		bodies.push_back(make_shared<CSphere>(0.1, 1200));
		THEN("This body have max mass")
		{
			shared_ptr<CBody> maxMassBody = UI.FindMaxMass(bodies);
			CBody* temp = maxMassBody.get();
			CHECK(3.6 == temp->GetMass());
		}
	}
	WHEN("Two bodies in vector")
	{
		bodies.push_back(make_shared<CSphere>(0.1, 1200));
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		THEN("Find body with max mass")
		{
			shared_ptr<CBody> maxMassBody = UI.FindMaxMass(bodies);
			CBody* temp = maxMassBody.get();
			CHECK(1200 == temp->GetMass());
		}
	}
	WHEN("Three bodies in vector")
	{
		bodies.push_back(make_shared<CSphere>(0.1, 1200));
		bodies.push_back(make_shared<CCylinder>(0.1, 1, 1200));
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		THEN("Find body with max mass")
		{
			shared_ptr<CBody> maxMassBody = UI.FindMaxMass(bodies);
			CBody* temp = maxMassBody.get();
			CHECK(1200 == temp->GetMass());
		}
	}
	WHEN("Two equal bodies in vector")
	{
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		THEN("Find body with max mass")
		{
			shared_ptr<CBody> maxMassBody = UI.FindMaxMass(bodies);
			CBody* temp = maxMassBody.get();
			CHECK(1200 == temp->GetMass());
		}
	}
}
SCENARIO("Find min mass body in water")
{
	vector<shared_ptr<CBody>> bodies;
	UserInterface UI = UserInterface();
	WHEN("One body in vector")
	{
		bodies.push_back(make_shared<CSphere>(0.1, 1200));
		THEN("This body have min mass")
		{
			shared_ptr<CBody> minMassBody = UI.FindMinMassInWater(bodies);
			CBody* temp = minMassBody.get();
			CHECK(3.6 == temp->GetMass());
		}
	}
	WHEN("Two bodies in vector")
	{
		bodies.push_back(make_shared<CSphere>(0.1, 1200));
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		THEN("Find body with min mass in water")
		{
			shared_ptr<CBody> minMassBody = UI.FindMinMassInWater(bodies);
			CBody* temp = minMassBody.get();
			CHECK(3.6 == temp->GetMass());
		}
	}
	WHEN("Three bodies in vector")
	{
		bodies.push_back(make_shared<CSphere>(0.1, 1200));
		bodies.push_back(make_shared<CCylinder>(0.1, 1, 1200));
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		THEN("Find body with min mass in water")
		{
			shared_ptr<CBody> minMassBody = UI.FindMinMassInWater(bodies);
			CBody* temp = minMassBody.get();
			CHECK(3.6 == temp->GetMass());
		}
	}
	WHEN("Two equal bodies in vector")
	{
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		bodies.push_back(make_shared<CParallelepiped>(1, 1, 1, 1200));
		THEN("Find body with min mass in water")
		{
			shared_ptr<CBody> minMassBody = UI.FindMinMassInWater(bodies);
			CBody* temp = minMassBody.get();
			CHECK(1200 == temp->GetMass());
		}
	}
}