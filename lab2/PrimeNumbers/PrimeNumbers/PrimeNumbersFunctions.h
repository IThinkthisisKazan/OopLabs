#pragma once
#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound);

set<int> GeneratePrimeSet(const vector<bool>& numbers);

vector<bool> SelectPrimeNumbers(int upperBound);