#include "wordFrequencyFunctions.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	std::cout.imbue(std::locale());
	Frequency frequency = CalcFrequency(cin);

	if (frequency.empty())
	{
		cout << "No words found\n";
		return 0;
	}

	for (auto el : frequency)
	{
		cout << el.first << " -> " << el.second << endl;
	}

	return 0;
}