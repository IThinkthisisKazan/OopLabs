#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

const int MATRIX_SIZE = 3;

void Transpose(double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
	int tmp;
	for (int i = 0; i < MATRIX_SIZE; i++)
		for (int j = i; j < MATRIX_SIZE; j++)
		{
			tmp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tmp;
		}
}

double FindDeterminant(const double matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	double determinant;
	determinant = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[1][0] * matrix[0][2] * matrix[2][1]
		+ matrix[2][0] * matrix[0][1] * matrix[1][2]
		- matrix[2][0] * matrix[1][1] * matrix[0][2]
		- matrix[1][0] * matrix[0][1] * matrix[2][2]
		- matrix[0][0] * matrix[2][1] * matrix[1][2];
	return determinant;
}

void FindAdditions(double matrix[MATRIX_SIZE][MATRIX_SIZE], double additionsMatrix[MATRIX_SIZE][MATRIX_SIZE], double determinant)
{
	additionsMatrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) * determinant;
	additionsMatrix[0][1] = ((-1) * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2])) * determinant;
	additionsMatrix[0][2] = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) * determinant;

	additionsMatrix[1][0] = ((-1) * (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2])) * determinant;
	additionsMatrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2]) * determinant;
	additionsMatrix[1][2] = ((-1) * (matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1])) * determinant;

	additionsMatrix[2][0] = (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2])* determinant;
	additionsMatrix[2][1] = ((-1) * (matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2])) * determinant;
	additionsMatrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * determinant;
}

bool ReadMatrixFromFile(const std::string& inputFileName, double matrix[MATRIX_SIZE][MATRIX_SIZE])
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
			j = j + 1;
		}
		if (j != MATRIX_SIZE)
		{
			std::cout << "Incorrect matrix!\n";
			return false;
		}
		i = i + 1;
	}
	if (i != MATRIX_SIZE)
	{
		std::cout << "Incorrect matrix!\n";
		return false;
	}
	return true;
}

bool InvertMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	double determinant = 0;
	determinant = FindDeterminant(matrix);
	if (determinant == 0)
	{
		std::cout << "Determinant is 0. This matrix cannot be inverted \n";
		return true;
	}
	Transpose(matrix);
	double additionMatrix[MATRIX_SIZE][MATRIX_SIZE];
	FindAdditions(matrix, additionMatrix,  1 / determinant);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j) {
			matrix[i][j] = additionMatrix[i][j];
		}
	}
	return true;
}

void PrintMatrix(const double matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (j < 2)
			{
				std::cout << std::setprecision(3) << matrix[i][j] << "\t";
			}
			else
			{
				std::cout << std::setprecision(3) << matrix[i][j] << '\n';
			}
		}
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

	double Matrix[MATRIX_SIZE][MATRIX_SIZE];

	if (!ReadMatrixFromFile(fileName, Matrix)) 
	{
		return 1;
	}

	InvertMatrix(Matrix);

	PrintMatrix(Matrix);

	return 0;
}