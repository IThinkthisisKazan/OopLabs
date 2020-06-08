#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

std::string FindAndReplace(std::string& htmlCode, const std::string& charRepresentation, const std::string& htmlEntity);
std::string HtmlDecode(const std::string& htmlCode);