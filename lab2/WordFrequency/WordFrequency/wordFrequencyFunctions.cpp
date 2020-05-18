#include "wordFrequencyFunctions.h"
#include <algorithm>
#include <locale.h>
#include <windows.h>

using namespace std;

Frequency CalcFrequency(std::istream& input)
{
	Frequency frequency;
	while (!input.eof())
	{
		string word;
		input >> word;
		if (word[0] != '\0')
		{
			for_each(word.begin(), word.end(), [](char& ch) 
			{
				ch = tolower(ch);
			});

			frequency[word]++;
		}
	}
	return frequency;
}
