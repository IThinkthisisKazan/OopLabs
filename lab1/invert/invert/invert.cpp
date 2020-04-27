#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

const int MATRIX_SIZE = 3;
typedef std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE> Matrix3x3;

void Transpose(Matrix3x3& matrix)
{
	double temp;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = i; j < MATRIX_SIZE; j++)
		{
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
}

double FindDeterminant(const Matrix3x3& matrix)
{
	double determinant = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[1][0] * matrix[0][2] * matrix[2][1]
		+ matrix[2][0] * matrix[0][1] * matrix[1][2]
		- matrix[2][0] * matrix[1][1] * matrix[0][2]
		- matrix[1][0] * matrix[0][1] * matrix[2][2]
		- matrix[0][0] * matrix[2][1] * matrix[1][2];

	return determinant;
}

void FindAdditions(const Matrix3x3 matrix, Matrix3x3& adjugateMatrix)
{
	adjugateMatrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]);
	adjugateMatrix[0][1] = ((-1) * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]));
	adjugateMatrix[0][2] = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);

	adjugateMatrix[1][0] = ((-1) * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]));
	adjugateMatrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2]);
	adjugateMatrix[1][2] = ((-1) * (matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]));

	adjugateMatrix[2][0] = (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]);
	adjugateMatrix[2][1] = ((-1) * (matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]));
	adjugateMatrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);
}

bool ReadMatrixFromFile(const std::string& inputFileName, Matrix3x3& matrix)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!(inputFile.is_open()))
	{
		std::cout << "File not found!\n";
		return false;
	}
	std::string row;
	int i = 0;
	while (std::getline(inputFile, row) && i < MATRIX_SIZE)
	{
		int j = 0;
		double number;
		std::stringstream ss(row);
		while (ss >> number)
		{
			matrix[i][j] = number;
			j++;
			if (j == MATRIX_SIZE) {
				break;
			}
		}
		if (j != MATRIX_SIZE)
		{
			std::cout << "Incorrect matrix!\n";
			return false;
		}
		i++;
	}
	if (i != MATRIX_SIZE)
	{
		std::cout << "Incorrect matrix!\n";
		return false;
	}
	return true;
}

bool InvertMatrix(Matrix3x3& matrix)
{
	double determinant = FindDeterminant(matrix);

	if (determinant == 0)
	{
		return false;
	}

	Transpose(matrix);
	Matrix3x3 adjugateMatrix;
	FindAdditions(matrix, adjugateMatrix);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) 
		{
			if (adjugateMatrix[i][j] == -0) 
			{
				adjugateMatrix[i][j] = 0;
			}
			matrix[i][j] = adjugateMatrix[i][j] * (1 / determinant);
		}
	}

	return true;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed);

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{

			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: invert.exe <matrix file>\n";
		return 1;
	}

	std::string fileName = argv[1];

	Matrix3x3 matrix;

	if (!ReadMatrixFromFile(fileName, matrix)) 
	{
		return 1;
	}

	if (!InvertMatrix(matrix)) {
		std::cout << "Matrix cannot be inverted";
		return 1;
	}

	PrintMatrix(matrix);

	return 0;
}