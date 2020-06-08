#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../PrimeNumbers/PrimeNumbers/PrimeNumbersFunctions.h"
#include <iostream>

using namespace std;

TEST_CASE("If upperBound < 2 should return empty set")
{
	int upperBound = 1;
	set<int> testSet = GeneratePrimeNumbersSet(upperBound);
	set<int> requeired = set<int>{};

	CHECK(testSet == requeired);
}

TEST_CASE("If upperBound is between 2 and MAX_NUMBER shoudl return set of prime numbers")
{
	int upperBound = 12;
	set<int> testSet = GeneratePrimeNumbersSet(upperBound);
	set<int> required = { 2, 3, 5, 7, 11 };

	CHECK(testSet == required);

	upperBound = 20;
	testSet = GeneratePrimeNumbersSet(upperBound);
	 required = { 2, 3, 5, 7, 11, 13, 17, 19 };

	CHECK(testSet == required);
}

TEST_CASE("If upperBound == 100'000'000 number count should be 5761255")
{
	int upperBound = 100000000;
	set<int> testSet = GeneratePrimeNumbersSet(upperBound);

	CHECK(testSet.size() == 5761455);
}