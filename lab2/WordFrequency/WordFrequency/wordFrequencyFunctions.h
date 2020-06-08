#pragma once
#include <iostream>
#include <map>
#include <string>


typedef std::map<std::string, int> Frequency;

Frequency CalcFrequency(std::istream& input);