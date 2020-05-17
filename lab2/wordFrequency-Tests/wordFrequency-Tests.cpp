#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WordFrequency/WordFrequency/wordFrequencyFunctions.h"
#include <iostream>
#include <sstream>

using namespace std;

TEST_CASE("CalcFrequency should return the frequency of occurrence of words")
{
	setlocale(LC_CTYPE, "rus");
	istringstream input("hello HEllo heLLO \n\n hi \n How\thow you");
	Frequency expected = {
		{ "hello", 3 },
		{ "hi", 1 },
		{ "how", 2 },
		{ "you", 1 }
	};
	Frequency frequency = CalcFrequency(input);
	CHECK(expected == frequency);
}

TEST_CASE("CaclFrequency should return empty frequency if no words were in input")
{
	istringstream input(" \t \n \t \n ");
	Frequency expected;
	Frequency frequency = CalcFrequency(input);
	CHECK(expected == frequency);
}