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

int StringToInt(const string str, int radix, bool& wasError)
{
	const int maxRadix = ('Z' - 'A') + 11;
	size_t i = 0;
	int number = 0;
	int n = 0;
	bool negativeSwitch = false;
	if (str[0] == '-')
	{
		negativeSwitch = true;
		i = 1;
	}
	while (i <= str.length() - 1 && !wasError)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			number = str[i] - '0';
		}
		else
		{
			number = str[i] - 'A' + 10;
		}
		if (negativeSwitch)
		{
			number = -number;
		}
		if (!SafeMult(n, radix, n) || !SafeAdd(n, number, n))
		{
			wasError = true;
			cout << "Overflow error" << endl;
		}
		i++;
	}
	return n;
}

string IntToString(int n, int radix) {
	string result = "";
	string negativeSwitch = "";
	int absN = 0;
	if (n < 0)
	{
		negativeSwitch = "-";
	}
	do
	{
		absN = abs(n % radix);
		if (absN > 9)
		{
			result = (char)(absN + 'A' - 10) + result;
		}
		else
		{
			result = (char)(absN + '0') + result;
		}
		n = n / radix;
	} while (n != 0);

	result = negativeSwitch + result;
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

bool CheckArgs(int source, int destination, const string value, bool& wasError)
{
	if (CheckNotation(source) && CheckNotation(destination))
	{
		string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int negativeSwitch = 0;
		if (value[0] == '-')
		{
			negativeSwitch = 1;
		}
		if (value.substr(negativeSwitch, value.size()).find_first_not_of(alphabet.substr(0, source)) == string::npos)
		{
			return true;
		}
		else
		{
			cout << "error in 3rd argument" << endl;
			wasError = true;
			return false;
		}
	}
	else
	{
		cout << "Notation out of range" << endl;
		wasError = true;
		return false;
	}
}

bool ConvertValue(int source, int destination, const string value)
{
	bool wasError = false;
	if (CheckArgs(source, destination, value, wasError))
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