#include <iostream>
#include "PrimeNumbersFunctions.h"

using namespace std;

const int MAX_NUMBER = 100000000;

void PrintSet(set<int> primeNumbers)
{
	for (auto it = primeNumbers.begin(); it != primeNumbers.end(); ++it)
	{
		cout << ' ' << *it;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout
			<< "Invalid number of arguments\n"
			<< "Use: PrimeNumbers.exe <upper bound>\n";
		return 1;
	}

	int upperBound = atoi(argv[1]);

	if (upperBound > MAX_NUMBER)
	{
		cout << "upperBound cannot exceed 100.000.000" << endl;
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);

	PrintSet(primeNumbers);
	return 0;
}