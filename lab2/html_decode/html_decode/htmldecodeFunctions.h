#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

std::string ReplaceEntity(std::string& htmlCode, const std::string& charRepresentation, const std::string& htmlEntity);
std::string HtmlDecode(std::string& htmlCode);