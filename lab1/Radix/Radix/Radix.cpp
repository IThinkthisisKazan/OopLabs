#include <iostream>
#include <string>
#include <algorithm>
#include <optional>

using namespace std;

struct Arguments
{
	int source = 0;
	int destination = 0;
	string value;
};

optional<Arguments> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout
			<< "Invalid number of arguments\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>" << endl;
		return std::nullopt;
	}
	Arguments args;

	args.source = std::atoi(argv[1]);
	args.destination = std::atoi(argv[2]);
	args.value = argv[3];

	return args;
}

bool SafeMult(int a, int b, int& result)
{
	if (a == 0 || b == 0)
	{
		result = 0;
		return true;
	}
	if (a > 0)
	{
		if (b > 0)
		{
			if (a <= (INT_MAX / b))
			{
				result = a * b;
				return true;
			}
		}
		else
		{
			if (b >= (INT_MIN / a))
			{
				result = a * b;
				return true;
			}
		}
	}
	else
	{
		if (b > 0)
		{
			if (a >= (INT_MIN / b))
			{
				result = a * b;
				return true;
			}
		}
		else
		{
			if (b >= (INT_MAX / a))
			{
				result = a * b;
				return true;
			}
		}
	}
	return false;
}

bool SafeAdd(int a, int b, int& result)
{
	if (b > 0)
	{
		if (INT_MAX - b >= a)
		{
			result = a + b;
			return true;
		}
	}
	else
	{
		if (INT_MIN - b <= a)
		{
			result = a + b;
			return true;
		}
	}
	return false;
}

bool CheckRadix(int number, int radix) {
	if (number >= 0 && number <= radix)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int extractDigit(char symbol, int radix, bool& wasError)
{
	int number;
	if (symbol >= '0' && symbol <= '9')
	{
		number = symbol - '0';
		if (CheckRadix(number, radix)) {
			return number;
		}
		wasError = true;
		return 0;
	}
	else
	{
		if (symbol >= 'A' && symbol <= 'Z') 
		{
			number = symbol - 'A' + 10;
			if (CheckRadix(number, radix)) {
				return number;
			}
			wasError = true;
			return 0;
		}
		else {
			wasError = true;
			cout << "Incorrect symbol in 3rd argument" << endl;
			return 0;
		}
	}
}

int StringToInt(const string& str, int radix, bool& wasError)
{
	const int maxRadix = ('Z' - 'A') + 11;
	size_t i = 0;
	int digit = 0;
	int n = 0;
	bool isNegative = false;
	if (str.length() == 0) {
		wasError = true;
		cout << "Value cannot be empty" << endl;
		return 0;
	}
	if (str[0] == '-')
	{
		isNegative = true;
		isNegative = true;
		i = 1;
	}
	while (i <= str.length() - 1 && !wasError)
	{
		digit = extractDigit(str[i], radix, wasError);
		if (isNegative)
		{
			digit = -digit;
		}
		if (!SafeMult(n, radix, n) || !SafeAdd(n, digit, n))
		{
			wasError = true;
			cout << "Overflow error" << endl;
		}
		i++;
	}
	return n;
}

char extractChar(int value) {
	if (value > 9)
	{
		return (char)(value + 'A' - 10);
	}
	else
	{
		return (char)(value + '0');
	}
}

string IntToString(int n, int radix) {
	string result = "";
	string isNegative = "";
	int absN = 0;
	if (n < 0)
	{
		isNegative = "-";
	}
	do
	{
		absN = abs(n % radix);
		result = extractChar(absN) + result;
		n = n / radix;
	} 
	while (n != 0);

	result = isNegative + result;
	return result;
}

int CheckNotation(int radix)
{
	if (radix < 2 || radix > 36)
	{
		return false;
	}
	return true;
}


bool ConvertValue(int source, int destination, const string& value)
{
	bool wasError = false;
	if (CheckNotation(source) && CheckNotation(destination))
	{
		int number = StringToInt(value, source, wasError);

		if (wasError)
		{
			return false;
		}

		string result = IntToString(number, destination);
		cout << result << endl;

		return true;
	}
	cout << "Error in 1st or 2nd argument" << endl;
	return false;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	string result;

	if (!ConvertValue(args->source, args->destination, args->value))
	{
		return 1;
	}

	return 0;
}