#pragma once

#include <string>

struct Car
{
	int id;
	double capacity;
	Car(int id, double capacity);
	std::string toString() const;
};