#pragma once
#include "stdafx.h"

std::vector<double> ReadVector(std::istream& input);
void ProcessVector(std::vector<double>& numbers);
void PrintVector(std::ostream& output, const std::vector<double>& numbers);