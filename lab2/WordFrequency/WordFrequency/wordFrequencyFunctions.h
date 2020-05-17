#pragma once
#include <iostream>
#include <map>
#include <string>
#include <locale.h> 


typedef std::map<std::string, int> Frequency;

Frequency CalcFrequency(std::istream& input);