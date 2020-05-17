#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include "lab2/vector/vector/VectorFunctions.h"

using namespace std;

TEST_CASE("should multiply all elements by minimal element")
{
	vector<double> numbers;
	vector<double> required;

	numbers = { 2, 3, 4, 5 };
	required = { 4, 6, 8, 10 };
	ProcessVector(numbers);
	CHECK(numbers == required);
}