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

int ExtractDigit(char symbol, int radix, bool& wasError)
{
	wasError = false;
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
	wasError = false;
	if (str.length() == 0) {
		wasError = true;
		return 0;
	}
	bool isNegative = false;
	size_t i = 0;
	if (str[0] == '-')
	{
		isNegative = true;
		i = 1;
	}
	int digit = 0;
	int n = 0;
	while (i <= str.length() - 1 && !wasError)
	{
		digit = ExtractDigit(str[i], radix, wasError);
		if (isNegative)
		{
			digit = -digit;
		}
		if (!SafeMult(n, radix, n) || !SafeAdd(n, digit, n))
		{
			wasError = true;
		}
		i++;
	}
	return n;
}

char extractChar(int value) 
{
	if (value > 9)
	{
		return (char)(value + 'A' - 10);
	}
	else
	{
		return (char)(value + '0');
	}
}

string IntToString(int n, int radix) 
{
	string isNegative;
	int absN = 0;
	if (n < 0)
	{
		isNegative = "-";
	}
	string result;
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


bool ConvertValue(int source, int destination, const string& value, string& result)
{
	bool wasError = false;
	if (CheckNotation(source) && CheckNotation(destination))
	{
		int number = StringToInt(value, source, wasError);

		if (wasError)
		{
			cout << "Error in 3rd argument" << endl;
			return false;
		}
		result = IntToString(number, destination);
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

	if (!ConvertValue(args->source, args->destination, args->value, result))
	{
		return 1;
	}

	cout << result << endl;
	return 0;
}