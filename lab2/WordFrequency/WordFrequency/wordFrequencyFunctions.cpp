#include "wordFrequencyFunctions.h"
#include <algorithm>
#include <locale.h>
#include <windows.h>

using namespace std;

char MyToLower(char& ch)
{
	if (ch > 'A' && ch < 'Z')
	{
		return ch + 'z' - 'Z';
	}
	if (ch > 'À' && ch < 'ß')
	{
		return CharLower(ch);
	}
	return ch;
}

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
				ch = MyToLower(ch);
			});
			frequency[word]++;
		}
	}
	return frequency;
}
