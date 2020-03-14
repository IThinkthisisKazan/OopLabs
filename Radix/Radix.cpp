#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int StringToInt(const std::string& str, int radix, bool& wasError) {
	int result = 0;
	size_t strsize = str.size() - 1;
	for (int i = strsize; i >= 0; i--) {
		if (isdigit(str[i])) {
			result += (str[i] - '0') * pow(radix, strsize - i);
		}
		else {
			if (('A' <= str[i]) && (str[i] <= 'Z')) {
				result += (str[i] - 55) * pow(radix, strsize - i);
			}
			else {
				wasError = true;
				break;
			}
		}
	}
	return result;
}

std::string IntToString(int n, int radix, bool& wasError) {
	std::string res = "";
	while (n > 0) {
		if (n % radix > 9) {
			res = (char)((n % radix) + 'A' - 10) + res;
		}
		else {
			res = (char)((n % radix) + '0') + res;
		}
		n = n / radix;
	}
	return res;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	std::string source = argv[1];
	std::string destination = argv[2];
	std::string value = argv[3];
	bool err = 0;
	int source2;
	try 
	{
		source2 = std::stoi(argv[1]);
	}
	catch(std::exception exception)
	{
		cout << "1st argument is not a number";
		return 1;
	}
	int destination2 = atoi(argv[2]);
	if (((source2 < 2) || (source2 > 32)) || ((destination2 < 2) || (destination2 > 32)))
	{
		cout << "Error: check args" << endl;
		return 1;
	}
	cout << source2 << endl;

	int val = StringToInt(value, source2, err);
	cout << IntToString(val, destination2, err) << endl;

	return 0;
}