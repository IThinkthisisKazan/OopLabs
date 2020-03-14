#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 

using namespace std;

int StringToInt(const std::string& str, int radix, bool& wasError) {
	try {
		int result = std::stoi(str, nullptr, radix);
		return result;
	}
	catch(std::out_of_range & err){
		cout << err.what();
		wasError = true;
		return 0;
	}
}

std::string IntToString(int n, int radix, bool& wasError) {
	std::string res = "";
	std::string negative = "";
	if (n < 0) {
		negative = "-";
		n = abs(n);
	}
	while (n > 0) {
		if (n % radix > 9) {
			res = (char)((n % radix) + 'A' - 10) + res;
		}
		else {
			res = (char)((n % radix) + '0') + res;
		}
		n = n / radix;
	}
	if (res == "") {
		res = "0";
	}
	res = negative + res;
	return res;
}

int IsDigits(const std::string& str)
{
	if (std::all_of(str.begin(), str.end(), ::isdigit)) {
		int result = std::stoi(str);
		if ((result > 2) && (result < 32)) {
			return result;
		} else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

bool CheckArgs(string& arg1, string& arg2, string& arg3) {
	if (IsDigits(arg1) != -1 && IsDigits(arg2) != -1) {
		std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int negativeSwitch = 0;
		if (arg3[0] == '-') {
			negativeSwitch = 1;
		}
		if (arg3.substr(negativeSwitch, arg3.size()).find_first_not_of(alphabet.substr(0, IsDigits(arg1) + 1)) == std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
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

	if (CheckArgs(source, destination, value)) {
		bool err = 0;
		int source2 = std::stoi(argv[1]);
		int destination2 = atoi(argv[2]);

		int val = StringToInt(value, source2, err);
		if (err) {
			cout << "Out of range";
			return 1;
		}
		cout << IntToString(val, destination2, err) << endl;
		
		return 0;
	}
	else {
		cout << "Input error";
		return 1;
	}
}