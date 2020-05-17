#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../vector/vector/VectorFunctions.h"
#include <vector>

using namespace std;

TEST_CASE("ReadVector should fill an array from input stream")
{
	istringstream input("2 3.1 4 5");
	vector<double> array;
	array = ReadVector(input);	
	vector<double> expected{ 2, 3.1, 4, 5 };
	CHECK(array == expected);
	array.clear();
}

TEST_CASE("ProcessVector hould multiply min number on each element")
{
	const double minNumber = 2;

	vector<double> numbers;
	vector<double> required;

	numbers = { 2, 3, 4 };
	required = { (2 * minNumber), (3 * minNumber), (4 * minNumber) };
	ProcessVector(numbers);
	CHECK(numbers == required);
}

TEST_CASE("ProcessVector should multiply all numbers by zero")
{
	const double minNumber = 0;

	vector<double> numbers = { 0, 0, 0, 0 };
	vector<double> required = { (0 * minNumber), (0 * minNumber), (0 * minNumber), (0 * minNumber) };

	ProcessVector(numbers);
	CHECK(numbers == required);
}

TEST_CASE("PrintVector should displays array")
{
	ostringstream output;
	vector<double> array{ 4, 6, 8, 10.1 };
	PrintVector(output, array);
	REQUIRE(output.str() == "4 6 8 10.1 \n");
}