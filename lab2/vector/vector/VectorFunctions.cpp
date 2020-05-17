#include "stdafx.h"
#include "VectorFunctions.h"

using namespace std;

vector<double> ReadVector(istream& input)
{
	return vector<double>(istream_iterator<double>(input), (istream_iterator<double>()));
}

void ProcessVector(vector<double>& vector)
{
	const double minElement = *min_element(vector.begin(), vector.end());
	for (size_t i = 0; i < vector.size(); i++)
	{
		vector.at(i) = vector.at(i) * minElement;
	}
}

void PrintVector(ostream& output, const vector<double>& vector)
{
	output << setprecision(3);
	copy(vector.begin(), vector.end(), ostream_iterator<double>(output, " "));
	output << endl;
}
