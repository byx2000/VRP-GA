#pragma once

#include <vector>
#include <string>

struct Result
{
	std::vector<std::vector<int>> path;
	std::vector<double> load;
	std::vector<double> mileage;
	int numGeneration;
	std::string toString() const;

	double totalTime() const;
	double totalMileage() const;
	int totalCarUse() const;
};