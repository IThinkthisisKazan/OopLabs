#include "stdafx.h"
#include "VectorFunctions.h"

using namespace std;

int main()
{
	vector<double> inputVector = ReadVector(cin);

	try
	{
		ProcessVector(inputVector);
		if (inputVector.empty())
		{
			cout << "Vector is emty";
		}
		else
		{
			sort(inputVector.begin(), inputVector.end());
			PrintVector(cout, inputVector);
			return 0;
		}
	}
	catch(const std::exception& e)
	{
		cout << e.what();
		return 1;
	}
}