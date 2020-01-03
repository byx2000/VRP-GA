#pragma once

#include <string>

struct Car
{
	int id;
	double capacity;
	double disLimit;

	Car(int id, double capacity, double disLimit);
	std::string toString() const;
};