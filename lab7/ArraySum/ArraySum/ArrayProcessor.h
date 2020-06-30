#pragma once
#include <numeric>
#include <string>
#include <vector>

template <typename T>
T ArraySum(std::vector<T> const& arr);

template <typename T>
T ArraySum(std::vector<T> const& arr)
{
	if (arr.empty())
	{
		return T();
	}
	T sum = arr[0];
	for (size_t i = 1; i < arr.size(); i++)
	{
		sum += arr[i];
	}
	return sum;
}