#include "PrimeNumbersFunctions.h"

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
	{
		return set<int>{};
	}

	vector<bool> isPrime = SelectPrimeNumbers(upperBound);

	set<int> primeNumbers = GeneratePrimeSet(isPrime);

	return primeNumbers;
}

set<int> GeneratePrimeSet(const vector<bool>& numbers)
{
	set<int> selectedNumbers;
	for (auto i = 2; i < numbers.size(); i++)
	{
		if (numbers[i])
		{
			selectedNumbers.insert(i);
		}
	}
	return selectedNumbers;
}

vector<bool> SelectPrimeNumbers(int upperBound)
{
	vector<bool> isPrime((int)upperBound + 1, true);
	for (int i = 2; i * i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}
	return isPrime;
}